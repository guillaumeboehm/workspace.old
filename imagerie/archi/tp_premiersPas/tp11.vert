//R. RAFFIN, IUT Aix-Marseille, département Informatique, site d'Arles
//M4104c, ARCHI IN
//romain.raffin[AT]univ-amu.fr

//Vertex Shader tres simple

//uniform float cputime;
uniform float cpuchaos;

void main(void) {
	vec4 point = gl_Vertex;
	//point.x += 1.0;
	//point.y += 1.0;

	//point.z = sin(5.0*point.x + cputime)*0.5;

	point += cpuchaos;

	gl_FrontColor = gl_Color;

	gl_Position = gl_ModelViewProjectionMatrix * point;
}
