#include "fonctions.h"

osg::ref_ptr<osg::Node> creationTerrain(std::string HeightImage, std::string Texture){

	osg::ref_ptr<osg::Image> heightMap = osgDB::readImageFile(HeightImage);
	osg::ref_ptr<osg::HeightField> terrain = new osg::HeightField();

	terrain->allocate(heightMap->s(), heightMap->t());
	terrain->setOrigin(osg::Vec3(-heightMap->s() / 2, -heightMap->t() / 2, 0));
	terrain->setXInterval(10.0f);
	terrain->setYInterval(10.0f);

	for (unsigned int r = 0; r < terrain->getNumRows(); r++)
		for (unsigned int c = 0; c < terrain->getNumColumns(); c++)
			terrain->setHeight(c, r, ((*heightMap->data(c, r)) / 255.0f) * 300.0f);

	osg::ref_ptr<osg::Geode> geode = new osg::Geode();

	osg::ref_ptr<osg::ShapeDrawable> terrain_drawable = new osg::ShapeDrawable(terrain);

	//materiau

	osg::ref_ptr<osg::Material> mat = new osg::Material;

	mat->setAmbient (osg::Material::FRONT_AND_BACK, osg::Vec4(0.3, 0.3, 0.3, 1.0));
	mat->setDiffuse (osg::Material::FRONT_AND_BACK, osg::Vec4(0.4, 0.4, 0.4, 1.0));
	mat->setSpecular(osg::Material::FRONT_AND_BACK, osg::Vec4(0.0, 0.0, 0.0, 1.0));
	mat->setShininess(osg::Material::FRONT_AND_BACK, 64);

	terrain_drawable->getOrCreateStateSet()->setAttributeAndModes(mat);

	//..................................

	//Texture

	osg::ref_ptr<osg::Texture2D> tex = new osg::Texture2D(osgDB::readImageFile(Texture));

	tex->setFilter(osg::Texture2D::MIN_FILTER, osg::Texture2D::LINEAR_MIPMAP_LINEAR);
	tex->setFilter(osg::Texture2D::MAG_FILTER, osg::Texture2D::LINEAR);
	tex->setWrap(osg::Texture::WRAP_S, osg::Texture::REPEAT);
	tex->setWrap(osg::Texture::WRAP_T, osg::Texture::REPEAT);

	osg::Matrixd matrix;
	matrix.makeScale(osg::Vec3(10, 10, 1.0));
	osg::ref_ptr<osg::TexMat> matTexture = new osg::TexMat;
	matTexture->setMatrix(matrix);

	geode->getOrCreateStateSet()->setTextureAttributeAndModes(0, 
								matTexture.get(), osg::StateAttribute::ON);

	geode->getOrCreateStateSet()->setTextureAttributeAndModes(0, tex);

	//..................................


	geode->addDrawable(terrain_drawable);

	return geode;
}


bool intersectionTerrain( float x, float y, osg::ref_ptr<osg::Node> terrain, osg::Vec3& position, osg::Vec3& normale){
	
	osg::ref_ptr<osgUtil::LineSegmentIntersector> intersector =
		new osgUtil::LineSegmentIntersector(osg::Vec3(x,y,1000), osg::Vec3(x, y,-1000));

	osgUtil::IntersectionVisitor iv(intersector.get());
	terrain->accept(iv);

	if (intersector->containsIntersections()){

		osgUtil::LineSegmentIntersector::Intersections& intersections = intersector->getIntersections();

		// Le segment étant vertical, on prend la première (et à priori unique) intersection trouvée
		const osgUtil::LineSegmentIntersector::Intersection& intersection = *(intersections.begin());
		position = intersection.getWorldIntersectPoint();
		normale = intersection.getWorldIntersectNormal();

		return true;
	}
	return false;
}

osg::ref_ptr<osg::Group> creationForet(osg::ref_ptr<osg::Node> terrain, int nb_arbres){
	
	osg::ref_ptr<osg::Group> foret = new osg::Group;

	//creation du quad d'un arbre

	osg::ref_ptr<osg::Texture2D>   texture = new osg::Texture2D;
	texture->setImage(osgDB::readImageFile("arbre.tga"));

	osg::ref_ptr<osg::Geometry> arbre;

	arbre = osg::createTexturedQuadGeometry(osg::Vec3(0.0, 0.0, 0.0),
												osg::Vec3(100.0, 0.0, 0.0),
												osg::Vec3(0.0, 0.0, 100.0),
												0.0, 0.0, 1.0, 1.0);

	arbre->getOrCreateStateSet()->setTextureAttributeAndModes(0, texture.get());
	arbre->getOrCreateStateSet()->setMode(GL_BLEND, osg::StateAttribute::ON);
	// On ajoute le quad dans le TRANSPARENT BIN, une collection d'objets transparents,
	// pour qu'ils soient triés selon la profondeur et affichés du plus éloigné au plus proche
	arbre->getOrCreateStateSet()->setRenderingHint(osg::StateSet::TRANSPARENT_BIN);

	//...........................

	srand(time(NULL));

	osg::ref_ptr<osg::Billboard> billboard;// = new osg::Billboard;
	//billboard->setMode(osg::Billboard::POINT_ROT_EYE);
	//billboard->addDrawable(arbre);
	//foret->addChild(billboard);
	osg::ref_ptr<osg::PositionAttitudeTransform> pat;
	for(int i=0; i<nb_arbres; ++i){

		osg::Vec3 pos;
		osg::Vec3 norm;

		float pos_arbreX;
		float pos_arbreY;
		float height_arbre;
		float width_arbre;

		do{
			pos_arbreX = float(rand()%1000000);
			pos_arbreY = float(rand()%1000000);
		}
		while(intersectionTerrain(pos_arbreX, pos_arbreY, terrain, pos, norm));

		//height_arbre = float(((rand()%160)+50))/10;
		//width_arbre = height_arbre;


		billboard = new osg::Billboard;
		pat = new osg::PositionAttitudeTransform;
		//billboard->setNormal(norm);
		//billboard->setPosition(0, pos);
		billboard->setMode(osg::Billboard::POINT_ROT_EYE);
		billboard->addDrawable(arbre);
		pat->setPosition(pos);
		pat->addChild(billboard);
		foret->addChild(pat);
	}



	return foret;
}