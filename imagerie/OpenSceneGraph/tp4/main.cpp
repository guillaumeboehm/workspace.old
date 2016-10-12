#include <osgViewer/Viewer>
#include <osg/ShapeDrawable>
#include <osg/Material>
#include <osgDB/ReadFile>
#include <osg/Geometry>
#include <osg/PositionAttitudeTransform>
#include <osgGA/NodeTrackerManipulator>
#include <osgGA/GUIEventHandler>
#include <osgViewer/ViewerEventHandlers>
#include <osg/TexMat>
#include <osg/LightSource>
#include <osgUtil/LineSegmentIntersector>
#include <osgSim/DOFTransform>
#include <osg/AnimationPath>
#include <osg/MatrixTransform>
#include <osgParticle/SmokeEffect>
#include <ctime>
#include <cstdlib>

osgViewer::Viewer viewer;
osg::ref_ptr<osg::Node> terrain;
osg::ref_ptr<osg::Node> tank;
float rot_turret=0.0f;
osg::Vec3 pos;

osg::ref_ptr<osgParticle::SmokeEffect> effectNode;

bool intersection_terrain( float x, float y, osg::Node* terrain, osg::Vec3& inter, osg::Vec3& normal)
{
	osg::ref_ptr<osgUtil::LineSegmentIntersector> intersector =
	new osgUtil::LineSegmentIntersector(osg::Vec3(x,y,1000), osg::Vec3(x, y,-1000));
	osgUtil::IntersectionVisitor iv(intersector.get());
	terrain->accept(iv);
	if (intersector->containsIntersections()){
		osgUtil::LineSegmentIntersector::Intersections& intersections = intersector->getIntersections();
		// Le segment étant vertical, on prend la première (et à priori unique) intersection trouvée
		const osgUtil::LineSegmentIntersector::Intersection& intersection = *(intersections.begin());
		inter = intersection.getWorldIntersectPoint();
		normal = intersection.getWorldIntersectNormal();

		return true;
	}

	return false;
}

class Deplacement : public osg::NodeCallback
{
public:
    virtual void operator() (osg::Node* n, osg::NodeVisitor* nv)
    {
		osg::PositionAttitudeTransform* pos_tank = (osg::PositionAttitudeTransform*)n;
		osg::Vec3 normal;
		intersection_terrain(pos_tank->getPosition().x(), pos_tank->getPosition().y() + 0.1, terrain, pos, normal);
		pos_tank->setPosition(pos);
		osg::Quat rotation;
		rotation.makeRotate(osg::Vec3f(0, 0, 1), normal);
		pos_tank->setAttitude(rotation);

		effectNode->setPosition(pos);
    }
};



class GestionEvenements : public osgGA::GUIEventHandler
{
 public:
 virtual bool handle( const osgGA::GUIEventAdapter& ea,
 osgGA::GUIActionAdapter& aa);
};

class ChercheNoeud : public osg::NodeVisitor
{
	public:
	ChercheNoeud ( const std::string& name ) 
	: osg::NodeVisitor( osg::NodeVisitor::TRAVERSE_ALL_CHILDREN ), _name( name ) {}
	// Méthode appelée pour chaque nœud du graphe. Si son nom correspond à celui passé
	// en paramètre au constructeur, on sauve l'adresse du nœud dans _node
	virtual void apply( osg::Node& node )
	{
		if (node.getName() == _name)
			_node = &node;
		traverse( node );
		// On continue le parcours du graphe
	}
	osg::Node* getNode() { return _node.get(); }

	protected:
	std::string _name;
	osg::ref_ptr<osg::Node> _node;
};




osg::Node* creation_terrain(){
	osg::Image* heightMap = osgDB::readImageFile("terrain.tga");

	osg::HeightField* terrain = new osg::HeightField();
	terrain->allocate(heightMap->s(), heightMap->t());
	terrain->setOrigin(osg::Vec3(-heightMap->s() / 2, -heightMap->t() / 2, 0));
	terrain->setXInterval(10.0f);
	terrain->setYInterval(10.0f);

	for (unsigned int r = 0; r < terrain->getNumRows(); r++)
		for (unsigned int c = 0; c < terrain->getNumColumns(); c++)
			terrain->setHeight(c, r, ((*heightMap->data(c, r)) / 255.0f) * 300.0f);

	osg::Geode* geode = new osg::Geode();
	geode->addDrawable(new osg::ShapeDrawable(terrain));

	osg::Material* mat = new osg::Material;

	mat->setAmbient (osg::Material::FRONT_AND_BACK, osg::Vec4(0.5, 0.5, 0.5, 1.0));
	mat->setDiffuse (osg::Material::FRONT_AND_BACK, osg::Vec4(0.9, 0.9, 0.9, 1.0));
	mat->setSpecular(osg::Material::FRONT_AND_BACK, osg::Vec4(0.0, 0.0, 0.0, 1.0));
	mat->setShininess(osg::Material::FRONT_AND_BACK, 64);
	geode->getOrCreateStateSet()->setAttributeAndModes(mat);

	osg::Texture2D* tex = new osg::Texture2D(osgDB::readImageFile("herbe.tga"));
	tex->setFilter(osg::Texture2D::MIN_FILTER, osg::Texture2D::LINEAR_MIPMAP_LINEAR);
	tex->setFilter(osg::Texture2D::MAG_FILTER, osg::Texture2D::LINEAR);
	tex->setWrap(osg::Texture::WRAP_S, osg::Texture::REPEAT);
	tex->setWrap(osg::Texture::WRAP_T, osg::Texture::REPEAT);
	geode->getOrCreateStateSet()->setTextureAttributeAndModes(0, tex);

	osg::Matrixd matrix;
	matrix.makeScale(osg::Vec3(10, 10, 1.0));
	osg::ref_ptr<osg::TexMat> matTexture = new osg::TexMat;
	matTexture->setMatrix(matrix);
	geode->getOrCreateStateSet()->setTextureAttributeAndModes(0,
	matTexture.get(), osg::StateAttribute::ON);

	return geode;

}

