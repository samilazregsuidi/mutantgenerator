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
	case 3: // STATE 1 - original.pml.nvr:5 - [(!((floor==2)))] (0:0:0 - 1)
		
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
		if (!( !((((int)now.floor)==2))))
			continue;
		_m = 3; goto P999; /* 0 */
	case 4: // STATE 5 - original.pml.nvr:7 - [(!((progress||waiting)))] (0:0:0 - 1)
		
#if defined(VERI) && !defined(NP)
#if NCLAIMS>1
		{	static int reported5 = 0;
			if (verbose && !reported5)
			{	int nn = (int) ((Pclaim *)pptr(0))->_n;
				printf("depth %ld: Claim %s (%d), state %d (line %d)\n",
					depth, procname[spin_c_typ[nn]], nn, (int) ((Pclaim *)pptr(0))->_p, src_claim[ (int) ((Pclaim *)pptr(0))->_p ]);
				reported5 = 1;
				fflush(stdout);
		}	}
#else
		{	static int reported5 = 0;
			if (verbose && !reported5)
			{	printf("depth %d: Claim, state %d (line %d)\n",
					(int) depth, (int) ((Pclaim *)pptr(0))->_p, src_claim[ (int) ((Pclaim *)pptr(0))->_p ]);
				reported5 = 1;
				fflush(stdout);
		}	}
#endif
#endif
		reached[2][5] = 1;
		if (!( !((((int)now.progress)||((int)now.waiting)))))
			continue;
		_m = 3; goto P999; /* 0 */
	case 5: // STATE 17 - original.pml.nvr:16 - [(!((progress||waiting)))] (0:0:0 - 1)
		
#if defined(VERI) && !defined(NP)
#if NCLAIMS>1
		{	static int reported17 = 0;
			if (verbose && !reported17)
			{	int nn = (int) ((Pclaim *)pptr(0))->_n;
				printf("depth %ld: Claim %s (%d), state %d (line %d)\n",
					depth, procname[spin_c_typ[nn]], nn, (int) ((Pclaim *)pptr(0))->_p, src_claim[ (int) ((Pclaim *)pptr(0))->_p ]);
				reported17 = 1;
				fflush(stdout);
		}	}
#else
		{	static int reported17 = 0;
			if (verbose && !reported17)
			{	printf("depth %d: Claim, state %d (line %d)\n",
					(int) depth, (int) ((Pclaim *)pptr(0))->_p, src_claim[ (int) ((Pclaim *)pptr(0))->_p ]);
				reported17 = 1;
				fflush(stdout);
		}	}
#endif
#endif
		reached[2][17] = 1;
		if (!( !((((int)now.progress)||((int)now.waiting)))))
			continue;
		_m = 3; goto P999; /* 0 */
	case 6: // STATE 22 - original.pml.nvr:20 - [(!((floor==2)))] (0:0:0 - 1)
		
#if defined(VERI) && !defined(NP)
#if NCLAIMS>1
		{	static int reported22 = 0;
			if (verbose && !reported22)
			{	int nn = (int) ((Pclaim *)pptr(0))->_n;
				printf("depth %ld: Claim %s (%d), state %d (line %d)\n",
					depth, procname[spin_c_typ[nn]], nn, (int) ((Pclaim *)pptr(0))->_p, src_claim[ (int) ((Pclaim *)pptr(0))->_p ]);
				reported22 = 1;
				fflush(stdout);
		}	}
#else
		{	static int reported22 = 0;
			if (verbose && !reported22)
			{	printf("depth %d: Claim, state %d (line %d)\n",
					(int) depth, (int) ((Pclaim *)pptr(0))->_p, src_claim[ (int) ((Pclaim *)pptr(0))->_p ]);
				reported22 = 1;
				fflush(stdout);
		}	}
#endif
#endif
		reached[2][22] = 1;
		if (!( !((((int)now.floor)==2))))
			continue;
		_m = 3; goto P999; /* 0 */
	case 7: // STATE 29 - original.pml.nvr:25 - [(!((progress||waiting)))] (0:0:0 - 1)
		
#if defined(VERI) && !defined(NP)
#if NCLAIMS>1
		{	static int reported29 = 0;
			if (verbose && !reported29)
			{	int nn = (int) ((Pclaim *)pptr(0))->_n;
				printf("depth %ld: Claim %s (%d), state %d (line %d)\n",
					depth, procname[spin_c_typ[nn]], nn, (int) ((Pclaim *)pptr(0))->_p, src_claim[ (int) ((Pclaim *)pptr(0))->_p ]);
				reported29 = 1;
				fflush(stdout);
		}	}
#else
		{	static int reported29 = 0;
			if (verbose && !reported29)
			{	printf("depth %d: Claim, state %d (line %d)\n",
					(int) depth, (int) ((Pclaim *)pptr(0))->_p, src_claim[ (int) ((Pclaim *)pptr(0))->_p ]);
				reported29 = 1;
				fflush(stdout);
		}	}
#endif
#endif
		reached[2][29] = 1;
		if (!( !((((int)now.progress)||((int)now.waiting)))))
			continue;
		_m = 3; goto P999; /* 0 */
	case 8: // STATE 36 - original.pml.nvr:28 - [-end-] (0:0:0 - 1)
		
#if defined(VERI) && !defined(NP)
#if NCLAIMS>1
		{	static int reported36 = 0;
			if (verbose && !reported36)
			{	int nn = (int) ((Pclaim *)pptr(0))->_n;
				printf("depth %ld: Claim %s (%d), state %d (line %d)\n",
					depth, procname[spin_c_typ[nn]], nn, (int) ((Pclaim *)pptr(0))->_p, src_claim[ (int) ((Pclaim *)pptr(0))->_p ]);
				reported36 = 1;
				fflush(stdout);
		}	}
#else
		{	static int reported36 = 0;
			if (verbose && !reported36)
			{	printf("depth %d: Claim, state %d (line %d)\n",
					(int) depth, (int) ((Pclaim *)pptr(0))->_p, src_claim[ (int) ((Pclaim *)pptr(0))->_p ]);
				reported36 = 1;
				fflush(stdout);
		}	}
#endif
#endif
		reached[2][36] = 1;
		if (!delproc(1, II)) continue;
		_m = 3; goto P999; /* 0 */

		 /* PROC controller */
	case 9: // STATE 1 - original.pml:81 - [progress = 0] (0:0:1 - 1)
		IfNotBlocked
		reached[1][1] = 1;
		(trpt+1)->bup.oval = ((int)now.progress);
		now.progress = 0;
#ifdef VAR_RANGES
		logval("progress", ((int)now.progress));
#endif
		;
		_m = 3; goto P999; /* 0 */
	case 10: // STATE 2 - original.pml:82 - [progress = 1] (0:0:1 - 1)
		IfNotBlocked
		reached[1][2] = 1;
		(trpt+1)->bup.oval = ((int)now.progress);
		now.progress = 1;
#ifdef VAR_RANGES
		logval("progress", ((int)now.progress));
