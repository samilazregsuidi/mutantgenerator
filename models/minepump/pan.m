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
	case 3: // STATE 1 - original.pml.nvr:6 - [(pumpOn)] (0:0:0 - 1)
		
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
		reached[5][1] = 1;
		if (!(((int)now.pumpOn)))
			continue;
		_m = 3; goto P999; /* 0 */
	case 4: // STATE 6 - original.pml.nvr:8 - [-end-] (0:0:0 - 1)
		
#if defined(VERI) && !defined(NP)
#if NCLAIMS>1
		{	static int reported6 = 0;
			if (verbose && !reported6)
			{	int nn = (int) ((Pclaim *)pptr(0))->_n;
				printf("depth %ld: Claim %s (%d), state %d (line %d)\n",
					depth, procname[spin_c_typ[nn]], nn, (int) ((Pclaim *)pptr(0))->_p, src_claim[ (int) ((Pclaim *)pptr(0))->_p ]);
				reported6 = 1;
				fflush(stdout);
		}	}
#else
		{	static int reported6 = 0;
			if (verbose && !reported6)
			{	printf("depth %d: Claim, state %d (line %d)\n",
					(int) depth, (int) ((Pclaim *)pptr(0))->_p, src_claim[ (int) ((Pclaim *)pptr(0))->_p ]);
				reported6 = 1;
				fflush(stdout);
		}	}
#endif
#endif
		reached[5][6] = 1;
		if (!delproc(1, II)) continue;
		_m = 3; goto P999; /* 0 */

		 /* PROC watersensor */
	case 5: // STATE 1 - original.pml:135 - [((waterLevel==low))] (0:0:0 - 1)
		IfNotBlocked
		reached[4][1] = 1;
		if (!((now.waterLevel==5)))
			continue;
		_m = 3; goto P999; /* 0 */
	case 6: // STATE 2 - original.pml:137 - [waterLevel = low] (0:19:1 - 1)
		IfNotBlocked
		reached[4][2] = 1;
		(trpt+1)->bup.oval = now.waterLevel;
		now.waterLevel = 5;
#ifdef VAR_RANGES
		logval("waterLevel", now.waterLevel);
#endif
		;
		/* merge: .(goto)(19, 5, 19) */
		reached[4][5] = 1;
		;
		/* merge: .(goto)(19, 18, 19) */
		reached[4][18] = 1;
		;
		_m = 3; goto P999; /* 2 */
	case 7: // STATE 3 - original.pml:138 - [waterLevel = medium] (0:19:1 - 1)
		IfNotBlocked
		reached[4][3] = 1;
		(trpt+1)->bup.oval = now.waterLevel;
		now.waterLevel = 3;
#ifdef VAR_RANGES
		logval("waterLevel", now.waterLevel);
#endif
		;
		/* merge: .(goto)(19, 5, 19) */
		reached[4][5] = 1;
		;
		/* merge: .(goto)(19, 18, 19) */
		reached[4][18] = 1;
		;
		_m = 3; goto P999; /* 2 */
	case 8: // STATE 18 - original.pml:152 - [.(goto)] (0:19:0 - 10)
		IfNotBlocked
		reached[4][18] = 1;
		;
		_m = 3; goto P999; /* 0 */
	case 9: // STATE 6 - original.pml:140 - [((waterLevel==medium))] (0:0:0 - 1)
		IfNotBlocked
		reached[4][6] = 1;
		if (!((now.waterLevel==3)))
			continue;
		_m = 3; goto P999; /* 0 */
	case 10: // STATE 7 - original.pml:142 - [waterLevel = low] (0:19:1 - 1)
		IfNotBlocked
		reached[4][7] = 1;
		(trpt+1)->bup.oval = now.waterLevel;
		now.waterLevel = 5;
#ifdef VAR_RANGES
		logval("waterLevel", now.waterLevel);
#endif
		;
		/* merge: .(goto)(19, 11, 19) */
		reached[4][11] = 1;
		;
		/* merge: .(goto)(19, 18, 19) */
		reached[4][18] = 1;
		;
		_m = 3; goto P999; /* 2 */
	case 11: // STATE 8 - original.pml:143 - [waterLevel = medium] (0:19:1 - 1)
		IfNotBlocked
		reached[4][8] = 1;
		(trpt+1)->bup.oval = now.waterLevel;
		now.waterLevel = 3;