osg::ref_ptr<osg::Group> creation_foret(osg::Node* terrain, int nb_arbres){
	osg::ref_ptr<osg::Group> foret = new osg::Group;
	osg::ref_ptr<osg::Texture2D> texture = new osg::Texture2D(osgDB::readImageFile("arbre.tga"));
	texture->setFilter(osg::Texture2D::MIN_FILTER, osg::Texture2D::LINEAR);
	texture->setFilter(osg::Texture2D::MAG_FILTER, osg::Texture2D::LINEAR);


	srand (static_cast <unsigned> (time(0)));
	float arbre_posx, arbre_posy, arbre_taille;
	for(int i=0; i<nb_arbres; ++i){

		arbre_posx = static_cast <float> (rand()) / (static_cast <float> (RAND_MAX/1200));
		arbre_posy = static_cast <float> (rand()) / (static_cast <float> (RAND_MAX/1200));
		arbre_taille = static_cast <float> (rand()) / (static_cast <float> (RAND_MAX/15)) + 5.0;
		std::cout << arbre_posx << " " << arbre_posy << std::endl;
		osg::ref_ptr<osg::Geometry> quad = osg::createTexturedQuadGeometry(
			osg::Vec3(-arbre_taille/2, 0, 0), // coin de départ
			osg::Vec3(arbre_taille, 0.0, 0.0), // largeur
			osg::Vec3(0.0, 0.0, arbre_taille), // hauteur
			0.0, 0.0, 1.0, 1.0); // coordonnées de texture
		quad->getOrCreateStateSet()->setTextureAttributeAndModes(0, texture.get());
		quad->getOrCreateStateSet()->setMode(GL_BLEND, osg::StateAttribute::ON);
		// On ajoute le quad dans le TRANSPARENT BIN, une collection d'objets transparents,
		// pour qu'ils soient triés selon la profondeur et affichés du plus éloigné au plus proche
		quad->getOrCreateStateSet()->setRenderingHint(osg::StateSet::TRANSPARENT_BIN);
		// On crée le billboard et on lui attache le quad à orienter face à la caméra
		osg::ref_ptr<osg::Billboard> billboard = new osg::Billboard;
		billboard->setMode(osg::Billboard::AXIAL_ROT);
		billboard->setAxis(osg::Vec3(0,0,1));
		billboard->addDrawable(quad);
		// Optionnel : on désactive l'éclairage sur le billboard
		billboard->getOrCreateStateSet()->setMode(GL_LIGHTING, osg::StateAttribute::OFF);

		osg::PositionAttitudeTransform* pos_arbre = new osg::PositionAttitudeTransform;
		osg::Vec3 posi, normal;
		intersection_terrain(arbre_posx, arbre_posy, terrain, posi, normal);
		pos_arbre->setPosition(posi);
		pos_arbre->setScale(osg::Vec3(10.0, 10.0, 10.0));
		pos_arbre->addChild(billboard);
		foret->addChild(pos_arbre);
	}

	return foret;
}

osg::PositionAttitudeTransform* creation_CHARRR(float posx, float posy, osg::Node* terrain){
	osg::Node* LECHARRR = osgDB::readNodeFile("t72-tank_des.flt");
	osg::PositionAttitudeTransform* pos_tank = new osg::PositionAttitudeTransform;
	osg::Vec3 posi, normal;
	intersection_terrain(posx, posy, terrain, posi, normal);
	pos_tank->setPosition(posi);
	pos_tank->setScale(osg::Vec3d(10, 10, 10));
	osg::Quat rotation;
	rotation.makeRotate(osg::Vec3f(0, 0, 1), normal);
	pos_tank->setAttitude(rotation);
	pos_tank->addChild(LECHARRR);
	pos_tank->setUpdateCallback(new Deplacement);
	return pos_tank;
}

