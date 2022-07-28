typedef features {
	bool Start = 1;
	bool Stop = 1;
	bool MethaneAlarm = 1;
	bool MethaneQuery = 1;
	bool Low = 0;
	bool Normal = 0;
	bool High = 1
}

features f;

active proctype test (){
	assert(f.Start && f.Stop && f.MethaneAlarm && f.MethaneQuery && !f.Low && f.Normal == false && f.High == true);
}
