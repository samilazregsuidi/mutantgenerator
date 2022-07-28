typedef features {
	bool Start = 1;
	bool Stop = 1
}

features f;

mtype = {stop, start, alarm, low, medium, high, ready, running, stopped, methanestop, lowstop, commandMsg, alarmMsg, levelMsg}

chan cCmd = [0] of {mtype}; 	/* stop, start			*/

mtype pstate = stopped; 		/* ready, running, stopped, methanestop, lowstop */

mtype uwants = stop; 			/* what the user wants */

active proctype controller() {
	mtype pcommand = start;
	mtype level = medium;
	
	do	::	atomic {
				cCmd?pcommand;
			};
			if	::	pcommand == stop;
					if	::	f.Stop;
							if	::	atomic {
										pstate == running;
									}
								::	else -> skip;
								fi;
							pstate = stopped;
						::	else -> skip;
						fi;
				::	pcommand == start;
					if	::	f.Start;
							if	::	atomic {
										pstate != running;
										pstate = ready;
									};
								::	else -> skip;
								fi;
						::	else -> skip;
						fi;
				::	else -> assert(false);
				fi;
			cCmd!pstate;
			
		od;
}

active proctype user() {
	do	::	if	::	uwants = start;
				::	uwants = stop;
				fi;
			cCmd!uwants;
			cCmd?_;			/* Sends back the state; ignore it */
		od;
}
