//R. RAFFIN, IUT Aix-Marseille, département Informatique, site d'Arles
//M4104c, ARCHI IN
//romain.raffin[AT]univ-amu.fr

//Fragment Shader pour la déformation, mise en couleur des points déformés (à faire)

varying float VChange; //oh tient, on reçoit une valeur de type float de la part du vertex shader

void main (void)
{
	gl_FragColor = gl_Color;	
	//gl_FragColor = vec4(0.0,0.0,1.0,1.0);		//"modif" de tous les pixels (bleu) pour l'instant
}
