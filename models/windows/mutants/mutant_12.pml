mtype = {blue, white, red}
chan source = [0] of {mtype};
chan q[2] = [3] of {mtype, byte, byte};
mtype rcvd = white;
mtype sent = white;

active [2] proctype p5(){
	byte NextFrame, AckExp, FrameExp, r, s, nbuf, i;
	chan in, out;
	mtype ball;
	byte frames[4];
	d_step {
		in = q[_pid];
		out = q[1 - _pid];
	};
	do
	::	atomic {
			nbuf < 3;
			nbuf++;
			if
			::	_pid / 2;
				source?ball;
			::	else ->
			fi;
			frames[NextFrame] = ball;
			out!ball, NextFrame, (FrameExp + 3) % (3 + 1);
			if
			::	_pid % 2;
				sent = ball;
			::	else ->
			fi;
			NextFrame = (NextFrame + 1) % (3 + 1);
		};
	::	atomic {
			in?ball, r, s;
			if
			::	r == FrameExp;
				if
				::	_pid % 2;
				::	else ->
					rcvd = ball;
				fi;
				FrameExp = (FrameExp + 1) % (3 + 1);
			::	else ->
			fi;
		};
		d_step {
			do
			::	((AckExp <= s) && (s < NextFrame)) || ((AckExp <= s) && (NextFrame < AckExp)) || ((s < NextFrame) && (NextFrame < AckExp));
				nbuf--;
				AckExp = (AckExp + 1) % (3 + 1);
			::	else ->
				break;
			od;
			skip;
		};
	::	timeout;
		d_step {
			NextFrame = AckExp;
			i = 1;
			do
			::	i <= nbuf;
				if
				::	_pid % 2;
					ball = frames[NextFrame];
				::	else ->
				fi;
				out!ball, NextFrame, (FrameExp + 3) % (3 + 1);
				NextFrame = (NextFrame + 1) % (3 + 1);
				i++;
			::	else ->
				break;
			od;
			i = 0;
		};
	od;
};

active proctype Source(){
	do
	::	source!white;
	::	source!red;
		break;
	od;
	do
	::	source!white;
	::	source!blue;
		break;
	od;
	end: 
do
	::	source!white;
	od;
};
