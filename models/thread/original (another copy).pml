/*
 * This file contains the theory of ADAPRO, expressed in the language of linear
 * temporal logic (notated in Promela, with the help of CPP macros). It defines 
 * the formal specification of the framework.
 */
/******************************************************************************/

/**
 * Expresses the predicate that Supervisor is in the given state.
 */
#define supervisor_in_state(state)                                             \
    states[0] == state

/**
 * Expresses the predicate that all Workers are in the given state.
 */
#define all_workers_in_state(state)                                            \
    states[1] == state && states[2] == state

/**
 * Expresses the predicate that there exists a Worker in the given state.
 */
#define some_workers_in_state(state)                                           \
    states[1] == state || states[2] == state

/**
 * Expresses the predicate that Supervisor is either in the state STOPPING or
 * ABORTING.
 */
#define supervisor_halting                                                     \
    states[0] == STOPPING || states[0] == ABORTING

/**
 * Expresses the predicate that Supervisor is either in the state STOPPED or
 * ABORTED.
 */
#define supervisor_halted                                                      \
    states[0] == STOPPED || states[0] == ABORTED

/**
 * Expresses the predicate that every Worker is either in the state STOPPED or
 * ABORTED.
 */
#define all_workers_halted                                                     \
    (states[1] == STOPPED || states[1] == ABORTED || states[1] == 0) &&        \
    (states[2] == STOPPED || states[2] == ABORTED || states[2] == 0)

/**
 * Expresses the predicate that Thread number i is in the state RUNNING with
 * command CONTINUE.
 */
#define executable(i)                                                          \
    states[i] == RUNNING && commands[i] == CONTINUE 

/**
 * Expresses the predicate that, infinitely often, every executable Thread gets
 * to execute its user-defined program logic.
 */
#define all_alive                                                              \
    []<>((executable(0)) -> (executing[0])) &&                                 \
    []<>((executable(1)) -> (executing[1])) &&                                 \
    []<>((executable(2)) -> (executing[2]))

/**
 * Expresses weak fairness, i.e. that every Thread that is persistently 
 * executable, will eventually get to execute its action.
 */
#define weak_fairness                                                          \
    (<>[](executable(0)) -> []<>(executing[0])) &&                             \
    (<>[](executable(1)) -> []<>(executing[1])) &&                             \
    (<>[](executable(2)) -> []<>(executing[2]))
/**
 * Expresses strong fairness, i.e. that every Thread that is infinitely often 
 * executable, will eventually get to execute its action.
 */
#define strong_fairness                                                        \
    ([]<>(executable(0)) -> []<>(executing[0])) &&                             \
    ([]<>(executable(1)) -> []<>(executing[1])) &&                             \
    ([]<>(executable(2)) -> []<>(executing[2]))

/**
 * Expresses the predicate that the initial state of any constructed Thread is 
 * READY and that its only possible successor state is STARTING. (This means 
 * that READY is a safe state, i.e. cannot directly lead into a transition to 
 * ABORTING.)
 */
#define READY_property(i)                                                      \
    states[i] == 0 U ((states[i] == READY) W (states[i] == STARTING))

/**
 * Expresses the predicate that the only possible successor states of STARTING
 * are RUNNING, PAUSED, and ABORTING. (Note that STARTING is not a safe state,
 * because it has an outgoing transition to ABORTING.)
 */
#define STARTING_property(i)                                                   \
    states[i] == STARTING -> (states[i] == STARTING U                          \
        (states[i] == RUNNING || states[i] == PAUSED ||                        \
         states[i] == STOPPING || states[i] == ABORTING))

/**
 * Expresses the predicate that the only possible successor states of RUNNING
 * are RUNNING, PAUSED, STOPPING, STOPPED. A Thread is allowed to stay in the
 * RUNNING state forever. (Note that RUNNING is not a safe state, since it has
 * an outgoing transition to ABORTING.)
 */
#define RUNNING_property(i)                                                    \
    states[i] == RUNNING -> ((states[i] == RUNNING) W                          \
    (states[i] == PAUSED || states[i] == STOPPING || states[i] == ABORTING))

/**
 * Expresses the predicate that the only possible successor states of PAUSED are
 * RUNNING and STOPPING. (PAUSED is a safe state, because it doesn't have an
 * outgoing transition to ABORTING.)
 */
