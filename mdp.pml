active proctype mdp(){
	int s = 0;
	
	do
	:: s == 0 -> 
		ct
		:: s0a0 -> 
			if
			:: s = 0;
			:: s = 2;
			fi;
			
		:: s0a1 -> s = 2;
		tc;
	
	:: s == 2 ->
		ct
		:: s2a0 -> 
			if
			:: [ 0.4 ] s = 0;
			:: [ 0.6 ] s = 2;
			fi;
			
		:: s2a1 ->
			if
			:: [ 0.4 ] s = 2;
			:: [ 0.3 ] s = 0 -> R - 1;
			:: [ 0.3 ] s = 1;
			fi;
		tc;
		
	:: s == 1 -> 
		ct 
		:: s1a0 ->
			if 
			:: [ 0.1 ] s = 1;
			:: [ 0.7 ] s = 0 -> R + 5;
			:: [ 0.2 ] s = 2;
			fi;
			
		:: s1a1 ->
			if 
			:: [ 0.95 ] s = 1;
			:: [ 0.05 ] s = 2;
			fi;
		tc;
	od;
}

bltl prop0 {
	[]_{k < 10} -> (s == 1 && R > 2 || []_{k > 5} s == 0)
}

