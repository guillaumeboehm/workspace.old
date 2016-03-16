#include "fonctions.h"


int main(void)
{		

	osg::ref_ptr<osgViewer::Viewer> viewer;
	viewer = new osgViewer::Viewer;
	osg::DisplaySettings::instance()->setNumMultiSamples(4);
	viewer->setUpViewInWindow( 100, 50, 800, 600 );

	osg::ref_ptr<osg::Group> scene = new osg::Group;

	osgViewer::Viewer::Windows fenetres;
	viewer->getWindows(fenetres);
	fenetres[0]->setWindowName("DES TANKS QUI EXPLOSENT!!!");
	
	//changer de lumiere

	osg::ref_ptr<osg::LightSource> lumiere = new osg::LightSource;

	lumiere->getLight()->setLightNum(0);

	lumiere->getLight()->setAmbient(osg::Vec4(0.5, 0.5, 0.5, 1.0));
	lumiere->getLight()->setDiffuse(osg::Vec4(0.9, 0.9, 0.9, 1.0));
	lumiere->getLight()->setSpecular(osg::Vec4(1.0, 1.0, 1.0, 1.0));

	scene->addChild(lumiere.get());

	scene->getOrCreateStateSet()->setMode(GL_LIGHT0, osg::StateAttribute::ON);

	//.............

	osg::ref_ptr<osg::Node> terrain = creationTerrain("terrain.tga", "herbe.tga");

	scene->addChild(terrain);
	scene->addChild(creationForet(terrain, 1));
	viewer->setSceneData(scene);
	
	return viewer->run();
}
