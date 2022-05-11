separator = ================================================================================

build:
	spin -a original.pml                                                 && \
	gcc -DCOLLAPSE -o pan pan.c                                         && \
#	echo "\n$(separator)\n"                                              && \
#	./pan -a -f    -n -N configuration_safety                            && \
	echo "\n$(separator)\n"                                             && \
	./pan -a -f    -n -m100000 -w30 -N liveness                         && \
	echo "\n$(separator)\n"                                             && \
	./pan -a -f    -n -m100000 -w28 -N fairness                         && \
	echo "\n$(separator)\n"                                             && \
	rm -f *.tmp                                                         && \
	rm -f *trail                                                        && \
	rm -f ./pan.*
