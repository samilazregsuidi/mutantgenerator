active proctype test1 (){
	bool b = false;
	b = (true -> false : true);
	
	assert(b == false);
}

active proctype test2 (){
	int i = 1 ;
	i = (i == 1 -> -1 : 1);
	
	assert(i == -1);
}
