typedef object {
	bool a;
	bool b
}

object mine;

proctype test(){
	
	if
	:: mine.a != true 	-> mine.a = true;
	:: mine.b != false 	-> mine.b = false;
	fi;
}

//11
