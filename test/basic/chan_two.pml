chan test = [0] of {byte}

active proctype sender(){
	byte b = 1;
	test!b;
}

active proctype receiver(){
	byte c;
	test?c;
	assert(c == 1);
}
