# 1 "test.pml"
# 1 "<built-in>"
# 1 "<command-line>"
# 31 "<command-line>"
# 1 "/usr/include/stdc-predef.h" 1 3 4
# 32 "<command-line>" 2
# 1 "test.pml"
# 150 "test.pml"
ltl fsm_ready
{
    (states[0] == 0 U ((states[0] == READY) W (states[0] == STARTING))) && (states[1] == 0 U ((states[1] == READY) W (states[1] == STARTING))) && (states[2] == 0 U ((states[2] == READY) W (states[2] == STARTING)))
}




ltl fsm_starting
{
    []((states[0] == STARTING -> (states[0] == STARTING U (states[0] == RUNNING || states[0] == PAUSED || states[0] == STOPPING || states[0] == ABORTING))) && (states[1] == STARTING -> (states[1] == STARTING U (states[1] == RUNNING || states[1] == PAUSED || states[1] == STOPPING || states[1] == ABORTING))) && (states[2] == STARTING -> (states[2] == STARTING U (states[2] == RUNNING || states[2] == PAUSED || states[2] == STOPPING || states[2] == ABORTING))))
}




ltl fsm_running
{
    []((states[0] == RUNNING -> ((states[0] == RUNNING) W (states[0] == PAUSED || states[0] == STOPPING || states[0] == ABORTING))) && (states[1] == RUNNING -> ((states[1] == RUNNING) W (states[1] == PAUSED || states[1] == STOPPING || states[1] == ABORTING))) && (states[2] == RUNNING -> ((states[2] == RUNNING) W (states[2] == PAUSED || states[2] == STOPPING || states[2] == ABORTING))))
}




ltl fsm_paused
{
    []((states[0] == PAUSED -> ((states[0] == PAUSED) W (states[0] == RUNNING || states[0] == STOPPING))) && (states[1] == PAUSED -> ((states[1] == PAUSED) W (states[1] == RUNNING || states[1] == STOPPING))) && (states[2] == PAUSED -> ((states[2] == PAUSED) W (states[2] == RUNNING || states[2] == STOPPING))))
}




ltl fsm_stopping
{
    [](([](states[0] == STOPPING -> (states[0] == STOPPING U (states[0] == STOPPED || states[0] == ABORTING)))) && ([](states[1] == STOPPING -> (states[1] == STOPPING U (states[1] == STOPPED || states[1] == ABORTING)))) && ([](states[2] == STOPPING -> (states[2] == STOPPING U (states[2] == STOPPED || states[2] == ABORTING)))))
}





ltl fsm_stopped
{
    [](((states[0] == STOPPED) -> ((states[0] == STOPPED) W [](states[0] == 0))) && ((states[1] == STOPPED) -> ((states[1] == STOPPED) W [](states[1] == 0))) && ((states[2] == STOPPED) -> ((states[2] == STOPPED) W [](states[2] == 0))))
}




ltl fsm_aborting
{
    [](([](states[0] == ABORTING -> (states[0] == ABORTING U (states[0] == ABORTED)))) && ([](states[1] == ABORTING -> (states[1] == ABORTING U (states[1] == ABORTED)))) && ([](states[2] == ABORTING -> (states[2] == ABORTING U (states[2] == ABORTED)))))
}





ltl fsm_aborted
{
    [](((states[0] == ABORTED) -> ((states[0] == ABORTED) W [](states[0] == 0))) && ((states[1] == ABORTED) -> ((states[1] == ABORTED) W [](states[1] == 0))) && ((states[2] == ABORTED) -> ((states[2] == ABORTED) W [](states[2] == 0))))
}





ltl abort_is_undoable
{
    [](((commands[0] == ABORT) -> ((commands[0] == ABORT) W [](commands[0] == 0))) && ((commands[1] == ABORT) -> ((commands[1] == ABORT) W [](commands[1] == 0))) && ((commands[2] == ABORT) -> ((commands[2] == ABORT) W [](commands[2] == 0))))
}





ltl supervisor_is_the_first_thread
{
    []((states[0] == 0) -> (states[1] == 0 && states[2] == 0))
}







