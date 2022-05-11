mtype = {stop, start, alarm, low, medium, high, ready, running, stopped, methanestop, lowstop, commandMsg, alarmMsg, levelMsg} 

mtype pstate = stopped; 		/* ready, running, stopped, methanestop, lowstop */
bool pumpOn = false; 


active proctype controller() {
	mtype pcommand = start;
	
	if	
	::	
		
		if	
		::	pcommand == stop;
		
			if 
			::
					pstate == running;
					pumpOn = false;
					pstate = stopped;
				
			::	else -> skip;
			fi;
						
		::	pcommand == start;
					
			if 
			::
					pstate != running;
					pstate = ready;
				
			::	else -> skip;
			fi;
								
		fi;
		
	fi;
}

