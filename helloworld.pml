active proctype test_a(){
	byte a;
	
	if
	:: [0.6] a = 1;
	:: [0.4] a = 2;
	fi;
}

active proctype test_b(){
	byte b;
	
	if
	:: [0.3] b = 1;
	:: [0.7] b = 2;
	fi;
}