#endif
		;
		_m = 3; goto P999; /* 0 */
	case 11: // STATE 3 - original.pml:84 - [((f.TTFull&&f.Exec))] (0:0:0 - 1)
		IfNotBlocked
		reached[1][3] = 1;
		if (!((((int)now.f.TTFull)&&((int)now.f.Exec))))
			continue;
		_m = 3; goto P999; /* 0 */
	case 12: // STATE 4 - original.pml:85 - [stop = ( (((( (person[0].in_elevator) -> (1) : (0) )+( (person[1].in_elevator) -> (1) : (0) ))<2)) -> (((cabin_button[floor].pushed||floor_button[floor].pushed)&&((floor==3)||!((cabin_button[3].pushed||floor_button[3].pushed))))) : (( ((cabin_button[3].pushed||floor_button[3].pushed)) -> ((floor==3)) : ((cabin_button[floor].pushed||(floor_button[floor].pushed&&((( (person[0].in_elevator) -> (1) : (0) )+( (person[1].in_elevator) -> (1) : (0) ))<2)))) )) )] (0:0:1 - 1)
		IfNotBlocked
		reached[1][4] = 1;
		(trpt+1)->bup.oval = ((int)((P1 *)_this)->stop);
		((P1 *)_this)->stop = ( (((( (((int)now.person[0].in_elevator)) ? (1) : (0) )+( (((int)now.person[1].in_elevator)) ? (1) : (0) ))<2)) ? (((((int)now.cabin_button[ Index(((int)now.floor), 4) ].pushed)||((int)now.floor_button[ Index(((int)now.floor), 4) ].pushed))&&((((int)now.floor)==3)|| !((((int)now.cabin_button[3].pushed)||((int)now.floor_button[3].pushed)))))) : (( ((((int)now.cabin_button[3].pushed)||((int)now.floor_button[3].pushed))) ? ((((int)now.floor)==3)) : ((((int)now.cabin_button[ Index(((int)now.floor), 4) ].pushed)||(((int)now.floor_button[ Index(((int)now.floor), 4) ].pushed)&&((( (((int)now.person[0].in_elevator)) ? (1) : (0) )+( (((int)now.person[1].in_elevator)) ? (1) : (0) ))<2)))) )) );
#ifdef VAR_RANGES
		logval("controller:stop", ((int)((P1 *)_this)->stop));
#endif
		;
		_m = 3; goto P999; /* 0 */
	case 13: // STATE 5 - original.pml:86 - [((f.TTFull&&!(f.Exec)))] (0:0:0 - 1)
		IfNotBlocked
		reached[1][5] = 1;
		if (!((((int)now.f.TTFull)&& !(((int)now.f.Exec)))))
			continue;
		_m = 3; goto P999; /* 0 */
	case 14: // STATE 6 - original.pml:87 - [stop = (cabin_button[floor].pushed||(floor_button[floor].pushed&&((( (person[0].in_elevator) -> (1) : (0) )+( (person[1].in_elevator) -> (1) : (0) ))<2)))] (0:0:1 - 1)
		IfNotBlocked
		reached[1][6] = 1;
		(trpt+1)->bup.oval = ((int)((P1 *)_this)->stop);
		((P1 *)_this)->stop = (((int)now.cabin_button[ Index(((int)now.floor), 4) ].pushed)||(((int)now.floor_button[ Index(((int)now.floor), 4) ].pushed)&&((( (((int)now.person[0].in_elevator)) ? (1) : (0) )+( (((int)now.person[1].in_elevator)) ? (1) : (0) ))<2)));
#ifdef VAR_RANGES
		logval("controller:stop", ((int)((P1 *)_this)->stop));
#endif
		;
		_m = 3; goto P999; /* 0 */
	case 15: // STATE 7 - original.pml:88 - [((!(f.TTFull)&&f.Exec))] (0:0:0 - 1)
		IfNotBlocked
		reached[1][7] = 1;
		if (!(( !(((int)now.f.TTFull))&&((int)now.f.Exec))))
			continue;
		_m = 3; goto P999; /* 0 */
	case 16: // STATE 8 - original.pml:89 - [stop = ((cabin_button[floor].pushed||floor_button[floor].pushed)&&((floor==3)||!((cabin_button[3].pushed||floor_button[3].pushed))))] (0:0:1 - 1)
		IfNotBlocked
		reached[1][8] = 1;
		(trpt+1)->bup.oval = ((int)((P1 *)_this)->stop);
		((P1 *)_this)->stop = ((((int)now.cabin_button[ Index(((int)now.floor), 4) ].pushed)||((int)now.floor_button[ Index(((int)now.floor), 4) ].pushed))&&((((int)now.floor)==3)|| !((((int)now.cabin_button[3].pushed)||((int)now.floor_button[3].pushed)))));
#ifdef VAR_RANGES
		logval("controller:stop", ((int)((P1 *)_this)->stop));
#endif
		;
		_m = 3; goto P999; /* 0 */
	case 17: // STATE 10 - original.pml:91 - [stop = (cabin_button[floor].pushed||floor_button[floor].pushed)] (0:0:1 - 1)
		IfNotBlocked
		reached[1][10] = 1;
		(trpt+1)->bup.oval = ((int)((P1 *)_this)->stop);
		((P1 *)_this)->stop = (((int)now.cabin_button[ Index(((int)now.floor), 4) ].pushed)||((int)now.floor_button[ Index(((int)now.floor), 4) ].pushed));
#ifdef VAR_RANGES
		logval("controller:stop", ((int)((P1 *)_this)->stop));
#endif
		;
		_m = 3; goto P999; /* 0 */
	case 18: // STATE 13 - original.pml:95 - [(stop)] (18:0:5 - 1)
		IfNotBlocked
		reached[1][13] = 1;
		if (!(((int)((P1 *)_this)->stop)))
			continue;
		if (TstOnly) return 1; /* TT */
		/* dead 1: stop */  (trpt+1)->bup.ovals = grab_ints(5);
		(trpt+1)->bup.ovals[0] = ((P1 *)_this)->stop;
#ifdef HAS_CODE
		if (!readtrail)
#endif
			((P1 *)_this)->stop = 0;
		/* merge: stop = 0(18, 14, 18) */
		reached[1][14] = 1;
		(trpt+1)->bup.ovals[1] = ((int)((P1 *)_this)->stop);
		((P1 *)_this)->stop = 0;
#ifdef VAR_RANGES
		logval("controller:stop", ((int)((P1 *)_this)->stop));
#endif
		;
		/* merge: door = open(18, 15, 18) */
		reached[1][15] = 1;
		(trpt+1)->bup.ovals[2] = now.door;
		now.door = 1;
#ifdef VAR_RANGES
		logval("door", now.door);
#endif
		;
		/* merge: cabin_button[floor].pushed = 0(18, 16, 18) */
		reached[1][16] = 1;
		(trpt+1)->bup.ovals[3] = ((int)now.cabin_button[ Index(((int)now.floor), 4) ].pushed);
		now.cabin_button[ Index(now.floor, 4) ].pushed = 0;
#ifdef VAR_RANGES
		logval("cabin_button[floor].pushed", ((int)now.cabin_button[ Index(((int)now.floor), 4) ].pushed));
#endif
		;
		/* merge: floor_button[floor].pushed = 0(18, 17, 18) */
		reached[1][17] = 1;
		(trpt+1)->bup.ovals[4] = ((int)now.floor_button[ Index(((int)now.floor), 4) ].pushed);
		now.floor_button[ Index(now.floor, 4) ].pushed = 0;
#ifdef VAR_RANGES
		logval("floor_button[floor].pushed", ((int)now.floor_button[ Index(((int)now.floor), 4) ].pushed));