bool GestionEvenements::handle( const osgGA::GUIEventAdapter& ea,
 osgGA::GUIActionAdapter& aa)
{
	switch(ea.getEventType()){
		case osgGA::GUIEventAdapter::KEYDOWN :

			switch(ea.getKey()){

				case 'a':
				{

					rot_turret += 3.0;

					ChercheNoeud rechercheTourelle("turret");
					tank->accept(rechercheTourelle);
					osg::Node* noeudTourelle = rechercheTourelle.getNode();
					if (noeudTourelle != NULL)
					{
						osgSim::DOFTransform* tourelleDOF =
						           dynamic_cast<osgSim::DOFTransform*>(noeudTourelle);
						tourelleDOF->setCurrentHPR(osg::Vec3(osg::DegreesToRadians(rot_turret),
						                                        0.0, 
						                                        0.0));
					}
				}
					break;
				case 'z':
				{

					rot_turret -= 3.0;

					ChercheNoeud rechercheTourelle("turret");
					tank->accept(rechercheTourelle);
					osg::Node* noeudTourelle = rechercheTourelle.getNode();
					if (noeudTourelle != NULL)
					{
						osgSim::DOFTransform* tourelleDOF =
						           dynamic_cast<osgSim::DOFTransform*>(noeudTourelle);
						tourelleDOF->setCurrentHPR(osg::Vec3(osg::DegreesToRadians(rot_turret),
						                                        0.0, 
						                                        0.0));
					}
				}
					break;
				case 'e':
					break;
			}
			break;

		case osgGA::GUIEventAdapter::PUSH :{
			int x = ea.getX();
			int y = ea.getY();
			if( ea.getButton() == osgGA::GUIEventAdapter::LEFT_MOUSE_BUTTON)
				std::cout << "bouton gauche" << std::endl;
			if (ea.getButton() == osgGA::GUIEventAdapter::MIDDLE_MOUSE_BUTTON)
				std::cout << "bouton milieu" << std::endl;
			if (ea.getButton() == osgGA::GUIEventAdapter::RIGHT_MOUSE_BUTTON)
				std::cout << "bouton droit" << std::endl;
			break;
 }
		case osgGA::GUIEventAdapter::DOUBLECLICK :
			break;
			}
 return false; // pour que l'événement soit traité par d'autres gestionnaires
}

int main(void){
	osg::DisplaySettings::instance()->setNumMultiSamples( 4 );
	viewer.setUpViewInWindow( 100, 50, 800, 600 );
	viewer.getCamera()->setClearColor( osg::Vec4( 0.5,0.5,0.5,1) );
	viewer.addEventHandler(new osgViewer::StatsHandler);

	osg::Group* scene = new osg::Group;

	osg::ref_ptr<osg::LightSource> lumiere = new osg::LightSource;
	lumiere->getLight()->setLightNum(0); // GL_LIGHT1
	lumiere->getLight()->setPosition(osg::Vec4(1, -1, 2, 0)); // 0 = directionnel
	lumiere->getLight()->setAmbient(osg::Vec4(0.5, 0.5, 0.5, 1.0));
	lumiere->getLight()->setDiffuse(osg::Vec4(0.9, 0.9, 0.9, 1.0));
	lumiere->getLight()->setSpecular(osg::Vec4(1.0, 1.0, 1.0, 1.0));
	scene->addChild(lumiere.get());

	terrain = creation_terrain();
	scene->addChild(terrain.get());
	scene->addChild(creation_foret(terrain, 50));

	tank = creation_CHARRR(0,0,terrain);
	scene->addChild(tank);

	effectNode = new osgParticle::SmokeEffect;
	effectNode->setTextureFileName("arbre.tga");
	effectNode->setIntensity(2);
	effectNode->setScale(40);
	effectNode->setPosition(pos);
	scene->addChild(effectNode.get());
/*
	// Ajout du cube dans un groupe osg::MatrixTransform auquel on affectera
	// l'animation path pour le faire évoluer au cours du temps.
	// On aurait aussi pu utiliser un osg::PositionAttitudetransform 
	osg::ref_ptr<osg::MatrixTransform> mt = new osg::MatrixTransform; 
	mt->addChild( tank );
	// Création d'un Animation Path 
	osg::ref_ptr<osg::AnimationPath> path = new osg::AnimationPath;
	// Définition du mode de boucle (autres possibilités : LOOP, NO_LOOPING) 
	path->setLoopMode( osg::AnimationPath::SWING );
	// Création de points de contrôle
	osg::AnimationPath::ControlPoint  p0(osg::Vec3(0,0,pos.z())); 
	osg::AnimationPath::ControlPoint  p1(osg::Vec3( 1000,0,pos.z())); 
	path->insert( 0.0f, p0 ); 
	// Au temps t=0 s, le cube est en p0
	path->insert( 2.0f, p1 );  
	// Au temps t=2 s, le cube est en p1
	// Mise en place du callback 
	osg::ref_ptr<osg::AnimationPathCallback> apc = new osg::AnimationPathCallback( path.get() ); 
	mt->setUpdateCallback( apc.get() ); 

	scene->addChild(mt);*/

	viewer.setSceneData(scene);

	osg::ref_ptr<GestionEvenements> gestionnaire = new GestionEvenements();
	viewer.addEventHandler(gestionnaire.get());

	return viewer.run();
}
