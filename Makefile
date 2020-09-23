CC=gcc
main: task
	
task: main.o help_func.o
	$(CC) main.o help_func.o -o main
	
main.o: main.c
	$(CC) -c main.c
	
help_func.o:
	$(CC) -c help_func.c
	
clean: 
	rm -rf *.o main
