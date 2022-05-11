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

/** The number of Threads, including Supervisor as Thread no. 0, to simulate. */
#define N 3

/** 
 * The numerical values of the states are:
 *     ABORTED     = 1,
 *     ABORTING    = 2,
 *     STOPPED     = 3,
 *     STOPPING    = 4,
 *     PAUSED      = 5,
 *     RUNNING     = 6,
 *     STARTING    = 7,
 *     READY       = 8
 */
mtype = {READY, STARTING, RUNNING, PAUSED, STOPPING, STOPPED, ABORTING, ABORTED};

/** 
 * The numerical values of the commands are:
 *     ABORT       = 9,
 *     STOP        = 10,
 *     PAUSE       = 11,
 *     CONTINUE    = 12,
 *     START       = 13
 */
mtype = {START, CONTINUE, PAUSE, STOP, ABORT};

/** 
 * It seems that mtype declarations have "big endian" ordering, which I find
 * counterintuitive. Hence, this definition:
 */
#define LT(x, y) x > y

/** 
 * Prettyprints the state transition for Thread number i. For automatic state
 * transitions, the command should be set to 0, in which case an underscore
 * ('_') will be printed instead of a command name.
 */
inline print_state_transition(i, state, command, next)
{
    if
    ::  i == 0  && command == 0 ->
            printf("Supervisor: (%e, _) -> %e\n", state, next)
    ::  i == 0  && command > 0  ->
            printf("Supervisor: (%e, %e) -> %e\n", state, command, next)
    ::  i > 0   && command == 0 ->
            printf("Worker %d: (%e, _) -> %e\n", i, state, next)
    ::  i > 0   && command > 0 ->
            printf("Worker %d: (%e, %e) -> %e\n", i, state, command, next)
    fi
}

/********************************** PRIVATE ***********************************/

/** States of the Threads. Index 0 is reserved for the Supervisor. */
mtype states[N];

/** Commands of the Threads. Index 0 is reserved for the Supervisor. */
mtype commands[N];

/** The array of Threads currently executing. */
bool executing[N];

/** See the documentation for ADAPRO::Control::Thread::set_state. */
#define set_state(i, state) states[i] = state

/** See the documentation for ADAPRO::Control::Thread::set_command. */
#define set_command(i, command)                                                \
    atomic                                                                     \
    {                                                                          \
        if                                                                     \
        ::  command == START && commands[i] == CONTINUE ->                     \
                assert(get_state(i) == READY);                                 \
                commands[i] = START                                            \
        ::  command == PAUSE && commands[i] == CONTINUE ->                     \
                assert(get_state(i) == STARTING || get_state(i) == RUNNING);   \
                commands[i] = PAUSE                                            \
        ::  command == CONTINUE &&                                             \
            (commands[i] == START || commands[i] == PAUSE) ->                  \
                assert(get_state(i) == STARTING || get_state(i) == PAUSED);    \
                commands[i] = CONTINUE                                         \
        ::  command == STOP &&                                                 \
            (commands[i] == CONTINUE || commands[i] == PAUSE) ->               \
                assert(get_state(i) == STARTING || get_state(i) == RUNNING ||  \
                        get_state(i) == PAUSED);                               \
                commands[i] = STOP                                             \
        ::  command == ABORT ->                                                \
                assert(get_state(i) != READY);                                 \
                commands[i] = ABORT                                            \
        ::  else -> printf("Thread %d ignores command %e.\n", i, commands[i])  \
        fi                                                                     \
    }

/********************************** PUBLIC ************************************/

/** See the documentation for ADAPRO::Control::Thread::get_state. */
#define get_state(i) states[i]

/** See the documentation for ADAPRO::Control::Thread::get_command. */
#define get_command(i) commands[i]

/********************************* PROTECTED **********************************/

/** 
 * Models the method ADAPRO::Control::Thread::prepare by non-deterministically
 * choosing between aborting, pausing, and doing nothing.
 */
inline prepare(i)
{
    if
    :: true -> abort(i)
    :: true -> set_command(i, PAUSE)
    :: true -> set_command(i, STOP)
    :: true -> skip
    fi
}

/** 
 * Models the method ADAPRO::Control::Thread::execute by non-deterministically
 * choosing between aborting, pausing, stopping, and doing nothing.
 */
inline execute(i)
{
    executing[i] = true;
    if
    :: true -> abort(i)
    /* :: true -> set_command(i, PAUSE) */
    :: true -> set_command(i, STOP)
    :: true -> skip
    fi
    executing[i] = false
}

/** 
 * Models the method ADAPRO::Control::Thread::finish by non-deterministically
 * choosing between aborting and doing nothing.
 */
