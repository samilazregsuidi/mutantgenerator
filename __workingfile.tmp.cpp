# 1 "__workingfile.tmp"
# 1 "<built-in>"
# 1 "<command-line>"
# 31 "<command-line>"
# 1 "/usr/include/stdc-predef.h" 1 3 4
# 32 "<command-line>" 2
# 1 "__workingfile.tmp"
mtype = {alarm}

chan cAlarm = [0] of {mtype};

bool pumpOn = false;
bool methane = false;


active proctype controller() {

 do

 :: atomic { cAlarm?_;
    pumpOn = false; };

 :: pumpOn = true;

 od;
}

active proctype methanealarm() {

 do

 :: atomic { methane = false;
  cAlarm!alarm; };

 :: methane = true;

 od;
}
