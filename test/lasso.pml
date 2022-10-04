active proctype test (){
	
	byte s = 1;
	
	do
	:: s == 1 -> s = 2;
	:: s == 1 -> s = 3;
	:: s == 3 -> s = 4;
	:: s == 3 -> s = 6;
	:: s == 3 -> s = 7;
	:: s == 4 -> s = 5;
	:: s == 5 -> s = 3;
	:: s == 6 -> s = 5;
	:: s == 7 -> s = 8;
	:: s == 8 -> s = 7; 
	od;
}

