int a = -1;
int b = 1;
	
active proctype I (){
	do
	:: a > b -> b++;
	:: a < b -> a++;
	:: a == b -> break; 
	od;
}

active proctype J (){
	atomic {
		(a == b);
		assert(a == b);
		}
}

