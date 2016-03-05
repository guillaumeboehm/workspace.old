#include <osgViewer/Viewer>
#include <osg/ShapeDrawable>
#include <osg/Material>
#include <osg/PositionAttitudeTransform>
#include <osgGA/NodeTrackerManipulator>
#include <osg/LightSource>
#include <osgGA/GUIEventHandler>
#include <osg/NodeCallback>
#include <osgDB/ReadFile>
#include <stdlib.h>
#include <time.h>
#include <osg/Texture2D>
#include <osgViewer/ViewerEventHandlers>
#include <osg/Switch>
#include <osg/Camera>
#include <iostream>

osg::ref_ptr<osgViewer::Viewer> viewer;
osg::ref_ptr<osg::LOD> vache_lod;
osg::ref_ptr<osg::Camera> cam1;
osg::ref_ptr<osg::Camera> cam2;
osg::ref_ptr<osg::Camera> cam3;

class GestionEvenements : public osgGA::GUIEventHandler 
{
public:
	GestionEvenements(osg::ref_ptr<osg::Group> _scene, osg::ref_ptr<osg::Switch> _switchNode){
		switchNode = _switchNode;
		scene = _scene ;
	}
	
	osg::ref_ptr<osg::Group> scene;
	osg::ref_ptr<osg::Switch> switchNode;

	virtual bool handle( const osgGA::GUIEventAdapter& ea, osgGA::GUIActionAdapter& aa);
};

bool GestionEvenements::handle( const osgGA::GUIEventAdapter& ea, osgGA::GUIActionAdapter& aa)
{
	osg::StateSet* state = scene->getOrCreateStateSet();
	
	switch(ea.getEventType()){
		case osgGA::GUIEventAdapter::KEYDOWN : // appui sur une touche
			switch(ea.getKey())
			{
				case 'a'://desactive ou active le troupeau
					if(switchNode->getValue(0))
						switchNode->setAllChildrenOff();
					else
						switchNode->setAllChildrenOn();
				break;
				case '1':
					//viewer->setCamera(cam1);
					std::cout<<"lol"<<std::endl;
				break;
				case '2':
					//viewer->setCamera(cam2);
					std::cout<<"lol"<<std::endl;
				break;
				case '3':
					//viewer->setCamera(cam3);
				break;
			}
		break;
	}
	return false ;
}

osg::ref_ptr<osg::Node> creation_sol(float taillex, float tailley){
	
	osg::ref_ptr<osg::Texture2D> tex_sol = new osg::Texture2D;
	tex_sol->setImage(osgDB::readImageFile("herbe.jpg"));
	tex_sol->setWrap( osg::Texture::WRAP_S, osg::Texture::REPEAT );
	tex_sol->setWrap( osg::Texture::WRAP_T, osg::Texture::REPEAT );

	osg::ref_ptr<osg::Geometry> sol = osg::createTexturedQuadGeometry(
		osg::Vec3(-1000.0, -1000.0, 0.0),
		osg::Vec3(taillex, 0.0, 0.0),
		osg::Vec3(0.0, tailley, 0.0),
		0.0, 0.0, 10.0, 10.0);
		
	sol->getOrCreateStateSet()->setTextureAttributeAndModes(0, tex_sol.get());
	sol->getOrCreateStateSet()->setMode(GL_DEPTH_TEST, osg::StateAttribute::ON);
	osg::ref_ptr<osg::Geode> sol_draw = new osg::Geode;
	sol_draw->addDrawable(sol.get());
	
	return sol_draw;
}

osg::ref_ptr<osg::Group> creation_troupeau(int nb_vaches, float taillex, float tailley){
	srand(time(NULL));
	
	osg::ref_ptr<osg::Group> troupeau = new osg::Group;
			
	for(unsigned int i=0; i<nb_vaches; ++i){

		osg::ref_ptr<osg::PositionAttitudeTransform> pat = new osg::PositionAttitudeTransform();
		pat->setPosition(osg::Vec3(rand()%(int)(taillex+1), rand()%(int)(tailley+1),570.0));
		pat->setAttitude(osg::Quat(osg::DegreesToRadians(float(rand()%360)), osg::Vec3(0.0, 0.0, 1.0)));
		
		pat->addChild(vache_lod.get());
		troupeau->addChild(pat.get());
	}
	
	return troupeau;
}




