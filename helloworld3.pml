mtype { up, down }
chan test = [0] of {mtype};

proctype send (){
 test!up;
 }
 
 proctype recv (){
 mtype what;
 test?what;
 }
