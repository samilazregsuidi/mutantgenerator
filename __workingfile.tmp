mtype = {alarm} 

chan cAlarm = [0] of {mtype}; 	/* alarm                */

bool pumpOn = false; 
bool methane = false; 


active proctype controller() {

	do  
	
	:: atomic { cAlarm?_;
	   pumpOn = false; };
	   
	:: pumpOn = true;
			
	od;
}

active proctype methanealarm() {

	do	
	
	:: 	atomic { methane = false;
		cAlarm!alarm; };
			
	::	methane = true;
		
	od;
}
