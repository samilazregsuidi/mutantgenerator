	switch (t->back) {
	default: Uerror("bad return move");
	case  0: goto R999; /* nothing to undo */

		 /* CLAIM never_0 */
;
		;
		;
		;
		
	case 5: // STATE 13
		;
		p_restor(II);
		;
		;
		goto R999;

		 /* PROC Source */

	case 6: // STATE 1
		;
		_m = unsend(now.source);
		;
		goto R999;

	case 7: // STATE 2
		;
		_m = unsend(now.source);
		;
		goto R999;

	case 8: // STATE 7
		;
		_m = unsend(now.source);
		;
		goto R999;

	case 9: // STATE 8
		;
		_m = unsend(now.source);
		;
		goto R999;

	case 10: // STATE 13
		;
		_m = unsend(now.source);
		;
		goto R999;

	case 11: // STATE 17
		;
		p_restor(II);
		;
		;
		goto R999;

		 /* PROC p5 */
	case 12: // STATE 3
		sv_restor();
		goto R999;

	case 13: // STATE 5
		;
		((P0 *)_this)->nbuf = trpt->bup.oval;
		;
		goto R999;
;
		;
		
	case 15: // STATE 11
		;
		((P0 *)_this)->frames[ Index(((P0 *)_this)->NextFrame, 4) ] = trpt->bup.ovals[1];
		XX = 1;
		unrecv(now.source, XX-1, 0, ((P0 *)_this)->ball, 1);
		((P0 *)_this)->ball = trpt->bup.ovals[0];
		;
		;
		ungrab_ints(trpt->bup.ovals, 2);
		goto R999;

	case 16: // STATE 11
		;
		((P0 *)_this)->frames[ Index(((P0 *)_this)->NextFrame, 4) ] = trpt->bup.oval;
		;
		goto R999;

	case 17: // STATE 12
		;
		_m = unsend(((P0 *)_this)->out);
		;
		goto R999;

	case 18: // STATE 18
		;
		((P0 *)_this)->NextFrame = trpt->bup.ovals[1];
		now.sent = trpt->bup.ovals[0];
		;
		ungrab_ints(trpt->bup.ovals, 2);
		goto R999;

	case 19: // STATE 18
		;
		((P0 *)_this)->NextFrame = trpt->bup.oval;
		;
		goto R999;

	case 20: // STATE 20
		;
		XX = 1;
		unrecv(((P0 *)_this)->in, XX-1, 0, ((P0 *)_this)->ball, 1);
		unrecv(((P0 *)_this)->in, XX-1, 1, ((int)((P0 *)_this)->r), 0);
		unrecv(((P0 *)_this)->in, XX-1, 2, ((int)((P0 *)_this)->s), 0);
		((P0 *)_this)->ball = trpt->bup.ovals[0];
		((P0 *)_this)->r = trpt->bup.ovals[1];
		((P0 *)_this)->s = trpt->bup.ovals[2];
		;
		;
		ungrab_ints(trpt->bup.ovals, 3);
		goto R999;

	case 21: // STATE 21
		;
	/* 0 */	((P0 *)_this)->r = trpt->bup.oval;
		;
		;
		goto R999;

	case 22: // STATE 27
		;
		((P0 *)_this)->FrameExp = trpt->bup.oval;
		;
		goto R999;

	case 23: // STATE 27
		;
		((P0 *)_this)->FrameExp = trpt->bup.ovals[1];
		now.rcvd = trpt->bup.ovals[0];
		;
		ungrab_ints(trpt->bup.ovals, 2);
		goto R999;

	case 24: // STATE 27
		;
		((P0 *)_this)->FrameExp = trpt->bup.oval;
		;
		goto R999;
;
		
	case 25: // STATE 30
		goto R999;
	case 26: // STATE 41
		sv_restor();
		goto R999;
;
		;
			case 28: // STATE 60
		sv_restor();
		goto R999;

	case 29: // STATE 64
		;
		p_restor(II);
		;
		;
		goto R999;
	}