#ifdef VAR_RANGES
		logval("waterLevel", now.waterLevel);
#endif
		;
		/* merge: .(goto)(19, 11, 19) */
		reached[4][11] = 1;
		;
		/* merge: .(goto)(19, 18, 19) */
		reached[4][18] = 1;
		;
		_m = 3; goto P999; /* 2 */
	case 12: // STATE 9 - original.pml:144 - [waterLevel = high] (0:19:1 - 1)
		IfNotBlocked
		reached[4][9] = 1;
		(trpt+1)->bup.oval = now.waterLevel;
		now.waterLevel = 6;
#ifdef VAR_RANGES
		logval("waterLevel", now.waterLevel);
#endif
		;
		/* merge: .(goto)(19, 11, 19) */
		reached[4][11] = 1;
		;
		/* merge: .(goto)(19, 18, 19) */
		reached[4][18] = 1;
		;
		_m = 3; goto P999; /* 2 */
	case 13: // STATE 12 - original.pml:146 - [((waterLevel==high))] (0:0:0 - 1)
		IfNotBlocked
		reached[4][12] = 1;
		if (!((now.waterLevel==6)))
			continue;
		_m = 3; goto P999; /* 0 */
	case 14: // STATE 13 - original.pml:148 - [waterLevel = medium] (0:19:1 - 1)
		IfNotBlocked
		reached[4][13] = 1;
		(trpt+1)->bup.oval = now.waterLevel;
		now.waterLevel = 3;
#ifdef VAR_RANGES
		logval("waterLevel", now.waterLevel);
#endif
		;
		/* merge: .(goto)(19, 16, 19) */
		reached[4][16] = 1;
		;
		/* merge: .(goto)(19, 18, 19) */
		reached[4][18] = 1;
		;
		_m = 3; goto P999; /* 2 */
	case 15: // STATE 14 - original.pml:149 - [waterLevel = high] (0:19:1 - 1)
		IfNotBlocked
		reached[4][14] = 1;
		(trpt+1)->bup.oval = now.waterLevel;
		now.waterLevel = 6;
#ifdef VAR_RANGES
		logval("waterLevel", now.waterLevel);
#endif
		;
		/* merge: .(goto)(19, 16, 19) */
		reached[4][16] = 1;
		;
		/* merge: .(goto)(19, 18, 19) */
		reached[4][18] = 1;
		;
		_m = 3; goto P999; /* 2 */
	case 16: // STATE 19 - original.pml:152 - [cLevel!waterLevel] (0:0:0 - 1)
		IfNotBlocked
		reached[4][19] = 1;
		if (q_len(now.cLevel))
			continue;
#ifdef HAS_CODE
		if (readtrail && gui) {
			char simtmp[64];
			sprintf(simvals, "%d!", now.cLevel);
		sprintf(simtmp, "%d", now.waterLevel); strcat(simvals, simtmp);		}
#endif
		
		qsend(now.cLevel, 0, now.waterLevel, 1);
		{ boq = now.cLevel; };
		_m = 2; goto P999; /* 0 */
	case 17: // STATE 24 - original.pml:155 - [-end-] (0:0:0 - 1)
		IfNotBlocked
		reached[4][24] = 1;
		if (!delproc(1, II)) continue;
		_m = 3; goto P999; /* 0 */

		 /* PROC user */
	case 18: // STATE 1 - original.pml:123 - [uwants = start] (0:0:1 - 1)
		IfNotBlocked
		reached[3][1] = 1;
		(trpt+1)->bup.oval = now.uwants;
		now.uwants = 8;
#ifdef VAR_RANGES
		logval("uwants", now.uwants);
#endif
		;
		_m = 3; goto P999; /* 0 */
	case 19: // STATE 2 - original.pml:124 - [uwants = stop] (0:0:1 - 1)
		IfNotBlocked
		reached[3][2] = 1;
		(trpt+1)->bup.oval = now.uwants;
		now.uwants = 13;
#ifdef VAR_RANGES
		logval("uwants", now.uwants);
#endif
		;
		_m = 3; goto P999; /* 0 */
	case 20: // STATE 5 - original.pml:126 - [cCmd!uwants] (0:0:0 - 3)
		IfNotBlocked
		reached[3][5] = 1;
		if (q_len(now.cCmd))
			continue;
