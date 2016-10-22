//file cell.cpp

#include "cell.h"

Cell::Cell()
	:RectangleShape(Vector2f(CELL_SIZE, CELL_SIZE)), state(0), elapsed_time(0)
{
	setOutlineThickness(0.1);
	setOutlineColor(sf::Color(sf::Black));

	if(state == 0)
		setFillColor(sf::Color(sf::Green));
	if(state == 1)
		setFillColor(sf::Color(sf::Red));
}

void Cell::increase(){
	elapsed_time++;
	//change state conditions
}