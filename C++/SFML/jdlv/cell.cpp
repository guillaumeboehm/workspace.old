//file cell.cpp

#include "cell.h"

Cell::Cell()
	:RectangleShape(sf::Vector2f(CELL_SIZE, CELL_SIZE)), state(0), elapsed_time(0)
{
	setOutlineThickness(0.1);
	setOutlineColor(sf::Color(sf::Color::Black));

	if(state == 0)
		setFillColor(sf::Color(sf::Color::Green));
	if(state == 1)
		setFillColor(sf::Color(sf::Color::Red));
}

void Cell::increase(){
	elapsed_time++;
	//change state conditions
}