#define PAUSED_property(i)                                                     \
    states[i] == PAUSED ->                                                     \
    ((states[i] == PAUSED) W (states[i] == RUNNING || states[i] == STOPPING))

/**
 * Expresses the predicate that the only possible successor states of STOPPING
 * are STOPPED and ABORTING. (STOPPING is not a safe state because it has an
 * outgoing transition to ABORTING.)
 */
#define STOPPING_property(i)                                                   \
    [](states[i] == STOPPING -> (states[i] == STOPPING U                       \
        (states[i] == STOPPED || states[i] == ABORTING)))

/**
 * Expresses the predicate that the only possible successor state of ABORTING is
 * ABORTED. (Since it doesn't have a loop, it is a safe state.)
 */
#define ABORTING_property(i)                                                   \
    [](states[i] == ABORTING -> (states[i] == ABORTING U                       \
        (states[i] == ABORTED)))

/**
 * Expresses the predicate that the values in the array lhs that equal to rhs
 * remain constant.
 */
#define final(lhs, rhs)                                                        \
    ((lhs[0] == rhs) -> ((lhs[0] == rhs) W [](lhs[0] == 0))) &&                \
    ((lhs[1] == rhs) -> ((lhs[1] == rhs) W [](lhs[1] == 0))) &&                \
    ((lhs[2] == rhs) -> ((lhs[2] == rhs) W [](lhs[2] == 0)))

/******************************************************************************/

/**
 * See READY_property.
 */
ltl fsm_ready
{
    (READY_property(0)) && (READY_property(1)) && (READY_property(2))
}

/**
 * See STARTING_property.
 */
ltl fsm_starting
{
    []((STARTING_property(0)) && (STARTING_property(1)) && (STARTING_property(2)))
}

/**
 * See RUNNING_property.
 */
ltl fsm_running
{
    []((RUNNING_property(0)) && (RUNNING_property(1)) && (RUNNING_property(2)))
}

/**
 * See PAUSED_property.
 */
ltl fsm_paused
{
    []((PAUSED_property(0)) && (PAUSED_property(1)) && (PAUSED_property(2)))
}

/**
 * See STOPPING_property.
 */
ltl fsm_stopping
{
    []((STOPPING_property(0)) && (STOPPING_property(1)) && (STOPPING_property(2)))
}

/**
 * Expresses the predicate that the state STOPPED is a fixed point state for any
 * Thread.
 */
ltl fsm_stopped
{
    [](final(states, STOPPED))
}

/**
 * See ABORTING_property.
 */
ltl fsm_aborting
{
    []((ABORTING_property(0)) && (ABORTING_property(1)) && (ABORTING_property(2)))
}

/**
 * Expresses the predicate that the state ABORTED is a fixed point state for any
 * Thread.
 */
ltl fsm_aborted
{
    [](final(states, ABORTED))
}

/**
 * Expresses the predicate that the command ABORT is a fixed point command for
 * any Thread.
 */
ltl abort_is_undoable
{
    [](final(commands, ABORT))
}

/**
 * Expresses the predicate that Supervisor is the first Thread that will be
 * created.
 */
ltl supervisor_is_the_first_thread
{
    []((supervisor_in_state(0)) -> (all_workers_in_state(0)))
}

/**
 * Expresses the predicate that the only situation in which a Worker is in state 
 * READY is the one where Supervisor is in state STARTING. The justification for
 * this claim is that Supervisor is the Thread that constructs Workers, i.e.
 * causes them to obtain their initial states and commands.
 */
ltl supervisor_constructs_workers
{
    []((some_workers_in_state(READY)) -> !(supervisor_in_state(0)))
}

/**
 * Expresses the predicate that once all workers have stopped, Supervisor
 * eventually stops, unless an external command pauses Supervisor indefinitely.
 * (Without external interference, Supervisor is always guaranteed to eventually 
 * stop after all workers have stopped.)
 */
ltl supervisor_stops_after_all_workers_stop
{
    []((all_workers_in_state(STOPPED)) -> 
        ([]<>(supervisor_in_state(PAUSED)) || <>(supervisor_in_state(STOPPED))))
}

/**
 * Expresses the predicate, that unless paused by an external command, 
 * Supervisor will eventually halt after one or more Workers have aborted.
 */
ltl supervisor_stops_after_some_workers_abort
{
    []((some_workers_in_state(ABORTED)) -> 
        ([]<>(supervisor_in_state(PAUSED)) || <>(supervisor_in_state(STOPPED))))
}

