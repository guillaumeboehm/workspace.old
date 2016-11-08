/*-----------------------------------------*
 *         fichier suites.c                *
 *-----------------------------------------*/
#include "include/suites_m.h"
#include <stdio.h> 
#include <stdlib.h>
/*
typedef struct s_suite {
			 int val[LG_MAX];   // valeur des termes
			 int lg;            // longueur de la suite
			} *suite;
*/

suite s_vide()
{
    suite u = (suite)malloc(sizeof(struct s_suite));
    u->lg = 0;
    return u;
}

void s_del(suite u){
    free(u);
}

suite s_const(int lg, int valeur)
{
    suite u = (suite)malloc(sizeof(struct s_suite)); 
    
    u->lg = lg;
    for(int i=0; i<lg; i++) u->val[i] = valeur;
     
    return u;
}

suite s_t2s(int tab[], int nb)
{
    suite u = (suite)malloc(sizeof(struct s_suite));
    
    u->lg = nb;
    
    for(int i=0; i<nb; i++) u->val[i]=tab[i];
    
    return u;
}

suite s_adj(int t, suite u)
{
    if(u->lg == LG_MAX -1) { perror("taille suite dépassée"); exit(-1); }
    u->val[u->lg++] = t;
    return u;
}

int s_longueur(suite u)
{
    return u->lg;
}

int s_ieme(suite u, int i)
{
    if( 0<= i && i < u->lg) return u->val[i];
    else
    {
        perror("sortie de liste");
        exit(-1);
    }
}

suite s_modif(suite u, int i, int elt)
{ 
    u->val[i] = elt;
    return u;
}

int s_max(suite u)
{
    int i;
    int max = u->val[0];
    for(i=1;i<u->lg;i++) 
        if(u->val[i]>max) max = u->val[i];
    return max;
}

int s_imax(suite u)
{
    int i, indice = 0;
    int max = u->val[0];

    for(i=1;i<u->lg;i++) 
        if(u->val[i]>max) {max = u->val[i]; indice = i; }
    return indice;
}

void s_print(suite u)
{
    for(int i=0; i< u->lg; i++) printf("%d\t ",u->val[i]);
    
    printf("\n");
}
