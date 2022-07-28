#define NB 3
#define NF 4

#define LEFT _pid
#define RIGHT (_pid + 1)%NB

#define THIS _pid

#define FREE 0
#define USED THIS + 1

mtype = {THINKING, HUNGRY, EATING}

mtype state[NB];

byte fork[NF];

byte nr_eat;

active [NB] proctype Philosopher() {
	
Thinking:
	state[THIS] = THINKING;

	if
	:: atomic { 
		fork[LEFT] == FREE;
		fork[LEFT] = USED;
		state[THIS] = HUNGRY;
		
		fork[RIGHT] == FREE;
		fork[RIGHT] = USED;
		
		state[THIS] = EATING;
		nr_eat++;
	};
	
	:: atomic { 
		fork[RIGHT] == FREE;
		fork[RIGHT] = USED;
		state[THIS] = HUNGRY;
		
		fork[LEFT] == FREE;
		fork[LEFT] = USED;
		
		state[THIS] = EATING;
		nr_eat++;
	};
	fi;
	
	atomic {
		fork[RIGHT] = FREE;
		fork[LEFT] = FREE; 
		state[THIS] = THINKING;
		nr_eat--;
		goto Thinking;
	}
}