inline finish(i)
{
    if
    :: true -> abort(i)
    :: true -> skip
    fi
}

/** Aborts the Thread number i. Always non-blocking. */
inline abort(i)
{
    assert(_pid != 1);      /* Supervisor is not allowed to abort Workers. */
    set_command(i, ABORT);
}

/********************************** PRIVATE ***********************************/

/** 
 * Simulates the Thread class constructor by initializing the state and
 * commmand of thread number i Thread with their legal default values.
 */
inline ctor(i)
{
    d_step
    {
        states[i]   = READY;
        commands[i] = CONTINUE
    }
}

inline dtor(i)
{
    d_step
    {
        states[i]   = 0;
        commands[i] = 0;
        executing[i]= false
    }
}

/** Models the default transition callback of a Thread that does nothing. */
inline trans_cb(s)
{
    skip
}

inline covariant_transition(state, command, next)
{
    print_state_transition(k, state, command, next);
    set_state(k, next);
    /*trans_cb(next)*/
}

inline contravariant_transition(state, command, next)
{
    /*trans_cb(next);*/
    print_state_transition(k, state, command, next);
    set_state(k, next)
}

/** Models the ADAPRO::Control::Thread::run method. */
proctype Thread(byte k)
{
    /* Startup: */
    get_command(k) == START;
    covariant_transition(READY, START, STARTING);
    set_command(k, CONTINUE);
    prepare(k);

    /* Execution: */
    do
    ::  get_command(k) == CONTINUE                          -> 
            assert(get_state(k) == STARTING || get_state(k) == RUNNING || 
                get_state(k) == PAUSED);
            if
            ::  get_state(k) == STARTING    ->
                    covariant_transition(STARTING, CONTINUE, RUNNING)
            ::  get_state(k) == PAUSED      ->
                    covariant_transition(PAUSED, CONTINUE, RUNNING)
            ::  else                        ->
                    skip
            fi
            execute(k)
    ::  get_command(k) == PAUSE                             ->
            if
            ::  get_state(k) == PAUSED  ->
                    get_command(k) != PAUSED
            ::  else                    ->
                    assert(get_state(k) == STARTING || get_state(k) == RUNNING || 
                        get_state(k) == STARTING);
                    if
                    ::  get_state(k) == STARTING || get_state(k) == RUNNING ->
                            contravariant_transition(RUNNING, PAUSE, PAUSED)
                    ::  else                    ->
                            skip
                    fi
            fi
    ::  get_command(k) == STOP || get_command(k) == ABORT   ->
            break
    od

    /* Shutdown: */
    if
    ::  get_command(k) == STOP      ->
            assert(get_state(k) == STARTING || get_state(k) == RUNNING || 
                get_state(k) == PAUSED);
            covariant_transition(get_state(k), STOP, STOPPING);
            finish(k);
            contravariant_transition(STOPPING, STOP, STOPPED)
    ::  get_command(k) == ABORT     ->
            assert(get_state(k) == STARTING || get_state(k) == RUNNING || 
                get_state(k) == STOPPING);
            covariant_transition(get_state(k), ABORT, ABORTING);
            contravariant_transition(ABORTING, ABORT, ABORTED)
    ::  else                        ->
            assert(false)
    fi
}

/********************************** PUBLIC ************************************/

/** Models Control::Thread::wait_for_state_mask(Data::State::START_MASK). */
inline wait_for_START_mask(i)
{
    if
    ::  _pid == 0   ->
            printf("Init is waiting for START mask on Thread %d...\n", i)
    ::  _pid == 1   ->
            printf("Supervisor is waiting for START mask on Thread %d...\n", i)
    ::  _pid > 1    ->
            printf("Worker %d is waiting for START mask on Thread %d...\n", _pid - 1, i)
    fi
    get_state(i) == RUNNING     ||
    get_state(i) == PAUSED      ||
    get_state(i) == STOPPING    ||
    get_state(i) == STOPPED     ||
    get_state(i) == ABORTING    ||
    get_state(i) == ABORTED;
    printf("Waiting ended.\n")
}

/** Models Control::Thread::wait_for_state_mask(Data::State::PAUSE_MASK). */
inline wait_for_PAUSE_mask(i)
{
    if
    ::  _pid == 0   ->
            printf("Init is waiting for PAUSED mask on Thread %d...\n", i)
    ::  _pid == 1   ->
            printf("Supervisor is waiting for PAUSED mask on Thread %d...\n", i)
    ::  _pid > 1    ->
            printf("Worker %d is waiting for PAUSED mask on Thread %d...\n", _pid - 1, i)
    fi
    get_state(i) == PAUSED      ||
    get_state(i) == STOPPING    ||
    get_state(i) == STOPPED     ||
    get_state(i) == ABORTING    ||
    get_state(i) == ABORTED;
    printf("Waiting ended.\n")
}

