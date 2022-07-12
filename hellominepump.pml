bool pumpOn = true;
bool methane = false;

active proctype controller() {

	int test = 21;
	bool b = true;

	do  
	
	:: pumpOn -> 
		pumpOn = false;
	   
	:: !pumpOn -> 
		pumpOn = true;
			
	od;
	
	do	
	
	:: 	methane = false;
			
	::	methane = true;
		
	od;
}
