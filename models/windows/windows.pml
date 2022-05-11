#define MaxSeq	3		/* file: ex.9c */
#define MaxSeq_plus_1	4
#define inc(x)	x = (x + 1) % (MaxSeq + 1)
 
#define CHECKIT

#ifdef CHECKIT
mtype = { red, white, blue };	/* Wolper's test */
chan source = [0] of { mtype };
chan q[2] = [MaxSeq] of { mtype, byte, byte };
mtype rcvd = white;
mtype sent = white;
#else
chan q[2] = [MaxSeq] of { byte, byte };
#endif

active [2] proctype p5()
{	byte	NextFrame, AckExp, FrameExp,
	r, s, nbuf, i;
	chan in, out;
#ifdef CHECKIT
 	mtype	ball;
 	byte frames[MaxSeq_plus_1];
#endif

	d_step {
		in = q[_pid];
		out = q[1-_pid]
 	};

	do
 	:: atomic {
		nbuf < MaxSeq ->
		nbuf++;
#ifdef CHECKIT
		if
 		:: _pid%2 -> source?ball
 		:: else
 		fi;
		frames[NextFrame] = ball;
		out!ball, NextFrame , (FrameExp + MaxSeq) % (MaxSeq + 1);
		if
		:: _pid%2 -> sent = ball;
		:: else
		fi;
#else
 		out!NextFrame , (FrameExp + MaxSeq) % (MaxSeq + 1);
#endif
#ifdef VERBOSE
		printf("MSC: nbuf: %d\n", nbuf);
#endif
		inc(NextFrame)
 	}
#ifdef CHECKIT
 	:: atomic { in?ball,r,s ->
#else
	:: atomic { in?r,s ->
#endif
		if
		:: r == FrameExp ->
#ifdef VERBOSE
			printf("MSC: accept %d\n", r);
#endif
#ifdef CHECKIT
 			if
			:: _pid%2
 			:: else -> rcvd = ball
 			fi;
#endif
			inc(FrameExp)
 		:: else
#ifdef VERBOSE
			-> printf("MSC: reject\n")
#endif
		fi
 	};
	d_step {
	 	do
		:: ((AckExp <= s) && (s <  NextFrame)) || ((AckExp <= s) && (NextFrame <  AckExp)) || ((s <  NextFrame) && (NextFrame <  AckExp)) ->
			nbuf--;
#ifdef VERBOSE
			printf("MSC: nbuf: %d\n", nbuf);
#endif
			inc(AckExp)
		:: else ->
#ifdef VERBOSE
			printf("MSC: %d %d %d\n", AckExp, s, NextFrame);
#endif
			break
		od;
 		skip
	}
	:: timeout ->
	d_step {
		NextFrame = AckExp;
#ifdef VERBOSE
		printf("MSC: timeout\n");
#endif
		i = 1;
		do
		:: i <= nbuf ->
#ifdef CHECKIT
			if
			:: _pid%2 -> ball = frames[NextFrame]
 			:: else
			fi;		
			out!ball, NextFrame , (FrameExp + MaxSeq) % (MaxSeq + 1);
#else
			out!NextFrame , (FrameExp + MaxSeq) % (MaxSeq + 1);
#endif
			inc(NextFrame);
			i++
		:: else ->
			break
		od;
		i = 0
	}
	od
}
#ifdef CHECKIT
active proctype Source()
{
	do
	:: source!white
	:: source!red -> break
 	od;
	do
	:: source!white
	:: source!blue -> break
	od;
end:	do
	:: source!white
	od
}

#define sw	(sent == white)
#define sr	(sent == red)
#define sb	(sent == blue)

#define rw	(rcvd == white)
#define rr	(rcvd == red)
#define rb	(rcvd == blue)


#endif
