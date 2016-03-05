//R. RAFFIN, IUT Aix-Marseille, dépt. Informatique - Arles
//TP simple, affichages de quelques points
//compilation par : g++ -Wall TP1points.cpp -lGL -lGLU -lglut -lGLEW -o TP1points

#include <cstdio>
#include <cstdlib>
#include <cmath>

#include <GL/glew.h>
#include <GL/freeglut.h>
#include <iostream>

using namespace std;

GLuint leVBO;

//classes
class objetGeometrique{
private:
	int nbPts;

protected:
	float* vertices;
	
public:
	inline objetGeometrique(float _nbPts){ nbPts = _nbPts; vertices = NULL;}
	inline ~objetGeometrique(){ if(vertices != NULL) delete vertices;}
	inline int get_nbPts(){ return nbPts; }
	inline void set_nbPts(float _nbPts){ nbPts = _nbPts; }
	float* retVertices();
};

float* objetGeometrique::retVertices(){
	return vertices;
}

class Cercle :public objetGeometrique{
private:
	float Cx;
	float Cy;
	float r;

public:
	inline Cercle(float _nbPts, float _Cx, float _Cy, float _r):objetGeometrique(_nbPts), Cx(_Cx), Cy(_Cy), r(_r){}
	inline ~Cercle(){}
	void calcul_points();

};

void Cercle::calcul_points(){
	vertices = new float[get_nbPts()*3];
	float pas = 360.0/(float)get_nbPts();
	
	for(int i=0; i<(int)get_nbPts()*3; i+=3){
		float pas2 = ((pas*(i/3))*M_PI)/180.0;
		vertices[i] = Cx + cos(pas2)*r;
		vertices[i+1] = Cy + sin(pas2)*r;
		vertices[i+2] = 0.0;
	}
}






static void RenderScene()
{
	glClear(GL_COLOR_BUFFER_BIT);

	glEnableVertexAttribArray(0); //glEnableVertexAttribArray - Enable or disable a generic vertex attribute array

	glBindBuffer(GL_ARRAY_BUFFER, leVBO);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0); //Commencer de 0, chaque position sera sur 3 éléments, de type float

	glDrawArrays(GL_LINE_LOOP, 0, 200); //3 éléments à utiliser pour le dessin

	glDisableVertexAttribArray(0); //glDisableVertexAttribArray disables the generic vertex attribute array specified by index

	glutSwapBuffers();
}


static void InitializeGlutCallbacks()
{
	glutDisplayFunc(RenderScene);
}

static void CreateVertexBuffer()
{
	//float vertices[27]; // 3 points à 3 coordonnées x,y,z par point
/*
//1er sommet
	vertices[0] = 0.0f;
	vertices[1] = 0.0f;
	vertices[2] = 0.0f;

//2ème sommet
	vertices[3] = 0.25f;
	vertices[4] = 0.25f;
	vertices[5] = 0.0f;

//3ème sommet
	vertices[6] = 0.0f;
	vertices[7] = 0.9f;
	vertices[8] = 0.0f;

	vertices[9] = -0.25f; //pour tester
	vertices[10] = 0.25f;
	vertices[11] = 0.0f;

	vertices[12] = -.9f;
	vertices[13] = 0.0f;
	vertices[14] = 0.0f;

	vertices[15] = -0.25f;
	vertices[16] = -0.25f;
	vertices[17] = 0.0f;

	vertices[18] = 0.0f;
	vertices[19] = -0.9f;
	vertices[20] = 0.0f;

	vertices[21] = 0.25f;
	vertices[22] = -0.25f;
	vertices[23] = 0.0f;

	vertices[24] = 0.9f;
	vertices[25] = 0.0f;
	vertices[26] = 0.0f;*/
	
	/*srand (time(NULL)); //des points random
	for(unsigned int i=0; i<27; ++i)
		vertices[i] = ((rand()%201)/100.0)-1.0;*/
		
	//affiche un cercle de centre 0 et de rayon 1
	Cercle c1(200, 0.5, 0, 0.5);
	c1.calcul_points();
	float* vertices = c1.retVertices();
	

 	glGenBuffers(1, &leVBO); //génération d'une référence de buffer object
	glBindBuffer(GL_ARRAY_BUFFER, leVBO); //liaison du buffer avec un type tableau de données
	glBufferData(GL_ARRAY_BUFFER, sizeof(float)*c1.get_nbPts()*3, vertices, GL_STATIC_DRAW); //création et initialisation du container de données (3 sommets -> 9 float)

}


int main(int argc, char** argv)
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE|GLUT_RGBA);
	glutInitWindowSize(500, 500);
	glutInitWindowPosition(100, 100);
	glutCreateWindow("TP1 : quelques points");

	InitializeGlutCallbacks();

	//toujours après l'initialisation de glut
	GLenum res = glewInit();

	if (res != GLEW_OK) {
		cerr << "Error: " << glewGetErrorString(res) << endl;
		return (EXIT_FAILURE);
	}

	//cout << "Using GLEW Version: " << glewGetString(GLEW_VERSION);

	glClearColor(0.0f, 0.0f, 0.0f, 0.0f);

	CreateVertexBuffer();

	glutMainLoop();

	return (EXIT_SUCCESS);
}