/** Models Control::Thread::wait_for_state_mask(Data::State::RESUME_MASK). */
inline wait_for_RESUME_mask(i)
{
    if
    ::  _pid == 0   ->
            printf("Init is waiting for RESUME mask on Thread %d...\n", i)
    ::  _pid == 1   ->
            printf("Supervisor is waiting for RESUME mask on Thread %d...\n", i)
    ::  _pid > 1    ->
            printf("Worker %d is waiting for RESUME mask on Thread %d...\n", _pid - 1, i)
    fi
    get_state(i) == RUNNING     ||
    get_state(i) == STOPPING    ||
    get_state(i) == STOPPED     ||
    get_state(i) == ABORTING    ||
    get_state(i) == ABORTED;
    printf("Waiting ended.\n")
}

/** Models Control::Thread::wait_for_state_mask(Data::State::HALT_MASK). */
inline wait_for_HALT_mask(i)
{
    if
    ::  _pid == 0   ->
            printf("Init is waiting for HALT mask on Thread %d...\n", i)
    ::  _pid == 1   ->
            printf("Supervisor is waiting for HALT mask on Thread %d...\n", i)
    ::  _pid > 1    ->
            printf("Worker %d is waiting for HALT mask on Thread %d...\n", _pid - 1, i)
    fi
    get_state(i) == STOPPED     ||
    get_state(i) == ABORTED;
    printf("Waiting ended.\n")
}

/** Models Control::Thread::wait_for_state_mask(Data::State::ABORT_MASK). */
inline wait_for_ABORT_mask(i)
{
    if
    ::  _pid == 0   ->
            printf("Init is waiting for ABORTED mask on Thread %d...\n", i)
    ::  _pid == 1   ->
            printf("Supervisor is waiting for ABORTED mask on Thread %d...\n", i)
    ::  _pid > 1    ->
            printf("Worker %d is waiting for ABORTED mask on Thread %d...\n", _pid - 1, i)
    fi
    get_state(i) == ABORTED;
    printf("Waiting ended.\n")
}

/** 
 * Starts the Thread number i. If wait is true, then this macro blocks until
 * the Thread has entered a state greater than or equal to RUNNING.
 */
inline start(i, wait)
{
    set_command(i, START);
    run Thread(i);
    if
    ::  wait -> wait_for_START_mask(i)
    ::  else -> skip
    fi
}

/** 
 * Pauses the Thread number i. If wait is true, then this macro blocks until the 
 * Thread has entered a state greater than or equal to PAUSED.
 */
inline pause(i, wait)
{
    set_command(i, PAUSE);
    if
    ::  wait -> wait_for_PAUSE_mask(i)
    ::  else -> skip
    fi
}

/** 
 * Resumes the Thread number i. If wait is true, then this macro blocks until
 * the Thread has entered a state greater than or equal to RUNNING.
 */
inline resume(i, wait)
{
    set_command(i, CONTINUE);
    if
    ::  wait -> wait_for_RESUME_mask(i)
    ::  else -> skip
    fi
}

/** 
 * Stops the Thread number i. If wait is true, then this macro blocks until
 * the Thread has entered the state STOPPED or ABORTED.
 */
inline stop(i, wait)
{
    set_command(i, STOP);
    if
    ::  wait -> wait_for_HALT_mask(i)
    ::  else -> skip
    fi
}

/**
 * Supervisor propagates commands in serial mode if and only if this variable is
 * set to true. As of ADAPRO 5.0.0, Supervisor keeps querying a configuration
 * parameter corresponding with this condition during runtime.
 */
bool serialize_commands;

/**
 * Should be true if and only if all Workers have entered the state STOPPED. 
 * This is a private field of Supervisor, but modeled as a global variable to 
 * enable more precise simulation of constructors.
 */
bool all_workers_stopped;

/**
 * Should be true if and only if one or more Workers have entered the state
 * ABORTED. This is a private field of Supervisor, but modeled as a global 
 * variable to enable more precise simulation of constructors.
 */
bool exists_aborted_worker;

/**
 * Supervisor sets this true when calling its transition callback on CONTINUE
 * for the first time. This is used for the mechanism that prevents Supervisor
 * for propagating the CONTINUE command when starting. Doing so would prevent
 * Workers from starting in the state PAUSED. This is a private field of
 * Supervisor, but modeled as a global variable to enable more precise
 * simulation of constructors.
 */
