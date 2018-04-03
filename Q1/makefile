all: driver matrix stack
	gcc -fopenmp -g -o driver driver.o matrix.o stack.o

driver: driver.c
	gcc -fopenmp -finline-functions	-g -c driver.c

stack: stack.c
	gcc -fopenmp -g -c stack.c

matrix: matrix.c
	gcc -fopenmp -g -c matrix.c
