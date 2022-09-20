#include "./ltl.inc"
active proctype test_a(){
	byte a;
	if
	::	a = 1;
	::	a = 2;
	fi;
}
active proctype test_b(){
	byte b;
	if
	::	b = 1;
	::	b = 2;
	fi;
}