#ifdef HAS_CODE
		if (readtrail && gui) {
			char simtmp[64];
			sprintf(simvals, "%d!", now.cCmd);
		sprintf(simtmp, "%d", now.uwants); strcat(simvals, simtmp);		}
#endif
		
		qsend(now.cCmd, 0, now.uwants, 1);
		{ boq = now.cCmd; };
		_m = 2; goto P999; /* 0 */
	case 21: // STATE 6 - original.pml:127 - [cCmd?_] (0:0:1 - 1)
		reached[3][6] = 1;
		if (boq != now.cCmd) continue;
		if (q_len(now.cCmd) == 0) continue;

		XX=1;
		(trpt+1)->bup.oval = qrecv(now.cCmd, XX-1, 0, 0);
		;
		qrecv(now.cCmd, XX-1, 0, 1);
		
#ifdef HAS_CODE
		if (readtrail && gui) {
			char simtmp[32];
			sprintf(simvals, "%d?", now.cCmd);
		sprintf(simtmp, "%d", ((int)_)); strcat(simvals, simtmp);		}
#endif
		if (q_zero(now.cCmd))
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
	case 22: // STATE 10 - original.pml:129 - [-end-] (0:0:0 - 1)
		IfNotBlocked
		reached[3][10] = 1;
		if (!delproc(1, II)) continue;
		_m = 3; goto P999; /* 0 */

		 /* PROC methanesensor */
	case 23: // STATE 1 - original.pml:109 - [cMethane?_] (0:0:1 - 1)
		reached[2][1] = 1;
		if (boq != now.cMethane) continue;
		if (q_len(now.cMethane) == 0) continue;

		XX=1;
		(trpt+1)->bup.oval = qrecv(now.cMethane, XX-1, 0, 0);
		;
		qrecv(now.cMethane, XX-1, 0, 1);
		
#ifdef HAS_CODE
		if (readtrail && gui) {
			char simtmp[32];
			sprintf(simvals, "%d?", now.cMethane);
		sprintf(simtmp, "%d", ((int)_)); strcat(simvals, simtmp);		}
#endif
		if (q_zero(now.cMethane))
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
	case 24: // STATE 2 - original.pml:111 - [(methane)] (0:0:0 - 1)
		IfNotBlocked
		reached[2][2] = 1;
		if (!(((int)now.methane)))
			continue;
		_m = 3; goto P999; /* 0 */
	case 25: // STATE 3 - original.pml:112 - [cMethane!methanestop] (0:0:0 - 1)
		IfNotBlocked
		reached[2][3] = 1;
		if (q_len(now.cMethane))
			continue;
#ifdef HAS_CODE
		if (readtrail && gui) {
			char simtmp[64];
			sprintf(simvals, "%d!", now.cMethane);
		sprintf(simtmp, "%d", 12); strcat(simvals, simtmp);		}
#endif
		
		qsend(now.cMethane, 0, 12, 1);
		{ boq = now.cMethane; };
		_m = 2; goto P999; /* 0 */
	case 26: // STATE 4 - original.pml:113 - [(!(methane))] (0:0:0 - 1)
		IfNotBlocked
		reached[2][4] = 1;
		if (!( !(((int)now.methane))))
			continue;
		_m = 3; goto P999; /* 0 */
	case 27: // STATE 5 - original.pml:114 - [cMethane!ready] (0:0:0 - 1)
		IfNotBlocked
		reached[2][5] = 1;
		if (q_len(now.cMethane))
			continue;
#ifdef HAS_CODE
		if (readtrail && gui) {
			char simtmp[64];
			sprintf(simvals, "%d!", now.cMethane);
		sprintf(simtmp, "%d", 2); strcat(simvals, simtmp);		}
#endif
		
		qsend(now.cMethane, 0, 2, 1);
		{ boq = now.cMethane; };
		_m = 2; goto P999; /* 0 */
	case 28: // STATE 12 - original.pml:118 - [-end-] (0:0:0 - 1)
		IfNotBlocked
		reached[2][12] = 1;
		if (!delproc(1, II)) continue;
		_m = 3; goto P999; /* 0 */

		 /* PROC methanealarm */
	case 29: // STATE 1 - original.pml:100 - [methane = 1] (0:0:1 - 1)
		IfNotBlocked
		reached[1][1] = 1;
		(trpt+1)->bup.oval = ((int)now.methane);
		now.methane = 1;
