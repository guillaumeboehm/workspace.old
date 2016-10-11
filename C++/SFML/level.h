#ifndef LEVEL_H
#define LEVEL_H

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <SFML/System.hpp>
#include <fstream>
#include <iostream>
#include <stdexcept>

/******zone du niveau******/
const int LVL_WIDTH = 10;
const int LVL_HEIGHT = 10;
/**************************/

typedef unsigned char ubyte;

class Level{
public:
	inline Level(){ raw_decor_ground = new ubyte[LVL_WIDTH*LVL_HEIGHT];
					raw_decor = new ubyte[LVL_WIDTH*LVL_HEIGHT];
					}
	inline ~Level(){ delete raw_decor_ground;
					 delete raw_decor;
					}
	void ReadDecorGround(std::istream&); //lit le fichier du sol du niveau
	//void ReadDecor(std::istream&); //lit le fichier du reste du decor du niveau
	void LoadDecor(); //charge les sprites en fonction des données du niveau
	void drawLvl(sf::RenderWindow&, sf::Sprite*); //dessine le niveau sur la fenetre
private:
	ubyte* raw_decor_ground; //sol du niveau en char
	ubyte* raw_decor; //reste du decor du niveai en char
	/*
	ubyte* raw_utilities; //utilitaires du decor en char
	ubyte* raw_mob; //mobs du niveau en char*/
	sf::Sprite* decor_ground; //sol du niveau a dessiner
	/*Sprite* decor; //reste du decor du niveau a dessiner
	Utilities *utilities; //utilitaires du decor du niveau a dessiner
	Mob *mob; //mobs a dessiner
	*/


};

#endif //LEVEL_H