#endif
		;
		_m = 3; goto P999; /* 4 */
	case 19: // STATE 18 - original.pml:100 - [((((person[0].to_floor!=floor)||!(person[0].in_elevator))&&((person[1].to_floor!=floor)||!(person[1].in_elevator))))] (0:0:0 - 1)
		IfNotBlocked
		reached[1][18] = 1;
		if (!((((((int)now.person[0].to_floor)!=((int)now.floor))|| !(((int)now.person[0].in_elevator)))&&((((int)now.person[1].to_floor)!=((int)now.floor))|| !(((int)now.person[1].in_elevator))))))
			continue;
		_m = 3; goto P999; /* 0 */
	case 20: // STATE 20 - original.pml:103 - [(!(f.QuickClose))] (0:0:0 - 1)
		IfNotBlocked
		reached[1][20] = 1;
		if (!( !(((int)now.f.QuickClose))))
			continue;
		_m = 3; goto P999; /* 0 */
	case 21: // STATE 21 - original.pml:106 - [((floor_button[floor].pushed||cabin_button[floor].pushed))] (26:0:3 - 1)
		IfNotBlocked
		reached[1][21] = 1;
		if (!((((int)now.floor_button[ Index(((int)now.floor), 4) ].pushed)||((int)now.cabin_button[ Index(((int)now.floor), 4) ].pushed))))
			continue;
		/* merge: floor_button[floor].pushed = 0(26, 22, 26) */
		reached[1][22] = 1;
		(trpt+1)->bup.ovals = grab_ints(3);
		(trpt+1)->bup.ovals[0] = ((int)now.floor_button[ Index(((int)now.floor), 4) ].pushed);
		now.floor_button[ Index(now.floor, 4) ].pushed = 0;
#ifdef VAR_RANGES
		logval("floor_button[floor].pushed", ((int)now.floor_button[ Index(((int)now.floor), 4) ].pushed));
#endif
		;
		/* merge: cabin_button[floor].pushed = 0(26, 23, 26) */
		reached[1][23] = 1;
		(trpt+1)->bup.ovals[1] = ((int)now.cabin_button[ Index(((int)now.floor), 4) ].pushed);
		now.cabin_button[ Index(now.floor, 4) ].pushed = 0;
#ifdef VAR_RANGES
		logval("cabin_button[floor].pushed", ((int)now.cabin_button[ Index(((int)now.floor), 4) ].pushed));
#endif
		;
		/* merge: waiting = 1(26, 24, 26) */
		reached[1][24] = 1;
		(trpt+1)->bup.ovals[2] = ((int)now.waiting);
		now.waiting = 1;
#ifdef VAR_RANGES
		logval("waiting", ((int)now.waiting));
#endif
		;
		_m = 3; goto P999; /* 3 */
	case 22: // STATE 26 - original.pml:111 - [waiting = 0] (0:0:1 - 1)
		IfNotBlocked
		reached[1][26] = 1;
		(trpt+1)->bup.oval = ((int)now.waiting);
		now.waiting = 0;
#ifdef VAR_RANGES
		logval("waiting", ((int)now.waiting));
#endif
		;
		_m = 3; goto P999; /* 0 */
	case 23: // STATE 35 - original.pml:118 - [((f.OpenIfIdle||f.Park))] (0:0:0 - 1)
		IfNotBlocked
		reached[1][35] = 1;
		if (!((((int)now.f.OpenIfIdle)||((int)now.f.Park))))
			continue;
		_m = 3; goto P999; /* 0 */
	case 24: // STATE 36 - original.pml:121 - [((floor==0))] (41:0:1 - 1)
		IfNotBlocked
		reached[1][36] = 1;
		if (!((((int)now.floor)==0)))
			continue;
		/* merge: waiting = 1(0, 37, 41) */
		reached[1][37] = 1;
		(trpt+1)->bup.oval = ((int)now.waiting);
		now.waiting = 1;
#ifdef VAR_RANGES
		logval("waiting", ((int)now.waiting));
#endif
		;
		_m = 3; goto P999; /* 1 */
	case 25: // STATE 39 - original.pml:125 - [((((((((floor_button[0].pushed||cabin_button[0].pushed)||floor_button[1].pushed)||cabin_button[1].pushed)||floor_button[2].pushed)||cabin_button[2].pushed)||floor_button[3].pushed)||cabin_button[3].pushed))] (76:0:1 - 1)
		IfNotBlocked
		reached[1][39] = 1;
		if (!((((((((((int)now.floor_button[0].pushed)||((int)now.cabin_button[0].pushed))||((int)now.floor_button[1].pushed))||((int)now.cabin_button[1].pushed))||((int)now.floor_button[2].pushed))||((int)now.cabin_button[2].pushed))||((int)now.floor_button[3].pushed))||((int)now.cabin_button[3].pushed))))
			continue;
		/* merge: waiting = 0(0, 40, 76) */
		reached[1][40] = 1;
		(trpt+1)->bup.oval = ((int)now.waiting);
		now.waiting = 0;
#ifdef VAR_RANGES
		logval("waiting", ((int)now.waiting));
#endif
		;
		/* merge: .(goto)(0, 52, 76) */
		reached[1][52] = 1;
		;
		/* merge: .(goto)(0, 55, 76) */
		reached[1][55] = 1;
		;
		_m = 3; goto P999; /* 3 */
	case 26: // STATE 43 - original.pml:130 - [(f.OpenIfIdle)] (0:0:0 - 1)
		IfNotBlocked
		reached[1][43] = 1;
		if (!(((int)now.f.OpenIfIdle)))
			continue;
		_m = 3; goto P999; /* 0 */
	case 27: // STATE 44 - original.pml:131 - [waiting = 1] (0:0:1 - 1)
		IfNotBlocked
		reached[1][44] = 1;
		(trpt+1)->bup.oval = ((int)now.waiting);
		now.waiting = 1;
#ifdef VAR_RANGES
		logval("waiting", ((int)now.waiting));
#endif
		;
		_m = 3; goto P999; /* 0 */
	case 28: // STATE 45 - original.pml:133 - [((((((((floor_button[0].pushed||cabin_button[0].pushed)||floor_button[1].pushed)||cabin_button[1].pushed)||floor_button[2].pushed)||cabin_button[2].pushed)||floor_button[3].pushed)||cabin_button[3].pushed))] (76:0:1 - 1)
		IfNotBlocked
		reached[1][45] = 1;
		if (!((((((((((int)now.floor_button[0].pushed)||((int)now.cabin_button[0].pushed))||((int)now.floor_button[1].pushed))||((int)now.cabin_button[1].pushed))||((int)now.floor_button[2].pushed))||((int)now.cabin_button[2].pushed))||((int)now.floor_button[3].pushed))||((int)now.cabin_button[3].pushed))))
			continue;
		/* merge: waiting = 0(0, 46, 76) */
		reached[1][46] = 1;
		(trpt+1)->bup.oval = ((int)now.waiting);
		now.waiting = 0;
#ifdef VAR_RANGES
		logval("waiting", ((int)now.waiting));
#endif
		;
		/* merge: .(goto)(0, 50, 76) */
		reached[1][50] = 1;
		;
		/* merge: .(goto)(0, 52, 76) */
		reached[1][52] = 1;
		;
		/* merge: .(goto)(0, 55, 76) */
		reached[1][55] = 1;
		;
		_m = 3; goto P999; /* 4 */
	case 29: // STATE 56 - original.pml:143 - [(f.Overload)] (0:0:0 - 1)
		IfNotBlocked
		reached[1][56] = 1;
		if (!(((int)now.f.Overload)))
			continue;
		_m = 3; goto P999; /* 0 */
	case 30: // STATE 57 - original.pml:144 - [(((( (person[0].in_elevator) -> (1) : (0) )+( (person[1].in_elevator) -> (1) : (0) ))<2))] (73:0:2 - 1)
		IfNotBlocked
		reached[1][57] = 1;
		if (!(((( (((int)now.person[0].in_elevator)) ? (1) : (0) )+( (((int)now.person[1].in_elevator)) ? (1) : (0) ))<2)))
			continue;
		/* merge: .(goto)(73, 60, 73) */
		reached[1][60] = 1;
		;
		/* merge: cabin_button[floor].pushed = 0(73, 61, 73) */
		reached[1][61] = 1;
		(trpt+1)->bup.ovals = grab_ints(2);
		(trpt+1)->bup.ovals[0] = ((int)now.cabin_button[ Index(((int)now.floor), 4) ].pushed);
		now.cabin_button[ Index(now.floor, 4) ].pushed = 0;
