active proctype test () {
	int i;

begin:
	skip;
	if
	:: i == 0 -> 
		i++;
		goto begin;
	:: true -> skip;
	:: else -> skip;
	fi;
}
