#include "Bouffee.h"
#include <GL/glu.h>
#include "glut.h"
#include "vector3f.h"

void Bouffee::anime(float temps){
	xpos += vitesse_x * temps;
	ypos += vitesse_y * temps;
	zpos += vitesse_z * temps;
	taille += temps;
	vie -= temps;
}

void Bouffee::affiche(Texture* texture, float x, float y, float z){
	// Comme on ne veut pas que ce quadrilatère soit affecté
	// par la lumière, on désactive l’éclairage juste avant
	// de l’afficher, et on le réactivera juste après. Vous
	// n’aurez donc pas besoin de spécifier la normale du
	// quadrilatère
	glDisable(GL_LIGHTING);
	// On veut pouvoir voir les deux côtés du quadrilatère
	glDisable(GL_CULL_FACE);
	// On active le blending pour que la couleur de la texture
	// se mélange à la couleur du reste de la scène dans des
	// proportions données par la valeur alpha de chaque texel
	// de la texture
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glEnable(GL_BLEND);
	// Affichage du quadrilatère texturé avec la texture RGBA
	
	glEnable(GL_TEXTURE_2D);
	texture->utiliser();
	
	glPushMatrix();
	
	glTranslatef(x, y, z);
	
	glColor3f(1.0f,1.0f,1.0f);
	
	float matrice [16];
	glGetFloatv( GL_MODELVIEW_MATRIX, matrice );
	Vector3f Haut, Droite;
	Droite.x = matrice[0] * (taille / 2.0f);
	Droite.y = matrice[4] * (taille / 2.0f);
	Droite.z = matrice[8] * (taille / 2.0f);
	Haut.x = matrice[1] * (taille / 2.0f);
	Haut.y = matrice[5] * (taille / 2.0f);
	Haut.z = matrice[9] * (taille / 2.0f);
	Vector3f A, B, C, D;
	// On calcule la position des 4 sommets du quadrilatère
	A.x = xpos + Haut.x - Droite.x;
	A.y = ypos + Haut.y - Droite.y;
	A.z = zpos + Haut.z - Droite.z;
	B.x = xpos + Haut.x + Droite.x;
	B.y = ypos + Haut.y + Droite.y;
	B.z = zpos + Haut.z + Droite.z;
	C.x = xpos - Haut.x + Droite.x;
	C.y = ypos - Haut.y + Droite.y;
	C.z = zpos - Haut.z + Droite.z;
	D.x = xpos - Haut.x - Droite.x;
	D.y = ypos - Haut.y - Droite.y;
	D.z = zpos - Haut.z - Droite.z;
	// Affichage du billboard
	glBegin(GL_QUADS);
		glTexCoord2f(0,0);
		glVertex3f(D.x,D.y,D.z);
		glTexCoord2f(1,0);
		glVertex3f(C.x,C.y,C.z);
		glTexCoord2f(1,1);
		glVertex3f(B.x,B.y,B.z);
		glTexCoord2f(0,1);
		glVertex3f(A.x,A.y,A.z);
	glEnd();
	
	glPopMatrix();
	
	glDisable(GL_TEXTURE_2D);
	
	// On désactive le blending
	glDisable(GL_BLEND);
	// On reactive l’utilisation de la lumière
	glEnable(GL_LIGHTING);
	// Pour ne voir qu’un seul côté des polygones
	glEnable(GL_CULL_FACE);
}