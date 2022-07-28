int array[8];

active [4] proctype test (){
	array[0] = 890;
	array[1] = 67;
	array[2] = 23;
	array[3] = 8620;
	
	array[4] = 378;
	array[5] = 264;
	array[6] = 983;
	array[7] = 2344;
	
	do
	:: _pid > 0 ->
		array[_pid - 1] > array[_pid];
		array[_pid - 1] 
	
}

init {

	array[0] = 890;
	array[1] = 67;
	array[2] = 23;
	array[3] = 8620;
	
	array[4] = 378;
	array[5] = 264;
	array[6] = 983;
	array[7] = 2344;
	
}
