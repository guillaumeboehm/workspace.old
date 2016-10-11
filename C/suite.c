//suite.c

#include "suite.h"

/*constructeur a vide*/
suite s_vide(){
	suite u;
	u.val = (int*) malloc(LG_MAX*sizeof(int));
	u.lg = 0;
	return u;
}
/**************************/

/*constructeur avec une valeur constante*/
suite s_const(int _lg, int _val){
	suite u = s_vide();
	u.lg = _lg;
	for(unsigned int i = 0; i<u.lg; ++i)
		u.val[i] = _val;
	return u;
}
/****************************/

/*constructeur avec une tableau en param*/
suite s_t2s(int tab[], int _lg){ //essayer en passant la referance (si existe en c)
	suite u = s_vide();
	u.lg = _lg;
	for(unsigned int i = 0; i<_lg; ++i)
		u.val[i] = tab[i];
	return u;
}
/****************************/

/*ajout d'un element a la suite*/
suite s_adj(int t, suite u){
	u.val[u.lg++] = t;
	return u;
}
/******************************/

/*retourne la longueur de la suite*/
int s_longueur(suite u){
	return u.lg;
}
/***************************/

/*retourne le terme de la suite a la position i*/
int s_ieme(suite u, int i){
	return u.val[i];
}
/******************************/

/*modifie une valeur de la suite*/
suite s_modif(suite u, int i, int elt){
	u.val[i] = elt;
	return u;
}
/*******************************/

/*copie une suite dans une autre*/
suite s_copy(suite u){
	suite v = s_t2s(u.val, u.lg);
	return v;
}
/*******************************/

/*retourne la valeur la plus haute de la suite*/
int s_max(suite u){
	int max = u.val[0];
	for(unsigned int i=0; i<u.lg; ++i)
		if(u.val[i]>max) max = u.val[i];
	return max;
}
/********************************/

/*retourne l'indice de la plus haute valeur de la suite*/
int s_imax(suite u){
	int max = s_max(u);
	for(unsigned int i=0; i<u.lg; ++i)
		if(u.val[i]==max) return i;
}
/**********************************/

/*affiche la suite*/
void s_print(suite u){
	printf("[");
	for(unsigned int i = 0; i<u.lg-1; ++i)
		printf("%d,",u.val[i]);
	printf("%d]\n",u.val[u.lg-1]);
}
/***********************************/