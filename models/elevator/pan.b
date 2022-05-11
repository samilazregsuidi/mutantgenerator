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
		;
		;
		;
		;
		;
		;
		;
		;
		
	case 17: // STATE 54
		;
		p_restor(II);
		;
		;
		goto R999;

		 /* PROC controller */

	case 18: // STATE 1
		;
		now.progress = trpt->bup.oval;
		;
		goto R999;

	case 19: // STATE 2
		;
		now.progress = trpt->bup.oval;
		;
		goto R999;
;
		;
		
	case 21: // STATE 4
		;
		((P1 *)_this)->stop = trpt->bup.oval;
		;
		goto R999;
;
		;
		
	case 23: // STATE 6
		;
		((P1 *)_this)->stop = trpt->bup.oval;
		;
		goto R999;
;
		;
		
	case 25: // STATE 8
		;
		((P1 *)_this)->stop = trpt->bup.oval;
		;
		goto R999;

	case 26: // STATE 10
		;
		((P1 *)_this)->stop = trpt->bup.oval;
		;
		goto R999;

	case 27: // STATE 17
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
		
	case 30: // STATE 24
		;
		waiting = trpt->bup.ovals[2];
		now.cabin_button[ Index(now.floor, 4) ].pushed = trpt->bup.ovals[1];
		now.floor_button[ Index(now.floor, 4) ].pushed = trpt->bup.ovals[0];
		;
		ungrab_ints(trpt->bup.ovals, 3);
		goto R999;

	case 31: // STATE 26
		;
		waiting = trpt->bup.oval;
		;
		goto R999;
;
		;
		
	case 33: // STATE 37
		;
		waiting = trpt->bup.oval;
		;
		goto R999;

	case 34: // STATE 40
		;
		waiting = trpt->bup.oval;
		;
		goto R999;
;
		;
		
	case 36: // STATE 44
		;
		waiting = trpt->bup.oval;
		;
		goto R999;

	case 37: // STATE 46
		;
		waiting = trpt->bup.oval;
		;
		goto R999;
;
		;
		
	case 39: // STATE 62
		;
		now.floor_button[ Index(now.floor, 4) ].pushed = trpt->bup.ovals[1];
		now.cabin_button[ Index(now.floor, 4) ].pushed = trpt->bup.ovals[0];
		;
		ungrab_ints(trpt->bup.ovals, 2);
		goto R999;

	case 40: // STATE 62
		;
		now.floor_button[ Index(now.floor, 4) ].pushed = trpt->bup.ovals[1];
		now.cabin_button[ Index(now.floor, 4) ].pushed = trpt->bup.ovals[0];
		;
		ungrab_ints(trpt->bup.ovals, 2);
		goto R999;
;
		;
		
	case 42: // STATE 75
		;
		now.door = trpt->bup.ovals[4];
		now.cabin_button[3].pushed = trpt->bup.ovals[3];
		now.cabin_button[2].pushed = trpt->bup.ovals[2];
		now.cabin_button[1].pushed = trpt->bup.ovals[1];
		now.cabin_button[0].pushed = trpt->bup.ovals[0];
		;
		ungrab_ints(trpt->bup.ovals, 5);
		goto R999;

	case 43: // STATE 75
		;
		now.door = trpt->bup.oval;
		;
		goto R999;

	case 44: // STATE 81
		;
		((P1 *)_this)->_6_9_set = trpt->bup.oval;
		;
		goto R999;

	case 45: // STATE 84
		;
		((P1 *)_this)->_6_9_set = trpt->bup.ovals[1];
		now.direction = trpt->bup.ovals[0];
		;
		ungrab_ints(trpt->bup.ovals, 2);
		goto R999;
