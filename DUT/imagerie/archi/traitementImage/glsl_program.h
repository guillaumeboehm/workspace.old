//RRAFFIN, Iut de provence, département Informatique, ARCHI IN GLSL
//romain.raffin[AT]univ-provence.fr

//une classe pour les ShaderProgram
#ifndef _H_GLSL_PROGRAM
#define _H_GLSL_PROGRAM

#include <GL/gl.h>

#include "glsl_fs.h"
#include "glsl_vs.h"

class GLSL_Program {

public:

	GLuint idprogram;
	GLSL_Program(void);
	GLSL_Program(const GLSL_Program&);
	~GLSL_Program();

	void Use_VertexShader(GLSL_VS&);
	void Use_FragmentShader(GLSL_FS&);
	void Link_Shaders();
	void Activate();
	void Deactivate();
};

#endif