#ifdef VAR_RANGES
		logval("cabin_button[floor].pushed", ((int)now.cabin_button[ Index(((int)now.floor), 4) ].pushed));
#endif
		;
		/* merge: floor_button[floor].pushed = 0(73, 62, 73) */
		reached[1][62] = 1;
		(trpt+1)->bup.ovals[1] = ((int)now.floor_button[ Index(((int)now.floor), 4) ].pushed);
		now.floor_button[ Index(now.floor, 4) ].pushed = 0;
#ifdef VAR_RANGES
		logval("floor_button[floor].pushed", ((int)now.floor_button[ Index(((int)now.floor), 4) ].pushed));
#endif
		;
		_m = 3; goto P999; /* 3 */
	case 31: // STATE 61 - original.pml:147 - [cabin_button[floor].pushed = 0] (0:73:2 - 3)
		IfNotBlocked
		reached[1][61] = 1;
		(trpt+1)->bup.ovals = grab_ints(2);
		(trpt+1)->bup.ovals[0] = ((int)now.cabin_button[ Index(((int)now.floor), 4) ].pushed);
		now.cabin_button[ Index(now.floor, 4) ].pushed = 0;
#ifdef VAR_RANGES
		logval("cabin_button[floor].pushed", ((int)now.cabin_button[ Index(((int)now.floor), 4) ].pushed));
#endif
		;
		/* merge: floor_button[floor].pushed = 0(73, 62, 73) */
		reached[1][62] = 1;
		(trpt+1)->bup.ovals[1] = ((int)now.floor_button[ Index(((int)now.floor), 4) ].pushed);
		now.floor_button[ Index(now.floor, 4) ].pushed = 0;
#ifdef VAR_RANGES
		logval("floor_button[floor].pushed", ((int)now.floor_button[ Index(((int)now.floor), 4) ].pushed));
#endif
		;
		_m = 3; goto P999; /* 1 */
	case 32: // STATE 63 - original.pml:150 - [(f.Empty)] (0:0:0 - 1)
		IfNotBlocked
		reached[1][63] = 1;
		if (!(((int)now.f.Empty)))
			continue;
		_m = 3; goto P999; /* 0 */
	case 33: // STATE 64 - original.pml:152 - [(((person[0].in_elevator==0)&&(person[1].in_elevator==0)))] (116:0:5 - 1)
		IfNotBlocked
		reached[1][64] = 1;
		if (!(((((int)now.person[0].in_elevator)==0)&&(((int)now.person[1].in_elevator)==0))))
			continue;
		/* merge: cabin_button[0].pushed = 0(116, 65, 116) */
		reached[1][65] = 1;
		(trpt+1)->bup.ovals = grab_ints(5);
		(trpt+1)->bup.ovals[0] = ((int)now.cabin_button[0].pushed);
		now.cabin_button[0].pushed = 0;
#ifdef VAR_RANGES
		logval("cabin_button[0].pushed", ((int)now.cabin_button[0].pushed));
#endif
		;
		/* merge: cabin_button[1].pushed = 0(116, 66, 116) */
		reached[1][66] = 1;
		(trpt+1)->bup.ovals[1] = ((int)now.cabin_button[1].pushed);
		now.cabin_button[1].pushed = 0;
#ifdef VAR_RANGES
		logval("cabin_button[1].pushed", ((int)now.cabin_button[1].pushed));
#endif
		;
		/* merge: cabin_button[2].pushed = 0(116, 67, 116) */
		reached[1][67] = 1;
		(trpt+1)->bup.ovals[2] = ((int)now.cabin_button[2].pushed);
		now.cabin_button[2].pushed = 0;
#ifdef VAR_RANGES
		logval("cabin_button[2].pushed", ((int)now.cabin_button[2].pushed));
#endif
		;
		/* merge: cabin_button[3].pushed = 0(116, 68, 116) */
		reached[1][68] = 1;
		(trpt+1)->bup.ovals[3] = ((int)now.cabin_button[3].pushed);
		now.cabin_button[3].pushed = 0;
#ifdef VAR_RANGES
		logval("cabin_button[3].pushed", ((int)now.cabin_button[3].pushed));
#endif
		;
		/* merge: .(goto)(116, 71, 116) */
		reached[1][71] = 1;
		;
		/* merge: .(goto)(116, 74, 116) */
		reached[1][74] = 1;
		;
		/* merge: door = closed(116, 75, 116) */
		reached[1][75] = 1;
		(trpt+1)->bup.ovals[4] = now.door;
		now.door = 2;
#ifdef VAR_RANGES
		logval("door", now.door);
#endif
		;
		/* merge: .(goto)(0, 80, 116) */
		reached[1][80] = 1;
		;
		_m = 3; goto P999; /* 8 */
	case 34: // STATE 74 - original.pml:161 - [.(goto)] (0:116:1 - 4)
		IfNotBlocked
		reached[1][74] = 1;
		;
		/* merge: door = closed(116, 75, 116) */
		reached[1][75] = 1;
		(trpt+1)->bup.oval = now.door;
		now.door = 2;
#ifdef VAR_RANGES
		logval("door", now.door);
#endif
		;
		/* merge: .(goto)(0, 80, 116) */
		reached[1][80] = 1;
		;
		_m = 3; goto P999; /* 2 */
	case 35: // STATE 81 - original.pml:168 - [set = 0] (0:0:1 - 1)
		IfNotBlocked
		reached[1][81] = 1;
		(trpt+1)->bup.oval = ((int)((P1 *)_this)->_6_9_set);
		((P1 *)_this)->_6_9_set = 0;
#ifdef VAR_RANGES
		logval("controller:set", ((int)((P1 *)_this)->_6_9_set));
#endif
		;
		_m = 3; goto P999; /* 0 */
	case 36: // STATE 82 - original.pml:169 - [(f.Shuttle)] (96:0:2 - 1)
		IfNotBlocked
		reached[1][82] = 1;
		if (!(((int)now.f.Shuttle)))
			continue;
		/* merge: direction = ( ((floor==0)) -> (up) : (( ((floor==(4-1))) -> (down) : (direction) )) )(96, 83, 96) */
		reached[1][83] = 1;
		(trpt+1)->bup.ovals = grab_ints(2);
		(trpt+1)->bup.ovals[0] = now.direction;
		now.direction = ( ((((int)now.floor)==0)) ? (4) : (( ((((int)now.floor)==(4-1))) ? (3) : (now.direction) )) );
#ifdef VAR_RANGES
		logval("direction", now.direction);
#endif
		;
		/* merge: set = 1(96, 84, 96) */
		reached[1][84] = 1;
		(trpt+1)->bup.ovals[1] = ((int)((P1 *)_this)->_6_9_set);
		((P1 *)_this)->_6_9_set = 1;
#ifdef VAR_RANGES
		logval("controller:set", ((int)((P1 *)_this)->_6_9_set));
#endif
		;
		/* merge: .(goto)(0, 87, 96) */
		reached[1][87] = 1;
		;
		_m = 3; goto P999; /* 3 */
	case 37: // STATE 88 - original.pml:175 - [(f.Exec)] (0:0:0 - 1)
		IfNotBlocked
		reached[1][88] = 1;
		if (!(((int)now.f.Exec)))
			continue;
		_m = 3; goto P999; /* 0 */
	case 38: // STATE 89 - original.pml:177 - [((!(set)&&(cabin_button[3].pushed||floor_button[3].pushed)))] (106:0:3 - 1)
		IfNotBlocked
		reached[1][89] = 1;
		if (!(( !(((int)((P1 *)_this)->_6_9_set))&&(((int)now.cabin_button[3].pushed)||((int)now.floor_button[3].pushed)))))
			continue;
		if (TstOnly) return 1; /* TT */
		/* dead 1: _6_9_set */  (trpt+1)->bup.ovals = grab_ints(3);
		(trpt+1)->bup.ovals[0] = ((P1 *)_this)->_6_9_set;
