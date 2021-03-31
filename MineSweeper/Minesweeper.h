#ifndef MINESWEEPER_H
#define MINESWEEPER_H

#include <SFML/Graphics.hpp>
#include "Tile.h"

class Minesweeper {

private:

    int width;
    int height;
    int bombs;
    float tileSize;

    int remainingTiles;
    bool alive;
    bool won;

    sf::FloatRect box;
    sf::Texture& textures;
	std::vector<Tile> tiles;

public:

    Minesweeper(int width, int height, int bombs, float tileSize, sf::Texture& textures, sf::Vector2f position);

    Tile& getTile(sf::Vector2i index);

    void insertTile(Tile tile);

    sf::Vector2i getBoardSize();

    sf::FloatRect& getBox();

    bool isAlive();

    bool hasWon();

    int getRemainingTiles();

    void newGame();

    void newGame(int width, int height, int bombs);

    int getAdjacentBombsCount(Tile& tile);

    int getAdjacentFlagsCount(Tile& tile);

    void revealAdjacent(Tile& tile);

    void unfold(Tile& tile);

    void revealBombs();

    int calculateRemainingTiles();

    void pollEvents(sf::Event event);

    void update();

    void render(sf::RenderWindow& window);
};

#endif