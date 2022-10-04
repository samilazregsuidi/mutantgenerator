#include "./ltl.inc"
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
				};
			::	else;
				skip;
			fi;
			pstate = stopped;
		::	pcommand == start;
			if
			::	atomic {
					pstate != running;
					pstate = ready;
				};
			::	else;
				skip;
			fi;
		::	else;
			assert((false));
		fi;
		cCmd!pstate;
	::	atomic {
			cAlarm?_;
			readMsg = alarmMsg;
		};
		if
		::	atomic {
				pstate == running;
				pumpOn = false;
			};
		::	else;
			skip;
		fi;
		pstate = methanestop;
	::	atomic {
			cLevel?level;
			readMsg = levelMsg;
		};
		if
		::	level == high;
			if
			::	pstate == ready || pstate == alarmMsg;
				atomic {
					cMethane!pstate;
					cMethane?pstate;
					if
					::	pstate == ready;
						pstate = running;
						pumpOn = true;
					::	else;
						skip;
					fi;
				};
			::	else;
				skip;
			fi;
		::	level == low;
			if
			::	atomic {
					pstate == running;
					pumpOn = false;
					pstate = lowstop;
				};
			::	else;
				skip;
			fi;
		::	level == medium;
			skip;
		fi;
	od;
}
active proctype user(){
	do
	::	if
		::	uwants = start;
		::	uwants = stop;
		fi;
		cCmd!uwants;
		cCmd?_;
	od;
}
active proctype methanealarm(){
	do
	::	methane = true;
		cAlarm!alarm;
	::	methane = false;
	od;
}
active proctype methanesensor(){
	do
	::	atomic {
			cMethane?_;
			if
			::	methane;
				cMethane!methanestop;
			::	!methane;
				cMethane!ready;
			fi;
		};
	od;
}
active proctype watersensor(){
	do
	::	atomic {
			if
			::	waterLevel == low;
				if
				::	waterLevel = low;
				::	waterLevel = medium;
				fi;
			::	waterLevel == medium;
				if
				::	waterLevel = low;
				::	waterLevel = medium;
				::	waterLevel = high;
				fi;
			::	waterLevel == high;
				if
				::	waterLevel = medium;
				::	waterLevel = high;
				fi;
			fi;
			cLevel!waterLevel;
		};
	od;
}