#ifdef VAR_RANGES
		logval("methane", ((int)now.methane));
#endif
		;
		_m = 3; goto P999; /* 0 */
	case 30: // STATE 2 - original.pml:101 - [cAlarm!alarm] (0:0:0 - 1)
		IfNotBlocked
		reached[1][2] = 1;
		if (q_len(now.cAlarm))
			continue;
#ifdef HAS_CODE
		if (readtrail && gui) {
			char simtmp[64];
			sprintf(simvals, "%d!", now.cAlarm);
		sprintf(simtmp, "%d", 11); strcat(simvals, simtmp);		}
#endif
		
		qsend(now.cAlarm, 0, 11, 1);
		{ boq = now.cAlarm; };
		_m = 2; goto P999; /* 0 */
	case 31: // STATE 3 - original.pml:102 - [methane = 0] (0:0:1 - 1)
		IfNotBlocked
		reached[1][3] = 1;
		(trpt+1)->bup.oval = ((int)now.methane);
		now.methane = 0;
#ifdef VAR_RANGES
		logval("methane", ((int)now.methane));
#endif
		;
		_m = 3; goto P999; /* 0 */
	case 32: // STATE 7 - original.pml:104 - [-end-] (0:0:0 - 1)
		IfNotBlocked
		reached[1][7] = 1;
		if (!delproc(1, II)) continue;
		_m = 3; goto P999; /* 0 */

		 /* PROC controller */
	case 33: // STATE 1 - original.pml:18 - [cCmd?pcommand] (21:0:2 - 1)
		reached[0][1] = 1;
		if (boq != now.cCmd) continue;
		if (q_len(now.cCmd) == 0) continue;

		XX=1;
		(trpt+1)->bup.ovals = grab_ints(2);
		(trpt+1)->bup.ovals[0] = ((P0 *)_this)->pcommand;
		;
		((P0 *)_this)->pcommand = qrecv(now.cCmd, XX-1, 0, 1);
#ifdef VAR_RANGES
		logval("controller:pcommand", ((P0 *)_this)->pcommand);
#endif
		;
		
#ifdef HAS_CODE
		if (readtrail && gui) {
			char simtmp[32];
			sprintf(simvals, "%d?", now.cCmd);
		sprintf(simtmp, "%d", ((P0 *)_this)->pcommand); strcat(simvals, simtmp);		}
#endif
		if (q_zero(now.cCmd))
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
		/* merge: readMsg = commandMsg(0, 2, 21) */
		reached[0][2] = 1;
		(trpt+1)->bup.ovals[1] = readMsg;
		readMsg = 9;
#ifdef VAR_RANGES
		logval("readMsg", readMsg);
#endif
		;
		_m = 4; goto P999; /* 1 */
	case 34: // STATE 4 - original.pml:22 - [((pcommand==stop))] (0:0:1 - 1)
		IfNotBlocked
		reached[0][4] = 1;
		if (!((((P0 *)_this)->pcommand==13)))
			continue;
		if (TstOnly) return 1; /* TT */
		/* dead 1: pcommand */  (trpt+1)->bup.oval = ((P0 *)_this)->pcommand;
#ifdef HAS_CODE
		if (!readtrail)
#endif
			((P0 *)_this)->pcommand = 0;
		_m = 3; goto P999; /* 0 */
	case 35: // STATE 5 - original.pml:25 - [((pstate==running))] (23:0:2 - 1)
		IfNotBlocked
		reached[0][5] = 1;
		if (!((now.pstate==10)))
			continue;
		/* merge: pumpOn = 0(23, 6, 23) */
		reached[0][6] = 1;
		(trpt+1)->bup.ovals = grab_ints(2);
		(trpt+1)->bup.ovals[0] = ((int)now.pumpOn);
		now.pumpOn = 0;
#ifdef VAR_RANGES
		logval("pumpOn", ((int)now.pumpOn));
#endif
		;
		/* merge: pstate = stopped(23, 7, 23) */
		reached[0][7] = 1;
		(trpt+1)->bup.ovals[1] = now.pstate;
		now.pstate = 4;
#ifdef VAR_RANGES
		logval("pstate", now.pstate);
