/** 
 * \file jeu.c 
 * code pour le jeu
 */

#include "../include/jeu.h"

/** 
 * \fn int compte_voisins_vivants_c (int i, int j, grille g);
 * \param i coordonnee x de la cellule
 * \param j coordonnee y de la cellule
 * \param g grille du jeu
 * \brief compte le nombre de voisins vivants de la cellule (i,j)
 * les bords sont cycliques.
 *
 * \return le nombre de voisins vivants
 */
int compte_voisins_vivants_c (int i, int j, grille g){
	int v = 0, l=g.nbl, c = g.nbc;
	v+= est_vivante(modulo(i-1,l),modulo(j-1,c),g);
	v+= est_vivante(modulo(i-1,l),modulo(j,c),g);
	v+= est_vivante(modulo(i-1,l),modulo(j+1,c),g);
	v+= est_vivante(modulo(i,l),modulo(j-1,c),g);
	v+= est_vivante(modulo(i,l),modulo(j+1,c),g);
	v+= est_vivante(modulo(i+1,l),modulo(j-1,c),g);
	v+= est_vivante(modulo(i+1,l),modulo(j,c),g);
	v+= est_vivante(modulo(i+1,l),modulo(j+1,c),g);

	return v; 
}

/** 
 * \fn int compte_voisins_vivants_nc (int i, int j, grille g);
 * \param i coordonnee x de la cellule
 * \param j coordonnee y de la cellule
 * \param g grille du jeu
 * \brief compte le nombre de voisins vivants de la cellule (i,j)
 * les bords sont non-cycliques.
 *
 * \return le nombre de voisins vivants
 */
int compte_voisins_vivants_nc (int i, int j, grille g){
	int v = 0, l=g.nbl, c = g.nbc;
	
	if(i>0 && j>0) 	v+= est_vivante(modulo(i-1,l),modulo(j-1,c),g);
	if(i>0) 	v+= est_vivante(modulo(i-1,l),modulo(j,c),g);
	if(i>0 && j<l) 	v+= est_vivante(modulo(i-1,l),modulo(j+1,c),g);
	if(j>0) 	v+= est_vivante(modulo(i,l),modulo(j-1,c),g);
	if(j>0) 	v+= est_vivante(modulo(i,l),modulo(j+1,c),g);
	if(i<c && j>0) 	v+= est_vivante(modulo(i+1,l),modulo(j-1,c),g);
	if(i<c) 	v+= est_vivante(modulo(i+1,l),modulo(j,c),g);
	if(i<c && j<l) 	v+= est_vivante(modulo(i+1,l),modulo(j+1,c),g);

	return v; 
}

/**
 * \fn int compte_voisins_vivants (int i, int j, grille g);
 * \param g grille du jeu
 * \param gc grille temporaire pour le jeu
 * \brief fait évoluer la grille g d'un pas de temps
 *
 */
void evolue (grille *g, grille *gc){
	copie_grille (*g,*gc); // copie temporaire de la grille
	int i,j,l=g->nbl, c = g->nbc,v;
	for (i=0; i<l; i++)
	{
		for (j=0; j<c; ++j)
		{
			v = compte_voisins_vivants (i, j, *gc);
			if (est_vivante(i,j,*g)) 
			{ // evolution d'une cellule vivante
				if(v==2 || v==3) set_vivante (i,j,*g);
				else if ( v!=2 && v!= 3 ) set_morte(i,j,*g);
			}
			else 
			{ // evolution d'une cellule morte
				if ( v==3 && !est_non_viable(i,j,*g)) set_vivante (i,j,*g);
			}
		}
	}
	return;
}


void est_oscillante(grille* gsource, grille* gc){

	int l = gsource->nbl;
	int c = gsource->nbc;

	//copie la grille source dans un grille temporaire
	grille g;
	alloue_grille(l, c, &g);

	copie_grille(*gsource, g);
	/*********************************************/

	const int MAX_STEP = 100;

	int same = 0;
	int periode;
	grille tab[100];

	int step = 0;

	while (step<MAX_STEP && same==0)
	{
		evolue(&g,gc);
		for(unsigned int i=step-1; i>=0; --i)
			if(egal_grille(g, tab[i])){
				same = 1;
				periode = step-i;
			}

		//ajout de l'etat de la grille au tableau
		alloue_grille(l, c, &tab[step]);
		copie_grille(*gsource, tab[step++]);
	}
	for(unsigned int i=0; i<step; ++i){
		libere_grille(&tab[i]);
	}

	if(same == 0)
		printf("La grille oscille au bout de %d pas\n", periode);
	else
		printf("La grille n'est pas oscillatoire au bout de 100 pas\n");


	return;
}