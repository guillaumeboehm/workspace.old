/*-----------------------------------------*
 *         fichier test.c                  *
 *-----------------------------------------*/

#include <stdio.h>

void main(){
 
int suite[] = {6,2,9,5,3,6,12,7,15,4,8,7,32,23,45,12,8,9,16,20,9};
int longueurs[21];
int ssuite[21];
int result[21];
int i, j;

// for(i=0;i<21;i++) printf("%d ",suite[i]);

for(i=20; i>=0;i--){
    longueurs[i]=1; ssuite[i]=-1;
    for(j=20;j>i;j--)
        if(suite[j]>suite[i] && longueurs[j]>=longueurs[i])
        { 
            longueurs[i]=longueurs[j]+1;
            ssuite[i] = j;
            
        }
    }  


int max = 0, imax = 0;
    
for(i=0;i<21;i++)
    if(longueurs[i] > max) { max = longueurs[i] ; imax = i; }
 
for(i=imax;ssuite[i]>-1;i = ssuite[i]) printf("%d\t ", suite[i]);

printf("%d\n", suite[i]);
 

}