;
		;
		
	case 47: // STATE 91
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
		
	case 49: // STATE 101
		;
		((P1 *)_this)->_6_9_set = trpt->bup.ovals[2];
		now.direction = trpt->bup.ovals[1];
	/* 0 */	((P1 *)_this)->_6_9_set = trpt->bup.ovals[0];
		;
		;
		ungrab_ints(trpt->bup.ovals, 3);
		goto R999;

	case 50: // STATE 115
		;
		now.floor = trpt->bup.ovals[2];
		((P1 *)_this)->_6_9_set = trpt->bup.ovals[1];
	/* 0 */	((P1 *)_this)->_6_9_set = trpt->bup.ovals[0];
		;
		;
		ungrab_ints(trpt->bup.ovals, 3);
		goto R999;

	case 51: // STATE 115
		;
		now.floor = trpt->bup.oval;
		;
		goto R999;

	case 52: // STATE 115
		;
		now.floor = trpt->bup.ovals[2];
		now.direction = trpt->bup.ovals[1];
		now.direction = trpt->bup.ovals[0];
		;
		ungrab_ints(trpt->bup.ovals, 3);
		goto R999;

	case 53: // STATE 120
		;
		p_restor(II);
		;
		;
		goto R999;

		 /* PROC ptPersonDetermined */

	case 54: // STATE 1
		;
		now.person[ Index(((P0 *)_this)->_pid, 2) ].at_floor = trpt->bup.oval;
		;
		goto R999;

	case 55: // STATE 2
		;
		now.person[ Index(((P0 *)_this)->_pid, 2) ].at_floor = trpt->bup.oval;
		;
		goto R999;

	case 56: // STATE 3
		;
		now.person[ Index(((P0 *)_this)->_pid, 2) ].at_floor = trpt->bup.oval;
		;
		goto R999;

	case 57: // STATE 4
		;
		now.person[ Index(((P0 *)_this)->_pid, 2) ].at_floor = trpt->bup.oval;
		;
		goto R999;

	case 58: // STATE 7
		;
		now.floor_button[ Index(now.person[ Index(((P0 *)_this)->_pid, 2) ].at_floor, 4) ].pushed = trpt->bup.oval;
		;
		goto R999;

	case 59: // STATE 12
		;
		now.person[ Index(((P0 *)_this)->_pid, 2) ].in_elevator = trpt->bup.ovals[1];
		now.person[ Index(((P0 *)_this)->_pid, 2) ].at_floor = trpt->bup.ovals[0];
		;
		ungrab_ints(trpt->bup.ovals, 2);
		goto R999;

	case 60: // STATE 23
		;
		now.cabin_button[ Index(now.person[ Index(((P0 *)_this)->_pid, 2) ].to_floor, 4) ].pushed = trpt->bup.ovals[1];
		now.person[ Index(((P0 *)_this)->_pid, 2) ].to_floor = trpt->bup.ovals[0];
		;
		ungrab_ints(trpt->bup.ovals, 2);
		goto R999;

	case 61: // STATE 23
		;
		now.cabin_button[ Index(now.person[ Index(((P0 *)_this)->_pid, 2) ].to_floor, 4) ].pushed = trpt->bup.ovals[1];
		now.person[ Index(((P0 *)_this)->_pid, 2) ].to_floor = trpt->bup.ovals[0];
		;
		ungrab_ints(trpt->bup.ovals, 2);
		goto R999;

	case 62: // STATE 23
		;
		now.cabin_button[ Index(now.person[ Index(((P0 *)_this)->_pid, 2) ].to_floor, 4) ].pushed = trpt->bup.ovals[1];
		now.person[ Index(((P0 *)_this)->_pid, 2) ].to_floor = trpt->bup.ovals[0];
		;
		ungrab_ints(trpt->bup.ovals, 2);
		goto R999;

	case 63: // STATE 23
		;
		now.cabin_button[ Index(now.person[ Index(((P0 *)_this)->_pid, 2) ].to_floor, 4) ].pushed = trpt->bup.ovals[1];
		now.person[ Index(((P0 *)_this)->_pid, 2) ].to_floor = trpt->bup.ovals[0];
		;
		ungrab_ints(trpt->bup.ovals, 2);
		goto R999;

	case 64: // STATE 23
		;
		now.cabin_button[ Index(now.person[ Index(((P0 *)_this)->_pid, 2) ].to_floor, 4) ].pushed = trpt->bup.oval;
		;
		goto R999;
;
		;
		
	case 66: // STATE 28
		;
		now.person[ Index(((P0 *)_this)->_pid, 2) ].in_elevator = trpt->bup.ovals[2];
		now.person[ Index(((P0 *)_this)->_pid, 2) ].to_floor = trpt->bup.ovals[1];
		now.person[ Index(((P0 *)_this)->_pid, 2) ].at_floor = trpt->bup.ovals[0];
		;
		ungrab_ints(trpt->bup.ovals, 3);
		goto R999;
;
		
	case 67: // STATE 34
		goto R999;

	case 68: // STATE 32
		;
		now.person[ Index(((P0 *)_this)->_pid, 2) ].in_elevator = trpt->bup.ovals[2];
		now.person[ Index(((P0 *)_this)->_pid, 2) ].to_floor = trpt->bup.ovals[1];
		now.person[ Index(((P0 *)_this)->_pid, 2) ].at_floor = trpt->bup.ovals[0];
		;
		ungrab_ints(trpt->bup.ovals, 3);
		goto R999;

	case 69: // STATE 41
		;
		p_restor(II);
		;
		;
		goto R999;
	}

