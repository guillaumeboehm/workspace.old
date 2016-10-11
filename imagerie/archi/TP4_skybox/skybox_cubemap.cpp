//R. RAFFIN, IUT Aix-Marseille, département Informatique, site d'Arles
//M4104c, ARCHI IN
//romain.raffin[AT]univ-amu.fr

#include <GL/glew.h>

#include <FreeImage.h>
#include <cstring>

#include "fonctions.h"
#include "skybox_cubemap.h"

SkyBoxCubeMap::SkyBoxCubeMap()
{
	MAXFACES = 6;
	DisplayListId = 0;
	created = false;
}

SkyBoxCubeMap::~SkyBoxCubeMap()
{
	glDeleteTextures(1, &cube_map_texture_ID);
}

SkyBoxCubeMap::SkyBoxCubeMap(const SkyBoxCubeMap& _copie)
{
	MAXFACES = _copie.MAXFACES;


	if (created) //les textures ont été créées, il faut les supprimer
		glDeleteTextures(1, &cube_map_texture_ID);

	//Afaire Create();

	// Afaire CreateDisplayList(_copie->bbmin, _copie->bbmax);

}

void SkyBoxCubeMap::LoadTextureCubeMap()
{

	GLenum cube_map_target[6] = {
		GL_TEXTURE_CUBE_MAP_NEGATIVE_X,
		GL_TEXTURE_CUBE_MAP_POSITIVE_X,
		GL_TEXTURE_CUBE_MAP_NEGATIVE_Y,
		GL_TEXTURE_CUBE_MAP_POSITIVE_Y,
		GL_TEXTURE_CUBE_MAP_NEGATIVE_Z,
		GL_TEXTURE_CUBE_MAP_POSITIVE_Z
	};

	char fichiers[MAXFACES][50];

	strcpy(fichiers[SKYBOXCM_LEFT], "data/islands_west.png");
	strcpy(fichiers[SKYBOXCM_RIGHT], "data/islands_east.png");

	strcpy(fichiers[SKYBOXCM_BOTTOM], "data/islands_down_rot.png");
	strcpy(fichiers[SKYBOXCM_TOP], "data/islands_up_rot.png");

	strcpy(fichiers[SKYBOXCM_BACK], "data/islands_north.png");
	strcpy(fichiers[SKYBOXCM_FRONT], "data/islands_south.png");


	glGenTextures( 1, &cube_map_texture_ID);
	glBindTexture( GL_TEXTURE_CUBE_MAP, cube_map_texture_ID );

	for (unsigned int i = 0; i < MAXFACES; i++) {

		// Get the image file type from FreeImage.
		FREE_IMAGE_FORMAT fifmt = FreeImage_GetFileType(fichiers[i], 0);

		// Actually load the image file.
		FIBITMAP *image = FreeImage_Load(fifmt, fichiers[i],0);

		image = FreeImage_ConvertTo24Bits(image);

		if( image != NULL ) {
			BYTE *bits = new BYTE[FreeImage_GetWidth(image) * FreeImage_GetHeight(image) * 3];
			BYTE *pixels = (BYTE*)FreeImage_GetBits(image);
			for(unsigned int pix = 0; pix < FreeImage_GetWidth(image) * FreeImage_GetHeight(image); pix++) {
				bits[pix*3+0] = pixels[pix*3+2];
				bits[pix*3+1] = pixels[pix*3+1];
				bits[pix*3+2] = pixels[pix*3+0];
			}

			glTexImage2D(cube_map_target[i], 0, 3, FreeImage_GetWidth(image), FreeImage_GetHeight(image), 0, GL_RGB, GL_UNSIGNED_BYTE, bits );

			FreeImage_Unload(image);
			delete bits;
		}

	} //fin de la boucle qui parcourt les 6 images

	glTexParameteri(GL_TEXTURE_CUBE_MAP_ARB, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_CUBE_MAP_ARB, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_CUBE_MAP_ARB, GL_TEXTURE_WRAP_S, GL_CLAMP);
	glTexParameteri(GL_TEXTURE_CUBE_MAP_ARB, GL_TEXTURE_WRAP_T, GL_CLAMP);
}

