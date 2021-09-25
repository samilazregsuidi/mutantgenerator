bool pumpOn = false; 
bool methane = false; 


active proctype controller() {

	do  
	
	:: pumpOn -> 
		pumpOn = false;
	   
	:: !pumpOn -> 
		pumpOn = true;
			
	od;
}

active proctype methanealarm() {

	do	
	
	:: 	methane = false;
			
	::	methane = true;
		
	od;
}
