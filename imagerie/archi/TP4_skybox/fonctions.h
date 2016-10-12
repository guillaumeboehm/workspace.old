//R. RAFFIN, IUT Aix-Marseille, département Informatique, site d'Arles
//M4104c, ARCHI IN
//romain.raffin[AT]univ-amu.fr

#ifndef _H_FONCTIONS
#define _H_FONCTIONS

#include <GL/gl.h>


//des structures moches mais rapides à mettre à mettre en place
struct indexedface {
	unsigned int S1,S2,S3;
};

struct point3D {
	double x;
	double y;
	double z;
};

//des utilitaires
float tirage_alea(float, float);

//des fonctions mathématiques
float fDegree2Radian(const float);
float fRadian2Degree(const float);

//des fonctions pour les shaders
void PrintProgramInfo(GLuint);
void PrintShaderInfo(GLuint);
int ReadSourceFile(const char*, char **);

//des fonctions pour les textures
void LoadTexture(const char*, GLuint*);

#endif