#endif
		;
		/* merge: .(goto)(0, 12, 23) */
		reached[0][12] = 1;
		;
		/* merge: .(goto)(0, 22, 23) */
		reached[0][22] = 1;
		;
		_m = 3; goto P999; /* 4 */
	case 36: // STATE 13 - original.pml:32 - [((pcommand==start))] (0:0:1 - 1)
		IfNotBlocked
		reached[0][13] = 1;
		if (!((((P0 *)_this)->pcommand==8)))
			continue;
		if (TstOnly) return 1; /* TT */
		/* dead 1: pcommand */  (trpt+1)->bup.oval = ((P0 *)_this)->pcommand;
#ifdef HAS_CODE
		if (!readtrail)
#endif
			((P0 *)_this)->pcommand = 0;
		_m = 3; goto P999; /* 0 */
	case 37: // STATE 14 - original.pml:35 - [((pstate!=running))] (23:0:1 - 1)
		IfNotBlocked
		reached[0][14] = 1;
		if (!((now.pstate!=10)))
			continue;
		/* merge: pstate = ready(0, 15, 23) */
		reached[0][15] = 1;
		(trpt+1)->bup.oval = now.pstate;
		now.pstate = 2;
#ifdef VAR_RANGES
		logval("pstate", now.pstate);
#endif
		;
		/* merge: .(goto)(0, 20, 23) */
		reached[0][20] = 1;
		;
		/* merge: .(goto)(0, 22, 23) */
		reached[0][22] = 1;
		;
		_m = 3; goto P999; /* 3 */
	case 38: // STATE 23 - original.pml:42 - [cCmd!pstate] (0:0:0 - 7)
		IfNotBlocked
		reached[0][23] = 1;
		if (q_len(now.cCmd))
			continue;
#ifdef HAS_CODE
		if (readtrail && gui) {
			char simtmp[64];
			sprintf(simvals, "%d!", now.cCmd);
		sprintf(simtmp, "%d", now.pstate); strcat(simvals, simtmp);		}
#endif
		
		qsend(now.cCmd, 0, now.pstate, 1);
		{ boq = now.cCmd; };
		_m = 2; goto P999; /* 0 */
	case 39: // STATE 24 - original.pml:44 - [cAlarm?_] (33:0:2 - 1)
		reached[0][24] = 1;
		if (boq != now.cAlarm) continue;
		if (q_len(now.cAlarm) == 0) continue;

		XX=1;
		(trpt+1)->bup.ovals = grab_ints(2);
		(trpt+1)->bup.ovals[0] = qrecv(now.cAlarm, XX-1, 0, 0);
		;
		qrecv(now.cAlarm, XX-1, 0, 1);
		
#ifdef HAS_CODE
		if (readtrail && gui) {
			char simtmp[32];
			sprintf(simvals, "%d?", now.cAlarm);
		sprintf(simtmp, "%d", ((int)_)); strcat(simvals, simtmp);		}
#endif
		if (q_zero(now.cAlarm))
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
		/* merge: readMsg = alarmMsg(0, 25, 33) */
		reached[0][25] = 1;
		(trpt+1)->bup.ovals[1] = readMsg;
		readMsg = 7;
#ifdef VAR_RANGES
		logval("readMsg", readMsg);
#endif
		;
		_m = 4; goto P999; /* 1 */
	case 40: // STATE 27 - original.pml:49 - [((pstate==running))] (71:0:2 - 1)
		IfNotBlocked
		reached[0][27] = 1;
		if (!((now.pstate==10)))
			continue;
		/* merge: pumpOn = 0(71, 28, 71) */
		reached[0][28] = 1;
		(trpt+1)->bup.ovals = grab_ints(2);
		(trpt+1)->bup.ovals[0] = ((int)now.pumpOn);
		now.pumpOn = 0;
#ifdef VAR_RANGES
		logval("pumpOn", ((int)now.pumpOn));
#endif
		;
		/* merge: pstate = methanestop(71, 29, 71) */
		reached[0][29] = 1;
		(trpt+1)->bup.ovals[1] = now.pstate;
		now.pstate = 12;
#ifdef VAR_RANGES
		logval("pstate", now.pstate);
