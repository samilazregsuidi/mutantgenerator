mtype = {ON, OFF}

chan test = [0] of {mtype}

active proctype sender(){
	mtype t = ON;
	test!t;
}

active proctype receiver(){
	mtype c;
	test?c;
	assert(c == ON);
}
