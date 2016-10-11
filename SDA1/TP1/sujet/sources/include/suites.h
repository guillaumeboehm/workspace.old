/*-----------------------------------------*
 *         fichier suites.h                *
 *-----------------------------------------*/

#include <stdbool.h>

#ifndef __SUITES__
#define LG_MAX 128

typedef struct s_suite {
			 int val[LG_MAX];   // valeur des termes
			 int lg;            // longueur de la suite
			 bool rv;
			} suite;
suite s_vide();
suite s_const(int lg, int valeur);
suite s_t2s(int tab[], int nb);
suite s_adj(int t, suite u);
int s_longueur(suite u);
int s_ieme(suite u, int i);
suite s_modif(suite u, int i, int elt);
int s_maxs(suite u);
int s_imax(suite u);
void s_print(suite u);

#define __SUITES__
#endif
