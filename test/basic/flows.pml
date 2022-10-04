typedef structure {
	bool a;
	bool b;
	bool c;
	bool d
}

structure s;

active proctype I(){

	s.a = true;
	s.b = true;
	
	if
	::	s.a == true;
		do
		::  s.c = false;
		::  s.d = false;
		:: (s.a && !s.c && !s.d) 
			-> break
		od;
		
	::	s.b == true;
		do
		:: s.c = true;
		:: s.d = true;
		:: (s.b && s.c && s.d) 
			-> break
		od;
	fi;
}

active proctype J(){
	do
	::	if
		:: s.a = !s.a
		:: s.b = !s.b
		fi;
		
	:: 	(s.a || s.b) 
		-> break
	od;
}
