main: libjeu
	gcc -o bin/main obj/main.o obj/io.o -ljeu -L lib/

libjeu: obj/main.o obj/grille.o obj/io.o obj/jeu.o
	ar -crv lib/libjeu.a obj/grille.o obj/jeu.o
	ranlib lib/libjeu.a

obj/main.o: src/main.c include/grille.h include/io.h include/jeu.h
	gcc -c src/main.c -o obj/main.o

obj/grille.o: src/grille.c include/grille.h
	gcc -c src/grille.c -o obj/grille.o

obj/io.o: src/io.c include/io.h
	gcc -c src/io.c -o obj/io.o

obj/jeu.o: src/jeu.c include/jeu.h
	gcc -c src/jeu.c -o obj/jeu.o

clean:
	rm obj/*.o bin/main

archive:
	tar -czvf BOEHM_Guillaume_Jeu_De_La_Vie.tar.gz src include obj lib doc Makefile