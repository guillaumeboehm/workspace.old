/*-----------------------------------------*
 *         fichier ssuites.c               *
 *-----------------------------------------*/
#include "include/suites_m.h"
#include "include/ssuites_m.h"
#include <stdlib.h>
#include <stdio.h>

/*
typedef struct s_ssuite{
                    suite ms;
                    int prem;
                    int ch[LG_MAX];
                } *sous_suite;
*/
                
sous_suite ss_vide(suite u)
{
    sous_suite su = (sous_suite)malloc(sizeof(struct s_ssuite));
    
    su->ms = u;
    su->prem = 0;
    for(int i=0; i<LG_MAX; i++) su->ch[i] = -1;
    
    return su;
}

void ss_del(sous_suite su){
    free(su);
}

int ss_longueur(sous_suite su)
{
    int lg = 0;
    
    for(int i=su->prem; su->ch[i] !=-1 && i < su->ms->lg; i = su->ch[i])
    {
        lg ++;
    }
    
    return lg;
}

int ss_ieme(sous_suite su, int i)
{
    int j = su->prem;
    
    for(; su->ch[j] != -1 && i>0; j = su->ch[j]) i--;
    
    if(i==0) return su->ms->val[j];
    else {perror("en dehors de la sous-suite"); exit(-1);}

}



sous_suite ss_modifie_suiv(sous_suite su, int i, int n_suiv)
{
    su->ch[i] = n_suiv; // il faut ajouter pas mal de test pour que cette fonction soit sûre
    return su;
}

sous_suite ss_insere(sous_suite su, int ind_of_u)
// insertion de u_(ind_of_u) dans la sous-suite su
// s'il y est déjà, pas de changement
{
    int j = su->prem;
    if(ind_of_u < j)
        {su->prem = ind_of_u; su->ch[ind_of_u] = j;} // insertion en tête
    else
        {   
           for(;su->ch[j] < ind_of_u && su->ch[j] != -1; j = su->ch[j]){}
           if(su->ch[j] != ind_of_u)
           {
               su->ch[ind_of_u] = su->ch[j];
               su->ch[j] = ind_of_u;
           } 
        }
    return su;
}

void ss_print(sous_suite su)
{
    int j = su->prem;
    
    for(;j!= -1; j = su->ch[j]) printf("%d\t ", su->ms->val[j]);
     
    printf("\n");
}

sous_suite ss_supprime(sous_suite su, int ind_of_u){ // a reprendre
    int j=su->prem;

    if(su->prem == ind_of_u){
        su->prem = su->ch[ind_of_u];
    }
    else{
        for(; su->ch[j] < ind_of_u && su->ch[j] != -1; j=su->ch[j]);
        while(su->ch[j] != -1){
            int temp = su->ch[j];
            su->ch[j] = su->ch[su->ch[j]];
            j = temp;
        }
    }
    return su;
}

suite ss_ss2s(sous_suite su){
    suite u = s_vide();
    int j = su->prem;
    for(; j != -1; j = su->ch[j]){
        u->val[u->lg++] = su->ms->val[j];
    }
    return u;
}