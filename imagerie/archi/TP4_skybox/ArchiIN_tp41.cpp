//R. RAFFIN, IUT Aix-Marseille, département Informatique, site d'Arles
//M4104c, ARCHI IN
//romain.raffin[AT]univ-amu.fr

//Skybox "à l'ancienne", avec 6 images plaquées sur les 6 faces d'un cube

#include <GL/glew.h>

#include <GL/gl.h>
#include <GL/freeglut.h>

#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <cmath>

#include <iostream>

#include "glsl_fs.h"
#include "glsl_vs.h"
#include "glsl_program.h"

#include "fonctions.h"
#include "objetsOFF.h"
#include "skybox.h"

using namespace std;

#define ECHAP 27

//GLSL_Program * mes_shaders;
float angle = 0.0f;

//pour les VBO
GLuint VBOCouleurs;
GLuint VBOSommets;
GLuint VBONormales;

Objet monobjet;
SkyBox maskybox;

//variables pour la gestion des paramètres de la fenêtre
float windowRatio = 1.0f;
int windowHeight = 500;
int windowWidth = 500;

unsigned int nbimages;

//une fonction qui permet de changer à intervalles réguliers le titre de la fenêtre Glut/openGL
//pour afficher, par exemple, le nombre d'images/sec
static void callback_Timer(int value)
{

	char message[100];
	strcpy(message, "TP41 Skybox ");

	char nombre[10];
	sprintf(nombre, "%u", nbimages);
	strcat(message, nombre);
	strcat(message, " im/s");

	glutSetWindowTitle(message);

	nbimages = 0;

	glutTimerFunc( 1000, callback_Timer, value); //on repart pour une alarm dans 1 s

}


void BeforeReallyQuit()
{
	cerr << "Nettoyage des ressources\n";

//	delete mes_shaders;

	//Desallocation des Buffers OpenGL créés pour les VBO
	glDeleteBuffers((GLsizei) 1, &VBOSommets);
	glDeleteBuffers((GLsizei) 1, &VBOCouleurs);
	glDeleteBuffers((GLsizei) 1, &VBONormales);

	cerr << "System Clear :-)\n";
}

void LoadOFFObject(Objet * _objet, const char * _fichier_off)
{
	_objet -> charge_OFF(_fichier_off);
}

void CreateVBOFromObject(Objet * _monobjet)
{

	if (glewIsSupported("GL_ARB_vertex_buffer_object") == GL_FALSE) {
		cerr << "VBO impossibles, non supportés\n";
		exit (1);
	}

	//A priori, les VBO sont supportés
	//création des tableaux de normales et points
	float * lnormales = new float[_monobjet -> nbfaces * 9];
	float * lsommets = new float[_monobjet -> nbfaces * 9];
	float * lcolors = new float[_monobjet -> nbfaces * 9];

	//remplissage des tableaux
	//tableau des couleurs, 1 par point, tirée aléatoirement
	unsigned int cpt = 0;
	for (unsigned int i = 0; i < _monobjet -> nbfaces; i++) {
		lcolors[cpt++] = tirage_alea(0.0, 0.5); //R
		lcolors[cpt++] = tirage_alea(0.0, 0.5); //G
		lcolors[cpt++] = tirage_alea(0.0, 0.5); //B

		lcolors[cpt++] = tirage_alea(0.0, 0.5); //R
		lcolors[cpt++] = tirage_alea(0.0, 0.5); //G
		lcolors[cpt++] = tirage_alea(0.0, 0.5); //B

		lcolors[cpt++] = tirage_alea(0.0, 0.5); //R
		lcolors[cpt++] = tirage_alea(0.0, 0.5); //G
		lcolors[cpt++] = tirage_alea(0.0, 0.5); //B
	}

	//tableau des normales
	cpt=0;
	for (unsigned int i = 0; i < _monobjet -> nbfaces; i++) {
		//On recopie UNE normale par sommets
		lnormales[cpt++] = _monobjet -> lfacesnormales[i].x;
		lnormales[cpt++] = _monobjet -> lfacesnormales[i].y;
		lnormales[cpt++] = _monobjet -> lfacesnormales[i].z;

		lnormales[cpt++] = _monobjet -> lfacesnormales[i].x;
		lnormales[cpt++] = _monobjet -> lfacesnormales[i].y;
		lnormales[cpt++] = _monobjet -> lfacesnormales[i].z;

		lnormales[cpt++] = _monobjet -> lfacesnormales[i].x;
		lnormales[cpt++] = _monobjet -> lfacesnormales[i].y;
		lnormales[cpt++] = _monobjet -> lfacesnormales[i].z;
	}

	cpt = 0;
	//remplissage du tableau des sommets (!! non indexé, 3 points par faces = lourd)
	for (unsigned int i = 0; i < _monobjet -> nbfaces; i++) {

		lsommets[cpt++] = _monobjet->lpoints[_monobjet->lfaces[i].S1].x;
		lsommets[cpt++] = _monobjet->lpoints[_monobjet->lfaces[i].S1].y;
		lsommets[cpt++] = _monobjet->lpoints[_monobjet->lfaces[i].S1].z;

		lsommets[cpt++] = _monobjet->lpoints[_monobjet->lfaces[i].S2].x;
		lsommets[cpt++] = _monobjet->lpoints[_monobjet->lfaces[i].S2].y;
		lsommets[cpt++] = _monobjet->lpoints[_monobjet->lfaces[i].S2].z;

		lsommets[cpt++] = _monobjet->lpoints[_monobjet->lfaces[i].S3].x;
		lsommets[cpt++] = _monobjet->lpoints[_monobjet->lfaces[i].S3].y;
		lsommets[cpt++] = _monobjet->lpoints[_monobjet->lfaces[i].S3].z;
	}


	//VBO pour les sommets
	glGenBuffers((GLsizei) 1, &VBOSommets);
	glBindBuffer(GL_ARRAY_BUFFER, VBOSommets);
	glBufferData(GL_ARRAY_BUFFER, _monobjet -> nbfaces * 9 * sizeof(float), lsommets, GL_STATIC_DRAW);

	//VBO pour les couleurs
	glGenBuffers((GLsizei) 1, &VBOCouleurs);
	glBindBuffer(GL_ARRAY_BUFFER, VBOCouleurs);
	glBufferData(GL_ARRAY_BUFFER, _monobjet -> nbfaces * 9 * sizeof(float), lcolors, GL_STATIC_DRAW);

	//VBO pour les normales
	glGenBuffers((GLsizei) 1, &VBONormales);
	glBindBuffer(GL_ARRAY_BUFFER, VBONormales);
	glBufferData(GL_ARRAY_BUFFER, _monobjet -> nbfaces * 9 * sizeof(float) , lnormales, GL_STATIC_DRAW);

	//on peut les jeter, ca a été transféré à la CG
	delete []lcolors;
	delete []lnormales;
	delete []lsommets;
}