ltl supervisor_constructs_workers
{
    []((states[1] == READY || states[2] == READY) -> !(states[0] == 0))
}







ltl supervisor_stops_after_all_workers_stop
{
    []((states[1] == STOPPED && states[2] == STOPPED) ->
        ([]<>(states[0] == PAUSED) || <>(states[0] == STOPPED)))
}





ltl supervisor_stops_after_some_workers_abort
{
    []((states[1] == ABORTED || states[2] == ABORTED) ->
        ([]<>(states[0] == PAUSED) || <>(states[0] == STOPPED)))
}




ltl supervisor_never_aborts {!<>(states[0] == ABORTED || commands[0] == ABORT)}




ltl supervisor_halts_last
{
    []((states[0] == STOPPING || states[0] == ABORTING) -> <>((states[1] == STOPPED || states[1] == ABORTED || states[1] == 0) && (states[2] == STOPPED || states[2] == ABORTED || states[2] == 0)))
}

ltl liveness
{
    ([]<>((states[0] == RUNNING && commands[0] == CONTINUE) -> (executing[0])) && []<>((states[1] == RUNNING && commands[1] == CONTINUE) -> (executing[1])) && []<>((states[2] == RUNNING && commands[2] == CONTINUE) -> (executing[2]))) W (states[0] == STOPPING || states[0] == ABORTING)
}

ltl fairness
{
    (([]<>(states[0] == RUNNING && commands[0] == CONTINUE) -> []<>(executing[0])) && ([]<>(states[1] == RUNNING && commands[1] == CONTINUE) -> []<>(executing[1])) && ([]<>(states[2] == RUNNING && commands[2] == CONTINUE) -> []<>(executing[2])))
}
# 301 "test.pml"
mtype = {READY, STARTING, RUNNING, PAUSED, STOPPING, STOPPED, ABORTING, ABORTED};
# 311 "test.pml"
mtype = {START, CONTINUE, PAUSE, STOP, ABORT};
# 324 "test.pml"
inline print_state_transition(i, state, command, next)
{
    if
    :: i == 0 && command == 0 ->
            printf("Supervisor: (%e, _) -> %e\n", state, next)
    :: i == 0 && command > 0 ->
            printf("Supervisor: (%e, %e) -> %e\n", state, command, next)
    :: i > 0 && command == 0 ->
            printf("Worker %d: (%e, _) -> %e\n", i, state, next)
    :: i > 0 && command > 0 ->
            printf("Worker %d: (%e, %e) -> %e\n", i, state, command, next)
    fi
}




mtype states[3];


mtype commands[3];


bool executing[3];
# 393 "test.pml"
inline prepare(i)
{
    if
    :: true -> abort(i)
    :: true -> atomic { if :: PAUSE == START && commands[i] == CONTINUE -> assert(states[i] == READY); commands[i] = START :: PAUSE == PAUSE && commands[i] == CONTINUE -> assert(states[i] == STARTING || states[i] == RUNNING); commands[i] = PAUSE :: PAUSE == CONTINUE && (commands[i] == START || commands[i] == PAUSE) -> assert(states[i] == STARTING || states[i] == PAUSED); commands[i] = CONTINUE :: PAUSE == STOP && (commands[i] == CONTINUE || commands[i] == PAUSE) -> assert(states[i] == STARTING || states[i] == RUNNING || states[i] == PAUSED); commands[i] = STOP :: PAUSE == ABORT -> assert(states[i] != READY); commands[i] = ABORT :: else -> printf("Thread %d ignores command %e.\n", i, commands[i]) fi }
    :: true -> atomic { if :: STOP == START && commands[i] == CONTINUE -> assert(states[i] == READY); commands[i] = START :: STOP == PAUSE && commands[i] == CONTINUE -> assert(states[i] == STARTING || states[i] == RUNNING); commands[i] = PAUSE :: STOP == CONTINUE && (commands[i] == START || commands[i] == PAUSE) -> assert(states[i] == STARTING || states[i] == PAUSED); commands[i] = CONTINUE :: STOP == STOP && (commands[i] == CONTINUE || commands[i] == PAUSE) -> assert(states[i] == STARTING || states[i] == RUNNING || states[i] == PAUSED); commands[i] = STOP :: STOP == ABORT -> assert(states[i] != READY); commands[i] = ABORT :: else -> printf("Thread %d ignores command %e.\n", i, commands[i]) fi }
    :: true -> skip
    fi
}





