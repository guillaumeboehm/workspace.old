#ifndef FUMEE_HPP
#define FUMEE_HPP

#include "stb_image.h"
#include "Bouffee.h"
#include "texture.hpp"
#include <list>

class Fumee {
private:
	float x,y,z;
	float intervalle_emission;
	float temps_ecoule;
	Texture* texture;
	std::list<Bouffee> liste_bouffees;
public:
	inline Fumee(float _x=0, float _y=0, float _z=0, float _intervalle_emission=1, Texture* _texture=NULL)
		:x(_x), y(_y), z(_z), intervalle_emission(_intervalle_emission), temps_ecoule(0), texture(_texture)
	{}	
	inline ~Fumee() { if(texture != NULL) delete texture; }
	
	void anime(float temps);	
	void affiche();
};

#endif