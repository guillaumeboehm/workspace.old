//level.cpp file
#include "level.h"

/*fonction de lecture des char pour le sol du niveau*/
void Level::ReadDecorGround(std::istream& f){
	if(!f)
		throw std::runtime_error("fail to open source file");
	for(unsigned int i=0; i<LVL_WIDTH*LVL_HEIGHT; ++i){
		f>>raw_decor_ground[i];
		std::cout<<raw_decor_ground[i];
	}
	//f.read((char *)raw_decor_ground, LVL_WIDTH*LVL_HEIGHT);
}

/*fonction de dessin du niveau dans la fenetre*/
void Level::drawLvl(sf::RenderWindow& w, sf::Sprite* sprite_array){

	for(unsigned int i=0; i<LVL_WIDTH*LVL_HEIGHT; ++i){

		sprite_array[raw_decor_ground[i]].setPosition(sf::Vector2f(0+12*(i%LVL_WIDTH),0+(12*(int)(i/LVL_WIDTH))));
		//std::cout<<raw_decor_ground[i]+"\n";
		//std::cout<<"lol\n";
		w.draw(sprite_array[raw_decor_ground[i]]);
	}
}