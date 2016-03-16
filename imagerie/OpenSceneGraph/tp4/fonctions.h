#ifndef FONCTIONS_HPP
#define FONCTIONS_HPP

#include <stdlib.h>
#include <time.h>
#include <iostream>
#include <sstream>
#include <string>
#include <osgViewer/Viewer>
#include <osg/Image>
#include <osg/ShapeDrawable>
#include <osgDB/ReadFile>
#include <osg/Material>
#include <osg/Texture2D>
#include <osg/TexMat>
#include <osgUtil/LineSegmentIntersector>
#include <osgUtil/IntersectionVisitor>
#include <osg/PositionAttitudeTransform>

osg::ref_ptr<osg::Node> creationTerrain(std::string HeightImage, std::string Texture);

bool intersection_terrain( float x, float y,
							osg::ref_ptr<osg::Node> terrain,
							osg::Vec3& position,
							osg::Vec3& normale);

osg::ref_ptr<osg::Group> creationForet(osg::ref_ptr<osg::Node> terrain, int nb_arbres);


#endif