#ifdef HAS_CODE
		if (!readtrail)
#endif
			((P1 *)_this)->_6_9_set = 0;
		/* merge: direction = ( ((3<floor)) -> (down) : (( ((3>floor)) -> (up) : (stay) )) )(106, 90, 106) */
		reached[1][90] = 1;
		(trpt+1)->bup.ovals[1] = now.direction;
		now.direction = ( ((3<((int)now.floor))) ? (3) : (( ((3>((int)now.floor))) ? (4) : (5) )) );
#ifdef VAR_RANGES
		logval("direction", now.direction);
#endif
		;
		/* merge: set = 1(106, 91, 106) */
		reached[1][91] = 1;
		(trpt+1)->bup.ovals[2] = ((int)((P1 *)_this)->_6_9_set);
		((P1 *)_this)->_6_9_set = 1;
#ifdef VAR_RANGES
		logval("controller:set", ((int)((P1 *)_this)->_6_9_set));
#endif
		;
		/* merge: .(goto)(0, 94, 106) */
		reached[1][94] = 1;
		;
		/* merge: .(goto)(0, 97, 106) */
		reached[1][97] = 1;
		;
		_m = 3; goto P999; /* 4 */
	case 39: // STATE 98 - original.pml:185 - [(f.Park)] (0:0:0 - 1)
		IfNotBlocked
		reached[1][98] = 1;
		if (!(((int)now.f.Park)))
			continue;
		_m = 3; goto P999; /* 0 */
	case 40: // STATE 99 - original.pml:187 - [((!(set)&&!((((((((floor_button[0].pushed||cabin_button[0].pushed)||floor_button[1].pushed)||cabin_button[1].pushed)||floor_button[2].pushed)||cabin_button[2].pushed)||floor_button[3].pushed)||cabin_button[3].pushed))))] (113:0:3 - 1)
		IfNotBlocked
		reached[1][99] = 1;
		if (!(( !(((int)((P1 *)_this)->_6_9_set))&& !((((((((((int)now.floor_button[0].pushed)||((int)now.cabin_button[0].pushed))||((int)now.floor_button[1].pushed))||((int)now.cabin_button[1].pushed))||((int)now.floor_button[2].pushed))||((int)now.cabin_button[2].pushed))||((int)now.floor_button[3].pushed))||((int)now.cabin_button[3].pushed))))))
			continue;
		if (TstOnly) return 1; /* TT */
		/* dead 1: _6_9_set */  (trpt+1)->bup.ovals = grab_ints(3);
		(trpt+1)->bup.ovals[0] = ((P1 *)_this)->_6_9_set;
#ifdef HAS_CODE
		if (!readtrail)
#endif
			((P1 *)_this)->_6_9_set = 0;
		/* merge: direction = ( ((0<floor)) -> (down) : (( ((0>floor)) -> (up) : (stay) )) )(113, 100, 113) */
		reached[1][100] = 1;
		(trpt+1)->bup.ovals[1] = now.direction;
		now.direction = ( ((0<((int)now.floor))) ? (3) : (( ((0>((int)now.floor))) ? (4) : (5) )) );
#ifdef VAR_RANGES
		logval("direction", now.direction);
#endif
		;
		/* merge: set = 1(113, 101, 113) */
		reached[1][101] = 1;
		(trpt+1)->bup.ovals[2] = ((int)((P1 *)_this)->_6_9_set);
		((P1 *)_this)->_6_9_set = 1;
#ifdef VAR_RANGES
		logval("controller:set", ((int)((P1 *)_this)->_6_9_set));
#endif
		;
		/* merge: .(goto)(0, 104, 113) */
		reached[1][104] = 1;
		;
		/* merge: .(goto)(0, 107, 113) */
		reached[1][107] = 1;
		;
		_m = 3; goto P999; /* 4 */
	case 41: // STATE 108 - original.pml:195 - [(set)] (117:0:3 - 1)
		IfNotBlocked
		reached[1][108] = 1;
		if (!(((int)((P1 *)_this)->_6_9_set)))
			continue;
		if (TstOnly) return 1; /* TT */
		/* dead 1: _6_9_set */  (trpt+1)->bup.ovals = grab_ints(3);
		(trpt+1)->bup.ovals[0] = ((P1 *)_this)->_6_9_set;
#ifdef HAS_CODE
		if (!readtrail)
#endif
			((P1 *)_this)->_6_9_set = 0;
		/* merge: set = 0(117, 109, 117) */
		reached[1][109] = 1;
		(trpt+1)->bup.ovals[1] = ((int)((P1 *)_this)->_6_9_set);
		((P1 *)_this)->_6_9_set = 0;
#ifdef VAR_RANGES
		logval("controller:set", ((int)((P1 *)_this)->_6_9_set));
#endif
		;
		/* merge: .(goto)(117, 114, 117) */
		reached[1][114] = 1;
		;
		/* merge: floor = ( ((direction==up)) -> ((floor+1)) : (( ((direction==down)) -> ((floor-1)) : (floor) )) )(117, 115, 117) */
		reached[1][115] = 1;
		(trpt+1)->bup.ovals[2] = ((int)now.floor);
		now.floor = ( ((now.direction==4)) ? ((((int)now.floor)+1)) : (( ((now.direction==3)) ? ((((int)now.floor)-1)) : (((int)now.floor)) )) );
#ifdef VAR_RANGES
		logval("floor", ((int)now.floor));
#endif
		;
		/* merge: .(goto)(0, 118, 117) */
		reached[1][118] = 1;
		;
		_m = 3; goto P999; /* 4 */
	case 42: // STATE 114 - original.pml:201 - [.(goto)] (0:117:1 - 2)
		IfNotBlocked
		reached[1][114] = 1;
		;
		/* merge: floor = ( ((direction==up)) -> ((floor+1)) : (( ((direction==down)) -> ((floor-1)) : (floor) )) )(117, 115, 117) */
		reached[1][115] = 1;
		(trpt+1)->bup.oval = ((int)now.floor);
		now.floor = ( ((now.direction==4)) ? ((((int)now.floor)+1)) : (( ((now.direction==3)) ? ((((int)now.floor)-1)) : (((int)now.floor)) )) );
#ifdef VAR_RANGES
		logval("floor", ((int)now.floor));
#endif
		;
		/* merge: .(goto)(0, 118, 117) */
		reached[1][118] = 1;
		;
		_m = 3; goto P999; /* 2 */
	case 43: // STATE 111 - original.pml:198 - [direction = ( ((floor==0)) -> (up) : (( ((floor==(4-1))) -> (down) : (direction) )) )] (0:117:3 - 1)
		IfNotBlocked
		reached[1][111] = 1;
		(trpt+1)->bup.ovals = grab_ints(3);
		(trpt+1)->bup.ovals[0] = now.direction;
		now.direction = ( ((((int)now.floor)==0)) ? (4) : (( ((((int)now.floor)==(4-1))) ? (3) : (now.direction) )) );
#ifdef VAR_RANGES
		logval("direction", now.direction);
