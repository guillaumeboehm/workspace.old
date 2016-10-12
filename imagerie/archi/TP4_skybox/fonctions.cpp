//R. RAFFIN, IUT Aix-Marseille, département Informatique, site d'Arles
//M4104c, ARCHI IN
//romain.raffin[AT]univ-amu.fr

#include <iostream>
#include <fstream>
#include <cmath>
#include <cstring>
#include <cstdlib>

#include <FreeImage.h>

#include <GL/glew.h>

#include "fonctions.h"

using namespace std;

#ifndef M_PI
define M_PI	3.14159265358979323846
#endif

//Une fonction qui tire aléatoirement un nombre entre borneinf et bornesup
//!!attention, il faut avoir initialisé le rendomizer par un srandom((unsigned int)(time(NULL)));
float tirage_alea(float _borneinf, float _bornesup)
{
//random() -> entre 0 et RAND_MAX
	float res = _borneinf + ((double)random() / ((double)RAND_MAX + 1.0) * _bornesup);
	return res;
}

//Un fonction qui peut servir, pour transformer du degré en radians (attention, en float)
float fDegree2Radian(const float _Dangle)
{
	return (_Dangle * M_PI / 180.0f);
}

//Un fonction qui peut servir, pour transformer du radians en degré (attention, en float)
float fRadian2Degree(const float _Rangle)
{
	return (_Rangle * 180.0f / M_PI);
}

//Pour afficher les informations sur un ProgramShader dont l'ID est passée en paramètres
void PrintProgramInfo(GLuint _program)
{
	int length = 0;
	int charsWritten  = 0;
	char *info;

	glGetProgramiv(_program, GL_INFO_LOG_LENGTH, &length);

	if ( length > 0 ) {
		info = new char[length];
		glGetProgramInfoLog(_program, length, &charsWritten, info);
		cerr << info << endl;
		delete [] info;
	}
}

//Pour avoir des infos sur un (vertex|fragment) shader dont l'id est passé en paramètre
void PrintShaderInfo(GLuint _shader)
{
	int length = 0;
	int charsWritten= 0;
	char *info;

	glGetShaderiv(_shader, GL_INFO_LOG_LENGTH, &length);

	if (length > 0) {
		info = new char[length];
		glGetShaderInfoLog(_shader, length, &charsWritten, info);
		cerr << info << endl;
		delete [] info;
	}
}

//Pour lire un fichier source de shader, ne fait rien que d'entasser les lignes dans un buffer
int ReadSourceFile(const char* _filename, char ** _wtabchar )
{
	int taille;

	ifstream monfichier;
	monfichier.open (_filename, ios::binary );

	//on "calcule" le nombre de caractères dans le fichier
	monfichier.seekg (0, ios::end);
	taille = monfichier.tellg();
	monfichier.seekg (0, ios::beg);

	(*_wtabchar) = new char [taille + 1];

	//on lit tout le fichier en 1 coup
	monfichier.read (*_wtabchar , taille);
	(*_wtabchar)[taille] = '\0';

	monfichier.close();

	return (taille);
}

//Chargement d'une texture dont le nom est passé en param
//Génère le TexImage2D automatiquement (ID passé en paramètre)
void LoadTexture(const char* _tex_filename, GLuint* _tex_desc)
{
	//Get the image file type from FreeImage.
	FREE_IMAGE_FORMAT fifmt = FreeImage_GetFileType(_tex_filename, 0);

	//Actually load the image file.
	FIBITMAP *image = FreeImage_Load(fifmt, _tex_filename,0);

	//Now, there is no guarantee that the image file
	//loaded will be GL_RGB, so we force FreeImage to
	//convert the image to GL_RGB.
	image = FreeImage_ConvertTo24Bits(image);


	if( image != NULL ) {
		glGenTextures( 1, _tex_desc);
		glBindTexture( GL_TEXTURE_2D, *_tex_desc );
		glTexParameteri( GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER, GL_LINEAR );
		glTexParameteri( GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER, GL_LINEAR );


		//This is important to note, FreeImage loads textures in
		//BGR format. Now we could just use the GL_BGR extension
		//But, we will simply swap the B and R components ourselves.
		//Firstly, allocate the new bit data doe the image.
		BYTE *bits = new BYTE[FreeImage_GetWidth(image) * FreeImage_GetHeight(image) * 3];

		//get a pointer to FreeImage's data.
		BYTE *pixels = (BYTE*)FreeImage_GetBits(image);

		//Iterate through the pixels, copying the data
		//from 'pixels' to 'bits' except in RGB format.
		for(unsigned int pix=0; pix<FreeImage_GetWidth(image) * FreeImage_GetHeight(image); pix++) {
			bits[pix*3+0]=pixels[pix*3+2];
			bits[pix*3+1]=pixels[pix*3+1];
			bits[pix*3+2]=pixels[pix*3+0];

		}

		//The new 'glTexImage2D' function, the prime difference
		//being that it gets the width, height and pixel information
		//from 'bits', which is the RGB pixel data..
		glTexImage2D( GL_TEXTURE_2D, 0, 3, FreeImage_GetWidth(image), FreeImage_GetHeight(image), 0, GL_RGB, GL_UNSIGNED_BYTE, bits );

		//Unload the image.
		//and free the bit data.
		FreeImage_Unload(image);
		delete bits;
	}

}
