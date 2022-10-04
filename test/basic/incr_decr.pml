active proctype I (){
	int i = 0;
	byte b = 1;
	i++;
	b++;
	assert(i == 1 && b == 2);
	i--;
	b--;
	assert(i == 0 && b == 1);	
}
