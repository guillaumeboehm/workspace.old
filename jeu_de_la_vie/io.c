/** 
 * \file io.c 
 * code pour l'affichage
 */

#include "io.h"

/** 
 * \fn void affiche_trait (int c);
 * \param c longueur du trait
 * \brief affichage d'un trait horizontal
 *
 */
void affiche_trait (int c){
	int i;
	for (i=0; i<c; ++i) printf ("|---");
	printf("|\n");
	return;
}

/** 
 * \fn void affiche_ligne (int c, int* ligne);
 * \param c longueur de la ligne
 * \param ligne tableau de valeurs de la ligne
 * \brief affichage d'une ligne de la grille
 *
 */
void affiche_ligne (int c, int* ligne){
	int i;
	for (i=0; i<c; ++i) 
		if (ligne[i] == 0 ) printf ("|   "); else printf ("| O ");
	printf("|\n");
	return;
}

/** 
 * \fn void affiche_grille (grille g);
 * \param g grille a afficher
 * \brief affichage d'une grille
 *
 */
void affiche_grille (grille g){
	int i, l=g.nbl, c=g.nbc;
	printf("\n");
	affiche_trait(c);
	for (i=0; i<l; ++i) {
		affiche_ligne(c, g.cellules[i]);
		affiche_trait(c);
	}	
	printf("\n"); 
	return;
}

/** 
 * \fn void efface_grille (grille g);
 * \param g grille a effacer
 * \brief effacement d'une grille
 *
 */
void efface_grille (grille g){
	printf("\n\e[%dA",g.nbl*2 + 5); 
}

/** 
 * \fn void debut_jeu(grille *g, grille *gc);
 * \param g grille du jeu
 * \param gc grille temporaire pour le jeu
 * \brief debute le jeu
 *
 */
void debut_jeu(grille *g, grille *gc){
	char c = getchar();
	int compt = 1;
	while (c != 'q') // touche 'q' pour quitter
	{ 
		switch (c) {
			case '\n' : 
			{ // touche "entree" pour évoluer
				evolue(g,gc);
				efface_grille(*g);
				printf("evolution : %d", compt++);
				affiche_grille(*g);
				break;
			}
			default : 
			{ // touche non traitée
				printf("\n\e[1A");
				break;
			}
		}
		c = getchar(); 
	}
	return;	
}
