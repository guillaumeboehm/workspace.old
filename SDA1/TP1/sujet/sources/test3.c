/*-----------------------------------------*
 *         fichier test3.c                  *
 *-----------------------------------------*/

#include <stdio.h>
#include "include/suites_m.h"
#include "include/ssuites_m.h"

void main(){

int tab[] = {6,2,9,5,3,6,12,7,15,4,8,7,32,23,45,12,8,9,16,20,9, -2, -9};
suite longueurs = s_const(23,1);
suite u = s_t2s(tab,23);

sous_suite ssc = ss_vide(u);
int i, j;

// for(i=0;i<21;i++) printf("%d ",suite[i]);

for(i=22; i>=0;i--){
    for(j=22;j>i;j--)
        if(s_ieme(u,j)>s_ieme(u,i) && s_ieme(longueurs,j)>=s_ieme(longueurs,i))
        { 
            longueurs=s_modif(longueurs,i, s_ieme(longueurs,j)+1);
            ssc = ss_modifie_suiv(ssc, i, j);
            
        }
    }  

s_print(u);
//s_print(longueurs);

ssc->prem = s_imax(longueurs);

 
ss_print(ssc);

ssc = ss_insere(ssc,5);

ssc = ss_insere(ssc,0);

ssc = ss_insere(ssc,20);

//ssc = ss_supprime(ssc, 5);
ss_print(ssc);

suite u2 = ss_ss2s(ssc);

s_print(u2);



ss_del(ssc);
s_del(u);
}
