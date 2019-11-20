files : swap.o main.o p

all : $(files)

swap.o : swap.c
	gcc -c swap.c

main.o : main.c
	gcc -c main.c

p : swap.o main.o
	gcc -o p main.o swap.o	

clean :
	rm *.o p	