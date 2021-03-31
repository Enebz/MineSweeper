#ifndef GAME_H
#define GAME_H

#include <SFML/Graphics.hpp>
#include <iostream>
#include "Minesweeper.h"
#include "Controls.h"


class Game {

private:
    sf::RenderWindow window;
    sf::Vector2u windowSize;

    sf::Texture textures;

    Minesweeper minesweeper = Minesweeper(9, 9, 10, 32.0, textures, sf::Vector2f(0, 64));
    Controls controls = Controls(minesweeper, textures, sf::Vector2f(0, 0));

public:
   
    Game();

    void run();

    void init();

    void update();

    void render();
};

#endif

