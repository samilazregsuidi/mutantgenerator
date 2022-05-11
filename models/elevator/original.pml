typedef features {
	bool TTFull;
	bool Shuttle;
	bool QuickClose;
	bool Park;
	bool Overload;
	bool OpenIfIdle;
	bool Exec;
	bool Empty;
	bool Elevator;
}

features f;
typedef tPerson {
	bool in_elevator;
	byte to_floor;
	byte at_floor;
}

typedef tButton {
	bool pushed;
}

tPerson person[2];
tButton cabin_button[4];
tButton floor_button[4];
byte floor = 0;
mtype = {stay, up, down, closed, open}
mtype door = closed;
mtype direction = stay;

active [2] proctype ptPersonDetermined(){
	if
	::	person[_pid].at_floor = 0;
	::	person[_pid].at_floor = 1;
	::	person[_pid].at_floor = 2;
	::	person[_pid].at_floor = 3;
	fi;
	do
	::	atomic {
			floor_button[person[_pid].at_floor].pushed = true;
		};
		if
		::	skip;
		::	atomic {
				floor == person[_pid].at_floor && door == open;
				person[_pid].at_floor = 0;
				person[_pid].in_elevator = true;
				if
				::	floor != 0;
					person[_pid].to_floor = 0;
				::	floor != 1;
					person[_pid].to_floor = 1;
				::	floor != 2;
					person[_pid].to_floor = 2;
				::	floor != 3;
					person[_pid].to_floor = 3;
				fi;
				cabin_button[person[_pid].to_floor].pushed = true;
				if
				::	door == closed;
					floor == person[_pid].to_floor && door == open;
					person[_pid].at_floor = floor;
					person[_pid].to_floor = 0;
					person[_pid].in_elevator = false;
				::	timeout;
					person[_pid].at_floor = floor;
					person[_pid].to_floor = 0;
					person[_pid].in_elevator = false;
				fi;
			};
		fi;
	od;
};
bool progress = false;
bool waiting = false;