inline execute(i)
{
    executing[i] = true;
    if
    :: true -> abort(i)

    :: true -> atomic { if :: STOP == START && commands[i] == CONTINUE -> assert(states[i] == READY); commands[i] = START :: STOP == PAUSE && commands[i] == CONTINUE -> assert(states[i] == STARTING || states[i] == RUNNING); commands[i] = PAUSE :: STOP == CONTINUE && (commands[i] == START || commands[i] == PAUSE) -> assert(states[i] == STARTING || states[i] == PAUSED); commands[i] = CONTINUE :: STOP == STOP && (commands[i] == CONTINUE || commands[i] == PAUSE) -> assert(states[i] == STARTING || states[i] == RUNNING || states[i] == PAUSED); commands[i] = STOP :: STOP == ABORT -> assert(states[i] != READY); commands[i] = ABORT :: else -> printf("Thread %d ignores command %e.\n", i, commands[i]) fi }
    :: true -> skip
    fi
    executing[i] = false
}





inline finish(i)
{
    if
    :: true -> abort(i)
    :: true -> skip
    fi
}


inline abort(i)
{
    assert(_pid != 1);
    atomic { if :: ABORT == START && commands[i] == CONTINUE -> assert(states[i] == READY); commands[i] = START :: ABORT == PAUSE && commands[i] == CONTINUE -> assert(states[i] == STARTING || states[i] == RUNNING); commands[i] = PAUSE :: ABORT == CONTINUE && (commands[i] == START || commands[i] == PAUSE) -> assert(states[i] == STARTING || states[i] == PAUSED); commands[i] = CONTINUE :: ABORT == STOP && (commands[i] == CONTINUE || commands[i] == PAUSE) -> assert(states[i] == STARTING || states[i] == RUNNING || states[i] == PAUSED); commands[i] = STOP :: ABORT == ABORT -> assert(states[i] != READY); commands[i] = ABORT :: else -> printf("Thread %d ignores command %e.\n", i, commands[i]) fi };
}







inline ctor(i)
{
    d_step
    {
        states[i] = READY;
        commands[i] = CONTINUE
    }
}

inline dtor(i)
{
    d_step
    {
        states[i] = 0;
        commands[i] = 0;
        executing[i]= false
    }
}


inline trans_cb(s)
{
    skip
}

inline covariant_transition(state, command, next)
{
    print_state_transition(k, state, command, next);
    states[k] = next;

}

inline contravariant_transition(state, command, next)
{

    print_state_transition(k, state, command, next);
    states[k] = next
}


proctype Thread(byte k)
{

    commands[k] == START;
    covariant_transition(READY, START, STARTING);
    atomic { if :: CONTINUE == START && commands[k] == CONTINUE -> assert(states[k] == READY); commands[k] = START :: CONTINUE == PAUSE && commands[k] == CONTINUE -> assert(states[k] == STARTING || states[k] == RUNNING); commands[k] = PAUSE :: CONTINUE == CONTINUE && (commands[k] == START || commands[k] == PAUSE) -> assert(states[k] == STARTING || states[k] == PAUSED); commands[k] = CONTINUE :: CONTINUE == STOP && (commands[k] == CONTINUE || commands[k] == PAUSE) -> assert(states[k] == STARTING || states[k] == RUNNING || states[k] == PAUSED); commands[k] = STOP :: CONTINUE == ABORT -> assert(states[k] != READY); commands[k] = ABORT :: else -> printf("Thread %d ignores command %e.\n", k, commands[k]) fi };
    prepare(k);


    do
    :: commands[k] == CONTINUE ->
            assert(states[k] == STARTING || states[k] == RUNNING ||
                states[k] == PAUSED);
            if
            :: states[k] == STARTING ->
                    covariant_transition(STARTING, CONTINUE, RUNNING)
            :: states[k] == PAUSED ->
                    covariant_transition(PAUSED, CONTINUE, RUNNING)
            :: else ->
                    skip
            fi
            execute(k)
    :: commands[k] == PAUSE ->
            if
            :: states[k] == PAUSED ->
                    commands[k] != PAUSED
            :: else ->
                    assert(states[k] == STARTING || states[k] == RUNNING ||
                        states[k] == STARTING);
                    if
                    :: states[k] == STARTING || states[k] == RUNNING ->
                            contravariant_transition(RUNNING, PAUSE, PAUSED)
                    :: else ->
                            skip
                    fi
            fi
    :: commands[k] == STOP || commands[k] == ABORT ->
            break
    od


    if
    :: commands[k] == STOP ->
            assert(states[k] == STARTING || states[k] == RUNNING ||
                states[k] == PAUSED);
            covariant_transition(states[k], STOP, STOPPING);
            finish(k);
            contravariant_transition(STOPPING, STOP, STOPPED)
    :: commands[k] == ABORT ->
            assert(states[k] == STARTING || states[k] == RUNNING ||
                states[k] == STOPPING);
            covariant_transition(states[k], ABORT, ABORTING);
            contravariant_transition(ABORTING, ABORT, ABORTED)
    :: else ->
            assert(false)
    fi
}




