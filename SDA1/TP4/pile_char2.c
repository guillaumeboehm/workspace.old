//file pile_char2.c
#include "pile_char2.h"

Spile pile_vide(){
	Spile p;
	return p;
}

Spile empiler(Spile p, S e){
	Spile pt = malloc(sizeof(struct spile));
	pt->e = e;
	pt->s = p;
	return pt;
}

Spile depiler(Spile p){
	return p->s;
}

Spile remplacer(Spile p, S e){
	p->e = e;
	return p;
}

S sommet(Spile p){
	return p->e;
}

Bool vide(Spile p){
	return p==NULL;
}

unsigned int hauteur(Spile p){
	if(p==NULL)
		return 0;
	else
		return 1+hauteur(depiler(p));
}