void GeomInit(void)
{
	//on charge l'obbjet OFF
	LoadOFFObject(&monobjet, "data/spaceshuttle.off");
	//on crée les VertexBufferObjets
	CreateVBOFromObject(&monobjet);

	cerr << "Géomètrie chargée\n" << endl;

	maskybox.LoadSingleTexture(SKYBOX_BACK, "data/islands_south.png");
	maskybox.LoadSingleTexture(SKYBOX_FRONT, "data/islands_north.png");
	maskybox.LoadSingleTexture(SKYBOX_TOP, "data/islands_up.png");
	maskybox.LoadSingleTexture(SKYBOX_BOTTOM, "data/islands_down.png");
	maskybox.LoadSingleTexture(SKYBOX_RIGHT, "data/islands_east.png");
	maskybox.LoadSingleTexture(SKYBOX_LEFT, "data/islands_west.png");
	maskybox.Create();

	struct point3D* bbmin;
	bbmin = new struct point3D();

	bbmin->x = -10000.0;
	bbmin->y = -10000.0;
	bbmin->z = -10000.0;

	struct point3D* bbmax;
	bbmax = new struct point3D();
	bbmax->x = 10000.0;
	bbmax->y = 10000.0;
	bbmax->z = 10000.0;


	maskybox.CreateDisplayList(bbmin, bbmax);

	delete bbmin;
	delete bbmax;

	cerr << "SkyBox créée" << endl;
}

static void callback_Window(GLsizei width, GLsizei height)
{
//au cas où h soit nul et entraîne une division par 0
	if(height == 0)
		height = 1;

	glViewport(0, 0, width, height);

	windowWidth = width;
	windowHeight = height;

	windowRatio = float(windowWidth) / float(windowHeight);

	cerr << "callback_Window " << "new width " << windowWidth << " new height " << windowHeight << endl;

	// Reset the coordinate system before modifying
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	// Set the correct perspective.
	gluPerspective(45, windowRatio, 1, 100000);

	glMatrixMode(GL_MODELVIEW);
}

static void callback_Idle()
{
	angle += 0.005f; //pour la rotation de l'objet sur lui-même

	glutPostRedisplay();
}

