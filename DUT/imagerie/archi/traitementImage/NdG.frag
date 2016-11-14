//R. RAFFIN, IUT Aix-Marseille, département Informatique, site d'Arles
//M4104c, ARCHI IN
//romain.raffin[AT]univ-amu.fr

//Fragment Shader pour le traitement d'images

uniform sampler2D colorMap;

void main(void)
{

	int i = 0;
	vec4 sum = vec4(0.0);
	
//changement en niveau de gris
	vec4 temp = texture2D(colorMap, gl_TexCoord[0].st); //on recupère la couleur du pixel
	sum = vec4(0.299 * temp.r + 0.587 * temp.g + 0.114 * temp.b); // on la change en niveau de gris
//............................

	gl_FragColor = sum; //on dessine le pixel avec le niveau de gris
}
