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
#include <osg/Fog>
#include <osgParticle/PrecipitationEffect>
#include <osgShadow/ShadowedScene>
#include <osgShadow/ShadowMap>
#include <osgShadow/SoftShadowMap>
#include <osgGA/DriveManipulator>
#include <osgText/Text>
#include <osg/NodeCallback>
#include <iostream>
#include <sstream>
#include <string>

osg::ref_ptr<osgViewer::Viewer> viewer;
osg::ref_ptr<osg::LOD> vache_lod;
osg::ref_ptr<osgText::Text> vitesse_txt = new  osgText::Text;
osg::ref_ptr<osgGA::DriveManipulator> camera;

class CallbackVitesse : public osg::NodeCallback{
public:
	virtual void operator() (osg::Node* n, osg::NodeVisitor* nv)
	{

		double d = camera->getVelocity();
		std::ostringstream o;
		o << d;
		std::string s = o.str();
		vitesse_txt->setText(s);
	}
};

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

osg::ref_ptr<osg::Node> creationHUD(){
	// On crée une caméra qui correspond à un écran de 1280x1024
	osg::Camera* camera = new osg::Camera;
	camera->setProjectionMatrix(osg::Matrix::ortho2D(0, 1366, 0, 750));  
	camera->setReferenceFrame(osg::Transform::ABSOLUTE_RF);
	camera->setViewMatrix(osg::Matrix::identity());
	camera->setClearMask(GL_DEPTH_BUFFER_BIT);

	// Le sous-graphe de la caméra sera affiché après celui de la caméra principale,
	// donc par dessus le reste de la scène.
	camera->setRenderOrder(osg::Camera::POST_RENDER);

	// Les éléments graphiques du HUD (ici un simple texte) constitueront un sous-graphe
	// de la caméra que l'on vient de créer
	vitesse_txt->setColor(osg::Vec4f(osg::Vec3(0, 0, 0), 1));
	vitesse_txt->setPosition(osg::Vec3(50.0f, 50.0f, 0.0f));
	vitesse_txt->setText("0");
	vitesse_txt->setCharacterSize(20);
	vitesse_txt->setFont("arial.ttf");

	osg::Geode* geode = new osg::Geode();
	geode->getOrCreateStateSet()->setMode(GL_LIGHTING, osg::StateAttribute::OFF);
	geode->addDrawable(vitesse_txt);

	camera->addChild(geode);
	return camera;
}


int main(void)
{		
	viewer = new osgViewer::Viewer;
	osg::DisplaySettings::instance()->setNumMultiSamples(4);
	viewer->setUpViewInWindow( 100, 50, 800, 600 );

	camera = new osgGA::DriveManipulator();
	viewer->setCameraManipulator(camera.get());
	viewer->getCamera()->setClearColor( osg::Vec4( 0,0.7,1,1 ) );

	osgViewer::Viewer::Windows fenetres;
	viewer->getWindows(fenetres);
	fenetres[0]->setWindowName("Vaches");
	viewer->addEventHandler(new osgViewer::StatsHandler);
	
	osg::ref_ptr<osg::Group> scene = new osg::Group;
	osg::ref_ptr<osg::Switch> switchNode = new osg::Switch;

	switchNode->setUpdateCallback(new CallbackVitesse);

	osg::ref_ptr<osgShadow::ShadowedScene> shadowScene = new osgShadow::ShadowedScene;
	osg::ref_ptr<osgShadow::SoftShadowMap> sm = new osgShadow::SoftShadowMap;

	//changer de lumiere

	osg::ref_ptr<osg::LightSource> lumiere = new osg::LightSource;

	lumiere->getLight()->setLightNum(1);// GL_LIGHT1
	lumiere->getLight()->setPosition(osg::Vec4(1,-1, 1, 0));// 0 = directionnel

	lumiere->getLight()->setAmbient(osg::Vec4(0.2, 0.2, 0.2, 1.0));
	lumiere->getLight()->setDiffuse(osg::Vec4(0.4, 0.4, 0.4, 1.0));
	lumiere->getLight()->setSpecular(osg::Vec4(1.0, 1.0, 1.0, 1.0));

	scene->addChild(lumiere.get());

	scene->getOrCreateStateSet()->setMode(GL_LIGHT0, osg::StateAttribute::OFF);
	scene->getOrCreateStateSet()->setMode(GL_LIGHT1, osg::StateAttribute::ON);

	//.............

	//shadows

	sm->setSoftnessWidth(0.003);

	shadowScene->setShadowTechnique(sm.get());
	shadowScene->addChild(lumiere.get());
	scene->addChild(shadowScene.get());

	viewer->setSceneData(scene);

	//.............

	//fog

	osg::ref_ptr<osg::Fog> fog = new osg::Fog;

	fog->setMode(osg::Fog::LINEAR);
	fog->setColor(osg::Vec4(0,0.7,1, 1));
	fog->setStart(8000);
	fog->setEnd(30000);

	scene->getOrCreateStateSet()->setAttribute(fog, osg::StateAttribute::ON);
	scene->getOrCreateStateSet()->setMode(GL_FOG, osg::StateAttribute::ON);

	//..............
	

	//pluie

	osg::ref_ptr<osgParticle::PrecipitationEffect>  precipNode = new osgParticle::PrecipitationEffect;

	precipNode->setWind(osg::Vec3(10,0,0));
	precipNode->setParticleSpeed(0.4);
	precipNode->snow(1); 
	// ou « snow » pour de la neige
	//scene->addChild(precipNode.get());

	//..............
	osg::ref_ptr<GestionEvenements> gestionnaire = new GestionEvenements(scene, switchNode);
	viewer->addEventHandler(gestionnaire.get());
	
	shadowScene->addChild(creation_sol(9000.0, 9000.0).get());
	
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
	shadowScene->addChild(switchNode.get());
	scene->addChild(creationHUD().get());
	
	return viewer->run();
}