void DrawVBO()
{
	//On éteint la lumière pour profiter des couleurs...
	glDisable(GL_LIGHTING);
	glDisable(GL_LIGHT0);

	glEnableClientState(GL_VERTEX_ARRAY);
	glEnableClientState(GL_COLOR_ARRAY);
	glEnableClientState(GL_NORMAL_ARRAY);

	glBindBuffer( GL_ARRAY_BUFFER, VBOSommets);
	glVertexPointer( 3, GL_FLOAT, 0, (char *) NULL );

	glBindBuffer( GL_ARRAY_BUFFER, VBOCouleurs);
	glColorPointer( 3, GL_FLOAT, 0, (char *) NULL );

	glBindBuffer( GL_ARRAY_BUFFER, VBONormales);
	glNormalPointer(GL_FLOAT, 0, (char *) NULL );

	glDrawArrays(GL_TRIANGLES, 0, monobjet.nbfaces * 3);

	glDisableClientState(GL_NORMAL_ARRAY);
	glDisableClientState(GL_COLOR_ARRAY);
	glDisableClientState(GL_VERTEX_ARRAY);
}

static void RenderScene(void)
{

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glLoadIdentity();

	float distance = 0.0f;
	float max = fmax(monobjet.max.x, monobjet.max.y);
	max = fmax(monobjet.max.z, max);

	//c'est nul de le faire à chaque image si l'objet ne change pas !
	distance = max / tan(M_PI / 4.0f);

	//glLightfv(GL_LIGHT0,GL_POSITION,Light1Pos);

	gluLookAt(0.0, 0.0, distance * 5.0f, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);

	glRotatef(angle, 1, 1, 	1);

	glPushMatrix();
	maskybox.OpenGLDraw();
	glPopMatrix();

	glPushMatrix();
	glTranslatef(-monobjet.centroid.x, -monobjet.centroid.y, -monobjet.centroid.z);
	DrawVBO();
	glPopMatrix();

	nbimages++;
	glutSwapBuffers();
}

static void callback_Keyboard(unsigned char key, int x, int y)
{
	switch (key) {
	case ECHAP:
		cout << "callback_Keyboard - " << "sortie de la boucle de rendu" << endl;
		glutLeaveMainLoop(); //retour au main()
		break;
	default:
		cerr << "La touche " << int(key) << " est non active." << endl;
		break;
	}
}

void GlInit()
{
	glEnable(GL_DEPTH_TEST);
	glClearColor(0.5, 0.5, 1.0, 1.0);

	glShadeModel(GL_SMOOTH);

	nbimages = 0;
	glutTimerFunc(5000, callback_Timer, 0); //démarrage de la fonction action_timer dans 5s
}

static GLvoid InitializeGlutCallbacks()
{
	//quelle fonction est appelée au rendu ?
	glutDisplayFunc(RenderScene);

	//quelle fonction est appelée quand le GPU est en attente ?
	//fonction inutile, on utilise un timer pour bloquer le framerate
	glutIdleFunc(callback_Idle);

	//quelle fonction est appelée pour traiter les événements du clavier (classique) ?
	glutKeyboardFunc(callback_Keyboard);

	//quelle fonction est appelée pour traiter les alarmes ?
	//glutTimerFunc();à appeler lors de la mise en place en l'alarme

	//quelle fonction est appelée pour traiter les événements souris ?
	//glutMotionFunc(callback_Mouse);

	//quelle fonction est appelée pour traiter les événements sur la fenêtre ?
	glutReshapeFunc(callback_Window);

	//quelle fonction est appelée pour traiter les touches spéciales du clavier ?
	//glutSpecialFunc(&callback_SpecialKeys);
}

void GlewInit()
{
	GLenum err = glewInit();

	if (err != GLEW_OK) {
		cerr << "Erreur: " << glewGetErrorString(err) << endl;
	}
	cerr << "initGLEW_ok, ref GLEW " << glewGetString(GLEW_VERSION) << endl;

	if (glewIsSupported("GL_VERSION_2_0"))
		cerr << "ok OpenGL 2.0\n";
	else {
		cerr << "OpenGL 2.0 impossible\n";
		exit(1);
	}

	cout << "OpenGL Vendor: " << (char*) glGetString(GL_VENDOR) << "\n";
	cout << "OpenGL Renderer: " << (char*) glGetString(GL_RENDERER) << "\n";
	cout << "OpenGL Version: " << (char*) glGetString(GL_VERSION) << "\n";
	//si vous voulez vraiment avoir plus d'informations, décommentez la ligne suivante...
	//cout << "OpenGL Extensions:\n" << (char*) glGetString(GL_EXTENSIONS) << "\n";
}

void MyInit()
{
	atexit(&BeforeReallyQuit); // fonction appellée dès que le signal QUIT est reçu

	//srandom((unsigned int)(time(NULL))); // pour le générateur pseudo-aléatoire
}

int main(int argc, char **argv)
{
	//on crée le contexte OpenGL et la fenêtre
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGBA);
	glutInitWindowPosition(100,100);
	glutInitWindowSize(windowWidth, windowHeight);
	glutCreateWindow("TP41 Skyboxes ");

	//attachement des fonctions de l'OpenGL
	InitializeGlutCallbacks();

	MyInit();
	GlewInit();

	GlInit();
	GeomInit();

	glutMainLoop();

	return(EXIT_SUCCESS);
}