/**
 * Expresses the predicate that Supervisor never aborts.
 */
ltl supervisor_never_aborts {!<>(states[0] == ABORTED || commands[0] == ABORT)}

/**
 * Expresses the predicate that Supervisor is the last Thread to halt.
 */
ltl supervisor_halts_last
{
    []((supervisor_halting) -> <>(all_workers_halted))
}

ltl liveness
{
    (all_alive) W (supervisor_halting)
}

ltl fairness
{
    (strong_fairness)
}

mtype = {ABORT, STOP, ABORTED, ABORTING, STOPPED, PAUSE, STOPPING, CONTINUE, START, PAUSED, RUNNING, STARTING, READY}

mtype states[3];
mtype commands[3];
bool executing[3];
inline abort(i){
	assert((_pid != 1));
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
		::	else -> skip;
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
			::	else -> skip;
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
			::	STOP == STOP && (commands[i] == CONTINUE || commands[i] == PAUSE);
				assert((states[i] == STARTING || states[i] == RUNNING || states[i] == PAUSED));
				commands[i] = STOP;
			::	STOP == ABORT;
				assert((states[i] != READY));
				commands[i] = ABORT;
			::	else -> skip;
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
			::	else -> skip;
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
		::	else -> skip;
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
		::	else ->
			skip;
		fi;
		execute(k)
	::	commands[k] == PAUSE;
		if
		::	states[k] == PAUSED;
			commands[k] != PAUSED;
		::	else ->
			assert((states[k] == STARTING || states[k] == RUNNING || states[k] == STARTING));
			if
			::	states[k] == STARTING || states[k] == RUNNING;
				contravariant_transition(RUNNING, PAUSE, PAUSED)
			::	else ->
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
	::	else ->
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
		::	else -> skip;
		fi;
	};
	run Thread(i);
	if
	::	waiit;
		waiit_for_START_mask(i)
	::	else ->
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
		::	else -> skip;
		fi;
	};
	if
	::	waiit;
		waiit_for_PAUSE_mask(i)
	::	else ->
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
		::	else -> skip;
		fi;
	};
	if
	::	waiit;
		waiit_for_RESUME_mask(i)
	::	else ->
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
		::	else -> skip;
		fi;
	};
	if
	::	waiit;
		waiit_for_HALT_mask(i)
	::	else ->
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
		::	else ->
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
	::	else ->
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
	::	else ->
		j = 1;
		break;
	od;
}
inline propagate_command_in_lifo(command){
	if
	::	command == START || command == PAUSED;
		covariant_propagation(command, true)
	::	else ->
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
	::	else ->
		j = 1;
		break;
	od;
}
inline propagate_command(command){
	if
	::	command == CONTINUE && !supervisor_started;
		supervisor_started = true;
	::	else ->
		if
		::	serialize_commands;
			propagate_command_in_lifo(command)
		::	else ->
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
	::	else ->
		j = 1;
		break;
	od;
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
		::	else -> skip;
		fi;
	};
	run Supervisor();
	waiit_for_START_mask(0)
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
	::	else ->
		skip;
	fi;
	executing[0] = false;
}
inline sv_trans_cb(s){
	if
	::	s == RUNNING;
		propagate_command(CONTINUE)
	::	s == PAUSED;
		propagate_command(PAUSE)
	::	s == ABORTING || s == STOPPING;
		propagate_command(STOP)
	::	else ->
		skip;
	fi;
}
inline sv_covariant_transition(state, command, next){
	print_state_transition(0, state, command, next)
	states[0] = next;
	sv_trans_cb(next)
}
inline sv_contravariant_transition(state, command, next){
	sv_trans_cb(next)
	print_state_transition(0, state, command, next)
	states[0] = next;
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
		::	else ->
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
		::	else ->
			break;
		od;
	};
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
		::	else -> skip;
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
		::	else ->
			skip;
		fi;
		sv_execute()
	::	commands[0] == PAUSE;
		if
		::	states[0] == PAUSED;
			commands[0] != PAUSED;
		::	else ->
			assert((states[0] == STARTING || states[0] == RUNNING || states[0] == STARTING));
			if
			::	states[0] == STARTING || states[0] == RUNNING;
				sv_contravariant_transition(RUNNING, PAUSE, PAUSED)
			::	else ->
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
	::	else ->
		assert((false));
	fi;
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
