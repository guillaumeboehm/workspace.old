//R. RAFFIN, IUT Aix-Marseille, département Informatique, site d'Arles
//M4104c, ARCHI IN
//romain.raffin[AT]univ-amu.fr

//Fragment Shader tres simple

void main (void) {
	vec4 vectcolor = gl_Color;
	gl_FragColor = gl_Color;		//modif de tous les pixels (bleu)
}
