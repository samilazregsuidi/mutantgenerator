#define rand	pan_rand
#define pthread_equal(a,b)	((a)==(b))
#if defined(HAS_CODE) && defined(VERBOSE)
	#ifdef BFS_PAR
		bfs_printf("Pr: %d Tr: %d\n", II, t->forw);
	#else
		cpu_printf("Pr: %d Tr: %d\n", II, t->forw);
	#endif
#endif
	switch (t->forw) {
	default: Uerror("bad forward move");
	case 0:	/* if without executable clauses */
		continue;
	case 1: /* generic 'goto' or 'skip' */
		IfNotBlocked
		_m = 3; goto P999;
	case 2: /* generic 'else' */
		IfNotBlocked
		if (trpt->o_pm&1) continue;
		_m = 3; goto P999;

		 /* CLAIM never_0 */
	case 3: // STATE 1 - original.pml.nvr:5 - [((rcvd==blue))] (6:0:0 - 1)
		
#if defined(VERI) && !defined(NP)
#if NCLAIMS>1
		{	static int reported1 = 0;
			if (verbose && !reported1)
			{	int nn = (int) ((Pclaim *)pptr(0))->_n;
				printf("depth %ld: Claim %s (%d), state %d (line %d)\n",
					depth, procname[spin_c_typ[nn]], nn, (int) ((Pclaim *)pptr(0))->_p, src_claim[ (int) ((Pclaim *)pptr(0))->_p ]);
				reported1 = 1;
				fflush(stdout);
		}	}
#else
		{	static int reported1 = 0;
			if (verbose && !reported1)
			{	printf("depth %d: Claim, state %d (line %d)\n",
					(int) depth, (int) ((Pclaim *)pptr(0))->_p, src_claim[ (int) ((Pclaim *)pptr(0))->_p ]);
				reported1 = 1;
				fflush(stdout);
		}	}
#endif
#endif
		reached[2][1] = 1;
		if (!((now.rcvd==3)))
			continue;
		/* merge: assert(!((rcvd==blue)))(0, 2, 6) */
		reached[2][2] = 1;
		spin_assert( !((now.rcvd==3)), " !((rcvd==3))", II, tt, t);
		/* merge: .(goto)(0, 7, 6) */
		reached[2][7] = 1;
		;
		_m = 3; goto P999; /* 2 */
	case 4: // STATE 4 - original.pml.nvr:6 - [(!((rcvd==red)))] (0:0:0 - 1)
		
#if defined(VERI) && !defined(NP)
#if NCLAIMS>1
		{	static int reported4 = 0;
			if (verbose && !reported4)
			{	int nn = (int) ((Pclaim *)pptr(0))->_n;
				printf("depth %ld: Claim %s (%d), state %d (line %d)\n",
					depth, procname[spin_c_typ[nn]], nn, (int) ((Pclaim *)pptr(0))->_p, src_claim[ (int) ((Pclaim *)pptr(0))->_p ]);
				reported4 = 1;
				fflush(stdout);
		}	}
#else
		{	static int reported4 = 0;
			if (verbose && !reported4)
			{	printf("depth %d: Claim, state %d (line %d)\n",
					(int) depth, (int) ((Pclaim *)pptr(0))->_p, src_claim[ (int) ((Pclaim *)pptr(0))->_p ]);
				reported4 = 1;
				fflush(stdout);
		}	}
#endif
#endif
		reached[2][4] = 1;
		if (!( !((now.rcvd==1))))
			continue;
		_m = 3; goto P999; /* 0 */
	case 5: // STATE 10 - original.pml.nvr:10 - [-end-] (0:0:0 - 1)
		
#if defined(VERI) && !defined(NP)
#if NCLAIMS>1
		{	static int reported10 = 0;
			if (verbose && !reported10)
			{	int nn = (int) ((Pclaim *)pptr(0))->_n;
				printf("depth %ld: Claim %s (%d), state %d (line %d)\n",
					depth, procname[spin_c_typ[nn]], nn, (int) ((Pclaim *)pptr(0))->_p, src_claim[ (int) ((Pclaim *)pptr(0))->_p ]);
				reported10 = 1;
				fflush(stdout);
		}	}
#else
		{	static int reported10 = 0;
			if (verbose && !reported10)
			{	printf("depth %d: Claim, state %d (line %d)\n",
					(int) depth, (int) ((Pclaim *)pptr(0))->_p, src_claim[ (int) ((Pclaim *)pptr(0))->_p ]);
				reported10 = 1;
				fflush(stdout);
		}	}
#endif
#endif
		reached[2][10] = 1;
		if (!delproc(1, II)) continue;
		_m = 3; goto P999; /* 0 */

		 /* PROC Source */
	case 6: // STATE 1 - original.pml:81 - [source!white] (0:0:0 - 1)
		IfNotBlocked
		reached[1][1] = 1;
		if (q_full(now.source))
			continue;
#ifdef HAS_CODE
		if (readtrail && gui) {
			char simtmp[64];
			sprintf(simvals, "%d!", now.source);
		sprintf(simtmp, "%d", 2); strcat(simvals, simtmp);		}
#endif
		
		qsend(now.source, 0, 2, 0, 0, 1);
		if (q_zero(now.source)) { boq = now.source; };
		_m = 2; goto P999; /* 0 */
	case 7: // STATE 2 - original.pml:82 - [source!red] (0:0:0 - 1)
		IfNotBlocked
		reached[1][2] = 1;
		if (q_full(now.source))
			continue;
#ifdef HAS_CODE
		if (readtrail && gui) {
			char simtmp[64];
			sprintf(simvals, "%d!", now.source);
		sprintf(simtmp, "%d", 1); strcat(simvals, simtmp);		}
#endif
		
		qsend(now.source, 0, 1, 0, 0, 1);
		if (q_zero(now.source)) { boq = now.source; };
		_m = 2; goto P999; /* 0 */
	case 8: // STATE 7 - original.pml:86 - [source!white] (0:0:0 - 1)
		IfNotBlocked
		reached[1][7] = 1;
		if (q_full(now.source))
			continue;
#ifdef HAS_CODE
		if (readtrail && gui) {
			char simtmp[64];
			sprintf(simvals, "%d!", now.source);
		sprintf(simtmp, "%d", 2); strcat(simvals, simtmp);		}
#endif
		
		qsend(now.source, 0, 2, 0, 0, 1);
		if (q_zero(now.source)) { boq = now.source; };
		_m = 2; goto P999; /* 0 */
	case 9: // STATE 8 - original.pml:87 - [source!blue] (0:0:0 - 1)
		IfNotBlocked
		reached[1][8] = 1;
		if (q_full(now.source))
			continue;
#ifdef HAS_CODE
		if (readtrail && gui) {
			char simtmp[64];
			sprintf(simvals, "%d!", now.source);
		sprintf(simtmp, "%d", 3); strcat(simvals, simtmp);		}
#endif
		
		qsend(now.source, 0, 3, 0, 0, 1);
		if (q_zero(now.source)) { boq = now.source; };
		_m = 2; goto P999; /* 0 */
	case 10: // STATE 13 - original.pml:92 - [source!white] (0:0:0 - 1)
		IfNotBlocked
		reached[1][13] = 1;
		if (q_full(now.source))
			continue;
#ifdef HAS_CODE
		if (readtrail && gui) {
			char simtmp[64];
			sprintf(simvals, "%d!", now.source);
		sprintf(simtmp, "%d", 2); strcat(simvals, simtmp);		}
#endif
		
		qsend(now.source, 0, 2, 0, 0, 1);
		if (q_zero(now.source)) { boq = now.source; };
		_m = 2; goto P999; /* 0 */
	case 11: // STATE 17 - original.pml:94 - [-end-] (0:0:0 - 1)
		IfNotBlocked
		reached[1][17] = 1;
		if (!delproc(1, II)) continue;
		_m = 3; goto P999; /* 0 */

		 /* PROC p5 */
	case 12: // STATE 3 - original.pml:12 - [D_STEP12]
		IfNotBlocked

		reached[0][3] = 1;
		reached[0][t->st] = 1;
		reached[0][tt] = 1;

		if (TstOnly) return 1;

		sv_save();
		S_000_0: /* 2 */
		((P0 *)_this)->in = now.q[ Index(((int)((P0 *)_this)->_pid), 2) ];
S_001_0: /* 2 */
		((P0 *)_this)->out = now.q[ Index((1-((int)((P0 *)_this)->_pid)), 2) ];
		goto S_061_0;
S_061_0: /* 1 */

#if defined(C_States) && (HAS_TRACK==1)
		c_update((uchar *) &(now.c_state[0]));
#endif
		_m = 3; goto P999;

	case 13: // STATE 4 - original.pml:18 - [((nbuf<3))] (9:0:1 - 1)
		IfNotBlocked
		reached[0][4] = 1;
		if (!((((int)((P0 *)_this)->nbuf)<3)))
			continue;
		/* merge: nbuf = (nbuf+1)(0, 5, 9) */
		reached[0][5] = 1;
		(trpt+1)->bup.oval = ((int)((P0 *)_this)->nbuf);
		((P0 *)_this)->nbuf = (((int)((P0 *)_this)->nbuf)+1);
#ifdef VAR_RANGES
		logval("p5:nbuf", ((int)((P0 *)_this)->nbuf));
#endif
		;
		_m = 3; goto P999; /* 1 */
	case 14: // STATE 6 - original.pml:21 - [((_pid%2))] (0:0:0 - 1)
		IfNotBlocked
		reached[0][6] = 1;
		if (!((((int)((P0 *)_this)->_pid)%2)))
			continue;
		_m = 3; goto P999; /* 0 */
	case 15: // STATE 7 - original.pml:22 - [source?ball] (12:0:2 - 1)
		reached[0][7] = 1;
		if (q_zero(now.source))
		{	if (boq != now.source) continue;
		} else
		{	if (boq != -1) continue;
		}
		if (q_len(now.source) == 0) continue;

		XX=1;
		(trpt+1)->bup.ovals = grab_ints(2);
		(trpt+1)->bup.ovals[0] = ((P0 *)_this)->ball;
		;
		((P0 *)_this)->ball = qrecv(now.source, XX-1, 0, 1);
#ifdef VAR_RANGES
		logval("p5:ball", ((P0 *)_this)->ball);
#endif
		;
		
#ifdef HAS_CODE
		if (readtrail && gui) {
			char simtmp[32];
			sprintf(simvals, "%d?", now.source);
		sprintf(simtmp, "%d", ((P0 *)_this)->ball); strcat(simvals, simtmp);		}
#endif
		if (q_zero(now.source))
		{	boq = -1;
#ifndef NOFAIR
			if (fairness
			&& !(trpt->o_pm&32)
			&& (now._a_t&2)
			&&  now._cnt[now._a_t&1] == II+2)
			{	now._cnt[now._a_t&1] -= 1;
#ifdef VERI
				if (II == 1)
					now._cnt[now._a_t&1] = 1;
#endif
#ifdef DEBUG
			printf("%3ld: proc %d fairness ", depth, II);
			printf("Rule 2: --cnt to %d (%d)\n",
				now._cnt[now._a_t&1], now._a_t);
#endif
				trpt->o_pm |= (32|64);
			}
#endif

		};
		/* merge: .(goto)(12, 10, 12) */
		reached[0][10] = 1;
		;
		/* merge: frames[NextFrame] = ball(12, 11, 12) */
		reached[0][11] = 1;
		(trpt+1)->bup.ovals[1] = ((int)((P0 *)_this)->frames[ Index(((int)((P0 *)_this)->NextFrame), 4) ]);
		((P0 *)_this)->frames[ Index(((P0 *)_this)->NextFrame, 4) ] = ((P0 *)_this)->ball;
#ifdef VAR_RANGES
		logval("p5:frames[p5:NextFrame]", ((int)((P0 *)_this)->frames[ Index(((int)((P0 *)_this)->NextFrame), 4) ]));
#endif
		;
		_m = 4; goto P999; /* 2 */
	case 16: // STATE 11 - original.pml:25 - [frames[NextFrame] = ball] (0:12:1 - 3)
		IfNotBlocked
		reached[0][11] = 1;
		(trpt+1)->bup.oval = ((int)((P0 *)_this)->frames[ Index(((int)((P0 *)_this)->NextFrame), 4) ]);
		((P0 *)_this)->frames[ Index(((P0 *)_this)->NextFrame, 4) ] = ((P0 *)_this)->ball;
#ifdef VAR_RANGES
		logval("p5:frames[p5:NextFrame]", ((int)((P0 *)_this)->frames[ Index(((int)((P0 *)_this)->NextFrame), 4) ]));
#endif
		;
		_m = 3; goto P999; /* 0 */
	case 17: // STATE 12 - original.pml:26 - [out!ball,NextFrame,((FrameExp+3)%(3+1))] (0:0:0 - 1)
		IfNotBlocked
		reached[0][12] = 1;
		if (q_full(((P0 *)_this)->out))
			continue;
#ifdef HAS_CODE
		if (readtrail && gui) {
			char simtmp[64];
			sprintf(simvals, "%d!", ((P0 *)_this)->out);
		sprintf(simtmp, "%d", ((P0 *)_this)->ball); strcat(simvals, simtmp);		strcat(simvals, ",");
		sprintf(simtmp, "%d", ((int)((P0 *)_this)->NextFrame)); strcat(simvals, simtmp);		strcat(simvals, ",");
		sprintf(simtmp, "%d", ((((int)((P0 *)_this)->FrameExp)+3)%(3+1))); strcat(simvals, simtmp);		}
#endif
		
		qsend(((P0 *)_this)->out, 0, ((P0 *)_this)->ball, ((int)((P0 *)_this)->NextFrame), ((((int)((P0 *)_this)->FrameExp)+3)%(3+1)), 3);
		if (q_zero(((P0 *)_this)->out)) { boq = ((P0 *)_this)->out; };
		_m = 2; goto P999; /* 0 */
	case 18: // STATE 13 - original.pml:28 - [((_pid%2))] (61:0:2 - 1)
		IfNotBlocked
		reached[0][13] = 1;
		if (!((((int)((P0 *)_this)->_pid)%2)))
			continue;
		/* merge: sent = ball(61, 14, 61) */
		reached[0][14] = 1;
		(trpt+1)->bup.ovals = grab_ints(2);
		(trpt+1)->bup.ovals[0] = sent;
		sent = ((P0 *)_this)->ball;
#ifdef VAR_RANGES
		logval("sent", sent);
#endif
		;
		/* merge: .(goto)(61, 17, 61) */
		reached[0][17] = 1;
		;
		/* merge: NextFrame = ((NextFrame+1)%(3+1))(61, 18, 61) */
		reached[0][18] = 1;
		(trpt+1)->bup.ovals[1] = ((int)((P0 *)_this)->NextFrame);
		((P0 *)_this)->NextFrame = ((((int)((P0 *)_this)->NextFrame)+1)%(3+1));
#ifdef VAR_RANGES
		logval("p5:NextFrame", ((int)((P0 *)_this)->NextFrame));
#endif
		;
		/* merge: .(goto)(0, 62, 61) */
		reached[0][62] = 1;
		;
		_m = 3; goto P999; /* 4 */
	case 19: // STATE 17 - original.pml:32 - [.(goto)] (0:61:1 - 2)
		IfNotBlocked
		reached[0][17] = 1;
		;
		/* merge: NextFrame = ((NextFrame+1)%(3+1))(61, 18, 61) */
		reached[0][18] = 1;
		(trpt+1)->bup.oval = ((int)((P0 *)_this)->NextFrame);
		((P0 *)_this)->NextFrame = ((((int)((P0 *)_this)->NextFrame)+1)%(3+1));
#ifdef VAR_RANGES
		logval("p5:NextFrame", ((int)((P0 *)_this)->NextFrame));
#endif
		;
		/* merge: .(goto)(0, 62, 61) */
		reached[0][62] = 1;
		;
		_m = 3; goto P999; /* 2 */
	case 20: // STATE 20 - original.pml:35 - [in?ball,r,s] (0:0:3 - 1)
		reached[0][20] = 1;
		if (q_zero(((P0 *)_this)->in))
		{	if (boq != ((P0 *)_this)->in) continue;
		} else
		{	if (boq != -1) continue;
		}
		if (q_len(((P0 *)_this)->in) == 0) continue;

		XX=1;
		(trpt+1)->bup.ovals = grab_ints(3);
		(trpt+1)->bup.ovals[0] = ((P0 *)_this)->ball;
		(trpt+1)->bup.ovals[1] = ((int)((P0 *)_this)->r);
		(trpt+1)->bup.ovals[2] = ((int)((P0 *)_this)->s);
		;
		((P0 *)_this)->ball = qrecv(((P0 *)_this)->in, XX-1, 0, 0);
#ifdef VAR_RANGES
		logval("p5:ball", ((P0 *)_this)->ball);
#endif
		;
		((P0 *)_this)->r = qrecv(((P0 *)_this)->in, XX-1, 1, 0);
#ifdef VAR_RANGES
		logval("p5:r", ((int)((P0 *)_this)->r));
#endif
		;
		((P0 *)_this)->s = qrecv(((P0 *)_this)->in, XX-1, 2, 1);
#ifdef VAR_RANGES
		logval("p5:s", ((int)((P0 *)_this)->s));
#endif
		;
		
#ifdef HAS_CODE
		if (readtrail && gui) {
			char simtmp[32];
			sprintf(simvals, "%d?", ((P0 *)_this)->in);
		sprintf(simtmp, "%d", ((P0 *)_this)->ball); strcat(simvals, simtmp);		strcat(simvals, ",");
		sprintf(simtmp, "%d", ((int)((P0 *)_this)->r)); strcat(simvals, simtmp);		strcat(simvals, ",");
		sprintf(simtmp, "%d", ((int)((P0 *)_this)->s)); strcat(simvals, simtmp);		}
#endif
		if (q_zero(((P0 *)_this)->in))
		{	boq = -1;
#ifndef NOFAIR
			if (fairness
			&& !(trpt->o_pm&32)
			&& (now._a_t&2)
			&&  now._cnt[now._a_t&1] == II+2)
			{	now._cnt[now._a_t&1] -= 1;
#ifdef VERI
				if (II == 1)
					now._cnt[now._a_t&1] = 1;
#endif
#ifdef DEBUG
			printf("%3ld: proc %d fairness ", depth, II);
			printf("Rule 2: --cnt to %d (%d)\n",
				now._cnt[now._a_t&1], now._a_t);
#endif
				trpt->o_pm |= (32|64);
			}
#endif

		};
		_m = 4; goto P999; /* 0 */
	case 21: // STATE 21 - original.pml:37 - [((r==FrameExp))] (0:0:1 - 1)
		IfNotBlocked
		reached[0][21] = 1;
		if (!((((int)((P0 *)_this)->r)==((int)((P0 *)_this)->FrameExp))))
			continue;
		if (TstOnly) return 1; /* TT */
		/* dead 1: r */  (trpt+1)->bup.oval = ((P0 *)_this)->r;
#ifdef HAS_CODE
		if (!readtrail)
#endif
			((P0 *)_this)->r = 0;
		_m = 3; goto P999; /* 0 */
	case 22: // STATE 22 - original.pml:39 - [((_pid%2))] (41:0:1 - 1)
		IfNotBlocked
		reached[0][22] = 1;
		if (!((((int)((P0 *)_this)->_pid)%2)))
			continue;
		/* merge: .(goto)(41, 26, 41) */
		reached[0][26] = 1;
		;
		/* merge: FrameExp = ((FrameExp+1)%(3+1))(41, 27, 41) */
		reached[0][27] = 1;
		(trpt+1)->bup.oval = ((int)((P0 *)_this)->FrameExp);
		((P0 *)_this)->FrameExp = ((((int)((P0 *)_this)->FrameExp)+1)%(3+1));
#ifdef VAR_RANGES
		logval("p5:FrameExp", ((int)((P0 *)_this)->FrameExp));
#endif
		;
		/* merge: .(goto)(41, 30, 41) */
		reached[0][30] = 1;
		;
		_m = 3; goto P999; /* 3 */
	case 23: // STATE 24 - original.pml:41 - [rcvd = ball] (0:41:2 - 1)
		IfNotBlocked
		reached[0][24] = 1;
		(trpt+1)->bup.ovals = grab_ints(2);
		(trpt+1)->bup.ovals[0] = now.rcvd;
		now.rcvd = ((P0 *)_this)->ball;
#ifdef VAR_RANGES
		logval("rcvd", now.rcvd);
#endif
		;
		/* merge: .(goto)(41, 26, 41) */
		reached[0][26] = 1;
		;
		/* merge: FrameExp = ((FrameExp+1)%(3+1))(41, 27, 41) */
		reached[0][27] = 1;
		(trpt+1)->bup.ovals[1] = ((int)((P0 *)_this)->FrameExp);
		((P0 *)_this)->FrameExp = ((((int)((P0 *)_this)->FrameExp)+1)%(3+1));
#ifdef VAR_RANGES
		logval("p5:FrameExp", ((int)((P0 *)_this)->FrameExp));
#endif
		;
		/* merge: .(goto)(41, 30, 41) */
		reached[0][30] = 1;
		;
		_m = 3; goto P999; /* 3 */
	case 24: // STATE 27 - original.pml:43 - [FrameExp = ((FrameExp+1)%(3+1))] (0:41:1 - 3)
		IfNotBlocked
		reached[0][27] = 1;
		(trpt+1)->bup.oval = ((int)((P0 *)_this)->FrameExp);
		((P0 *)_this)->FrameExp = ((((int)((P0 *)_this)->FrameExp)+1)%(3+1));
#ifdef VAR_RANGES
		logval("p5:FrameExp", ((int)((P0 *)_this)->FrameExp));
#endif
		;
		/* merge: .(goto)(41, 30, 41) */
		reached[0][30] = 1;
		;
		_m = 3; goto P999; /* 1 */
	case 25: // STATE 30 - original.pml:46 - [.(goto)] (0:41:0 - 2)
		IfNotBlocked
		reached[0][30] = 1;
		;
		_m = 3; goto P999; /* 0 */
	case 26: // STATE 41 - original.pml:47 - [D_STEP47]
		if (!(((boq == -1 && ((((((int)((P0 *)_this)->AckExp)<=((int)((P0 *)_this)->s))&&(((int)((P0 *)_this)->s)<((int)((P0 *)_this)->NextFrame)))||((((int)((P0 *)_this)->AckExp)<=((int)((P0 *)_this)->s))&&(((int)((P0 *)_this)->NextFrame)<((int)((P0 *)_this)->AckExp))))||((((int)((P0 *)_this)->s)<((int)((P0 *)_this)->NextFrame))&&(((int)((P0 *)_this)->NextFrame)<((int)((P0 *)_this)->AckExp)))))) || (boq == -1 /* else */)))
			continue;

		reached[0][41] = 1;
		reached[0][t->st] = 1;
		reached[0][tt] = 1;

		if (TstOnly) return 1;

		sv_save();
		S_037_0: /* 2 */
S_036_0: /* 2 */
S_031_0: /* 2 */
		if (!(((((((int)((P0 *)_this)->AckExp)<=((int)((P0 *)_this)->s))&&(((int)((P0 *)_this)->s)<((int)((P0 *)_this)->NextFrame)))||((((int)((P0 *)_this)->AckExp)<=((int)((P0 *)_this)->s))&&(((int)((P0 *)_this)->NextFrame)<((int)((P0 *)_this)->AckExp))))||((((int)((P0 *)_this)->s)<((int)((P0 *)_this)->NextFrame))&&(((int)((P0 *)_this)->NextFrame)<((int)((P0 *)_this)->AckExp))))))
			goto S_036_1;
S_032_0: /* 2 */
		((P0 *)_this)->nbuf = (((int)((P0 *)_this)->nbuf)-1);
#ifdef VAR_RANGES
		logval("p5:nbuf", ((int)((P0 *)_this)->nbuf));
#endif
		;
S_033_0: /* 2 */
		((P0 *)_this)->AckExp = ((((int)((P0 *)_this)->AckExp)+1)%(3+1));
#ifdef VAR_RANGES
		logval("p5:AckExp", ((int)((P0 *)_this)->AckExp));
#endif
		;
		goto S_037_0; /* ';' */
S_036_1: /* 3 */
S_034_0: /* 2 */
		/* else */;
S_035_0: /* 2 */
		goto S_038_0;	/* 'goto' */
S_036_2: /* 3 */
		Uerror("blocking sel in d_step (nr.0, near line 48)");
S_038_0: /* 2 */
		goto S_039_0;	/* 'break' */
S_039_0: /* 2 */
		if (!(1))
			Uerror("block in d_step seq, line 47");
		goto S_061_0; /* ';' */

#if defined(C_States) && (HAS_TRACK==1)
		c_update((uchar *) &(now.c_state[0]));
#endif
		_m = 3; goto P999;

	case 27: // STATE 42 - original.pml:57 - [(timeout)] (0:0:0 - 1)
		IfNotBlocked
		reached[0][42] = 1;
		if (!(((trpt->tau)&1)))
			continue;
		_m = 1; goto P999; /* 0 */
	case 28: // STATE 60 - original.pml:58 - [D_STEP58]
		IfNotBlocked

		reached[0][60] = 1;
		reached[0][t->st] = 1;
		reached[0][tt] = 1;

		if (TstOnly) return 1;

		sv_save();
		S_042_0: /* 2 */
		((P0 *)_this)->NextFrame = ((int)((P0 *)_this)->AckExp);
#ifdef VAR_RANGES
		logval("p5:NextFrame", ((int)((P0 *)_this)->NextFrame));
#endif
		;
S_043_0: /* 2 */
		((P0 *)_this)->i = 1;
#ifdef VAR_RANGES
		logval("p5:i", ((int)((P0 *)_this)->i));
#endif
		;
S_056_0: /* 2 */
S_055_0: /* 2 */
S_044_0: /* 2 */
		if (!((((int)((P0 *)_this)->i)<=((int)((P0 *)_this)->nbuf))))
			goto S_055_1;
S_048_0: /* 2 */
S_045_0: /* 2 */
		if (!((((int)((P0 *)_this)->_pid)%2)))
			goto S_048_1;
S_046_0: /* 2 */
		((P0 *)_this)->ball = ((int)((P0 *)_this)->frames[ Index(((int)((P0 *)_this)->NextFrame), 4) ]);
#ifdef VAR_RANGES
		logval("p5:ball", ((P0 *)_this)->ball);
#endif
		;
		goto S_049_0;
S_048_1: /* 3 */
S_047_0: /* 2 */
		/* else */;
		goto S_049_0;
S_048_2: /* 3 */
		Uerror("blocking sel in d_step (nr.1, near line 63)");
S_049_0: /* 2 */
S_050_0: /* 2 */
		if (q_full(((P0 *)_this)->out))
			Uerror("block in d_step seq");
#ifdef HAS_CODE
		if (readtrail && gui) {
			char simtmp[64];
			sprintf(simvals, "%d!", ((P0 *)_this)->out);
		sprintf(simtmp, "%d", ((P0 *)_this)->ball); strcat(simvals, simtmp);		strcat(simvals, ",");
		sprintf(simtmp, "%d", ((int)((P0 *)_this)->NextFrame)); strcat(simvals, simtmp);		strcat(simvals, ",");
		sprintf(simtmp, "%d", ((((int)((P0 *)_this)->FrameExp)+3)%(3+1))); strcat(simvals, simtmp);		}
#endif
		
		qsend(((P0 *)_this)->out, 0, ((P0 *)_this)->ball, ((int)((P0 *)_this)->NextFrame), ((((int)((P0 *)_this)->FrameExp)+3)%(3+1)), 3);
		if (q_zero(((P0 *)_this)->out)) { boq = ((P0 *)_this)->out; Uerror("rv-attempt in d_step"); };
S_051_0: /* 2 */
		((P0 *)_this)->NextFrame = ((((int)((P0 *)_this)->NextFrame)+1)%(3+1));
#ifdef VAR_RANGES
		logval("p5:NextFrame", ((int)((P0 *)_this)->NextFrame));
#endif
		;
S_052_0: /* 2 */
		((P0 *)_this)->i = (((int)((P0 *)_this)->i)+1);
#ifdef VAR_RANGES
		logval("p5:i", ((int)((P0 *)_this)->i));
#endif
		;
		goto S_056_0; /* ';' */
S_055_1: /* 3 */
S_053_0: /* 2 */
		/* else */;
S_054_0: /* 2 */
		goto S_057_0;	/* 'goto' */
S_055_2: /* 3 */
		Uerror("blocking sel in d_step (nr.2, near line 61)");
S_057_0: /* 2 */
		goto S_058_0;	/* 'break' */
S_058_0: /* 2 */
		((P0 *)_this)->i = 0;
#ifdef VAR_RANGES
		logval("p5:i", ((int)((P0 *)_this)->i));
#endif
		;
		goto S_061_0; /* ';' */

#if defined(C_States) && (HAS_TRACK==1)
		c_update((uchar *) &(now.c_state[0]));
#endif
		_m = 3; goto P999;

	case 29: // STATE 64 - original.pml:77 - [-end-] (0:0:0 - 1)
		IfNotBlocked
		reached[0][64] = 1;
		if (!delproc(1, II)) continue;
		_m = 3; goto P999; /* 0 */
	case  _T5:	/* np_ */
		if (!((!(trpt->o_pm&4) && !(trpt->tau&128))))
			continue;
		/* else fall through */
	case  _T2:	/* true */
		_m = 3; goto P999;
#undef rand
	}

