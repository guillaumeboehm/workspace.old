#ifndef BEZIER_HPP
#define BEZIER_HPP

#include <cstdio>
#include <cstdlib>
#include <cmath>

#include <GL/glew.h>
#include <GL/freeglut.h>
#include <iostream>
#include <deque>

#include "point3.h"

typedef std::deque<point3> List;

class Bezier{
private:
	List* controlPoints;
	point3 evaluate(float t) const; //renvoi un point au parametre t sur la courbe (utilisée dans getPoints)
public:
	Bezier(List*);
	inline ~Bezier(){ delete controlPoints; }
	List* getControlPoints() const; //renvoi les points de controle
	List* getPoints(float step) const; //renvoi la courbe selon le pas précisé
};

#endif