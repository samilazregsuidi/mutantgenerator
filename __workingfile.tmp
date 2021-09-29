mtype = {stop, start, alarm, low, medium, high, ready, running, stopped, methanestop, lowstop, commandMsg, alarmMsg, levelMsg} 

chan cCmd = [0] of {mtype};  	/* stop, start			*/
chan cAlarm = [0] of {mtype}; 	/* alarm                */
chan cMethane = [0] of {mtype};  /* methanestop, ready   */
chan cLevel = [0] of {mtype}; 	/* low, medium, high    */

mtype pstate = stopped; 		/* ready, running, stopped, methanestop, lowstop */
mtype readMsg = commandMsg;		/* commandMsg, alarmMsg, levelMsg */

bool pumpOn = false; 
bool methane = false; 
mtype waterLevel = medium; 

mtype uwants = stop; 			/* what the user wants */


active proctype controller() {
	mtype pcommand = start;
	mtype level = medium;
	
	do	::	atomic {
				cCmd?pcommand;
				readMsg = commandMsg; 
			};
			if	::	pcommand == stop;
			
					if :: atomic {
						pstate == running;
						pumpOn = false;
						pstate = stopped;
					}  :: else -> skip;
					fi;
						
				::	pcommand == start;
					
					if :: atomic {
						pstate != running;
						pstate = ready;
					}; :: else -> skip;
					fi;
								
				fi;
			cCmd!pstate;
			
		::	atomic { 
				cAlarm?_;
				readMsg = alarmMsg;
			};
			
			if :: atomic {
				pstate == running;
				pumpOn = false;
				pstate = methanestop;
			}; :: else -> skip;
			fi;
			
		::	atomic { 
				cLevel?level;
				readMsg = levelMsg;
			};
			if	::	level == high;
					
							if	::	pstate == ready  ||  pstate == lowstop;
									
								if :: atomic {
									cMethane!pstate;
									cMethane?pstate;
									if	::	pstate == ready;
											pstate = running;
											pumpOn = true;
										::	else -> skip;
									fi;
								}; :: else -> skip;
								fi;
										
								::	else -> skip;
								fi;
							
				::	level == low;
				
					if :: atomic {
						pstate == running;
						pumpOn = false;
						pstate = lowstop;
					}; :: else -> skip;
					fi;
						
				::	level == medium;
					skip;
				fi;
		od;
}

active proctype methanealarm() {
	do	:: 	methane = true;
			cAlarm!alarm;
		::	methane = false;
		od;
}

active proctype methanesensor() {
	do	:: 	atomic {
				cMethane?_;
				if	::	methane;
						cMethane!methanestop;
					::	!methane;
						cMethane!ready;
					fi;
			};
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

active proctype watersensor() {
	do	:: 	atomic {
				if	::	waterLevel == low ->
						if	:: waterLevel = low;
							:: waterLevel = medium;
							fi;
					::	waterLevel == medium ->
						if	:: waterLevel = low;
							:: waterLevel = medium;
							:: waterLevel = high;
							fi;
					::	waterLevel == high ->
						if	:: waterLevel = medium;
							:: waterLevel = high;
							fi;
					fi;
				cLevel!waterLevel;
			};
		od;
};


