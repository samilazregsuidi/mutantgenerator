bool pumpOn = true;
bool methane = false;

active proctype controller() {

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