inline wait_for_START_mask(i)
{
    if
    :: _pid == 0 ->
            printf("Init is waiting for START mask on Thread %d...\n", i)
    :: _pid == 1 ->
            printf("Supervisor is waiting for START mask on Thread %d...\n", i)
    :: _pid > 1 ->
            printf("Worker %d is waiting for START mask on Thread %d...\n", _pid - 1, i)
    fi
    states[i] == RUNNING ||
    states[i] == PAUSED ||
    states[i] == STOPPING ||
    states[i] == STOPPED ||
    states[i] == ABORTING ||
    states[i] == ABORTED;
    printf("Waiting ended.\n")
}


inline wait_for_PAUSE_mask(i)
{
    if
    :: _pid == 0 ->
            printf("Init is waiting for PAUSED mask on Thread %d...\n", i)
    :: _pid == 1 ->
            printf("Supervisor is waiting for PAUSED mask on Thread %d...\n", i)
    :: _pid > 1 ->
            printf("Worker %d is waiting for PAUSED mask on Thread %d...\n", _pid - 1, i)
    fi
    states[i] == PAUSED ||
    states[i] == STOPPING ||
    states[i] == STOPPED ||
    states[i] == ABORTING ||
    states[i] == ABORTED;
    printf("Waiting ended.\n")
}


inline wait_for_RESUME_mask(i)
{
    if
    :: _pid == 0 ->
            printf("Init is waiting for RESUME mask on Thread %d...\n", i)
    :: _pid == 1 ->
            printf("Supervisor is waiting for RESUME mask on Thread %d...\n", i)
    :: _pid > 1 ->
            printf("Worker %d is waiting for RESUME mask on Thread %d...\n", _pid - 1, i)
    fi
    states[i] == RUNNING ||
    states[i] == STOPPING ||
    states[i] == STOPPED ||
    states[i] == ABORTING ||
    states[i] == ABORTED;
    printf("Waiting ended.\n")
}


inline wait_for_HALT_mask(i)
{
    if
    :: _pid == 0 ->
            printf("Init is waiting for HALT mask on Thread %d...\n", i)
    :: _pid == 1 ->
            printf("Supervisor is waiting for HALT mask on Thread %d...\n", i)
    :: _pid > 1 ->
            printf("Worker %d is waiting for HALT mask on Thread %d...\n", _pid - 1, i)
    fi
    states[i] == STOPPED ||
    states[i] == ABORTED;
    printf("Waiting ended.\n")
}


inline wait_for_ABORT_mask(i)
{
    if
    :: _pid == 0 ->
            printf("Init is waiting for ABORTED mask on Thread %d...\n", i)
    :: _pid == 1 ->
            printf("Supervisor is waiting for ABORTED mask on Thread %d...\n", i)
    :: _pid > 1 ->
            printf("Worker %d is waiting for ABORTED mask on Thread %d...\n", _pid - 1, i)
    fi
    states[i] == ABORTED;
    printf("Waiting ended.\n")
}





