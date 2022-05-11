separator = ================================================================================

build:
	spin -a original.pml                                                 && \
	gcc -DCOLLAPSE -o pan pan.c                                         && \
#	echo "\n$(separator)\n"                                              && \
#	./pan -a -f    -n -N configuration_safety                            && \
	echo "\n$(separator)\n"                                             && \
	./pan -a -f    -n -N fsm_ready                                      && \
	echo "\n$(separator)\n"                                             && \
	./pan -a -f    -n -m100000 -w26 -N fsm_starting                     && \
	echo "\n$(separator)\n"                                             && \
	./pan -a       -n -m100000 -w28 -N fsm_running                      && \
	echo "\n$(separator)\n"                                             && \
	./pan -a       -n -m100000 -w26 -N fsm_paused                       && \
	echo "\n$(separator)\n"                                             && \
	./pan -a -f    -n -m100000 -w28 -N fsm_stopping                     && \
	echo "\n$(separator)\n"                                             && \
	./pan -a       -n -m100000 -w26 -N fsm_stopped                      && \
	echo "\n$(separator)\n"                                             && \
	./pan -a -f    -n -m100000 -w26 -N fsm_aborting                     && \
	echo "\n$(separator)\n"                                             && \
	./pan -a       -n -m100000 -w26 -N fsm_aborted                      && \
	echo "\n$(separator)\n"                                             && \
	./pan -a -f -i -n -m100000 -w28 -N abort_is_undoable                && \
	echo "\n$(separator)\n"                                             && \
	./pan -a    -i -n -m100000 -w26 -N supervisor_is_the_first_thread   && \
	echo "\n$(separator)\n"                                             && \
	./pan -a    -i -n -m100000 -w26 -N supervisor_constructs_workers    && \
	echo "\n$(separator)\n"                                             && \
	./pan -a -f -i -n -m100000 -w26 -N supervisor_stops_after_all_workers_stop && \
	echo "\n$(separator)\n"                                             && \
	./pan -a -f -i -n -m100000 -w28 -N supervisor_stops_after_some_workers_abort && \
	echo "\n$(separator)\n"                                             && \
	./pan -a    -i -n -m100000 -w26 -N supervisor_never_aborts          && \
	echo "\n$(separator)\n"                                             && \
	./pan -a -f -i -n -m100000 -w26 -N supervisor_halts_last            && \
	echo "\n$(separator)\n"                                             && \
	./pan -a -f    -n -m100000 -w30 -N liveness                         && \
	echo "\n$(separator)\n"                                             && \
	./pan -a -f    -n -m100000 -w28 -N fairness                         && \
	echo "\n$(separator)\n"                                             && \
	rm -f *.tmp                                                         && \
	rm -f *trail                                                        && \
	rm -f ./pan.*
