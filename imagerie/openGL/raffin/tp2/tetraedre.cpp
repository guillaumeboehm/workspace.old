#include "tetraedre.hpp"
#include "math.h"
#include <iostream>

Tetraedre::Tetraedre(float _cote)
    : objetGeometrique(12), cote(_cote)
{
    CreateVertexBuffer();
    CreateColorBuffer();
}

Tetraedre::~Tetraedre(){ if(colors != 0) delete [] colors; }

void Tetraedre::CreateVertexBuffer(){
    vertices = new float [36];
    
    float x = 0.0f;
    float y = 0.0f;
    float z = 0.0f;

	vertices[0] = x + sqrt(3)/6*cote;
	vertices[1] = y - 1/4*sqrt(2/3)*cote ;
	vertices[2] = z - cote/2 ;

	vertices[3] = x - sqrt(3)/3*cote;
	vertices[4] = y - 1/4*sqrt(2/3)*cote ;
	vertices[5] = z;

	vertices[6] = x;
	vertices[7] = y + sqrt(6)/4*cote ;
	vertices[8] = z;

    vertices[9] = x - sqrt(3)/3*cote;
	vertices[10] = y - 1/4*sqrt(2/3)*cote;
	vertices[11] = z;

    vertices[12] = x;
	vertices[13] = y + sqrt(6)/4*cote;
	vertices[14] = z;

    vertices[15] = x + sqrt(3)/6*cote;
	vertices[16] = y - 1/4*sqrt(2/3)*cote;
	vertices[17] = z + cote/2;

    vertices[18] = x + sqrt(3)/6*cote;
	vertices[19] = y - 1/4*sqrt(2/3)*cote;
	vertices[20] = z - cote/2;

    vertices[21] = x;
	vertices[22] = y + sqrt(6)/4*cote;
	vertices[23] = z;

    vertices[24] = x + sqrt(3)/6*cote;
	vertices[25] = y - 1/4*sqrt(2/3)*cote;
	vertices[26] = z + cote/2;

    vertices[27] = x + sqrt(3)/6*cote;
	vertices[28] = y - 1/4*sqrt(2/3)*cote;
	vertices[29] = z - cote/2;

    vertices[30] = x - sqrt(3)/3*cote;
	vertices[31] = y - 1/4*sqrt(2/3)*cote;
	vertices[32] = z;

    vertices[33] = x + sqrt(3)/6*cote;
	vertices[34] = y - 1/4*sqrt(2/3)*cote;
	vertices[35] = z + cote/2;
}

void Tetraedre::CreateColorBuffer(){
    colors = new float[36];

    colors[0] = 1.0f;
    colors[1] = 0.0f;
    colors[2] = 0.0f;

    colors[3] = 0.0f;
    colors[4] = 1.0f;
    colors[5] = 0.0f;

    colors[6] = 0.0f;
    colors[7] = 0.0f;
    colors[8] = 1.0f;

    colors[9] = 0.0f;
    colors[10] = 1.0f;
    colors[11] = 0.0f;

    colors[12] = 0.0f;
    colors[13] = 0.0f;
    colors[14] = 1.0f;

    colors[15] = 1.0f;
    colors[16] = 1.0f;
    colors[17] = 0.0f;

    colors[18] = 1.0f;
    colors[19] = 0.0f;
    colors[20] = 0.0f;

    colors[21] = 0.0f;
    colors[22] = 0.0f;
    colors[23] = 1.0f;

    colors[24] = 1.0f;
    colors[25] = 1.0f;
    colors[26] = 0.0f;

    colors[27] = 1.0f;
    colors[28] = 0.0f;
    colors[29] = 0.0f;

    colors[30] = 0.0f;
    colors[31] = 1.0f;
    colors[32] = 0.0f;

    colors[33] = 1.0f;
    colors[34] = 1.0f;
    colors[35] = 0.0f;
}
