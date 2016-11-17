/** 
 * \file grille.h 
 * header pour les grilles
 */

#ifndef __GRILLE_H
#define __GRILLE_H

#include <stdlib.h>
#include <stdio.h>
#include <assert.h>

// structure grille : nombre de lignes, nombre de colonnes, tableau de tableau de cellules
/**
 * \struct grille
 * Déclaration de la structure d'une grille
 * \typedef typedef struct grille;
 * type synonyme de \c struct \c str_cercle
 */
typedef struct sgrille {int nbl; int nbc; int** cellules;} grille;
 
// alloue une grille de taille l*c, et initialise toutes les cellules à mortes
void alloue_grille (int l, int c, grille* g);

// libère une grille
void libere_grille (grille* g);

// alloue et initalise la grille g à partir d'un fichier
void init_grille_from_file (char * filename, grille* g);

/** 
 * \fn static inline int set_non_viable(int i, int j, grille g);
 * \relates grille
 * \param i coordonnee x de la cellule
 * \param j coordonnee y de la cellule
 * \param g grille du jeu
 * \brief teste si la cellule (i,j) de la grille g est non viable 
 *
 */
static inline void set_non_viable(int i, int j, grille g){g.cellules[i][j] = -1;}

/** 
 * \fn static inline void est_non_viable(int i, int j, grille g);
 * \relates grille
 * \param i coordonnee x de la cellule
 * \param j coordonnee y de la cellule
 * \param g grille du jeu
 * \brief rend non viable la cellule (i,j) de la grille g
 *
 */
static inline int est_non_viable(int i, int j, grille g){return g.cellules[i][j] == -1;}

/** 
 * \fn static inline void set_morte(int i, int j, grille g);
 * \relates grille
 * \param i coordonnee x de la cellule
 * \param j coordonnee y de la cellule
 * \param g grille du jeu
 * \brief rend morte la cellule (i,j) de la grille g
 *
 */
static inline void set_morte(int i, int j, grille g){g.cellules[i][j] = 0;}

/** 
 * \fn static inline void set_vivante(int i, int j, grille g);
 * \relates grille
 * \param i coordonnee x de la cellule
 * \param j coordonnee y de la cellule
 * \param g grille du jeu
 * \brief rend vivante la cellule (i,j) de la grille g
 *
 */
void (*set_vivante)(int, int, grille);
static inline void set_vivante_nv(int i, int j, grille g){g.cellules[i][j] = 1;}
static inline void set_vivante_v(int i, int j, grille g){g.cellules[i][j] += 1; if(g.cellules[i][j] >= 8) set_morte(i,j,g);}

/** 
 * \fn static inline int est_vivante(int i, int j, grille g);
 * \relates grille
 * \param i coordonnee x de la cellule
 * \param j coordonnee y de la cellule
 * \param g grille du jeu
 * \brief teste si la cellule (i,j) de la grille g est vivante
 *
 */
static inline int est_vivante(int i, int j, grille g){return g.cellules[i][j] >= 1;}

// recopie gs dans gd (sans allocation)
void copie_grille (grille gs, grille gd);

int egal_grille (grille gs, grille gd);

#endif
