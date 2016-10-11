//R. RAFFIN, IUT Aix-Marseille, département Informatique, site d'Arles
//M4104c, ARCHI IN
//romain.raffin[AT]univ-amu.fr

#ifndef _H_SKYBOX
#define _H_SKYBOX

#define SKYBOX_RIGHT 5
#define SKYBOX_LEFT 4

#define SKYBOX_TOP 3
#define SKYBOX_BOTTOM 2

#define SKYBOX_FRONT 1
#define SKYBOX_BACK 0

class SkyBox
{
private:
	unsigned int MAXFACES;
	bool created;
	GLuint DisplayListId;
	GLuint *IdTextureTab;
public:
	SkyBox();
	~SkyBox();

	SkyBox(const SkyBox&);
	void LoadSingleTexture(GLuint, const char*);
	void Create(void);
	void CreateDisplayList(const struct point3D*, const struct point3D *);
	void OpenGLDraw();


};

#endif
