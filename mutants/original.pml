#include "./ltl.inc"
typedef data {
	int a;
	int b;
	bool c;
}

proctype test(){
	data d;
	d.a = 0;
	d.b = d.b;
}
