mtype = {READY, STARTING, RUNNING, PAUSED, STOPPING, STOPPED, ABORTING, ABORTED, START, CONTINUE, PAUSE, STOP, ABORT};
mtype states[2];
mtype commands[2];


inline propagate_command(command)
{
    commands = READY;
}

inline abort(i)
{
    assert(_pid != 1);
    atomic { 
    	    if :: true;
		if 
		:: ABORT == START -> propagate_command(commands[0]);
		:: true ;
			if
			:: ABORT == PAUSE -> propagate_command(commands[1]);
			:: else -> skip;
			fi; 
		fi 
	      :: else -> propagate_command(commands[1]);
	      fi;
	};
	
}

proctype test(){
	abort(1);
}
