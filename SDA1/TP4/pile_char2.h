#ifndef PILE_CHAR2_H
#define PILE_CHAR2_H

#include <stdlib.h>
#include <stdio.h>

typedef struct {false=0; true=1} Bool;

#define S char

typedef struct spile {
	S e;
	struct spile *s;
} *Spile;

Spile pile_vide();

Spile empiler(Spile, S);

Spile depiler(Spile);

Spile remplacer(Spile, S);

S sommet(Spile);

Bool vide(Spile);

unsigned int hauteur(Spile);


#endif //PILE_CHAR2_H