main : nat0.o main.c
	gcc nat0.o main.c -o main

nat0.o : nat0.c nat0.h bool.h
	gcc -c nat0.c -o nat0.o
	
clean :
	rm *.o main