#endif
		;
		/* merge: direction = ( (((((((floor>0)&&(floor_button[0].pushed||cabin_button[0].pushed))||((floor>1)&&(floor_button[1].pushed||cabin_button[1].pushed)))||((floor>2)&&(floor_button[2].pushed||cabin_button[2].pushed)))||((floor>3)&&(floor_button[3].pushed||cabin_button[3].pushed)))&&(direction==down))) -> (down) : (( (((((((floor<0)&&(floor_button[0].pushed||cabin_button[0].pushed))||((floor<1)&&(floor_button[1].pushed||cabin_button[1].pushed)))||((floor<2)&&(floor_button[2].pushed||cabin_button[2].pushed)))||((floor<3)&&(floor_button[3].pushed||cabin_button[3].pushed)))&&(direction==up))) -> (up) : (( ((((((floor>0)&&(floor_button[0].pushed||cabin_button[0].pushed))||((floor>1)&&(floor_button[1].pushed||cabin_button[1].pushed)))||((floor>2)&&(floor_button[2].pushed||cabin_button[2].pushed)))||((floor>3)&&(floor_button[3].pushed||cabin_button[3].pushed)))) -> (down) : (( ((((((floor<0)&&(floor_button[0].pushed||cabin_button[0].pushed))||((floor<1)&&(floor_button[1].pushed||cabin_button[1].pushed)))||((floor<2)&&(floor_button[2].pushed||cabin_button[2].pushed)))||((floor<3)&&(floor_button[3].pushed||cabin_button[3].pushed)))) -> (up) : (stay) )) )) )) )(117, 112, 117) */
		reached[1][112] = 1;
		(trpt+1)->bup.ovals[1] = now.direction;
		now.direction = ( (((((((((int)now.floor)>0)&&(((int)now.floor_button[0].pushed)||((int)now.cabin_button[0].pushed)))||((((int)now.floor)>1)&&(((int)now.floor_button[1].pushed)||((int)now.cabin_button[1].pushed))))||((((int)now.floor)>2)&&(((int)now.floor_button[2].pushed)||((int)now.cabin_button[2].pushed))))||((((int)now.floor)>3)&&(((int)now.floor_button[3].pushed)||((int)now.cabin_button[3].pushed))))&&(now.direction==3))) ? (3) : (( (((((((((int)now.floor)<0)&&(((int)now.floor_button[0].pushed)||((int)now.cabin_button[0].pushed)))||((((int)now.floor)<1)&&(((int)now.floor_button[1].pushed)||((int)now.cabin_button[1].pushed))))||((((int)now.floor)<2)&&(((int)now.floor_button[2].pushed)||((int)now.cabin_button[2].pushed))))||((((int)now.floor)<3)&&(((int)now.floor_button[3].pushed)||((int)now.cabin_button[3].pushed))))&&(now.direction==4))) ? (4) : (( ((((((((int)now.floor)>0)&&(((int)now.floor_button[0].pushed)||((int)now.cabin_button[0].pushed)))||((((int)now.floor)>1)&&(((int)now.floor_button[1].pushed)||((int)now.cabin_button[1].pushed))))||((((int)now.floor)>2)&&(((int)now.floor_button[2].pushed)||((int)now.cabin_button[2].pushed))))||((((int)now.floor)>3)&&(((int)now.floor_button[3].pushed)||((int)now.cabin_button[3].pushed))))) ? (3) : (( ((((((((int)now.floor)<0)&&(((int)now.floor_button[0].pushed)||((int)now.cabin_button[0].pushed)))||((((int)now.floor)<1)&&(((int)now.floor_button[1].pushed)||((int)now.cabin_button[1].pushed))))||((((int)now.floor)<2)&&(((int)now.floor_button[2].pushed)||((int)now.cabin_button[2].pushed))))||((((int)now.floor)<3)&&(((int)now.floor_button[3].pushed)||((int)now.cabin_button[3].pushed))))) ? (4) : (5) )) )) )) );
#ifdef VAR_RANGES
		logval("direction", now.direction);
#endif
		;
		/* merge: .(goto)(117, 114, 117) */
		reached[1][114] = 1;
		;
		/* merge: floor = ( ((direction==up)) -> ((floor+1)) : (( ((direction==down)) -> ((floor-1)) : (floor) )) )(117, 115, 117) */
		reached[1][115] = 1;
		(trpt+1)->bup.ovals[2] = ((int)now.floor);
		now.floor = ( ((now.direction==4)) ? ((((int)now.floor)+1)) : (( ((now.direction==3)) ? ((((int)now.floor)-1)) : (((int)now.floor)) )) );
#ifdef VAR_RANGES
		logval("floor", ((int)now.floor));
#endif
		;
		/* merge: .(goto)(0, 118, 117) */
		reached[1][118] = 1;
		;
		_m = 3; goto P999; /* 4 */
	case 44: // STATE 120 - original.pml:204 - [-end-] (0:0:0 - 1)
		IfNotBlocked
		reached[1][120] = 1;
		if (!delproc(1, II)) continue;
		_m = 3; goto P999; /* 0 */

		 /* PROC ptPersonDetermined */
	case 45: // STATE 1 - original.pml:34 - [person[_pid].at_floor = 0] (0:0:1 - 1)
		IfNotBlocked
		reached[0][1] = 1;
		(trpt+1)->bup.oval = ((int)now.person[ Index(((int)((P0 *)_this)->_pid), 2) ].at_floor);
		now.person[ Index(((P0 *)_this)->_pid, 2) ].at_floor = 0;
#ifdef VAR_RANGES
		logval("person[_pid].at_floor", ((int)now.person[ Index(((int)((P0 *)_this)->_pid), 2) ].at_floor));
#endif
		;
		_m = 3; goto P999; /* 0 */
	case 46: // STATE 2 - original.pml:35 - [person[_pid].at_floor = 1] (0:0:1 - 1)
		IfNotBlocked
		reached[0][2] = 1;
		(trpt+1)->bup.oval = ((int)now.person[ Index(((int)((P0 *)_this)->_pid), 2) ].at_floor);
		now.person[ Index(((P0 *)_this)->_pid, 2) ].at_floor = 1;
#ifdef VAR_RANGES
		logval("person[_pid].at_floor", ((int)now.person[ Index(((int)((P0 *)_this)->_pid), 2) ].at_floor));
#endif
		;
		_m = 3; goto P999; /* 0 */
	case 47: // STATE 3 - original.pml:36 - [person[_pid].at_floor = 2] (0:0:1 - 1)
		IfNotBlocked
		reached[0][3] = 1;
		(trpt+1)->bup.oval = ((int)now.person[ Index(((int)((P0 *)_this)->_pid), 2) ].at_floor);
		now.person[ Index(((P0 *)_this)->_pid, 2) ].at_floor = 2;
#ifdef VAR_RANGES
		logval("person[_pid].at_floor", ((int)now.person[ Index(((int)((P0 *)_this)->_pid), 2) ].at_floor));
#endif
		;
		_m = 3; goto P999; /* 0 */
	case 48: // STATE 4 - original.pml:37 - [person[_pid].at_floor = 3] (0:0:1 - 1)
		IfNotBlocked
		reached[0][4] = 1;
		(trpt+1)->bup.oval = ((int)now.person[ Index(((int)((P0 *)_this)->_pid), 2) ].at_floor);
		now.person[ Index(((P0 *)_this)->_pid, 2) ].at_floor = 3;
#ifdef VAR_RANGES
		logval("person[_pid].at_floor", ((int)now.person[ Index(((int)((P0 *)_this)->_pid), 2) ].at_floor));
#endif
		;
		_m = 3; goto P999; /* 0 */
	case 49: // STATE 7 - original.pml:41 - [floor_button[person[_pid].at_floor].pushed = 1] (0:0:1 - 1)
		IfNotBlocked
		reached[0][7] = 1;
		(trpt+1)->bup.oval = ((int)now.floor_button[ Index(((int)now.person[ Index(((int)((P0 *)_this)->_pid), 2) ].at_floor), 4) ].pushed);
		now.floor_button[ Index(now.person[ Index(((P0 *)_this)->_pid, 2) ].at_floor, 4) ].pushed = 1;
