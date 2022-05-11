mtype = {READY, RUNNING};
mtype states[2];
mtype commands[2];


inline propagate_command()
{
    commands[0] = READY;
    states[k] = RUNNING;
}

proctype test(){
	byte k;
	k = 1;
	propagate_command();
}
