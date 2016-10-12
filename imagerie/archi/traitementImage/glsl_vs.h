//RRAFFIN, Iut de provence, département Informatique, ARCHI IN GLSL
//romain.raffin[AT]univ-provence.fr

//une classe pour les VertexShader
#ifndef _GLSL_VS
#define _GLSL_VS

#include <GL/gl.h>

class GLSL_VS {
public:
	GLuint idvs;

	GLSL_VS(void);
	GLSL_VS(const GLSL_VS&);

	int ReadSource(const char *);
	int Compile();
};

#endif

