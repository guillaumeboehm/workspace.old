// fichier vect.h

#ifndef __VECT__
#define __VECT__
 
 #define N 5
 
 typedef float fnum;     // qu'on pourra remplacer par d'autres types 
                            //comme des doubles, des rationnels, des complexes ...
 
 typedef fnum vect[N];
 // ... 
   void v_nul(vect v);                      // rend v égal au vecteur nul
   void v_modif_i(vect v, int i, fnum x);   // v :: i <- x
   fnum v_ieme(vect v, int i);              // v[i] ... on pourra aussi s'autoriser v[i] 
   void v_somme(vect v, vect w, vect r);    // r = v + w
   void v_prode(fnum a, vect v, vect r);    // r = a*v
   fnum v_prod_scal(vect v, vect w);        // produit scalaire
   
   void v_cp(vect u, vect r);               // r = u
   void v_print(vect v);                    // affichage
   void v_read(vect v);                     // saisie

#endif