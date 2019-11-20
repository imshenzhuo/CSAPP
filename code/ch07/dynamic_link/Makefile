files: prog

all: $(filse)

prog : main2.c libvector.so
	gcc -o prog main2.c ./libvector.so

libvector.so : addvec.c multvec.c
	gcc -shared -fPIC -o libvector.so addvec.c multvec.c
#	ar rcs libvector.a addvec.o multvec.o

addvec.o : addvec.c
	gcc -c addvec.c

multvec.o : multvec.c
	gcc -c multvec.c

clean :
	rm *.o *.a p