void SkyBoxCubeMap::CreateDisplayList(const struct point3D* _bbmin, const struct point3D * _bbmax)
{
	DisplayListId = glGenLists(1);
	glNewList(DisplayListId, GL_COMPILE);

	// Configuration de la texture
	glBindTexture(GL_TEXTURE_CUBE_MAP_ARB, cube_map_texture_ID);

	float t = 1.0f;

	// Rendu de la géométrie
	glBegin(GL_TRIANGLE_STRIP);   // X Négatif
	glTexCoord3f(-t,-t,-t);
	glVertex3f(_bbmin->x, _bbmin->y , _bbmin->z);
	glTexCoord3f(-t,t,-t);
	glVertex3f(_bbmin->x , _bbmax->y, _bbmin->z);
	glTexCoord3f(-t,-t,t);
	glVertex3f(_bbmin->x, _bbmin->y, _bbmax->z);
	glTexCoord3f(-t,t,t);
	glVertex3f(_bbmin->x, _bbmax->y, _bbmax->z);
	glEnd();

	glBegin(GL_TRIANGLE_STRIP);   // X Positif
	glTexCoord3f(t, -t,-t);
	glVertex3f(_bbmax->x, _bbmin->y, _bbmin->z);
	glTexCoord3f(t,-t,t);
	glVertex3f(_bbmax->x, _bbmin->y, _bbmax->z);
	glTexCoord3f(t,t,-t);
	glVertex3f(_bbmax->x, _bbmax->y, _bbmin->z);
	glTexCoord3f(t,t,t);
	glVertex3f(_bbmax->x, _bbmax->y, _bbmax->z);
	glEnd();

	glBegin(GL_TRIANGLE_STRIP);   // Y Négatif
	glTexCoord3f(-t,-t,-t);
	glVertex3f(_bbmin->x, _bbmin->y, _bbmin->z);
	glTexCoord3f(-t,-t,t);
	glVertex3f(_bbmin->x, _bbmin->y, _bbmax->z);
	glTexCoord3f(t, -t,-t);
	glVertex3f(_bbmax->x,_bbmin->y, _bbmin->z);
	glTexCoord3f(t,-t,t);
	glVertex3f(_bbmax->x, _bbmin->y, _bbmax->z);
	glEnd();

	glBegin(GL_TRIANGLE_STRIP);   // Y Positif
	glTexCoord3f(-t,t,-t);
	glVertex3f(_bbmin->x,_bbmax->y,_bbmin->z);
	glTexCoord3f(t,t,-t);
	glVertex3f(_bbmax->x, _bbmax->y, _bbmin->z);
	glTexCoord3f(-t,t,t);
	glVertex3f(_bbmin->x, _bbmax->y, _bbmax->z);
	glTexCoord3f(t,t,t);
	glVertex3f(_bbmax->x, _bbmax->y, _bbmax->z);
	glEnd();

	glBegin(GL_TRIANGLE_STRIP);   // Z Négatif
	glTexCoord3f(-t,-t,-t);
	glVertex3f(_bbmin->x, _bbmin->y, _bbmin->z);
	glTexCoord3f(t, -t,-t);
	glVertex3f(_bbmax->x, _bbmin->y, _bbmin->z);
	glTexCoord3f(-t,t,-t);
	glVertex3f(_bbmin->x, _bbmax->y, _bbmin->z);
	glTexCoord3f(t,t,-t);
	glVertex3f(_bbmax->x, _bbmax->y, _bbmin->z);
	glEnd();

	glBegin(GL_TRIANGLE_STRIP);   // Z Positif
	glTexCoord3f(-t,-t,t);
	glVertex3f(_bbmin->x, _bbmin->y, _bbmax->z);
	glTexCoord3f(-t,t,t);
	glVertex3f(_bbmin->x, _bbmax->y, _bbmax->z);
	glTexCoord3f(t,-t,t);
	glVertex3f(_bbmax->x, _bbmin->y, _bbmax->z);
	glTexCoord3f(t,t,t);
	glVertex3f(_bbmax->x, _bbmax->y, _bbmax->z);
	glEnd();

	glEndList();

	created = true;
}

// Avec glFrontFace(GL_CCW);
void SkyBoxCubeMap::OpenGLDraw()
{
	glEnable(GL_TEXTURE_CUBE_MAP);

	glDepthMask(GL_FALSE);

	glCallList(DisplayListId);

	glDepthMask(GL_TRUE);

	glDisable(GL_TEXTURE_CUBE_MAP);
}

