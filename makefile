assemble:
	gcc -o assemble -std=c11 -Wall -W -ggdb3 *.c *.h
	
clean:
	rm assemble
