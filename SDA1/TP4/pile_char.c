//file pile_char.c
#include "pile_char.h"

Pile pile_vide(){
	Pile pile;
	pile.h = 0;
	return p;
}

Pile empiler(Pile p, S e){
	p.tab[h++] = e;
	return p;
}

Pile depiler(Pile p){
	p.h--;
	return p;
}

Pile remplacer(Pile p, S e){
	depiler(Pile);
	empiler(Pile, e);
}

S sommet(Pile p){
	return p.tab[h];
}

Bool vide(Pile){
	return p.h==0;
}

unsigned int hauteur(Pile){
	return p.h;
}