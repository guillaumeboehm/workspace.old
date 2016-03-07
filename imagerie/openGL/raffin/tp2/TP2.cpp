//R. RAFFIN, IUT Aix-Marseille, dépt. Informatique - Arles
//TP couleurs, transformations, caméras
//compilation par : g++ -Wall TP2.cpp -lGLEW -lGLU -lGL -lglut -o TP2

#include <cstdio>
#include <cstdlib>

#include <GL/glew.h>
#include <GL/freeglut.h>
#include <iostream>
#include "tetraedre.hpp"

using namespace std;

GLuint leVBO;
GLuint leBufferCouleur;

float angle=0.0f;

Tetraedre tetraedre;

static void RenderSceneCouleurs(){
	glClear(GL_COLOR_BUFFER_BIT);

	glColor3f(1.0, 0.0, 0.0); //couleur générale

	//Liaison avec le buffer de vertex
	glEnableClientState(GL_VERTEX_ARRAY);
	glBindBuffer(GL_ARRAY_BUFFER, leVBO);
	glVertexPointer(3, GL_FLOAT, 0, 0); //description des données pointées

	//Liaison avec le buffer de couleur
	glEnableClientState(GL_COLOR_ARRAY);
	glBindBuffer(GL_ARRAY_BUFFER, leBufferCouleur);
	glColorPointer(3, GL_FLOAT, 0, 0); //description des données pointées

	glDrawArrays(GL_TRIANGLES, 0, tetraedre.getNbP()); //3 éléments à utiliser pour le dessin

	glDisableClientState(GL_VERTEX_ARRAY);
	glDisableClientState(GL_COLOR_ARRAY);

	glutSwapBuffers();
}

//A lier à la glutIdleFunc
static void IdleFunc()
{
	angle += 0.01f;
	glutPostRedisplay();

}

static void RenderSceneRotation()
{
	glClear(GL_COLOR_BUFFER_BIT);

	glMatrixMode(GL_MODELVIEW); //matrice de modélisation de la scène
	glLoadIdentity(); //matrice identité -> pas de transformation

	glColor3f(1.0, 0.0, 0.0);

	glRotatef(angle, 1, 1, 1); //rotation du tétraedre sur les trois axes

	//Liaison avec le buffer de vertex
	glEnableClientState(GL_VERTEX_ARRAY);
	glBindBuffer(GL_ARRAY_BUFFER, leVBO);
	glVertexPointer(3, GL_FLOAT, 0, 0); //Commencer de 0, chaque position sera sur 3 éléments, de type float

	//Liaison avec le buffer de couleur
	glEnableClientState(GL_COLOR_ARRAY);
	glBindBuffer(GL_ARRAY_BUFFER, leBufferCouleur);
	glColorPointer(3, GL_FLOAT, 0, 0); //description des données pointées

	glDrawArrays(GL_TRIANGLES, 0, tetraedre.getNbP()); //3 éléments à utiliser pour le dessin

	glDisableClientState(GL_VERTEX_ARRAY);

	glutSwapBuffers();
}

static void RenderSceneCameraOrthographique()
{
	glClear(GL_COLOR_BUFFER_BIT);

	glColor3f(1.0, 0.0, 0.0); //couleur générale

	//Modification de la matrice de projection
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity(); //remise à 0 (identité)

	glRotatef(90.0, 0, 1, 0); // rotation de la camera de 90° sur l'axe y pour avoir la vue de coté

	glOrtho(-10.0, 10.0, -10.0, 10.0, -10.0, 10.0); //projection orthogonale sur z=0, avec un volume de vue : xmin=-10, xmax=10, ymin=-10, ymax=10, ...

	//Modification de la matrice de modélisation de la scène
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	//Liaison avec le buffer de vertex
	glEnableClientState(GL_VERTEX_ARRAY);
	glBindBuffer(GL_ARRAY_BUFFER, leVBO);
	glVertexPointer(3, GL_FLOAT, 0, 0); //description des données pointées

	glDrawArrays(GL_TRIANGLES, 0, tetraedre.getNbP()); //3 éléments à utiliser pour le dessin

	glDisableClientState(GL_VERTEX_ARRAY);

	//parce que c'est joli...
	glColor3f(0.2, 0.5, 0.3);
	glutWireTeapot(2.0);

	glutSwapBuffers();
}

static void RenderSceneCameraPerspective()
{
	glClear(GL_COLOR_BUFFER_BIT);

	glColor3f(1.0, 0.0, 0.0); //couleur générale

	//Modification de la matrice de projection
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity(); //remise à 0 (identité)
	gluPerspective(90.0, 1.0, 0.1, 100); //définition d'une perspective (angle d'ouverture 90°,rapport L/H=1.0, near=0.1, far=100)

	//Modification de la matrice de modélisation de la scène
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	//Définition de la position de l'observateur
	gluLookAt(0.0, 0.0, 5.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);//paramètres position(0.0, 0.0, 5.0), point visé(0.0, 0.0, 0.0, upVector - verticale (0.0, 1.0, 0.0)

	//Liaison avec le buffer de vertex
	glEnableClientState(GL_VERTEX_ARRAY);
	glBindBuffer(GL_ARRAY_BUFFER, leVBO);
	glVertexPointer(3, GL_FLOAT, 0, 0); //description des données pointées

	glDrawArrays(GL_TRIANGLES, 0, tetraedre.getNbP()); //3 éléments à utiliser pour le dessin

	glDisableClientState(GL_VERTEX_ARRAY);

	//parce que c'est joli...
	glColor3f(0.2, 0.5, 0.3);
	glutWireTeapot(2.0);

	glutSwapBuffers();
}

static void InitializeGlutCallbacks()
{
	glutDisplayFunc(RenderSceneCameraOrthographique);
	//glutIdleFunc(IdleFunc);
}


static void CreateColorBuffer()
{
 	glGenBuffers(1, &leBufferCouleur); //génération d'une référence de buffer object
	glBindBuffer(GL_ARRAY_BUFFER, leBufferCouleur); //liaison du buffer avec un type tableau de données
	glBufferData(GL_ARRAY_BUFFER, sizeof(float)*tetraedre.getNbP() * 3, tetraedre.returnColors(), GL_STATIC_DRAW); //création et initialisation du container de données (3 couleurs -> 9 float)

}


static void CreateVertexBuffer()
{
 	glGenBuffers(1, &leVBO); //génération d'une référence de buffer object
	glBindBuffer(GL_ARRAY_BUFFER, leVBO); //liaison du buffer avec un type tableau de données
	glBufferData(GL_ARRAY_BUFFER, sizeof(float)*tetraedre.getNbP() * 3, tetraedre.returnVertices(), GL_STATIC_DRAW); //création et initialisation du container de données (3 sommets -> 9 float)
}

int main(int argc, char** argv)
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE|GLUT_RGBA);
	glutInitWindowSize(500, 500);
	glutInitWindowPosition(100, 100);
	glutCreateWindow("TP2 : couleurs, transformations, caméras");

	InitializeGlutCallbacks();

	//toujours après l'initialisation de glut
	GLenum res = glewInit();

	if (res != GLEW_OK) {
		cerr << "Error: " << glewGetErrorString(res) << endl;
		return (EXIT_FAILURE);
	}

	glClearColor(0.0f, 0.0f, 0.0f, 0.0f);

	//fonction de remplissage du buffer de vertex
		CreateVertexBuffer();

	//fonction de remplissage du buffer de couleurs
		CreateColorBuffer();

	glutMainLoop();

	return (EXIT_SUCCESS);
}