int main(void)
{	
	
	//cameras
		cam1 = new osg::Camera;
		cam1->setClearColor(osg::Vec4(0, 0.7, 1, 1)); 
		// Volume de vue : 60° de Field Of View, un rapport de 4/3, un plan near à 0.1 et far à 100
		cam1->setProjectionMatrixAsPerspective(30, 4.0 / 3.0, 0.1, 100);
		
		// Fixe la position et l'orientation du viewer
		cam1->setViewMatrixAsLookAt(	// Identique à gluLookAt() d'OpenGL
			osg::Vec3(0, -100000, 100000), 	// position de la caméra
			osg::Vec3(0, 0, 0),    	// point visé par la caméra
			osg::Vec3(0, 0, 1));   // vecteur perpendiculaire à la caméra
			
		cam2 = new osg::Camera;
		cam2->setClearColor(osg::Vec4(0, 0.7, 1, 1)); 
		// Volume de vue : 60° de Field Of View, un rapport de 4/3, un plan near à 0.1 et far à 100
		cam2->setProjectionMatrixAsPerspective(30, 4.0 / 3.0, 0.1, 100);
		
		// Fixe la position et l'orientation du viewer
		cam2->setViewMatrixAsLookAt(	// Identique à gluLookAt() d'OpenGL
			osg::Vec3(0, 100000, 100000), 	// position de la caméra
			osg::Vec3(0, 0, 0),    	// point visé par la caméra
			osg::Vec3(0, 0, 1));   // vecteur perpendiculaire à la caméra
			
		cam3 = new osg::Camera;
		cam3->setClearColor(osg::Vec4(0, 0.7, 1, 1)); 
		// Volume de vue : 60° de Field Of View, un rapport de 4/3, un plan near à 0.1 et far à 100
		cam3->setProjectionMatrixAsPerspective(30, 4.0 / 3.0, 0.1, 100);
		
		// Fixe la position et l'orientation du viewer
		cam3->setViewMatrixAsLookAt(	// Identique à gluLookAt() d'OpenGL
			osg::Vec3(0, 100000, -100000), 	// position de la caméra
			osg::Vec3(0, 0, 0),    	// point visé par la caméra
			osg::Vec3(0, 0, 1));   // vecteur perpendiculaire à la caméra
	
	//............
	
	viewer = new osgViewer::Viewer;
	osg::DisplaySettings::instance()->setNumMultiSamples(4);
	viewer->setUpViewInWindow( 100, 50, 800, 600 );
	viewer->getCamera()->setClearColor( osg::Vec4( 0,0.7,1,1 ) );
	osgViewer::Viewer::Windows fenetres;
	viewer->getWindows(fenetres);
	fenetres[0]->setWindowName("Vaches");
	viewer->addEventHandler(new osgViewer::StatsHandler);
	viewer->setCamera(cam1);
	

	
	osg::ref_ptr<osg::Group> scene = new osg::Group;
	osg::ref_ptr<osg::Switch> switchNode = new osg::Switch;
	
	osg::ref_ptr<GestionEvenements> gestionnaire = new GestionEvenements(scene, switchNode);
	viewer->addEventHandler(gestionnaire.get());
	
	scene->addChild(creation_sol(9000.0, 9000.0).get());
	
	vache_lod = new osg::LOD;
	vache_lod->setRangeMode( osg::LOD::DISTANCE_FROM_EYE_POINT );	
	
	osg::ref_ptr<osg::Node> vache_high = osgDB::readNodeFile("cow_high.3ds");
	vache_lod->addChild( vache_high.get(), 0, 10000 );
	osg::ref_ptr<osg::Node> vache_med = osgDB::readNodeFile("cow_mid.3ds");
	vache_lod->addChild( vache_med.get(), 10000, 1000000 );
	osg::ref_ptr<osg::Node> vache_low = osgDB::readNodeFile("cow_low.3ds");
	vache_lod->addChild( vache_low.get(), 1000000, 1000000000000 );	
	
	osg::ref_ptr<osg::Group> troupeau = creation_troupeau(50, 7000.0, 7000.0);
	
	switchNode->addChild(troupeau.get());	
	scene->addChild(switchNode.get());
	
	viewer->setSceneData(scene.get());
	
	return viewer->run();
}
