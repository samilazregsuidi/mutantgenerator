#include "./Theory.prp"
mtype = {READY, STARTING, RUNNING, PAUSED, START, CONTINUE, STOPPING, PAUSE, STOPPED, ABORTING, ABORTED, STOP, ABORT}
mtype states[3];
mtype commands[3];
bool executing[3];
inline abort(i){
	atomic {
		if
		::	ABORT == START && commands[i] == CONTINUE;
			assert((states[i] == READY));
			commands[i] = START;
		::	ABORT == PAUSE && commands[i] == CONTINUE;
			assert((states[i] == STARTING || states[i] == RUNNING));
			commands[i] = PAUSE;
		::	ABORT == CONTINUE && (commands[i] == START || commands[i] == PAUSE);
			assert((states[i] == STARTING || states[i] == PAUSED));
			commands[i] = CONTINUE;
		::	ABORT == STOP && (commands[i] == CONTINUE || commands[i] == PAUSE);
			assert((states[i] == STARTING || states[i] == RUNNING || states[i] == PAUSED));
			commands[i] = STOP;
		::	ABORT == ABORT;
			assert((states[i] != READY));
			commands[i] = ABORT;
		::	else;
			skip;
		fi;
	};
}
inline prepare(i){
	if
	::	true;
		abort(i)
	::	true;
		atomic {
			if
			::	PAUSE == START && commands[i] == CONTINUE;
				assert((states[i] == READY));
				commands[i] = START;
			::	PAUSE == PAUSE && commands[i] == CONTINUE;
				assert((states[i] == STARTING || states[i] == RUNNING));
				commands[i] = PAUSE;
			::	PAUSE == CONTINUE && (commands[i] == START || commands[i] == PAUSE);
				assert((states[i] == STARTING || states[i] == PAUSED));
				commands[i] = CONTINUE;
			::	PAUSE == STOP && (commands[i] == CONTINUE || commands[i] == PAUSE);
				assert((states[i] == STARTING || states[i] == RUNNING || states[i] == PAUSED));
				commands[i] = STOP;
			::	PAUSE == ABORT;
				assert((states[i] != READY));
				commands[i] = ABORT;
			::	else;
				skip;
			fi;
		};
	::	true;
		atomic {
			if
			::	STOP == START && commands[i] == CONTINUE;
				assert((states[i] == READY));
				commands[i] = START;
			::	STOP == PAUSE && commands[i] == CONTINUE;
				assert((states[i] == STARTING || states[i] == RUNNING));
				commands[i] = PAUSE;
			::	STOP == CONTINUE && (commands[i] == START || commands[i] == PAUSE);
				assert((states[i] == STARTING || states[i] == PAUSED));
				commands[i] = CONTINUE;
			::	STOP == STOP && (commands[i] != CONTINUE || commands[i] == PAUSE);
				assert((states[i] == STARTING || states[i] == RUNNING || states[i] == PAUSED));
				commands[i] = STOP;
			::	STOP == ABORT;
				assert((states[i] != READY));
				commands[i] = ABORT;
			::	else;
				skip;
			fi;
		};
	::	true;
		skip;
	fi;
}
inline execute(i){
	executing[i] = true;
	if
	::	true;
		abort(i)
	::	true;
		atomic {
			if
			::	STOP == START && commands[i] == CONTINUE;
				assert((states[i] == READY));
				commands[i] = START;
			::	STOP == PAUSE && commands[i] == CONTINUE;
				assert((states[i] == STARTING || states[i] == RUNNING));
				commands[i] = PAUSE;
			::	STOP == CONTINUE && (commands[i] == START || commands[i] == PAUSE);
				assert((states[i] == STARTING || states[i] == PAUSED));
				commands[i] = CONTINUE;
			::	STOP == STOP && (commands[i] == CONTINUE || commands[i] == PAUSE);
				assert((states[i] == STARTING || states[i] == RUNNING || states[i] == PAUSED));
				commands[i] = STOP;
			::	STOP == ABORT;
				assert((states[i] != READY));
				commands[i] = ABORT;
			::	else;
				skip;
			fi;
		};
	::	true;
		skip;
	fi;
	executing[i] = false;
}
inline finish(i){
	if
	::	true;
		abort(i)
	::	true;
		skip;
	fi;
}
inline ctor(i){
	d_step {
		states[i] = READY;
		commands[i] = CONTINUE;
	};
}
inline dtor(i){
	d_step {
		states[i] = 0;
		commands[i] = 0;
		executing[i] = false;
	};
}
inline trans_cb(s){
	skip;
}
inline covariant_transition(state, command, next){
	states[k] = next;
}
inline contravariant_transition(state, command, next){
	states[k] = next;
}
proctype Thread(byte k){
	commands[k] == START;
	covariant_transition(READY, START, STARTING)
	atomic {
		if
		::	CONTINUE == START && commands[k] == CONTINUE;
			assert((states[k] == READY));
			commands[k] = START;
		::	CONTINUE == PAUSE && commands[k] == CONTINUE;
			assert((states[k] == STARTING || states[k] == RUNNING));
			commands[k] = PAUSE;
		::	CONTINUE == CONTINUE && (commands[k] == START || commands[k] == PAUSE);
			assert((states[k] == STARTING || states[k] == PAUSED));
			commands[k] = CONTINUE;
		::	CONTINUE == STOP && (commands[k] == CONTINUE || commands[k] == PAUSE);
			assert((states[k] == STARTING || states[k] == RUNNING || states[k] == PAUSED));
			commands[k] = STOP;
		::	CONTINUE == ABORT;
			assert((states[k] != READY));
			commands[k] = ABORT;
		::	else;
			skip;
		fi;
	};
	prepare(k)
	do
	::	commands[k] == CONTINUE;
		assert((states[k] == STARTING || states[k] == RUNNING || states[k] == PAUSED));
		if
		::	states[k] == STARTING;
			covariant_transition(STARTING, CONTINUE, RUNNING)
		::	states[k] == PAUSED;
			covariant_transition(PAUSED, CONTINUE, RUNNING)
		::	else;
			skip;
		fi;
		execute(k)
	::	commands[k] == PAUSE;
		if
		::	states[k] == PAUSED;
			commands[k] != PAUSED;
		::	else;
			assert((states[k] == STARTING || states[k] == RUNNING || states[k] == STARTING));
			if
			::	states[k] == STARTING || states[k] == RUNNING;
				contravariant_transition(RUNNING, PAUSE, PAUSED)
			::	else;
				skip;
			fi;
		fi;
	::	commands[k] == STOP || commands[k] == ABORT;
		break;
	od;
	if
	::	commands[k] == STOP;
		assert((states[k] == STARTING || states[k] == RUNNING || states[k] == PAUSED));
		covariant_transition(states[k], STOP, STOPPING)
		finish(k)
		contravariant_transition(STOPPING, STOP, STOPPED)
	::	commands[k] == ABORT;
		assert((states[k] == STARTING || states[k] == RUNNING || states[k] == STOPPING));
		covariant_transition(states[k], ABORT, ABORTING)
		contravariant_transition(ABORTING, ABORT, ABORTED)
	::	else;
		assert((false));
	fi;
}
inline waiit_for_START_mask(i){
	states[i] == RUNNING || states[i] == PAUSED || states[i] == STOPPING || states[i] == STOPPED || states[i] == ABORTING || states[i] == ABORTED;
}
inline waiit_for_PAUSE_mask(i){
	states[i] == PAUSED || states[i] == STOPPING || states[i] == STOPPED || states[i] == ABORTING || states[i] == ABORTED;
}
inline waiit_for_RESUME_mask(i){
	states[i] == RUNNING || states[i] == STOPPING || states[i] == STOPPED || states[i] == ABORTING || states[i] == ABORTED;
}
inline waiit_for_HALT_mask(i){
	states[i] == STOPPED || states[i] == ABORTED;
}
inline waiit_for_ABORT_mask(i){
	states[i] == ABORTED;
}
inline start(i, waiit){
	atomic {
		if
		::	START == START && commands[i] == CONTINUE;
			assert((states[i] == READY));
			commands[i] = START;
		::	START == PAUSE && commands[i] == CONTINUE;
			assert((states[i] == STARTING || states[i] == RUNNING));
			commands[i] = PAUSE;
		::	START == CONTINUE && (commands[i] == START || commands[i] == PAUSE);
			assert((states[i] == STARTING || states[i] == PAUSED));
			commands[i] = CONTINUE;
		::	START == STOP && (commands[i] == CONTINUE || commands[i] == PAUSE);
			assert((states[i] == STARTING || states[i] == RUNNING || states[i] == PAUSED));
			commands[i] = STOP;
		::	START == ABORT;
			assert((states[i] != READY));
			commands[i] = ABORT;
		::	else;
			skip;
		fi;
	};
	run Thread(i);
	if
	::	waiit;
		waiit_for_START_mask(i)
	::	else;
		skip;
	fi;
}
inline pause(i, waiit){
	atomic {
		if
		::	PAUSE == START && commands[i] == CONTINUE;
			assert((states[i] == READY));
			commands[i] = START;
		::	PAUSE == PAUSE && commands[i] == CONTINUE;
			assert((states[i] == STARTING || states[i] == RUNNING));
			commands[i] = PAUSE;
		::	PAUSE == CONTINUE && (commands[i] == START || commands[i] == PAUSE);
			assert((states[i] == STARTING || states[i] == PAUSED));
			commands[i] = CONTINUE;
		::	PAUSE == STOP && (commands[i] == CONTINUE || commands[i] == PAUSE);
			assert((states[i] == STARTING || states[i] == RUNNING || states[i] == PAUSED));
			commands[i] = STOP;
		::	PAUSE == ABORT;
			assert((states[i] != READY));
			commands[i] = ABORT;
		::	else;
			skip;
		fi;
	};
	if
	::	waiit;
		waiit_for_PAUSE_mask(i)
	::	else;
		skip;
	fi;
}
inline resume(i, waiit){
	atomic {
		if
		::	CONTINUE == START && commands[i] == CONTINUE;
			assert((states[i] == READY));
			commands[i] = START;
		::	CONTINUE == PAUSE && commands[i] == CONTINUE;
			assert((states[i] == STARTING || states[i] == RUNNING));
			commands[i] = PAUSE;
		::	CONTINUE == CONTINUE && (commands[i] == START || commands[i] == PAUSE);
			assert((states[i] == STARTING || states[i] == PAUSED));
			commands[i] = CONTINUE;
		::	CONTINUE == STOP && (commands[i] == CONTINUE || commands[i] == PAUSE);
			assert((states[i] == STARTING || states[i] == RUNNING || states[i] == PAUSED));
			commands[i] = STOP;
		::	CONTINUE == ABORT;
			assert((states[i] != READY));
			commands[i] = ABORT;
		::	else;
			skip;
		fi;
	};
	if
	::	waiit;
		waiit_for_RESUME_mask(i)
	::	else;
		skip;
	fi;
}
inline stop(i, waiit){
	atomic {
		if
		::	STOP == START && commands[i] == CONTINUE;
			assert((states[i] == READY));
			commands[i] = START;
		::	STOP == PAUSE && commands[i] == CONTINUE;
			assert((states[i] == STARTING || states[i] == RUNNING));
			commands[i] = PAUSE;
		::	STOP == CONTINUE && (commands[i] == START || commands[i] == PAUSE);
			assert((states[i] == STARTING || states[i] == PAUSED));
			commands[i] = CONTINUE;
		::	STOP == STOP && (commands[i] == CONTINUE || commands[i] == PAUSE);
			assert((states[i] == STARTING || states[i] == RUNNING || states[i] == PAUSED));
			commands[i] = STOP;
		::	STOP == ABORT;
			assert((states[i] != READY));
			commands[i] = ABORT;
		::	else;
			skip;
		fi;
	};
	if
	::	waiit;
		waiit_for_HALT_mask(i)
	::	else;
		skip;
	fi;
}
bool serialize_commands;
bool all_workers_stopped;
bool exists_aborted_worker;
bool supervisor_started;
inline assert_all(k, state, command){
	d_step {
		do
		::	k < 3;
			assert((states[k] == state));
			assert((commands[k] == command));
			k++;
		::	else;
			break;
		od;
		k = 0;
	};
}
inline send_command(j, command, waiit){
	if
	::	command == START;
		start(j, waiit)
	::	command == PAUSE;
		pause(j, waiit)
	::	command == CONTINUE;
		resume(j, waiit)
	::	command == STOP || command == ABORT;
		stop(j, waiit)
	fi;
}
inline covariant_propagation(command, waiit){
	do
	::	j < 3;
		send_command(j, command, waiit)
		j++;
	::	else;
		j = 1;
		break;
	od;
}
inline contravariant_propagation(command){
	j = 3 - 1;
	do
	::	j > 0;
		send_command(j, command, true)
		j--;
	::	else;
		j = 1;
		break;
	od;
}
inline propagate_command_in_lifo(command){
	if
	::	command == START || command == PAUSED;
		covariant_propagation(command, true)
	::	else;
		contravariant_propagation(command)
	fi;
}
inline propagate_command_in_parallel(command){
	covariant_propagation(command, false)
	do
	::	j < 3;
		if
		::	command == START;
			waiit_for_START_mask(j)
		::	command == CONTINUE;
			waiit_for_RESUME_mask(j)
		::	command == PAUSE;
			waiit_for_PAUSE_mask(j)
		::	command == STOP;
			waiit_for_HALT_mask(j)
		fi;
		j++;
	::	else;
		j = 1;
		break;
	od;
}
inline propagate_command(command){
	if
	::	command == CONTINUE && !supervisor_started;
		supervisor_started = true;
	::	else;
		if
		::	serialize_commands;
			propagate_command_in_lifo(command)
		::	else;
			propagate_command_in_parallel(command)
		fi;
	fi;
}
inline check_worker_states(){
	all_workers_stopped = true;
	do
	::	j < 3;
		all_workers_stopped = all_workers_stopped && states[j] == STOPPED;
		exists_aborted_worker = exists_aborted_worker || states[j] == ABORTED;
		j++;
	::	else;
		j = 1;
		break;
	od;
}
inline sv_trans_cb(s){
	if
	::	s == RUNNING;
		propagate_command(CONTINUE)
	::	s == PAUSED;
		propagate_command(PAUSE)
	::	s == ABORTING || s == STOPPING;
		propagate_command(STOP)
	::	else;
		skip;
	fi;
}
inline sv_covariant_transition(state, command, next){
	states[0] = next;
	sv_trans_cb(next)
}
inline sv_contravariant_transition(state, command, next){
	sv_trans_cb(next)
	states[0] = next;
}
inline sv_prepare(){
	propagate_command(START)
}
inline sv_execute(){
	executing[0] = true;
	check_worker_states()
	if
	::	all_workers_stopped;
		stop(0, false)
	::	exists_aborted_worker;
		stop(0, false)
	::	else;
		skip;
	fi;
	executing[0] = false;
}
proctype Supervisor(){
	byte j = 1;
	commands[0] == START;
	sv_covariant_transition(READY, START, STARTING)
	atomic {
		if
		::	CONTINUE == START && commands[0] == CONTINUE;
			assert((states[0] == READY));
			commands[0] = START;
		::	CONTINUE == PAUSE && commands[0] == CONTINUE;
			assert((states[0] == STARTING || states[0] == RUNNING));
			commands[0] = PAUSE;
		::	CONTINUE == CONTINUE && (commands[0] == START || commands[0] == PAUSE);
			assert((states[0] == STARTING || states[0] == PAUSED));
			commands[0] = CONTINUE;
		::	CONTINUE == STOP && (commands[0] == CONTINUE || commands[0] == PAUSE);
			assert((states[0] == STARTING || states[0] == RUNNING || states[0] == PAUSED));
			commands[0] = STOP;
		::	CONTINUE == ABORT;
			assert((states[0] != READY));
			commands[0] = ABORT;
		::	else;
			skip;
		fi;
	};
	sv_prepare()
	do
	::	commands[0] == CONTINUE;
		assert((states[0] == STARTING || states[0] == RUNNING || states[0] == PAUSED));
		if
		::	states[0] == STARTING;
			sv_covariant_transition(STARTING, CONTINUE, RUNNING)
		::	states[0] == PAUSED;
			sv_covariant_transition(PAUSED, CONTINUE, RUNNING)
		::	else;
			skip;
		fi;
		sv_execute()
	::	commands[0] == PAUSE;
		if
		::	states[0] == PAUSED;
			commands[0] != PAUSED;
		::	else;
			assert((states[0] == STARTING || states[0] == RUNNING || states[0] == STARTING));
			if
			::	states[0] == STARTING || states[0] == RUNNING;
				sv_contravariant_transition(RUNNING, PAUSE, PAUSED)
			::	else;
				skip;
			fi;
		fi;
	::	commands[0] == STOP || commands[0] == ABORT;
		break;
	od;
	if
	::	commands[0] == STOP;
		assert((states[0] == STARTING || states[0] == RUNNING || states[0] == PAUSED));
		sv_covariant_transition(states[0], STOP, STOPPING)
		sv_contravariant_transition(STOPPING, STOP, STOPPED)
	::	commands[0] == ABORT;
		assert((states[0] == STARTING || states[0] == RUNNING || states[0] == STOPPING));
		sv_covariant_transition(states[0], ABORT, ABORTING)
		sv_contravariant_transition(ABORTING, ABORT, ABORTED)
	::	else;
		assert((false));
	fi;
}
inline sv_start_sync(){
	atomic {
		if
		::	START == START && commands[0] == CONTINUE;
			assert((states[0] == READY));
			commands[0] = START;
		::	START == PAUSE && commands[0] == CONTINUE;
			assert((states[0] == STARTING || states[0] == RUNNING));
			commands[0] = PAUSE;
		::	START == CONTINUE && (commands[0] == START || commands[0] == PAUSE);
			assert((states[0] == STARTING || states[0] == PAUSED));
			commands[0] = CONTINUE;
		::	START == STOP && (commands[0] == CONTINUE || commands[0] == PAUSE);
			assert((states[0] == STARTING || states[0] == RUNNING || states[0] == PAUSED));
			commands[0] = STOP;
		::	START == ABORT;
			assert((states[0] != READY));
			commands[0] = ABORT;
		::	else;
			skip;
		fi;
	};
	run Supervisor();
	waiit_for_START_mask(0)
}
inline sv_ctor(i){
	d_step {
		if
		::	true;
			serialize_commands = true;
		::	true;
			serialize_commands = false;
		fi;
		all_workers_stopped = false;
		exists_aborted_worker = false;
		supervisor_started = false;
		do
		::	i < 3;
			ctor(i)
			i++;
		::	else;
			break;
		od;
	};
}
inline sv_dtor(i){
	d_step {
		do
		::	i < 3;
			dtor(i)
			i++;
		::	else;
			break;
		od;
	};
}

init {
	byte i = 0;
	assert_all(i, 0, 0)
	sv_ctor(i)
	i = 0;
	assert_all(i, READY, CONTINUE)
	sv_start_sync()
	do
	::	if
		::	states[0] == RUNNING;
			if
			::	true;
				pause(0, true)
			::	true;
				pause(0, false)
			fi;
		::	states[0] == PAUSED;
			if
			::	true;
				resume(0, true)
			::	true;
				resume(0, false)
			fi;
		::	true;
			skip;
		fi;
	::	break;
	od;
	if
	::	true;
		if
		::	true;
			stop(0, true)
		::	true;
			stop(0, false)
		fi;
	::	true;
		skip;
	fi;
	waiit_for_HALT_mask(0)
	i = 0;
	sv_dtor(i)
	i = 0;
	assert_all(i, 0, 0)
};
