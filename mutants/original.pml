#include "./ltl.inc"
active proctype test(){
	int i = 0;
	if
	::	i == 0;
		i = 1;
	::	else;
		i = 0;
	fi;
}
