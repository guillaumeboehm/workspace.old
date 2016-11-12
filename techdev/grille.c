/** 
 * \file grille.c 
 * code pour les grilles
 */

#include "grille.h"

/** 
 * \fn void alloue_grille(int l, int c, grille* g);
 * \relates grille
 * \param l nombre de lignes de la grille
 * \param c nombre de colonnes de la grille
 * \param g grille a allouer
 * \brief alloue la grille g, et met tous les indices à 0
 *
 */
void alloue_grille (int l, int c, grille* g){
	g->nbl = l;
	g->nbc = c;
	g->cellules = malloc(l*sizeof(int*));
	for(unsigned int i = 0; i<l; ++i) 
		g->cellules[i] = calloc(c, sizeof(int));
}

/** 
 * \fn void libere_grille(grille* g);
 * \relates grille
 * \param g grille a liberer
 * \brief desalloue la grille g
 *
 */
void libere_grille (grille* g){
	
	for(unsigned int i = 0; i<g->nbl; ++i)
		free(g->cellules[i]);
	free(g->cellules);
}

/** 
 * \fn void init_grille_from_file (char * filename, grille* g);
 * \relates grille
 * \param filename nom du fichier permettant d'initialliser la grille
 * \param g grille a initialliser
 * \brief initialise la grille g gace au fichier filename
 *
 */
void init_grille_from_file (char * filename, grille* g){
	set_vivante = set_vivante_nv;
	FILE * pfile = NULL;
	pfile = fopen(filename, "r");
	assert (pfile != NULL);
	
	int i,j,n,l,c,vivantes=0;
	
	fscanf(pfile, "%d", & l);
	fscanf(pfile, "%d", & c);
	
	alloue_grille(l,c,g);
	
	fscanf(pfile, "%d", & vivantes);
	for (n=0; n< vivantes; ++n){
		fscanf(pfile, "%d", & i);
		fscanf(pfile, "%d", & j);
		set_vivante(i,j,*g);
	}
	
	fclose (pfile);
	return;
}


/** 
 * \fn void copie_grille (grille gs, grille gd);
 * \relates grille
 * \param gs grille source
 * \param gd grille destination
 * \brief recopie gs dans gd (sans allocation)
 *
 */
void copie_grille (grille gs, grille gd){
	int i, j;
	for (i=0; i<gs.nbl; ++i) for (j=0; j<gs.nbc; ++j) gd.cellules[i][j] = gs.cellules[i][j];
	return;	
}
