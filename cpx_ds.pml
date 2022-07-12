typedef S {
	byte b[2];
	bool c
}

typedef C {
	int a;
	S s[2]
}

active proctype test (){
	C cpx[2];
	int i = 9;
	i = 2;
	
	cpx[0].s[0].c = true;
	cpx[0].s[1].c = false;
	cpx[1].s[0].c = true;
	cpx[1].s[1].c = true;
	
	
	cpx[0].s[0].b[0] = 1;
	cpx[0].s[0].b[1] = 1;
	cpx[0].s[1].b[0] = 1;
	cpx[0].s[1].b[1] = 1;
	cpx[1].s[0].b[0] = 1;
	cpx[1].s[0].b[1] = 1;
	cpx[1].s[1].b[0] = 1;
	cpx[1].s[1].b[1] = 1;
 }
