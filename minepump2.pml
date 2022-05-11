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

active proctype watersensor(){
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
			fi;
			printf("test");
		fi;
		cLevel!waterLevel;
}

/*
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
}*/
