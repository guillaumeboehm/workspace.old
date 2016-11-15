#ifndef PILE_CHAR_H
#define PILE_CHAR_H

#include <stdlib.h>
#include <stdio.h>

typedef struct {false=0; true=1} Bool;

#define MAX_P 50
#define S char
typedef struct {
	S tab[MAX_P];
	unsigned int h;
} Pile;

//constructeur de la pile
Pile pile_vide();

//empile un entier au sommet de la pile
Pile empiler(Pile, S);

Pile depiler(Pile);

Pile remplacer(Pile, S);

S sommet(Pile);

Bool vide(Pile);

unsigned int hauteur(Pile);

#endif //PILE_CHAR_H