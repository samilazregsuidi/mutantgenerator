proctype test(){
	bool a;
	bool b;
	
	a = true;
	b = false;
	
	if
	:: a != true 	-> a = true;
	:: b != false 	-> b = false;
	fi;
}

//11
