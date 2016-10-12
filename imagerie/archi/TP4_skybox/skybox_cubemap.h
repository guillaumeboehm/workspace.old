//R. RAFFIN, IUT Aix-Marseille, département Informatique, site d'Arles
//M4104c, ARCHI IN
//romain.raffin[AT]univ-amu.fr

#ifndef _H_SKYBOX_CUBEMAP
#define _H_SKYBOX_CUBEMAP

#define SKYBOXCM_RIGHT 1
#define SKYBOXCM_LEFT 0

#define SKYBOXCM_TOP 2
#define SKYBOXCM_BOTTOM 3

#define SKYBOXCM_FRONT 4
#define SKYBOXCM_BACK 5

class SkyBoxCubeMap
{
private:
	unsigned int MAXFACES;
	bool created;
	GLuint DisplayListId;
	GLuint cube_map_texture_ID;
public:

	SkyBoxCubeMap();
	~SkyBoxCubeMap();

	SkyBoxCubeMap(const SkyBoxCubeMap&);
	void LoadTextureCubeMap();
	void Create(void);
	void CreateDisplayList(const struct point3D*, const struct point3D *);
	void OpenGLDraw();
};

#endif