bool supervisor_started;

/** 
 * Asserts that all the threads from k to N are in the given state with the
 * given command. Mutates the value of k, leaving it 0 at the end.
 */
inline assert_all(k, state, command)
{
    d_step
    {
        do
        ::  k < N   ->
                assert(get_state(k)     == state);
                assert(get_command(k)   == command);
                k++
        ::  else    ->
                break
        od
        k = 0
    }
}

/** Sends the given command to Worker number j. Waits iff wait == true. */
inline send_command(j, command, wait)
{
    if
    ::  command == START                    ->
            start(j, wait)
    ::  command == PAUSE                    ->
            pause(j, wait)
    ::  command == CONTINUE                 ->
            resume(j, wait)
    ::  command == STOP || command == ABORT ->
            stop(j, wait)
    fi
}

/**
 * Propagates the given command in covariant order, i.e. by iterating through
 * Workers in increasing order. Blocks if and only if wait is true.
 */
inline covariant_propagation(command, wait)
{
    do
    ::  j < N   ->
            send_command(j, command, wait);
            j++
    ::  else    ->
            j = 1;
            break
    od
}

/**
 * Propagates the given command in contravariant order, i.e. by iterating
 * through Workers in decreasing order.
 */
inline contravariant_propagation(command)
{
    j = N - 1;
    do
    ::  j > 0   ->
            send_command(j, command, true);
            j--
    ::  else    ->
            j = 1;
            break
    od
}

/**
 * Propagates the given command to all Workers, using the command propagate mode
 * determined by the value of the global variable serialize_commands.
 */
inline propagate_command(command)
{
    if
    ::  command == CONTINUE && !supervisor_started ->
            printf("Supervisor doesn't propagate the first CONTINUE command.\n");
            supervisor_started = true
    ::  else ->
            if
            ::  serialize_commands  -> propagate_command_in_lifo(command)
            ::  else                -> propagate_command_in_parallel(command)
            fi
    fi
}

/**
  * Sends the given command to all Workers using serial command propagation
  * mode. This means sending every command in the blocking way.
  */
inline propagate_command_in_lifo(command)
{
    if
    ::  command == START || command == PAUSED   ->
            covariant_propagation(command, true)
    ::  else                                    ->
            contravariant_propagation(command)
    fi
}

/**
  * Sends the given command to all Workers using parallel command propagation
  * mode. This means sending commands asynchronously first to every Worker, and
  * then waiting for them move to an appropriate state.
  */
inline propagate_command_in_parallel(command)
{
    printf("Supervisor propagating command %e...\n", command);
    covariant_propagation(command, false);
    do
    ::  j < N  ->
            if
            ::  command == START    -> wait_for_START_mask(j)
            ::  command == CONTINUE -> wait_for_RESUME_mask(j)
            ::  command == PAUSE    -> wait_for_PAUSE_mask(j)
            ::  command == STOP     -> wait_for_HALT_mask(j)
            fi
            j++
    ::  else   ->
            j = 1;
            break
    od
}

/** 
 * Checks whether of not there all Workers have moved to the state STOPPED or if 
 * there exists a worker in state ABORTED and sets the appropriate booleans.
 */
inline check_worker_states()
{
    all_workers_stopped = true;
    do
    ::  j < N   ->
            all_workers_stopped     =
                all_workers_stopped && get_state(j) == STOPPED;
            exists_aborted_worker   =
                exists_aborted_worker || get_state(j) == ABORTED;
            j++
    ::  else    ->
            j = 1;
            break
    od
}

inline sv_start_sync()
{
    set_command(0, START);
    run Supervisor();
    wait_for_START_mask(0);
}

/** 
 * Models the method ADAPRO::Control::Supervisor::prepare.
 */
inline sv_prepare()
{
    propagate_command(START);
}

/** 
 * Models the method ADAPRO::Control::Supervisor::execute.
 */
inline sv_execute()
{
    executing[0] = true;
    check_worker_states();
    if
    ::  all_workers_stopped     -> 
            printf("Supervisor will stop because all Workers have stopped...\n");
            stop(0, false)
    ::  exists_aborted_worker   -> 
            printf("Supervisor will stop because some Workers have aborted...\n");
            stop(0, false)
    ::  else                    ->
            skip
    fi
    executing[0] = false
}

/** Models the transition callback of ADAPRO::Control::Supervisor. */
inline sv_trans_cb(s)
{
    if
    ::  s == RUNNING                    ->
            propagate_command(CONTINUE)
    ::  s == PAUSED                     ->
            propagate_command(PAUSE)
    ::  s == ABORTING || s == STOPPING  ->
            propagate_command(STOP)
    ::  else                            ->
            skip
    fi
}