active proctype controller(){
	bool stop = false;
	do
	::	progress = false;
	::	progress = true;
		if
		::	f.TTFull && f.Exec;
			stop = (((person[0].in_elevator-> 1: 0) + (person[1].in_elevator-> 1: 0)) < 2-> (cabin_button[floor].pushed || floor_button[floor].pushed) && (floor == 3 || !(cabin_button[3].pushed || floor_button[3].pushed)): (cabin_button[3].pushed || floor_button[3].pushed-> floor == 3: cabin_button[floor].pushed || (floor_button[floor].pushed && ((person[0].in_elevator-> 1: 0) + (person[1].in_elevator-> 1: 0)) < 2)));
		::	f.TTFull && !f.Exec;
			stop = cabin_button[floor].pushed || (floor_button[floor].pushed && ((person[0].in_elevator-> 1: 0) + (person[1].in_elevator-> 1: 0)) < 2);
		::	!f.TTFull && f.Exec;
			stop = (cabin_button[floor].pushed || floor_button[floor].pushed) && (floor == 3 || !(cabin_button[3].pushed || floor_button[3].pushed));
		::	else ->
			stop = (cabin_button[floor].pushed || floor_button[floor].pushed);
		fi;
		if
		::	atomic {
				stop;
				stop = false;
				door = open;
				cabin_button[floor].pushed = false;
				floor_button[floor].pushed = false;
				(person[0].to_floor != floor || !person[0].in_elevator) && (person[1].to_floor != floor || !person[1].in_elevator);
			};
			if
			::	!f.QuickClose;
				do
				::	atomic {
						floor_button[floor].pushed || cabin_button[floor].pushed;
						floor_button[floor].pushed = false;
						cabin_button[floor].pushed = false;
						waiting = true;
					};
					waiting = false;
				::	else ->
					break;
				od;
			::	else ->
			fi;
			if
			::	f.OpenIfIdle || f.Park;
				if
				::	atomic {
						floor == 0;
						waiting = true;
					};
					atomic {
						(floor_button[0].pushed || cabin_button[0].pushed || floor_button[1].pushed || cabin_button[1].pushed || floor_button[2].pushed || cabin_button[2].pushed || floor_button[3].pushed || cabin_button[3].pushed);
						waiting = false;
					};
				::	else ->
					if
					::	f.OpenIfIdle;
						waiting = true;
						atomic {
							(floor_button[0].pushed || cabin_button[0].pushed || floor_button[1].pushed || cabin_button[1].pushed || floor_button[2].pushed || cabin_button[2].pushed || floor_button[3].pushed || cabin_button[3].pushed);
							waiting = false;
						};
					::	else ->
					fi;
				fi;
			::	else ->
			fi;
			atomic {
				if
				::	f.Overload;
					((person[0].in_elevator-> 1: 0) + (person[1].in_elevator-> 1: 0)) < 2;
				::	else ->
				fi;
				cabin_button[floor].pushed = false;
				floor_button[floor].pushed = false;
				if
				::	f.Empty;
					if
					::	(person[0].in_elevator == false && person[1].in_elevator == false);
						cabin_button[0].pushed = false;
						cabin_button[1].pushed = false;
						cabin_button[2].pushed = false;
						cabin_button[3].pushed = false;
					::	else ->
					fi;
				::	else ->
				fi;
				door = closed;
			};
		::	else ->
			skip;
		fi;
		atomic {
			bool set = false;
			if
			::	f.Shuttle;
				direction = (floor == 0-> up: (floor == 4 - 1-> down: direction));
				set = true;
			::	else ->
			fi;
			if
			::	f.Exec;
				if
				::	!set && (cabin_button[3].pushed || floor_button[3].pushed);
					direction = (3 < floor-> down: (3 > floor-> up: stay));
					set = true;
				::	else ->
				fi;
			::	else ->
			fi;
			if
			::	f.Park;
				if
				::	!set && !(floor_button[0].pushed || cabin_button[0].pushed || floor_button[1].pushed || cabin_button[1].pushed || floor_button[2].pushed || cabin_button[2].pushed || floor_button[3].pushed || cabin_button[3].pushed);
					direction = (0 < floor-> down: (0 > floor-> up: stay));
					set = true;
				::	else ->
				fi;
			::	else ->
			fi;
			if
			::	set;
				set = false;
			::	else ->
				direction = (floor == 0-> up: (floor == 4 - 1-> down: direction));
				direction = (((floor > 0 && (floor_button[0].pushed || cabin_button[0].pushed)) || (floor > 1 && (floor_button[1].pushed || cabin_button[1].pushed)) || (floor > 2 && (floor_button[2].pushed || cabin_button[2].pushed)) || (floor > 3 && (floor_button[3].pushed || cabin_button[3].pushed))) && direction == down-> down: (((floor < 0 && (floor_button[0].pushed || cabin_button[0].pushed)) || (floor < 1 && (floor_button[1].pushed || cabin_button[1].pushed)) || (floor < 2 && (floor_button[2].pushed || cabin_button[2].pushed)) || (floor < 3 && (floor_button[3].pushed || cabin_button[3].pushed))) && direction == up-> up: (((floor > 0 && (floor_button[0].pushed || cabin_button[0].pushed)) || (floor > 1 && (floor_button[1].pushed || cabin_button[1].pushed)) || (floor > 2 && (floor_button[2].pushed || cabin_button[2].pushed)) || (floor > 3 && (floor_button[3].pushed || cabin_button[3].pushed)))-> down: (((floor < 0 && (floor_button[0].pushed || cabin_button[0].pushed)) || (floor < 1 && (floor_button[1].pushed || cabin_button[1].pushed)) || (floor < 2 && (floor_button[2].pushed || cabin_button[2].pushed)) || (floor < 3 && (floor_button[3].pushed || cabin_button[3].pushed)))-> up: stay))));
			fi;
			floor = (direction == up-> floor + 1: (direction == down-> floor - 1: floor));
		};
	od;
};
