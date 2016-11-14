// fichier mat.h
#ifndef __MAT__
#define __MAT__

#include "vect.h"

#define M 6
 
typedef vect mat[M];
 
 void m_nulle(mat m);
 void m_modif_ij(mat m, int i, int j, fnum x); // idem pour les deux fonctions
 fnum m_ijeme(mat m, int i, int j);            // on pourra utiliser m[i][j]
 void v_prodm(mat m, vect v, vect r);          // r = m.v
 void m_prodm(mat m1, mat m2, mat r);          // r = m1.m2
 
 void m_cp(mat m, mat r);
 void m_print(mat m);
 void m_read(mat m);
 
#endif