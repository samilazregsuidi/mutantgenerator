int array[4];
active proctype test(){
	int i = 0;
	do
	::	i < 4;
		array[i] = i;
		i++;
	::	else;
		break;
	od;
	assert(array[0] == 0 && array[1] == 1 && array[2] == 2 && array[3] == 3);
}