inline start(i, wait)
{
    atomic { if :: START == START && commands[i] == CONTINUE -> assert(states[i] == READY); commands[i] = START :: START == PAUSE && commands[i] == CONTINUE -> assert(states[i] == STARTING || states[i] == RUNNING); commands[i] = PAUSE :: START == CONTINUE && (commands[i] == START || commands[i] == PAUSE) -> assert(states[i] == STARTING || states[i] == PAUSED); commands[i] = CONTINUE :: START == STOP && (commands[i] == CONTINUE || commands[i] == PAUSE) -> assert(states[i] == STARTING || states[i] == RUNNING || states[i] == PAUSED); commands[i] = STOP :: START == ABORT -> assert(states[i] != READY); commands[i] = ABORT :: else -> printf("Thread %d ignores command %e.\n", i, commands[i]) fi };
    run Thread(i);
    if
    :: wait -> wait_for_START_mask(i)
    :: else -> skip
    fi
}





inline pause(i, wait)
{
    atomic { if :: PAUSE == START && commands[i] == CONTINUE -> assert(states[i] == READY); commands[i] = START :: PAUSE == PAUSE && commands[i] == CONTINUE -> assert(states[i] == STARTING || states[i] == RUNNING); commands[i] = PAUSE :: PAUSE == CONTINUE && (commands[i] == START || commands[i] == PAUSE) -> assert(states[i] == STARTING || states[i] == PAUSED); commands[i] = CONTINUE :: PAUSE == STOP && (commands[i] == CONTINUE || commands[i] == PAUSE) -> assert(states[i] == STARTING || states[i] == RUNNING || states[i] == PAUSED); commands[i] = STOP :: PAUSE == ABORT -> assert(states[i] != READY); commands[i] = ABORT :: else -> printf("Thread %d ignores command %e.\n", i, commands[i]) fi };
    if
    :: wait -> wait_for_PAUSE_mask(i)
    :: else -> skip
    fi
}





inline resume(i, wait)
{
    atomic { if :: CONTINUE == START && commands[i] == CONTINUE -> assert(states[i] == READY); commands[i] = START :: CONTINUE == PAUSE && commands[i] == CONTINUE -> assert(states[i] == STARTING || states[i] == RUNNING); commands[i] = PAUSE :: CONTINUE == CONTINUE && (commands[i] == START || commands[i] == PAUSE) -> assert(states[i] == STARTING || states[i] == PAUSED); commands[i] = CONTINUE :: CONTINUE == STOP && (commands[i] == CONTINUE || commands[i] == PAUSE) -> assert(states[i] == STARTING || states[i] == RUNNING || states[i] == PAUSED); commands[i] = STOP :: CONTINUE == ABORT -> assert(states[i] != READY); commands[i] = ABORT :: else -> printf("Thread %d ignores command %e.\n", i, commands[i]) fi };
    if
    :: wait -> wait_for_RESUME_mask(i)
    :: else -> skip
    fi
}





inline stop(i, wait)
{
    atomic { if :: STOP == START && commands[i] == CONTINUE -> assert(states[i] == READY); commands[i] = START :: STOP == PAUSE && commands[i] == CONTINUE -> assert(states[i] == STARTING || states[i] == RUNNING); commands[i] = PAUSE :: STOP == CONTINUE && (commands[i] == START || commands[i] == PAUSE) -> assert(states[i] == STARTING || states[i] == PAUSED); commands[i] = CONTINUE :: STOP == STOP && (commands[i] == CONTINUE || commands[i] == PAUSE) -> assert(states[i] == STARTING || states[i] == RUNNING || states[i] == PAUSED); commands[i] = STOP :: STOP == ABORT -> assert(states[i] != READY); commands[i] = ABORT :: else -> printf("Thread %d ignores command %e.\n", i, commands[i]) fi };
    if
    :: wait -> wait_for_HALT_mask(i)
    :: else -> skip
    fi
}






bool serialize_commands;






bool all_workers_stopped;






