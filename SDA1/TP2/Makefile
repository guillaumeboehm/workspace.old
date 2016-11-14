main : vect.o vect3d.o main.c
	gcc vect.o vect3d.o main.c -o main

vect.o : vect.c vect.h
	gcc -c vect.c -o vect.o

vect3d.o : vect3d.h vect3d.c
	gcc -c vect3d.c -o vect3d.o
	
clean :
	rm *.o main
	