inline sv_covariant_transition(state, command, next)
{
    print_state_transition(0, state, command, next);
    set_state(0, next);
    sv_trans_cb(next)
}

inline sv_contravariant_transition(state, command, next)
{
    sv_trans_cb(next);
    print_state_transition(0, state, command, next);
    set_state(0, next)
}

/** 
 * Models the constructor of Supervisor, which first sets its own state and
 * command and then calls the Worker constructors.
 */
inline sv_ctor(i)
{
    d_step
    {
        if
        :: true -> serialize_commands = true
        :: true -> serialize_commands = false
        fi
        all_workers_stopped     = false;
        exists_aborted_worker   = false;
        supervisor_started      = false;
        do
        ::  i < N   ->
                ctor(i);
                i++
        ::  else    ->
                break
        od
    }
}

/**
 * Models the destructor of Supervisor.
 */
inline sv_dtor(i)
{
    d_step
    {
        do
        ::  i < N   ->
                dtor(i);
                i++
        ::  else    ->
                break
        od
    }
}

/** Models the ADAPRO Supervisor Thread. */
proctype Supervisor()
{
    /** 
     * The variable j is a local index variable that Supervisor uses for
     * iterating over Workers. Supervisor itself is the Thread number 0, so
     * this variable needs to always stay in the open interval ]0,N[.
     */
    byte j = 1;

    /* Startup: */
    get_command(0) == START;
    sv_covariant_transition(READY, START, STARTING);
    set_command(0, CONTINUE);
    sv_prepare();

    /* Execution: */
    do
    ::  get_command(0) == CONTINUE                          -> 
            assert(get_state(0) == STARTING || get_state(0) == RUNNING || 
                get_state(0) == PAUSED);
            if
            ::  get_state(0) == STARTING    ->
                    sv_covariant_transition(STARTING, CONTINUE, RUNNING)
            ::  get_state(0) == PAUSED      ->
                    sv_covariant_transition(PAUSED, CONTINUE, RUNNING)
            ::  else                        ->
                    skip
            fi
            sv_execute()
    ::  get_command(0) == PAUSE                             ->
            if
            ::  get_state(0) == PAUSED      ->
                    get_command(0) != PAUSED
            ::  else                        ->
                    assert(get_state(0) == STARTING || get_state(0) == RUNNING || 
                        get_state(0) == STARTING);
                    if
                    ::  get_state(0) == STARTING || get_state(0) == RUNNING ->
                            sv_contravariant_transition(RUNNING, PAUSE, PAUSED)
                    ::  else                                                ->
                            skip
                    fi
            fi
    ::  get_command(0) == STOP || get_command(0) == ABORT   ->
            break
    od

    /* Shutdown: */
    if
    ::  get_command(0) == STOP      ->
            assert(get_state(0) == STARTING || get_state(0) == RUNNING || 
                get_state(0) == PAUSED);
            sv_covariant_transition(get_state(0), STOP, STOPPING);
            sv_contravariant_transition(STOPPING, STOP, STOPPED)
    ::  get_command(0) == ABORT     ->
            assert(get_state(0) == STARTING || get_state(0) == RUNNING || 
                get_state(0) == STOPPING);
            sv_covariant_transition(get_state(0), ABORT, ABORTING);
            sv_contravariant_transition(ABORTING, ABORT, ABORTED)
    ::  else                        ->
            assert(false)
    fi
}

init
{
    byte i = 0;
    assert_all(i, 0, 0);
    sv_ctor(i);
    i = 0;
    assert_all(i, READY, CONTINUE);
    printf("Init starts Supervisor...\n");
    sv_start_sync();
    do
    ::  if
        ::  get_state(0) == RUNNING -> 
                printf("Init pauses Supervisor...\n");
                if
                ::  true -> pause(0, true)
                ::  true -> pause(0, false)
                fi
        ::  get_state(0) == PAUSED  -> 
                printf("Init resumes Supervisor...\n");
                if
                ::  true -> resume(0, true)
                ::  true -> resume(0, false)
                fi
        ::  true -> skip
        fi
    ::  break
    od
    if
    ::  printf("Init stops Supervisor...\n");
        if
        ::  true -> stop(0, true)
        ::  true -> stop(0, false)
        fi
    ::  true -> skip
    fi
    wait_for_HALT_mask(0);
    i = 0;
    sv_dtor(i);
    i = 0;
    assert_all(i, 0, 0)
}

