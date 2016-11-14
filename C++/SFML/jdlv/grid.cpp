//file grid.cpp

#include "grid.h"

Grid::Grid(sf::RenderWindow w){
	width = w.getSize().x/CELL_SIZE;
	length = w.getSize().y/CELL_SIZE;

	tab = new Cell[width*length];
	for(unsigned int i = 0; i<width*length; ++i){
		tab[i].setPosition(i%width, i/width);
	}
}

void Grid::increase(){
	for(unsigned int i = 0; i<width*length; ++i){
		tab[i].increase();
	}
}

void Grid::display(sf::RenderWindow w){
	for(unsigned int i = 0; i<width*length; ++i){
		w.draw(tab[i]);
	}
}