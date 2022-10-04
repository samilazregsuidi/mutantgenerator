chan test = [0] of {byte}

active proctype sender(){
	test!1;
}

active proctype receiver(){
	byte c;
	test?c;
	assert(c == 1);
}
