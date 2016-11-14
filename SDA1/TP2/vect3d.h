// fichier vect3d.h

#ifndef __VECT3D__
#define __VECT3D__
 
   #define N 5
 
   typedef float fnum;     // qu'on pourra remplacer par d'autres types 
                            //comme des doubles, des rationnels, des complexes ...
 
   typedef struct { float x;
                  float y;
                  float z;} vect3d;

   vect3d v3d_construct(float _x, float _y, float _z);

   float v3d_x(vect3d v);

   float v3d_y(vect3d v);

   float v3d_z(vect3d v);

   vect3d v3d_somme(vect3d v, vect3d v2);

   vect3d v3d_mult(float a, vect3d v);

   float v3d_scal(vect3d v, vect3d v2);

   vect3d v3d_input();

   void v3d_display(vect3d v);

#endif