	switch (t->back) {
	default: Uerror("bad return move");
	case  0: goto R999; /* nothing to undo */

		 /* CLAIM never_0 */
;
		;
		
	case 4: // STATE 6
		;
		p_restor(II);
		;
		;
		goto R999;

		 /* PROC watersensor */
;
		;
		
	case 6: // STATE 2
		;
		now.waterLevel = trpt->bup.oval;
		;
		goto R999;

	case 7: // STATE 3
		;
		now.waterLevel = trpt->bup.oval;
		;
		goto R999;
;
		
	case 8: // STATE 18
		goto R999;
;
		;
		
	case 10: // STATE 7
		;
		now.waterLevel = trpt->bup.oval;
		;
		goto R999;

	case 11: // STATE 8
		;
		now.waterLevel = trpt->bup.oval;
		;
		goto R999;

	case 12: // STATE 9
		;
		now.waterLevel = trpt->bup.oval;
		;
		goto R999;
;
		;
		
	case 14: // STATE 13
		;
		now.waterLevel = trpt->bup.oval;
		;
		goto R999;

	case 15: // STATE 14
		;
		now.waterLevel = trpt->bup.oval;
		;
		goto R999;

	case 16: // STATE 19
		;
		_m = unsend(now.cLevel);
		;
		goto R999;

	case 17: // STATE 24
		;
		p_restor(II);
		;
		;
		goto R999;

		 /* PROC user */

	case 18: // STATE 1
		;
		now.uwants = trpt->bup.oval;
		;
		goto R999;

	case 19: // STATE 2
		;
		now.uwants = trpt->bup.oval;
		;
		goto R999;

	case 20: // STATE 5
		;
		_m = unsend(now.cCmd);
		;
		goto R999;

	case 21: // STATE 6
		;
		XX = 1;
		unrecv(now.cCmd, XX-1, 0, trpt->bup.oval, 1);
		;
		;
		goto R999;

	case 22: // STATE 10
		;
		p_restor(II);
		;
		;
		goto R999;

		 /* PROC methanesensor */

	case 23: // STATE 1
		;
		XX = 1;
		unrecv(now.cMethane, XX-1, 0, trpt->bup.oval, 1);
		;
		;
		goto R999;
;
		;
		
	case 25: // STATE 3
		;
		_m = unsend(now.cMethane);
		;
		goto R999;
;
		;
		
	case 27: // STATE 5
		;
		_m = unsend(now.cMethane);
		;
		goto R999;

	case 28: // STATE 12
		;
		p_restor(II);
		;
		;
		goto R999;

		 /* PROC methanealarm */

	case 29: // STATE 1
		;
		now.methane = trpt->bup.oval;
		;
		goto R999;

	case 30: // STATE 2
		;
		_m = unsend(now.cAlarm);
		;
		goto R999;

	case 31: // STATE 3
		;
		now.methane = trpt->bup.oval;
		;
		goto R999;

	case 32: // STATE 7
		;
		p_restor(II);
		;
		;
		goto R999;

		 /* PROC controller */

	case 33: // STATE 2
		;
		readMsg = trpt->bup.ovals[1];
		XX = 1;
		unrecv(now.cCmd, XX-1, 0, ((P0 *)_this)->pcommand, 1);
		((P0 *)_this)->pcommand = trpt->bup.ovals[0];
		;
		;
		ungrab_ints(trpt->bup.ovals, 2);
		goto R999;

	case 34: // STATE 4
		;
	/* 0 */	((P0 *)_this)->pcommand = trpt->bup.oval;
		;
		;
		goto R999;

	case 35: // STATE 7
		;
		now.pstate = trpt->bup.ovals[1];
		now.pumpOn = trpt->bup.ovals[0];
		;
		ungrab_ints(trpt->bup.ovals, 2);
		goto R999;

	case 36: // STATE 13
		;
	/* 0 */	((P0 *)_this)->pcommand = trpt->bup.oval;
		;
		;
		goto R999;

	case 37: // STATE 15
		;
		now.pstate = trpt->bup.oval;
		;
		goto R999;

	case 38: // STATE 23
		;
		_m = unsend(now.cCmd);
		;
		goto R999;

	case 39: // STATE 25
		;
		readMsg = trpt->bup.ovals[1];
		XX = 1;
		unrecv(now.cAlarm, XX-1, 0, trpt->bup.ovals[0], 1);
		;
		;
		ungrab_ints(trpt->bup.ovals, 2);
		goto R999;

	case 40: // STATE 29
		;
		now.pstate = trpt->bup.ovals[1];
		now.pumpOn = trpt->bup.ovals[0];
		;
		ungrab_ints(trpt->bup.ovals, 2);
		goto R999;

	case 41: // STATE 36
		;
		readMsg = trpt->bup.ovals[1];
		XX = 1;
		unrecv(now.cLevel, XX-1, 0, ((P0 *)_this)->level, 1);
		((P0 *)_this)->level = trpt->bup.ovals[0];
		;
		;
		ungrab_ints(trpt->bup.ovals, 2);
		goto R999;

	case 42: // STATE 38
		;
	/* 0 */	((P0 *)_this)->level = trpt->bup.oval;
		;
		;
		goto R999;
;
		;
		
	case 44: // STATE 40
		;
		_m = unsend(now.cMethane);
		;
		goto R999;

	case 45: // STATE 41
		;
		XX = 1;
		unrecv(now.cMethane, XX-1, 0, now.pstate, 1);
		now.pstate = trpt->bup.oval;
		;
		;
		goto R999;

	case 46: // STATE 44
		;
		now.pumpOn = trpt->bup.ovals[1];
		now.pstate = trpt->bup.ovals[0];
		;
		ungrab_ints(trpt->bup.ovals, 2);
		goto R999;
;
		
	case 47: // STATE 48
		goto R999;
;
		
	case 48: // STATE 46
		goto R999;

	case 49: // STATE 58
		;
	/* 0 */	((P0 *)_this)->level = trpt->bup.oval;
		;
		;
		goto R999;

	case 50: // STATE 61
		;
		now.pstate = trpt->bup.ovals[1];
		now.pumpOn = trpt->bup.ovals[0];
		;
		ungrab_ints(trpt->bup.ovals, 2);
		goto R999;

	case 51: // STATE 67
		;
	/* 0 */	((P0 *)_this)->level = trpt->bup.oval;
		;
		;
		goto R999;

	case 52: // STATE 74
		;
		p_restor(II);
		;
		;
		goto R999;
	}

