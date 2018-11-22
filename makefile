all: shell.o
	gcc shell.o
shell.o: shell.c shell.o
	gcc -c shell.c
run:
	./a.out