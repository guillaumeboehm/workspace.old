//R. RAFFIN, IUT Aix-Marseille, département Informatique, site d'Arles
//M4104c, ARCHI IN
//romain.raffin[AT]univ-amu.fr

#include <GL/freeglut.h>

#include "fonctions.h"
#include "skybox.h"


SkyBox::SkyBox()
{
	MAXFACES = 6;
	DisplayListId = 0;
	IdTextureTab = new GLuint[MAXFACES];
	created = false;
}

SkyBox::~SkyBox()
{
	if ( created )	//on a créé des textures, on les supprime
		glDeleteTextures(MAXFACES, IdTextureTab);
	if ( IdTextureTab )	//on a aussi le tableau des indices de textures à supprimer
		delete[] IdTextureTab;
}

SkyBox::SkyBox(const SkyBox& _copie)
{
	MAXFACES = _copie.MAXFACES;

	if ( IdTextureTab ) // déjà alloué, il faut tout virer
		delete[] IdTextureTab;

	if ( created ) //les textures ont été créées, il faut les supprimer
		glDeleteTextures(MAXFACES, IdTextureTab);

	//re-création du tableau de texture
	IdTextureTab = new GLuint[MAXFACES];

	for (unsigned int i = 0; i < MAXFACES; i++)
		IdTextureTab[i] = _copie.IdTextureTab[i];

	//Afaire Create();
	//Afaire CreateDisplayList(_copie->bbmin, _copie->bbmax);

}

void SkyBox::LoadSingleTexture(GLuint _rank, const char * _imgfile)
{
	GLuint res = -1;
	LoadTexture(_imgfile, &res);
	IdTextureTab[_rank] = res;
}

void SkyBox::Create(void)
{
	for(unsigned int i = 0; i < MAXFACES; i++) {
		glBindTexture(GL_TEXTURE_2D, IdTextureTab[i]);
		glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	}

}

void SkyBox::CreateDisplayList(const struct point3D* _bbmin, const struct point3D * _bbmax)
{
	DisplayListId = glGenLists(1);
	glNewList(DisplayListId, GL_COMPILE);

	//Face arrière, BACK
	glBindTexture(GL_TEXTURE_2D, IdTextureTab[SKYBOX_BACK]);
	glBegin(GL_TRIANGLE_STRIP);
	glTexCoord2f(0.0f, 0.0f);
	glVertex3f(_bbmin->x, _bbmin->y, _bbmin->z);
	glTexCoord2f(1.0f, 0.0f);
	glVertex3f(_bbmax->x, _bbmin->y, _bbmin->z);
	glTexCoord2f(0.0f, 1.0f);
	glVertex3f(_bbmin->x, _bbmax->y, _bbmin->z);
	glTexCoord2f(1.0f, 1.0f);
	glVertex3f(_bbmax->x, _bbmax->y, _bbmin->z);
	glEnd();

	//Face avant, FRONT
	glBindTexture(GL_TEXTURE_2D, IdTextureTab[SKYBOX_FRONT]);
	glBegin(GL_TRIANGLE_STRIP);
	glTexCoord2f(1.0f, 0.0f);
	glVertex3f(_bbmin->x, _bbmin->y, _bbmax->z);
	glTexCoord2f(1.0f, 1.0f);
	glVertex3f(_bbmin->x, _bbmax->y, _bbmax->z);
	glTexCoord2f(0.0f, 0.0f);
	glVertex3f(_bbmax->x, _bbmin->y, _bbmax -> z);
	glTexCoord2f(0.0f, 1.0f);
	glVertex3f(_bbmax->x, _bbmax->y, _bbmax -> z);
	glEnd();

	//Face dessous, BOTTOM
	glBindTexture(GL_TEXTURE_2D, IdTextureTab[SKYBOX_BOTTOM]);
	glBegin(GL_TRIANGLE_STRIP);
	glTexCoord2f(0.0f, 1.0f);
	glVertex3f(_bbmin->x, _bbmin->y, _bbmin -> z);
	glTexCoord2f(0.0f, 0.0f);
	glVertex3f(_bbmin->x, _bbmin->y, _bbmax -> z);
	glTexCoord2f(1.0f, 1.0f);
	glVertex3f(_bbmax->x, _bbmin->y, _bbmin -> z);
	glTexCoord2f(1.0f, 0.0f);
	glVertex3f(_bbmax->x, _bbmin->y, _bbmax -> z);
	glEnd();

	//Face dessus, TOP
	glBindTexture(GL_TEXTURE_2D, IdTextureTab[SKYBOX_TOP]);
	glBegin(GL_TRIANGLE_STRIP);
	glTexCoord2f(0.0f, 0.0f);
	glVertex3f(_bbmin->x, _bbmax->y, _bbmin -> z);
	glTexCoord2f(1.0f, 0.0f);
	glVertex3f(_bbmax->x, _bbmax->y, _bbmin -> z);
	glTexCoord2f(0.0f, 1.0f);
	glVertex3f(_bbmin->x, _bbmax->y, _bbmax -> z);
	glTexCoord2f(1.0f, 1.0f);
	glVertex3f(_bbmax->x, _bbmax->y, _bbmax -> z);
	glEnd();

	//Face gauche, LEFT
	glBindTexture(GL_TEXTURE_2D, IdTextureTab[SKYBOX_LEFT]);
	glBegin(GL_TRIANGLE_STRIP);
	glTexCoord2f(0.0f, 0.0f);
	glVertex3f(_bbmax->x, _bbmin->y, _bbmin->z);
	glTexCoord2f(1.0f, 0.0f);
	glVertex3f(_bbmax->x, _bbmin->y, _bbmax->z);
	glTexCoord2f(0.0f, 1.0f);
	glVertex3f(_bbmax->x, _bbmax->y, _bbmin->z);
	glTexCoord2f(1.0f, 1.0f);
	glVertex3f(_bbmax->x, _bbmax->y, _bbmax->z);
	glEnd();

	//Face droite, RIGHT
	glBindTexture(GL_TEXTURE_2D, IdTextureTab[SKYBOX_RIGHT]);
	glBegin(GL_TRIANGLE_STRIP);
	glTexCoord2f(1.0f, 0.0f);
	glVertex3f(_bbmin->x, _bbmin->y, _bbmin->z);
	glTexCoord2f(1.0f, 1.0f);
	glVertex3f(_bbmin->x, _bbmax->y, _bbmin->z);
	glTexCoord2f(0.0f, 0.0f);
	glVertex3f(_bbmin->x, _bbmin->y, _bbmax->z);
	glTexCoord2f(0.0f, 1.0f);
	glVertex3f(_bbmin->x, _bbmax->y, _bbmax->z);
	glEnd();
	glEndList();

	created = true;
}

// Avec glFrontFace(GL_CCW);
void SkyBox::OpenGLDraw()
{
	glEnable(GL_TEXTURE_2D);
	glEnable(GL_CULL_FACE);
	glFrontFace(GL_CCW);

	glDepthMask(GL_FALSE);
	glPushMatrix();
	glCallList(DisplayListId);
	glPopMatrix();
	glDepthMask(GL_TRUE);

	glDisable(GL_CULL_FACE);
}

