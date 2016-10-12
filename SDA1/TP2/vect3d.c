#include <stdio.h>
#include <stdlib.h>
#include "vect3d.h"



vect3d v3d_construct(float _x, float _y, float _z){
  return (vect3d){_x, _y, _z};
}

float v3d_x(vect3d v){
  return v.x;
}

float v3d_y(vect3d v){
  return v.y;
}

float v3d_z(vect3d v){
  return v.z;
}

vect3d v3d_somme(vect3d v, vect3d v2){
  return (vect3d){v3d_x(v)*v3d_x(v2), v3d_y(v)*v3d_y(v2), v3d_z(v)*v3d_z(v2)};
}

vect3d v3d_mult(float a, vect3d v){
  return (vect3d){a*v3d_x(v), a*v3d_y(v), a*v3d_z(v)};
}

float v3d_scal(vect3d v, vect3d v2){
  return v3d_x(v)*v3d_x(v2) + v3d_y(v)*v3d_y(v2) + v3d_z(v)*v3d_z(v2);
}

vect3d v3d_input(){
	float x,y,z;
	printf("entrez le point x du vecteur : ");
	scanf("%f", &x);
	printf("entrez le point y du vecteur : ");
	scanf("%f", &y);
	printf("entrez le point z du vecteur : ");
	scanf("%f", &z);
	return (vect3d){x, y, z};
}


void v3d_display(vect3d v){
	printf("(%g,", v3d_x(v));
	printf("%g,", v3d_y(v));
	printf("%g)\n", v3d_z(v));
}