bool exists_aborted_worker;
# 715 "test.pml"
bool supervisor_started;





inline assert_all(k, state, command)
{
    d_step
    {
        do
        :: k < 3 ->
                assert(states[k] == state);
                assert(commands[k] == command);
                k++
        :: else ->
                break
        od
        k = 0
    }
}


inline send_command(j, command, wait)
{
    if
    :: command == START ->
            start(j, wait)
    :: command == PAUSE ->
            pause(j, wait)
    :: command == CONTINUE ->
            resume(j, wait)
    :: command == STOP || command == ABORT ->
            stop(j, wait)
    fi
}





inline covariant_propagation(command, wait)
{
    do
    :: j < 3 ->
            send_command(j, command, wait);
            j++
    :: else ->
            j = 1;
            break
    od
}





inline contravariant_propagation(command)
{
    j = 3 - 1;
    do
    :: j > 0 ->
            send_command(j, command, true);
            j--
    :: else ->
            j = 1;
            break
    od
}





inline propagate_command(command)
{
    if
    :: command == CONTINUE && !supervisor_started ->
            printf("Supervisor doesn't propagate the first CONTINUE command.\n");
            supervisor_started = true
    :: else ->
            if
            :: serialize_commands -> propagate_command_in_lifo(command)
            :: else -> propagate_command_in_parallel(command)
            fi
    fi
}





inline propagate_command_in_lifo(command)
{
    if
    :: command == START || command == PAUSED ->
            covariant_propagation(command, true)
    :: else ->
            contravariant_propagation(command)
    fi
}






inline propagate_command_in_parallel(command)
{
    printf("Supervisor propagating command %e...\n", command);
    covariant_propagation(command, false);
    do
    :: j < 3 ->
            if
            :: command == START -> wait_for_START_mask(j)
            :: command == CONTINUE -> wait_for_RESUME_mask(j)
            :: command == PAUSE -> wait_for_PAUSE_mask(j)
            :: command == STOP -> wait_for_HALT_mask(j)
            fi
            j++
    :: else ->
            j = 1;
            break
    od
}





inline check_worker_states()
{
    all_workers_stopped = true;
    do
    :: j < 3 ->
            all_workers_stopped =
                all_workers_stopped && states[j] == STOPPED;
            exists_aborted_worker =
                exists_aborted_worker || states[j] == ABORTED;
            j++
    :: else ->
            j = 1;
            break
    od
}

inline sv_start_sync()
{
    atomic { if :: START == START && commands[0] == CONTINUE -> assert(states[0] == READY); commands[0] = START :: START == PAUSE && commands[0] == CONTINUE -> assert(states[0] == STARTING || states[0] == RUNNING); commands[0] = PAUSE :: START == CONTINUE && (commands[0] == START || commands[0] == PAUSE) -> assert(states[0] == STARTING || states[0] == PAUSED); commands[0] = CONTINUE :: START == STOP && (commands[0] == CONTINUE || commands[0] == PAUSE) -> assert(states[0] == STARTING || states[0] == RUNNING || states[0] == PAUSED); commands[0] = STOP :: START == ABORT -> assert(states[0] != READY); commands[0] = ABORT :: else -> printf("Thread %d ignores command %e.\n", 0, commands[0]) fi };
    run Supervisor();
    wait_for_START_mask(0);
}




inline sv_prepare()
{
    propagate_command(START);
}




inline sv_execute()
{
    executing[0] = true;
    check_worker_states();
    if
    :: all_workers_stopped ->
            printf("Supervisor will stop because all Workers have stopped...\n");
            stop(0, false)
    :: exists_aborted_worker ->
            printf("Supervisor will stop because some Workers have aborted...\n");
            stop(0, false)
    :: else ->
            skip
    fi
    executing[0] = false
}


inline sv_trans_cb(s)
{
    if
    :: s == RUNNING ->
            propagate_command(CONTINUE)
    :: s == PAUSED ->
            propagate_command(PAUSE)
    :: s == ABORTING || s == STOPPING ->
            propagate_command(STOP)
    :: else ->
            skip
    fi
}