#ifdef VAR_RANGES
		logval("floor_button[person[_pid].at_floor].pushed", ((int)now.floor_button[ Index(((int)now.person[ Index(((int)((P0 *)_this)->_pid), 2) ].at_floor), 4) ].pushed));
#endif
		;
		_m = 3; goto P999; /* 0 */
	case 50: // STATE 10 - original.pml:46 - [(((floor==person[_pid].at_floor)&&(door==open)))] (21:0:2 - 1)
		IfNotBlocked
		reached[0][10] = 1;
		if (!(((((int)now.floor)==((int)now.person[ Index(((int)((P0 *)_this)->_pid), 2) ].at_floor))&&(now.door==1))))
			continue;
		/* merge: person[_pid].at_floor = 0(21, 11, 21) */
		reached[0][11] = 1;
		(trpt+1)->bup.ovals = grab_ints(2);
		(trpt+1)->bup.ovals[0] = ((int)now.person[ Index(((int)((P0 *)_this)->_pid), 2) ].at_floor);
		now.person[ Index(((P0 *)_this)->_pid, 2) ].at_floor = 0;
#ifdef VAR_RANGES
		logval("person[_pid].at_floor", ((int)now.person[ Index(((int)((P0 *)_this)->_pid), 2) ].at_floor));
#endif
		;
		/* merge: person[_pid].in_elevator = 1(21, 12, 21) */
		reached[0][12] = 1;
		(trpt+1)->bup.ovals[1] = ((int)now.person[ Index(((int)((P0 *)_this)->_pid), 2) ].in_elevator);
		now.person[ Index(((P0 *)_this)->_pid, 2) ].in_elevator = 1;
#ifdef VAR_RANGES
		logval("person[_pid].in_elevator", ((int)now.person[ Index(((int)((P0 *)_this)->_pid), 2) ].in_elevator));
#endif
		;
		_m = 3; goto P999; /* 2 */
	case 51: // STATE 13 - original.pml:50 - [((floor!=0))] (33:0:2 - 1)
		IfNotBlocked
		reached[0][13] = 1;
		if (!((((int)now.floor)!=0)))
			continue;
		/* merge: person[_pid].to_floor = 0(33, 14, 33) */
		reached[0][14] = 1;
		(trpt+1)->bup.ovals = grab_ints(2);
		(trpt+1)->bup.ovals[0] = ((int)now.person[ Index(((int)((P0 *)_this)->_pid), 2) ].to_floor);
		now.person[ Index(((P0 *)_this)->_pid, 2) ].to_floor = 0;
#ifdef VAR_RANGES
		logval("person[_pid].to_floor", ((int)now.person[ Index(((int)((P0 *)_this)->_pid), 2) ].to_floor));
#endif
		;
		/* merge: .(goto)(33, 22, 33) */
		reached[0][22] = 1;
		;
		/* merge: cabin_button[person[_pid].to_floor].pushed = 1(33, 23, 33) */
		reached[0][23] = 1;
		(trpt+1)->bup.ovals[1] = ((int)now.cabin_button[ Index(((int)now.person[ Index(((int)((P0 *)_this)->_pid), 2) ].to_floor), 4) ].pushed);
		now.cabin_button[ Index(now.person[ Index(((P0 *)_this)->_pid, 2) ].to_floor, 4) ].pushed = 1;
#ifdef VAR_RANGES
		logval("cabin_button[person[_pid].to_floor].pushed", ((int)now.cabin_button[ Index(((int)now.person[ Index(((int)((P0 *)_this)->_pid), 2) ].to_floor), 4) ].pushed));
#endif
		;
		_m = 3; goto P999; /* 3 */
	case 52: // STATE 15 - original.pml:52 - [((floor!=1))] (33:0:2 - 1)
		IfNotBlocked
		reached[0][15] = 1;
		if (!((((int)now.floor)!=1)))
			continue;
		/* merge: person[_pid].to_floor = 1(33, 16, 33) */
		reached[0][16] = 1;
		(trpt+1)->bup.ovals = grab_ints(2);
		(trpt+1)->bup.ovals[0] = ((int)now.person[ Index(((int)((P0 *)_this)->_pid), 2) ].to_floor);
		now.person[ Index(((P0 *)_this)->_pid, 2) ].to_floor = 1;
#ifdef VAR_RANGES
		logval("person[_pid].to_floor", ((int)now.person[ Index(((int)((P0 *)_this)->_pid), 2) ].to_floor));
#endif
		;
		/* merge: .(goto)(33, 22, 33) */
		reached[0][22] = 1;
		;
		/* merge: cabin_button[person[_pid].to_floor].pushed = 1(33, 23, 33) */
		reached[0][23] = 1;
		(trpt+1)->bup.ovals[1] = ((int)now.cabin_button[ Index(((int)now.person[ Index(((int)((P0 *)_this)->_pid), 2) ].to_floor), 4) ].pushed);
		now.cabin_button[ Index(now.person[ Index(((P0 *)_this)->_pid, 2) ].to_floor, 4) ].pushed = 1;
#ifdef VAR_RANGES
		logval("cabin_button[person[_pid].to_floor].pushed", ((int)now.cabin_button[ Index(((int)now.person[ Index(((int)((P0 *)_this)->_pid), 2) ].to_floor), 4) ].pushed));
#endif
		;
		_m = 3; goto P999; /* 3 */
	case 53: // STATE 17 - original.pml:54 - [((floor!=2))] (33:0:2 - 1)
		IfNotBlocked
		reached[0][17] = 1;
		if (!((((int)now.floor)!=2)))
			continue;
		/* merge: person[_pid].to_floor = 2(33, 18, 33) */
		reached[0][18] = 1;
		(trpt+1)->bup.ovals = grab_ints(2);
		(trpt+1)->bup.ovals[0] = ((int)now.person[ Index(((int)((P0 *)_this)->_pid), 2) ].to_floor);
		now.person[ Index(((P0 *)_this)->_pid, 2) ].to_floor = 2;
#ifdef VAR_RANGES
		logval("person[_pid].to_floor", ((int)now.person[ Index(((int)((P0 *)_this)->_pid), 2) ].to_floor));
#endif
		;
		/* merge: .(goto)(33, 22, 33) */
		reached[0][22] = 1;
		;
		/* merge: cabin_button[person[_pid].to_floor].pushed = 1(33, 23, 33) */
		reached[0][23] = 1;
		(trpt+1)->bup.ovals[1] = ((int)now.cabin_button[ Index(((int)now.person[ Index(((int)((P0 *)_this)->_pid), 2) ].to_floor), 4) ].pushed);
		now.cabin_button[ Index(now.person[ Index(((P0 *)_this)->_pid, 2) ].to_floor, 4) ].pushed = 1;
#ifdef VAR_RANGES
		logval("cabin_button[person[_pid].to_floor].pushed", ((int)now.cabin_button[ Index(((int)now.person[ Index(((int)((P0 *)_this)->_pid), 2) ].to_floor), 4) ].pushed));
#endif
		;
		_m = 3; goto P999; /* 3 */
	case 54: // STATE 19 - original.pml:56 - [((floor!=3))] (33:0:2 - 1)
		IfNotBlocked
		reached[0][19] = 1;
		if (!((((int)now.floor)!=3)))
			continue;
		/* merge: person[_pid].to_floor = 3(33, 20, 33) */
		reached[0][20] = 1;
		(trpt+1)->bup.ovals = grab_ints(2);
		(trpt+1)->bup.ovals[0] = ((int)now.person[ Index(((int)((P0 *)_this)->_pid), 2) ].to_floor);
		now.person[ Index(((P0 *)_this)->_pid, 2) ].to_floor = 3;
