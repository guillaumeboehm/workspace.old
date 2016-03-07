#include <GL/glu.h>
#include "glut.h"
#include "Fumee.h"

void Fumee::anime(float temps){
	temps_ecoule += temps;
	if(temps_ecoule >= intervalle_emission){
		temps_ecoule = 0;
		Bouffee bouffee(x,y,z,2);
		liste_bouffees.push_back(bouffee);
	}
	std::list<Bouffee>::iterator i;
	i = liste_bouffees.begin();
	while( i != liste_bouffees.end() ){
		if( i->getVie() <= 0 )
			i = liste_bouffees.erase(i);
		else
			i++;
	}
	
	i = liste_bouffees.begin();
	while( i != liste_bouffees.end() ){
		i->anime(temps);
		i++;
	}
}

void Fumee::affiche(float x, float y, float z){
	std::list<Bouffee>::iterator i;
	i = liste_bouffees.end();
	glDepthMask(GL_FALSE);
	while( i != liste_bouffees.begin() ){
		i->affiche(texture, x, y, z);
		i--;
	}
	glDepthMask(GL_TRUE);
}