inline sv_covariant_transition(state, command, next)
{
    print_state_transition(0, state, command, next);
    states[0] = next;
    sv_trans_cb(next)
}

inline sv_contravariant_transition(state, command, next)
{
    sv_trans_cb(next);
    print_state_transition(0, state, command, next);
    states[0] = next
}





inline sv_ctor(i)
{
    d_step
    {
        if
        :: true -> serialize_commands = true
        :: true -> serialize_commands = false
        fi
        all_workers_stopped = false;
        exists_aborted_worker = false;
        supervisor_started = false;
        do
        :: i < 3 ->
                ctor(i);
                i++
        :: else ->
                break
        od
    }
}




inline sv_dtor(i)
{
    d_step
    {
        do
        :: i < 3 ->
                dtor(i);
                i++
        :: else ->
                break
        od
    }
}


proctype Supervisor()
{





    byte j = 1;


    commands[0] == START;
    sv_covariant_transition(READY, START, STARTING);
    atomic { if :: CONTINUE == START && commands[0] == CONTINUE -> assert(states[0] == READY); commands[0] = START :: CONTINUE == PAUSE && commands[0] == CONTINUE -> assert(states[0] == STARTING || states[0] == RUNNING); commands[0] = PAUSE :: CONTINUE == CONTINUE && (commands[0] == START || commands[0] == PAUSE) -> assert(states[0] == STARTING || states[0] == PAUSED); commands[0] = CONTINUE :: CONTINUE == STOP && (commands[0] == CONTINUE || commands[0] == PAUSE) -> assert(states[0] == STARTING || states[0] == RUNNING || states[0] == PAUSED); commands[0] = STOP :: CONTINUE == ABORT -> assert(states[0] != READY); commands[0] = ABORT :: else -> printf("Thread %d ignores command %e.\n", 0, commands[0]) fi };
    sv_prepare();


    do
    :: commands[0] == CONTINUE ->
            assert(states[0] == STARTING || states[0] == RUNNING ||
                states[0] == PAUSED);
            if
            :: states[0] == STARTING ->
                    sv_covariant_transition(STARTING, CONTINUE, RUNNING)
            :: states[0] == PAUSED ->
                    sv_covariant_transition(PAUSED, CONTINUE, RUNNING)
            :: else ->
                    skip
            fi
            sv_execute()
    :: commands[0] == PAUSE ->
            if
            :: states[0] == PAUSED ->
                    commands[0] != PAUSED
            :: else ->
                    assert(states[0] == STARTING || states[0] == RUNNING ||
                        states[0] == STARTING);
                    if
                    :: states[0] == STARTING || states[0] == RUNNING ->
                            sv_contravariant_transition(RUNNING, PAUSE, PAUSED)
                    :: else ->
                            skip
                    fi
            fi
    :: commands[0] == STOP || commands[0] == ABORT ->
            break
    od


    if
    :: commands[0] == STOP ->
            assert(states[0] == STARTING || states[0] == RUNNING ||
                states[0] == PAUSED);
            sv_covariant_transition(states[0], STOP, STOPPING);
            sv_contravariant_transition(STOPPING, STOP, STOPPED)
    :: commands[0] == ABORT ->
            assert(states[0] == STARTING || states[0] == RUNNING ||
                states[0] == STOPPING);
            sv_covariant_transition(states[0], ABORT, ABORTING);
            sv_contravariant_transition(ABORTING, ABORT, ABORTED)
    :: else ->
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
    :: if
        :: states[0] == RUNNING ->
                printf("Init pauses Supervisor...\n");
                if
                :: true -> pause(0, true)
                :: true -> pause(0, false)
                fi
        :: states[0] == PAUSED ->
                printf("Init resumes Supervisor...\n");
                if
                :: true -> resume(0, true)
                :: true -> resume(0, false)
                fi
        :: true -> skip
        fi
    :: break
    od
    if
    :: printf("Init stops Supervisor...\n");
        if
        :: true -> stop(0, true)
        :: true -> stop(0, false)
        fi
    :: true -> skip
    fi
    wait_for_HALT_mask(0);
    i = 0;
    sv_dtor(i);
    i = 0;
    assert_all(i, 0, 0)
}
