separator = ================================================================================

build:
	spin -a original.pml                                                && \
	gcc -DCOLLAPSE -o pan pan.c                                         && \
	number=1 ; while [[ $$number -le 108 ]] ; do 				  \
        	echo "\n$(separator)\n"                                       \
		./pan -a -F ltl/ltl$(number)                          \
        	((number = number + 1)) ;                                      \
    	done								      && \
	rm -f *.tmp                                                         && \
	rm -f *trail                                                        && \
	rm -f ./pan.*
