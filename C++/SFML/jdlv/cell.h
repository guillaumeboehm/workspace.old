#ifndef CELL_H
#define CELL_H

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <SFML/System.hpp>
#include <fstream>
#include <iostream>
#include <stdexcept>

#define CELL_SIZE 4 //taille du carré de la cellule

enum State {dead=0, alive}

class Cell : public sf::RectangleShape{
private:
	State state;
	int elapsed_time;


public:
	Cell();
	inline ~Cell(){}
	void increase();


}



#endif //CELL_H