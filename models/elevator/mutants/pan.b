	switch (t->back) {
	default: Uerror("bad return move");
	case  0: goto R999; /* nothing to undo */

		 /* CLAIM never_0 */
;
		;
		;
		;
		;
		;
		;
		;
		;
		;
		
	case 8: // STATE 36
		;
		p_restor(II);
		;
		;
		goto R999;

		 /* PROC controller */

	case 9: // STATE 1
		;
		now.progress = trpt->bup.oval;
		;
		goto R999;

	case 10: // STATE 2
		;
		now.progress = trpt->bup.oval;
		;
		goto R999;
;
		;
		
	case 12: // STATE 4
		;
		((P1 *)_this)->stop = trpt->bup.oval;
		;
		goto R999;
;
		;
		
	case 14: // STATE 6
		;
		((P1 *)_this)->stop = trpt->bup.oval;
		;
		goto R999;
;
		;
		
	case 16: // STATE 8
		;
		((P1 *)_this)->stop = trpt->bup.oval;
		;
		goto R999;

	case 17: // STATE 10
		;
		((P1 *)_this)->stop = trpt->bup.oval;
		;
		goto R999;

	case 18: // STATE 17
		;
		now.floor_button[ Index(now.floor, 4) ].pushed = trpt->bup.ovals[4];
		now.cabin_button[ Index(now.floor, 4) ].pushed = trpt->bup.ovals[3];
		now.door = trpt->bup.ovals[2];
		((P1 *)_this)->stop = trpt->bup.ovals[1];
	/* 0 */	((P1 *)_this)->stop = trpt->bup.ovals[0];
		;
		;
		ungrab_ints(trpt->bup.ovals, 5);
		goto R999;
;
		;
		;
		;
		
	case 21: // STATE 24
		;
		now.waiting = trpt->bup.ovals[2];
		now.cabin_button[ Index(now.floor, 4) ].pushed = trpt->bup.ovals[1];
		now.floor_button[ Index(now.floor, 4) ].pushed = trpt->bup.ovals[0];
		;
		ungrab_ints(trpt->bup.ovals, 3);
		goto R999;

	case 22: // STATE 26
		;
		now.waiting = trpt->bup.oval;
		;
		goto R999;
;
		;
		
	case 24: // STATE 37
		;
		now.waiting = trpt->bup.oval;
		;
		goto R999;

	case 25: // STATE 40
		;
		now.waiting = trpt->bup.oval;
		;
		goto R999;
;
		;
		
	case 27: // STATE 44
		;
		now.waiting = trpt->bup.oval;
		;
		goto R999;

	case 28: // STATE 46
		;
		now.waiting = trpt->bup.oval;
		;
		goto R999;
;
		;
		
	case 30: // STATE 62
		;
		now.floor_button[ Index(now.floor, 4) ].pushed = trpt->bup.ovals[1];
		now.cabin_button[ Index(now.floor, 4) ].pushed = trpt->bup.ovals[0];
		;
		ungrab_ints(trpt->bup.ovals, 2);
		goto R999;

	case 31: // STATE 62
		;
		now.floor_button[ Index(now.floor, 4) ].pushed = trpt->bup.ovals[1];
		now.cabin_button[ Index(now.floor, 4) ].pushed = trpt->bup.ovals[0];
		;
		ungrab_ints(trpt->bup.ovals, 2);
		goto R999;
;
		;
		
	case 33: // STATE 75
		;
		now.door = trpt->bup.ovals[4];
		now.cabin_button[3].pushed = trpt->bup.ovals[3];
		now.cabin_button[2].pushed = trpt->bup.ovals[2];
		now.cabin_button[1].pushed = trpt->bup.ovals[1];
		now.cabin_button[0].pushed = trpt->bup.ovals[0];
		;
		ungrab_ints(trpt->bup.ovals, 5);
		goto R999;

	case 34: // STATE 75
		;
		now.door = trpt->bup.oval;
		;
		goto R999;

	case 35: // STATE 81
		;
		((P1 *)_this)->_6_9_set = trpt->bup.oval;
		;
		goto R999;

	case 36: // STATE 84
		;
		((P1 *)_this)->_6_9_set = trpt->bup.ovals[1];
		now.direction = trpt->bup.ovals[0];
		;
		ungrab_ints(trpt->bup.ovals, 2);
		goto R999;
;
		;
		
	case 38: // STATE 91
		;
		((P1 *)_this)->_6_9_set = trpt->bup.ovals[2];
		now.direction = trpt->bup.ovals[1];
	/* 0 */	((P1 *)_this)->_6_9_set = trpt->bup.ovals[0];
		;
		;
		ungrab_ints(trpt->bup.ovals, 3);
		goto R999;
;
		;
		
	case 40: // STATE 101
		;
		((P1 *)_this)->_6_9_set = trpt->bup.ovals[2];
		now.direction = trpt->bup.ovals[1];
	/* 0 */	((P1 *)_this)->_6_9_set = trpt->bup.ovals[0];
		;
		;
		ungrab_ints(trpt->bup.ovals, 3);
		goto R999;

	case 41: // STATE 115
		;
		now.floor = trpt->bup.ovals[2];
		((P1 *)_this)->_6_9_set = trpt->bup.ovals[1];
	/* 0 */	((P1 *)_this)->_6_9_set = trpt->bup.ovals[0];
		;
		;
		ungrab_ints(trpt->bup.ovals, 3);
		goto R999;

	case 42: // STATE 115
		;
		now.floor = trpt->bup.oval;
		;
		goto R999;

	case 43: // STATE 115
		;
		now.floor = trpt->bup.ovals[2];
		now.direction = trpt->bup.ovals[1];
		now.direction = trpt->bup.ovals[0];
		;
		ungrab_ints(trpt->bup.ovals, 3);
		goto R999;

	case 44: // STATE 120
		;
		p_restor(II);
		;
		;
		goto R999;

		 /* PROC ptPersonDetermined */

	case 45: // STATE 1
		;
		now.person[ Index(((P0 *)_this)->_pid, 2) ].at_floor = trpt->bup.oval;
		;
		goto R999;

	case 46: // STATE 2
		;
		now.person[ Index(((P0 *)_this)->_pid, 2) ].at_floor = trpt->bup.oval;
		;
		goto R999;

	case 47: // STATE 3
		;
		now.person[ Index(((P0 *)_this)->_pid, 2) ].at_floor = trpt->bup.oval;
		;
		goto R999;

	case 48: // STATE 4
		;
		now.person[ Index(((P0 *)_this)->_pid, 2) ].at_floor = trpt->bup.oval;
		;
		goto R999;

	case 49: // STATE 7
		;
		now.floor_button[ Index(now.person[ Index(((P0 *)_this)->_pid, 2) ].at_floor, 4) ].pushed = trpt->bup.oval;
		;
		goto R999;

	case 50: // STATE 12
		;
		now.person[ Index(((P0 *)_this)->_pid, 2) ].in_elevator = trpt->bup.ovals[1];
		now.person[ Index(((P0 *)_this)->_pid, 2) ].at_floor = trpt->bup.ovals[0];
		;
		ungrab_ints(trpt->bup.ovals, 2);
		goto R999;

	case 51: // STATE 23
		;
		now.cabin_button[ Index(now.person[ Index(((P0 *)_this)->_pid, 2) ].to_floor, 4) ].pushed = trpt->bup.ovals[1];
		now.person[ Index(((P0 *)_this)->_pid, 2) ].to_floor = trpt->bup.ovals[0];
		;
		ungrab_ints(trpt->bup.ovals, 2);
		goto R999;

	case 52: // STATE 23
		;
		now.cabin_button[ Index(now.person[ Index(((P0 *)_this)->_pid, 2) ].to_floor, 4) ].pushed = trpt->bup.ovals[1];
		now.person[ Index(((P0 *)_this)->_pid, 2) ].to_floor = trpt->bup.ovals[0];
		;
		ungrab_ints(trpt->bup.ovals, 2);
		goto R999;

	case 53: // STATE 23
		;
		now.cabin_button[ Index(now.person[ Index(((P0 *)_this)->_pid, 2) ].to_floor, 4) ].pushed = trpt->bup.ovals[1];
		now.person[ Index(((P0 *)_this)->_pid, 2) ].to_floor = trpt->bup.ovals[0];
		;
		ungrab_ints(trpt->bup.ovals, 2);
		goto R999;

	case 54: // STATE 23
		;
		now.cabin_button[ Index(now.person[ Index(((P0 *)_this)->_pid, 2) ].to_floor, 4) ].pushed = trpt->bup.ovals[1];
		now.person[ Index(((P0 *)_this)->_pid, 2) ].to_floor = trpt->bup.ovals[0];
		;
		ungrab_ints(trpt->bup.ovals, 2);
		goto R999;

	case 55: // STATE 23
		;
		now.cabin_button[ Index(now.person[ Index(((P0 *)_this)->_pid, 2) ].to_floor, 4) ].pushed = trpt->bup.oval;
		;
		goto R999;
;
		;
		
	case 57: // STATE 28
		;
		now.person[ Index(((P0 *)_this)->_pid, 2) ].in_elevator = trpt->bup.ovals[2];
		now.person[ Index(((P0 *)_this)->_pid, 2) ].to_floor = trpt->bup.ovals[1];
		now.person[ Index(((P0 *)_this)->_pid, 2) ].at_floor = trpt->bup.ovals[0];
		;
		ungrab_ints(trpt->bup.ovals, 3);
		goto R999;
;
		
	case 58: // STATE 34
		goto R999;

	case 59: // STATE 32
		;
		now.person[ Index(((P0 *)_this)->_pid, 2) ].in_elevator = trpt->bup.ovals[2];
		now.person[ Index(((P0 *)_this)->_pid, 2) ].to_floor = trpt->bup.ovals[1];
		now.person[ Index(((P0 *)_this)->_pid, 2) ].at_floor = trpt->bup.ovals[0];
		;
		ungrab_ints(trpt->bup.ovals, 3);
		goto R999;

	case 60: // STATE 41
		;
		p_restor(II);
		;
		;
		goto R999;
	}