#endif
		;
		/* merge: .(goto)(0, 34, 71) */
		reached[0][34] = 1;
		;
		/* merge: .(goto)(0, 72, 71) */
		reached[0][72] = 1;
		;
		_m = 3; goto P999; /* 4 */
	case 41: // STATE 35 - original.pml:57 - [cLevel?level] (69:0:2 - 1)
		reached[0][35] = 1;
		if (boq != now.cLevel) continue;
		if (q_len(now.cLevel) == 0) continue;

		XX=1;
		(trpt+1)->bup.ovals = grab_ints(2);
		(trpt+1)->bup.ovals[0] = ((P0 *)_this)->level;
		;
		((P0 *)_this)->level = qrecv(now.cLevel, XX-1, 0, 1);
#ifdef VAR_RANGES
		logval("controller:level", ((P0 *)_this)->level);
#endif
		;
		
#ifdef HAS_CODE
		if (readtrail && gui) {
			char simtmp[32];
			sprintf(simvals, "%d?", now.cLevel);
		sprintf(simtmp, "%d", ((P0 *)_this)->level); strcat(simvals, simtmp);		}
#endif
		if (q_zero(now.cLevel))
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
		/* merge: readMsg = levelMsg(0, 36, 69) */
		reached[0][36] = 1;
		(trpt+1)->bup.ovals[1] = readMsg;
		readMsg = 14;
#ifdef VAR_RANGES
		logval("readMsg", readMsg);
#endif
		;
		_m = 4; goto P999; /* 1 */
	case 42: // STATE 38 - original.pml:61 - [((level==high))] (0:0:1 - 1)
		IfNotBlocked
		reached[0][38] = 1;
		if (!((((P0 *)_this)->level==6)))
			continue;
		if (TstOnly) return 1; /* TT */
		/* dead 1: level */  (trpt+1)->bup.oval = ((P0 *)_this)->level;
#ifdef HAS_CODE
		if (!readtrail)
#endif
			((P0 *)_this)->level = 0;
		_m = 3; goto P999; /* 0 */
	case 43: // STATE 39 - original.pml:63 - [(((pstate==ready)||(pstate==lowstop)))] (0:0:0 - 1)
		IfNotBlocked
		reached[0][39] = 1;
		if (!(((now.pstate==2)||(now.pstate==1))))
			continue;
		_m = 3; goto P999; /* 0 */
	case 44: // STATE 40 - original.pml:66 - [cMethane!pstate] (0:0:0 - 1)
		IfNotBlocked
		reached[0][40] = 1;
		if (q_len(now.cMethane))
			continue;
#ifdef HAS_CODE
		if (readtrail && gui) {
			char simtmp[64];
			sprintf(simvals, "%d!", now.cMethane);
		sprintf(simtmp, "%d", now.pstate); strcat(simvals, simtmp);		}
#endif
		
		qsend(now.cMethane, 0, now.pstate, 1);
		{ boq = now.cMethane; };
		_m = 2; goto P999; /* 0 */
	case 45: // STATE 41 - original.pml:67 - [cMethane?pstate] (0:0:1 - 1)
		reached[0][41] = 1;
		if (boq != now.cMethane) continue;
		if (q_len(now.cMethane) == 0) continue;

		XX=1;
		(trpt+1)->bup.oval = now.pstate;
		;
		now.pstate = qrecv(now.cMethane, XX-1, 0, 1);
#ifdef VAR_RANGES
		logval("pstate", now.pstate);
#endif
		;
		
#ifdef HAS_CODE
		if (readtrail && gui) {
			char simtmp[32];
			sprintf(simvals, "%d?", now.cMethane);
		sprintf(simtmp, "%d", now.pstate); strcat(simvals, simtmp);		}
#endif
		if (q_zero(now.cMethane))
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
	case 46: // STATE 42 - original.pml:69 - [((pstate==ready))] (71:0:2 - 1)
		IfNotBlocked
		reached[0][42] = 1;
		if (!((now.pstate==2)))
			continue;
		/* merge: pstate = running(71, 43, 71) */
		reached[0][43] = 1;
		(trpt+1)->bup.ovals = grab_ints(2);
		(trpt+1)->bup.ovals[0] = now.pstate;
		now.pstate = 10;
#ifdef VAR_RANGES
		logval("pstate", now.pstate);
#endif
		;
		/* merge: pumpOn = 1(71, 44, 71) */
		reached[0][44] = 1;
		(trpt+1)->bup.ovals[1] = ((int)now.pumpOn);
		now.pumpOn = 1;
#ifdef VAR_RANGES
		logval("pumpOn", ((int)now.pumpOn));
