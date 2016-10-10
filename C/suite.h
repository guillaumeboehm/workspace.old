#ifndef SUITE_H
#define SUITE_H

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

#define LG_MAX 128

typedef struct { int * val;
				 int lg;} suite;

suite s_vide();
suite s_const(int _lg, int _val);
suite s_t2s(int tab[], int _lg);
suite s_adj(int t, suite u);
int s_longueur(suite u);
int s_ieme(suite u, int i);
suite s_modif(suite u, int i, int elt);
suite s_copy(suite u);
int s_max(suite u);
int s_imax(suite u);
void s_print(suite u);


#endif //SUITE_H