#ifdef VAR_RANGES
		logval("person[_pid].to_floor", ((int)now.person[ Index(((int)((P0 *)_this)->_pid), 2) ].to_floor));
#endif
		;
		/* merge: .(goto)(33, 22, 33) */
		reached[0][22] = 1;
		;
		/* merge: cabin_button[person[_pid].to_floor].pushed = 1(33, 23, 33) */
		reached[0][23] = 1;
		(trpt+1)->bup.ovals[1] = ((int)now.cabin_button[ Index(((int)now.person[ Index(((int)((P0 *)_this)->_pid), 2) ].to_floor), 4) ].pushed);
		now.cabin_button[ Index(now.person[ Index(((P0 *)_this)->_pid, 2) ].to_floor, 4) ].pushed = 1;
#ifdef VAR_RANGES
		logval("cabin_button[person[_pid].to_floor].pushed", ((int)now.cabin_button[ Index(((int)now.person[ Index(((int)((P0 *)_this)->_pid), 2) ].to_floor), 4) ].pushed));
#endif
		;
		_m = 3; goto P999; /* 3 */
	case 55: // STATE 23 - original.pml:59 - [cabin_button[person[_pid].to_floor].pushed = 1] (0:33:1 - 5)
		IfNotBlocked
		reached[0][23] = 1;
		(trpt+1)->bup.oval = ((int)now.cabin_button[ Index(((int)now.person[ Index(((int)((P0 *)_this)->_pid), 2) ].to_floor), 4) ].pushed);
		now.cabin_button[ Index(now.person[ Index(((P0 *)_this)->_pid, 2) ].to_floor, 4) ].pushed = 1;
#ifdef VAR_RANGES
		logval("cabin_button[person[_pid].to_floor].pushed", ((int)now.cabin_button[ Index(((int)now.person[ Index(((int)((P0 *)_this)->_pid), 2) ].to_floor), 4) ].pushed));
#endif
		;
		_m = 3; goto P999; /* 0 */
	case 56: // STATE 24 - original.pml:61 - [((door==closed))] (0:0:0 - 1)
		IfNotBlocked
		reached[0][24] = 1;
		if (!((now.door==2)))
			continue;
		_m = 3; goto P999; /* 0 */
	case 57: // STATE 25 - original.pml:62 - [(((floor==person[_pid].to_floor)&&(door==open)))] (38:0:3 - 1)
		IfNotBlocked
		reached[0][25] = 1;
		if (!(((((int)now.floor)==((int)now.person[ Index(((int)((P0 *)_this)->_pid), 2) ].to_floor))&&(now.door==1))))
			continue;
		/* merge: person[_pid].at_floor = floor(38, 26, 38) */
		reached[0][26] = 1;
		(trpt+1)->bup.ovals = grab_ints(3);
		(trpt+1)->bup.ovals[0] = ((int)now.person[ Index(((int)((P0 *)_this)->_pid), 2) ].at_floor);
		now.person[ Index(((P0 *)_this)->_pid, 2) ].at_floor = ((int)now.floor);
#ifdef VAR_RANGES
		logval("person[_pid].at_floor", ((int)now.person[ Index(((int)((P0 *)_this)->_pid), 2) ].at_floor));
#endif
		;
		/* merge: person[_pid].to_floor = 0(38, 27, 38) */
		reached[0][27] = 1;
		(trpt+1)->bup.ovals[1] = ((int)now.person[ Index(((int)((P0 *)_this)->_pid), 2) ].to_floor);
		now.person[ Index(((P0 *)_this)->_pid, 2) ].to_floor = 0;
#ifdef VAR_RANGES
		logval("person[_pid].to_floor", ((int)now.person[ Index(((int)((P0 *)_this)->_pid), 2) ].to_floor));
#endif
		;
		/* merge: person[_pid].in_elevator = 0(38, 28, 38) */
		reached[0][28] = 1;
		(trpt+1)->bup.ovals[2] = ((int)now.person[ Index(((int)((P0 *)_this)->_pid), 2) ].in_elevator);
		now.person[ Index(((P0 *)_this)->_pid, 2) ].in_elevator = 0;
#ifdef VAR_RANGES
		logval("person[_pid].in_elevator", ((int)now.person[ Index(((int)((P0 *)_this)->_pid), 2) ].in_elevator));
#endif
		;
		/* merge: .(goto)(38, 34, 38) */
		reached[0][34] = 1;
		;
		/* merge: .(goto)(0, 37, 38) */
		reached[0][37] = 1;
		;
		/* merge: .(goto)(0, 39, 38) */
		reached[0][39] = 1;
		;
		_m = 3; goto P999; /* 6 */
	case 58: // STATE 34 - original.pml:71 - [.(goto)] (0:38:0 - 2)
		IfNotBlocked
		reached[0][34] = 1;
		;
		/* merge: .(goto)(0, 37, 38) */
		reached[0][37] = 1;
		;
		/* merge: .(goto)(0, 39, 38) */
		reached[0][39] = 1;
		;
		_m = 3; goto P999; /* 2 */
	case 59: // STATE 29 - original.pml:66 - [(timeout)] (38:0:3 - 1)
		IfNotBlocked
		reached[0][29] = 1;
		if (!(((trpt->tau)&1)))
			continue;
		/* merge: person[_pid].at_floor = floor(38, 30, 38) */
		reached[0][30] = 1;
		(trpt+1)->bup.ovals = grab_ints(3);
		(trpt+1)->bup.ovals[0] = ((int)now.person[ Index(((int)((P0 *)_this)->_pid), 2) ].at_floor);
		now.person[ Index(((P0 *)_this)->_pid, 2) ].at_floor = ((int)now.floor);
#ifdef VAR_RANGES
		logval("person[_pid].at_floor", ((int)now.person[ Index(((int)((P0 *)_this)->_pid), 2) ].at_floor));
#endif
		;
		/* merge: person[_pid].to_floor = 0(38, 31, 38) */
		reached[0][31] = 1;
		(trpt+1)->bup.ovals[1] = ((int)now.person[ Index(((int)((P0 *)_this)->_pid), 2) ].to_floor);
		now.person[ Index(((P0 *)_this)->_pid, 2) ].to_floor = 0;
#ifdef VAR_RANGES
		logval("person[_pid].to_floor", ((int)now.person[ Index(((int)((P0 *)_this)->_pid), 2) ].to_floor));
#endif
		;
		/* merge: person[_pid].in_elevator = 0(38, 32, 38) */
		reached[0][32] = 1;
		(trpt+1)->bup.ovals[2] = ((int)now.person[ Index(((int)((P0 *)_this)->_pid), 2) ].in_elevator);
		now.person[ Index(((P0 *)_this)->_pid, 2) ].in_elevator = 0;
#ifdef VAR_RANGES
		logval("person[_pid].in_elevator", ((int)now.person[ Index(((int)((P0 *)_this)->_pid), 2) ].in_elevator));
#endif
		;
		/* merge: .(goto)(38, 34, 38) */
		reached[0][34] = 1;
		;
		/* merge: .(goto)(0, 37, 38) */
		reached[0][37] = 1;
		;
		/* merge: .(goto)(0, 39, 38) */
		reached[0][39] = 1;
		;
		_m = 1; goto P999; /* 6 */
	case 60: // STATE 41 - original.pml:74 - [-end-] (0:0:0 - 1)
		IfNotBlocked
		reached[0][41] = 1;
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

