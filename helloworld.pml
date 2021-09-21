proctype test() {
	bool a;
	bool b = false;
	bool c = true;
	c = a;
	bool d;
	
	atomic {
		d = true || false;
		printf("si ginialll!!!");
	};
}
