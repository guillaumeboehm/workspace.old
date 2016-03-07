#include <osgViewer/Viewer>
#include <osg/ShapeDrawable>
#include <osg/Material>
#include <osg/PositionAttitudeTransform>
#include <osgGA/NodeTrackerManipulator>
#include <osg/LightSource>
#include <osgGA/GUIEventHandler>
#include <osg/NodeCallback>
#include <osgText/Text>

float deplacementz = 0;
float deplacementx = 0;

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
	osg::ref_ptr<osgText::Text> text = new  osgText::Text;
	text->setColor(osg::Vec4f(osg::Vec3(0, 0, 0), 1));
	text->setPosition(osg::Vec3(50.0f, 50.0f, 0.0f));
	text->setText("Le texte de mon HUD");
	text->setCharacterSize(20);
	//text->setFont("arial.ttf");

	osg::Geode* geode = new osg::Geode();
	geode->getOrCreateStateSet()->setMode(GL_LIGHTING, osg::StateAttribute::OFF);
	geode->addDrawable(text);

	camera->addChild(geode);
	return camera;
}

class CallbackDeplacement : public osg::NodeCallback
 {
 public:
     virtual void operator() (osg::Node* n, osg::NodeVisitor* nv)
     {
         // code pour modifier le nœud, par exemple la position si il s 'agit
         // d'un nœud de type osg::PositionAttitudeTransform :
         osg::PositionAttitudeTransform* pos = (osg::PositionAttitudeTransform*)n;
         pos->setPosition(osg::Vec3(pos->getPosition().x() + deplacementx, pos->getPosition().y(), pos->getPosition().z() + deplacementz));
     }
 };

class GestionEvenements : public osgGA::GUIEventHandler 
{
public:
	GestionEvenements(osg::ref_ptr<osg::Group> _scene){
		scene = _scene ;
	}
	
	osg::ref_ptr<osg::Group> scene;

	virtual bool handle( const osgGA::GUIEventAdapter& ea, osgGA::GUIActionAdapter& aa);
};

bool GestionEvenements::handle( const osgGA::GUIEventAdapter& ea, osgGA::GUIActionAdapter& aa)
{
	osg::StateSet* state = scene->getOrCreateStateSet();
	
	switch(ea.getEventType()){
		case osgGA::GUIEventAdapter::KEYDOWN : // appui sur une touche
			switch(ea.getKey())
			{
				case '1':
					if(state->getMode(GL_LIGHT1) == osg::StateAttribute::OFF)
						state->setMode( GL_LIGHT1, osg::StateAttribute::ON );
					else
						state->setMode( GL_LIGHT1, osg::StateAttribute::OFF );
				break;
				
				case '2':
					if(state->getMode(GL_LIGHT2) == osg::StateAttribute::OFF)
						state->setMode( GL_LIGHT2, osg::StateAttribute::ON );
					else
						state->setMode( GL_LIGHT2, osg::StateAttribute::OFF );
				break;
			}
			
			if(ea.getKey() == 'z')
				deplacementz = 0.01;
				
			if(ea.getKey() == 's')
				deplacementz = -0.01;
				
			if(ea.getKey() == 'q')
				deplacementx = -0.01;
				
			if(ea.getKey() == 'd')
				deplacementx = 0.01;
			break;
		break;
		
		case osgGA::GUIEventAdapter::KEYUP : // relache une touche
			if(ea.getKey() == 'z')
				deplacementz = 0;
				
			if(ea.getKey() == 's')
				deplacementz = 0;
				
			if(ea.getKey() == 'q')
				deplacementx = 0;
				
			if(ea.getKey() == 'd')
				deplacementx = 0;
			break;
		break;
	}
	return false ;
}

