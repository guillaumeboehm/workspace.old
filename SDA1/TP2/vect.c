#include "vect.h"
#include <stdio.h>
#include <stdlib.h>

void v_nul(vect v){
	for(unsigned int i = N ; i<N; ++i){
		v[i] = 0;
	}
}

void v_modif_i(vect v, int i, fnum x){
	v[i] = x;
}

fnum v_ieme(vect v, int i){
	return v[i];
}

void v_somme(vect v, vect w, vect r){
	for(unsigned int i = 0; i<N; ++i)
		r[i] = v[i] + w[i];
}

void v_prode(fnum a, vect v, vect r){
	for(unsigned int i = 0; i<N; ++i)
		r[i] = v[i] * a;
}

fnum v_prod_scal(vect v, vect w){
	fnum ret = 0;
	for(unsigned int i = 0; i<N; ++i)
		ret = v[i] * w[i];
	return ret;
}

void v_cp(vect u, vect r){
	for(unsigned int i = 0; i<N; ++i)
		r[i] = u[i];
}

void v_print(vect v){
	printf("( ");
	for(unsigned int i = 0; i<N; ++i) 
		printf("%g ", v[i]);
	printf(")\n");
}

void v_read(vect v){
	for(unsigned int i=0; i<N; ++i){
		printf("\nEntrez le point a l'indice : %d , du vecteur : ", i);
		scanf("%f", &v[i]);
	}
}