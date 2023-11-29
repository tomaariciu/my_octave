build:
	gcc -g my_octave.c commands.c matrix.c allocation.c operations.c -Wall -Wextra -std=c99 -pedantic -o my_octave
run:
	./my_octave
pack:
	zip -FSr 312CA_AriciuToma_Tema2.zip README Makefile *.c *.h
clean:
	rm my_octave