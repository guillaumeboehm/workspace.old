/*-----------------------------------------*
 *         fichier ssuites.h                *
 *-----------------------------------------*/
#include "suites_m.h"

#ifndef __S_SUITES_M__
#define __S_SUITES_M__

typedef struct s_ssuite {
                    suite ms;
                    int prem;
                    int ch[LG_MAX];
                } *sous_suite;
                
sous_suite ss_vide(suite u);
void ss_del(sous_suite su);
int ss_longueur(sous_suite su);
int ss_ieme(sous_suite su, int i);
sous_suite ss_modifie_suiv(sous_suite su, int i, int n_suiv);

sous_suite ss_insere(sous_suite su, int ind_of_u);

void ss_print(sous_suite su);

sous_suite ss_supprime(sous_suite su, int ind_of_u);
/*supprime le terme u_(ind_of_u) de la sous_suite su
si ce terme n'est pas dans su, celle-ci reste inchangé*/

suite ss_ss2s(sous_suite su);
/*produit une suite a partir de la ssuite su*/

sous_suite ss_id(suite u);
// produit la ssuite dont les termes sont ceux de u

sous_suite ss_n_prem(suite u, int n);
// ssuite des n premiers termes de u

sous_suite ss_1_sur_2(suite u);
//ssuite a partir de u un terme sur 2

sous_suite ss_croissante_de_u0(suite u);
//la plus grande ssuite strictement croissante depuis u0

sous_suite ss_croissante(suite u);
//la plus grande sous_suite croissante

bool s_strictement_croissante(suite u);
//retourne vrai si la suite u est strictenent croissante

sous_suite ss_extract(suite u, suite mod);
//produit la ssuite des termes u_(mod_i)
//precondition : la suite mod doit etre strictement croissante

#endif
