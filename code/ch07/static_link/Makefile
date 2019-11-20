files: p

all: $(filse)

p : main2.c libvector.a
	gcc -o p main2.c ./libvector.a

libvector.a : addvec.o multvec.o
	ar rcs libvector.a addvec.o multvec.o

addvec.o : addvec.c
	gcc -c addvec.c

multvec.o : multvec.c
	gcc -c multvec.c

clean :
	rm *.o *.a p
