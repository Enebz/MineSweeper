#include <SFML/Graphics.hpp>
#include <iostream>
#include "Game.h"

int main()
{
    std::srand(std::time(NULL));

    Game game;
    game.run();
}