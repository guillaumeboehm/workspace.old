#ifndef GRID_H
#define GRID_H

#include "cell.h"
#include <memory>

typedef std::auto_ptr<Cell> PCell;

class Grid{
private:
	PCell tab;
	unsigned int width;
	unsigned int length;

public:
	Grid(sf::RenderWindow);
	inline ~Grid(){}
	void increase();
	void display(sf::RenderWindow);

};

#endif //GRID_H