int main(void)
{
	osgViewer::Viewer   viewer;
	osg::DisplaySettings::instance()->setNumMultiSamples(4);
	viewer.setUpViewInWindow( 100, 50, 800, 600 );
	viewer.getCamera()->setClearColor( osg::Vec4( 1,1,1,1 ) );
	osg::Group* scene = new osg::Group;
	
	osg::ref_ptr<GestionEvenements> gestionnaire = new GestionEvenements(scene);
	viewer.addEventHandler(gestionnaire.get());
	
	osg::StateSet* state = scene->getOrCreateStateSet(); 
	state->setMode( GL_LIGHT0, osg::StateAttribute::OFF ); 
	state->setMode( GL_LIGHT1, osg::StateAttribute::ON );
	
	osg::ref_ptr<osg::LightSource> lumiere = new osg::LightSource;
	lumiere->getLight()->setLightNum(1);// GL_LIGHT1
	lumiere->getLight()->setPosition(osg::Vec4(1,-1, 1, 0));// 0 = directionnel
	lumiere->getLight()->setAmbient(osg::Vec4(0.2, 0.2, 0.2, 1.0));
	lumiere->getLight()->setDiffuse(osg::Vec4(0.7, 0.4, 0.6, 1.0));
	lumiere->getLight()->setSpecular(osg::Vec4(1.0, 1.0, 1.0, 1.0));
	scene->addChild(lumiere.get());
	
	osg::ref_ptr<osg::LightSource> lumiere2 = new osg::LightSource;
	lumiere2->getLight()->setLightNum(2);// GL_LIGHT2
	lumiere2->getLight()->setPosition(osg::Vec4(1,-1, 1, 1));// 1 = ponctuelle
	lumiere2->getLight()->setAmbient(osg::Vec4(0.2, 0.2, 0.2, 1.0));
	lumiere2->getLight()->setDiffuse(osg::Vec4(0.7, 0.4, 0.6, 1.0));
	lumiere2->getLight()->setSpecular(osg::Vec4(1.0, 1.0, 1.0, 1.0));
	scene->addChild(lumiere2.get());



	osg::Material* matBoite = new osg::Material;
	matBoite->setAmbient (osg::Material::FRONT_AND_BACK, osg::Vec4(0.5, 0.0, 0.0, 1.0));
	matBoite->setDiffuse (osg::Material::FRONT_AND_BACK, osg::Vec4(0.9, 0.0, 0.0, 1.0));
	matBoite->setSpecular(osg::Material::FRONT_AND_BACK, osg::Vec4(0.2, 0.2, 0.2, 1.0));
	matBoite->setShininess(osg::Material::FRONT_AND_BACK, 64);
	
	osg::Material* matSphere = new osg::Material;
	matSphere->setAmbient (osg::Material::FRONT_AND_BACK, osg::Vec4(0.5, 0.5, 0.0, 1.0));
	matSphere->setDiffuse (osg::Material::FRONT_AND_BACK, osg::Vec4(0.9, 0.9, 0.0, 1.0));
	matSphere->setSpecular(osg::Material::FRONT_AND_BACK, osg::Vec4(0.2, 0.2, 0.2, 1.0));
	matSphere->setShininess(osg::Material::FRONT_AND_BACK, 64);
	
	osg::Material* matCone = new osg::Material;
	matCone->setAmbient (osg::Material::FRONT_AND_BACK, osg::Vec4(0.5, 0.0, 0.2, 1.0));
	matCone->setDiffuse (osg::Material::FRONT_AND_BACK, osg::Vec4(0.9, 0.0, 0.2, 1.0));
	matCone->setSpecular(osg::Material::FRONT_AND_BACK, osg::Vec4(0.2, 0.2, 0.2, 1.0));
	matCone->setShininess(osg::Material::FRONT_AND_BACK, 64);



	// Création d'une boîte centrée à l'origine, de dimensions 2x3x4:
	osg::Box* boite = new osg::Box(osg::Vec3(0, 0, 0), 2,3,4);
	osg::ShapeDrawable* boiteDrawable = new osg::ShapeDrawable(boite);
	boiteDrawable->getOrCreateStateSet()->setAttributeAndModes(matBoite);
	osg::Geode* boiteGeode = new osg::Geode();
	boiteGeode->addDrawable(boiteDrawable);
	boiteGeode->setName("Boite");
	
	osg::Sphere* sphere = new osg::Sphere(osg::Vec3(5, 0, 0), 1.0);
	osg::ShapeDrawable* sphereDrawable = new osg::ShapeDrawable(sphere);
	sphereDrawable->getOrCreateStateSet()->setAttributeAndModes(matSphere);
	osg::Geode* sphereGeode = new osg::Geode();
	sphereGeode->addDrawable(sphereDrawable);
	sphereGeode->setName("Sphere");
	
	osg::Cone* cone = new osg::Cone(osg::Vec3(0, 5, 0), 1.0, 2.0);
	osg::ShapeDrawable* coneDrawable = new osg::ShapeDrawable(cone);
	coneDrawable->getOrCreateStateSet()->setAttributeAndModes(matCone);
	osg::Geode* coneGeode = new osg::Geode();
	coneGeode->addDrawable(coneDrawable);
	coneGeode->setName("Cone");
	
	osg::PositionAttitudeTransform* boiteTransform = new osg::PositionAttitudeTransform();
	boiteTransform->addChild(boiteGeode);
	boiteTransform->setUpdateCallback(new CallbackDeplacement);
	osg::PositionAttitudeTransform* sphereTransform = new osg::PositionAttitudeTransform();
	sphereTransform->addChild(sphereGeode);
	osg::PositionAttitudeTransform* coneTransform = new osg::PositionAttitudeTransform();
	coneTransform->addChild(coneGeode);


	osg::ref_ptr<osgGA::NodeTrackerManipulator> manip = new osgGA::NodeTrackerManipulator;
	manip->setTrackNode(coneGeode);
	manip->setTrackerMode(osgGA::NodeTrackerManipulator::NODE_CENTER);
	viewer.setCameraManipulator(manip.get());
	
	scene->addChild(creationHUD().get());
	scene->addChild(coneTransform);
	scene->addChild(sphereTransform);
	scene->addChild(boiteTransform);
	viewer.setSceneData(scene);
	
	return viewer.run();
}
