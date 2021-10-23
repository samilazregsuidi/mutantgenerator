# 1 "__workingfile.tmp"
# 1 "<built-in>"
# 1 "<command-line>"
# 31 "<command-line>"
# 1 "/usr/include/stdc-predef.h" 1 3 4
# 32 "<command-line>" 2
# 1 "__workingfile.tmp"
proctype test(){
 bool a;

 a = true;

 if
 :: a != true -> a = true;
 :: a != false -> a = false;
 fi;
}
