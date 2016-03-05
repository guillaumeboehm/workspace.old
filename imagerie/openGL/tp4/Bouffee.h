#ifndef BOUFEE_HPP
#define BOUFEE_HPP

#include "texture.hpp"
#include "stb_image.h"

class Bouffee {
private:
	float xpos, ypos, zpos;
	float taille;
	float vitesse_x, vitesse_y, vitesse_z;
	float vie;
public:
	inline Bouffee(float _xpos=0, float _ypos=0, float _zpos=0,  float _vie=10, float _taille=1, float _vitesse_x=0, float _vitesse_y=5, float _vitesse_z=0)
		:xpos(_xpos), ypos(_ypos), zpos(_zpos),  vie(_vie), taille(_taille), vitesse_x(_vitesse_x), vitesse_y(_vitesse_y), vitesse_z(_vitesse_z)
	{}
	
	inline ~Bouffee() {}
	
	inline float getVie(){	return vie;	}
	
	void anime(float temps);
	
	void affiche(Texture*);
};

#endif