#endif
		;
		/* merge: .(goto)(71, 48, 71) */
		reached[0][48] = 1;
		;
		/* merge: .(goto)(0, 53, 71) */
		reached[0][53] = 1;
		;
		/* merge: .(goto)(0, 57, 71) */
		reached[0][57] = 1;
		;
		/* merge: .(goto)(0, 70, 71) */
		reached[0][70] = 1;
		;
		/* merge: .(goto)(0, 72, 71) */
		reached[0][72] = 1;
		;
		_m = 3; goto P999; /* 7 */
	case 47: // STATE 48 - original.pml:75 - [.(goto)] (0:71:0 - 2)
		IfNotBlocked
		reached[0][48] = 1;
		;
		/* merge: .(goto)(0, 53, 71) */
		reached[0][53] = 1;
		;
		/* merge: .(goto)(0, 57, 71) */
		reached[0][57] = 1;
		;
		/* merge: .(goto)(0, 70, 71) */
		reached[0][70] = 1;
		;
		/* merge: .(goto)(0, 72, 71) */
		reached[0][72] = 1;
		;
		_m = 3; goto P999; /* 4 */
	case 48: // STATE 46 - original.pml:73 - [(1)] (71:0:0 - 1)
		IfNotBlocked
		reached[0][46] = 1;
		if (!(1))
			continue;
		/* merge: .(goto)(71, 48, 71) */
		reached[0][48] = 1;
		;
		/* merge: .(goto)(0, 53, 71) */
		reached[0][53] = 1;
		;
		/* merge: .(goto)(0, 57, 71) */
		reached[0][57] = 1;
		;
		/* merge: .(goto)(0, 70, 71) */
		reached[0][70] = 1;
		;
		/* merge: .(goto)(0, 72, 71) */
		reached[0][72] = 1;
		;
		_m = 3; goto P999; /* 5 */
	case 49: // STATE 58 - original.pml:82 - [((level==low))] (0:0:1 - 1)
		IfNotBlocked
		reached[0][58] = 1;
		if (!((((P0 *)_this)->level==5)))
			continue;
		if (TstOnly) return 1; /* TT */
		/* dead 1: level */  (trpt+1)->bup.oval = ((P0 *)_this)->level;
#ifdef HAS_CODE
		if (!readtrail)
#endif
			((P0 *)_this)->level = 0;
		_m = 3; goto P999; /* 0 */
	case 50: // STATE 59 - original.pml:85 - [((pstate==running))] (71:0:2 - 1)
		IfNotBlocked
		reached[0][59] = 1;
		if (!((now.pstate==10)))
			continue;
		/* merge: pumpOn = 0(71, 60, 71) */
		reached[0][60] = 1;
		(trpt+1)->bup.ovals = grab_ints(2);
		(trpt+1)->bup.ovals[0] = ((int)now.pumpOn);
		now.pumpOn = 0;
#ifdef VAR_RANGES
		logval("pumpOn", ((int)now.pumpOn));
#endif
		;
		/* merge: pstate = lowstop(71, 61, 71) */
		reached[0][61] = 1;
		(trpt+1)->bup.ovals[1] = now.pstate;
		now.pstate = 1;
#ifdef VAR_RANGES
		logval("pstate", now.pstate);
#endif
		;
		/* merge: .(goto)(0, 66, 71) */
		reached[0][66] = 1;
		;
		/* merge: .(goto)(0, 70, 71) */
		reached[0][70] = 1;
		;
		/* merge: .(goto)(0, 72, 71) */
		reached[0][72] = 1;
		;
		_m = 3; goto P999; /* 5 */
	case 51: // STATE 67 - original.pml:92 - [((level==medium))] (0:0:1 - 1)
		IfNotBlocked
		reached[0][67] = 1;
		if (!((((P0 *)_this)->level==3)))
			continue;
		if (TstOnly) return 1; /* TT */
		/* dead 1: level */  (trpt+1)->bup.oval = ((P0 *)_this)->level;
#ifdef HAS_CODE
		if (!readtrail)
#endif
			((P0 *)_this)->level = 0;
		_m = 3; goto P999; /* 0 */
	case 52: // STATE 74 - original.pml:96 - [-end-] (0:0:0 - 1)
		IfNotBlocked
		reached[0][74] = 1;
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

