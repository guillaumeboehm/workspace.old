//main.cpp file
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <SFML/System.hpp>
#include "level.h"

/*********constantes**********/
const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;
const int SPRITES_COUNT = 2;
/*****************************/

sf::Sprite* sprite_array;


void load(){
    sprite_array = new sf::Sprite[SPRITES_COUNT];

    /*sprite test*/
    sprite_array[0].setColor(sf::Color::Green);

    /*sprite test 2*/
    sprite_array[1].setColor(sf::Color::White);
}

void unload(){
    delete sprite_array;
}

int main()
{
    //window settings
    sf::RenderWindow window(sf::VideoMode(SCREEN_WIDTH, SCREEN_HEIGHT), "Game", sf::Style::Titlebar|sf::Style::Close);
    window.setFramerateLimit(60);
    window.setMouseCursorVisible(false);
    sf::VideoMode Desktop_mode = sf::VideoMode::getDesktopMode();
    window.setPosition(sf::Vector2<int>((Desktop_mode.width - SCREEN_WIDTH)/2, (Desktop_mode.height - SCREEN_HEIGHT)/2));
    //*****************

    load();

    Level lvl;
    std::ifstream f("sample/sample.decorGround");
    lvl.ReadDecorGround(f);
    f.close();

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if ((event.type == sf::Event::Closed)
            or ((event.type == sf::Event::KeyPressed) && (event.key.code == sf::Keyboard::Escape)))
                window.close();
        }

        window.clear(sf::Color::Blue);
        /*content display*/
        lvl.drawLvl(window, sprite_array);
        /*****************/
        window.display();
    }

    unload();

    return 0;
}