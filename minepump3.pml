mtype = {levelMsg, stop, methanestop, alarm, running, commandMsg, start, alarmMsg, high, low, stopped, medium, ready, lowstop}
chan cCmd = [0] of {mtype};
chan cAlarm = [0] of {mtype};
chan cMethane = [0] of {mtype};
chan cLevel = [0] of {mtype};
mtype pstate = stopped;
mtype readMsg = commandMsg;
bool pumpOn = false;
bool methane = false;
mtype waterLevel = medium;
mtype uwants = stop;
active proctype controller(){
	mtype pcommand = start;
	mtype level = medium;
	do
	::	atomic {
			cCmd?pcommand;
			readMsg = commandMsg;
		};
		if
		::	pcommand == stop;
			if
			::	atomic {
					pstate == running;
					pumpOn = false;
					pstate = stopped;
				};
			::	else;
				skip;
			fi;
		::	pcommand == start;
			if
			::	atomic {
					pstate != running;
					pstate = ready;
				};
			::	else;
				break;
			fi;
		fi;
		cCmd!pstate;
	:: else 
		break;
	od;
}
