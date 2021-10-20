
 proctype test(){
	bool a;
	bool b;
	a = true;
	b = false;
	if
	::	true;
		if
		::	b == true;
			if
			:: atomic { 
				a == true;
				a = false; 
			}
			:: else -> skip;
			fi;
			
		::	else -> skip;
		fi;
		
	::	false;
	
		if
		::	a == true;
		
			if
			:: atomic { 
				b == true;
				b = false;
			}
			:: else -> skip;
			fi;
			
		::	else -> skip;
		fi;
		
	fi;
}

