#pragma once

#include "Tile.h"

class Minesweeper {

private:

    int width = 10;
    int height = 10;
    int bombs = 10;
    int tileSize = 64;

    int remainingTiles;
    bool alive;
    bool won;

    sf::FloatRect boundaries;

    sf::Texture &textures;


	std::vector<Tile> tiles;

public:

    Minesweeper(int tileSize, sf::Texture &textures_, sf::FloatRect boundaries)
        : textures(textures_)
    {
        this->tileSize = tileSize;
        this->boundaries = boundaries;
	}


    // Access methods
    Tile& getTile(sf::Vector2i index) {
        return tiles.at(index.y * width + index.x);
    }

    void insertTile(Tile tile) {
        tiles.at(tile.index.y * width + tile.index.x) = tile;
    }

    sf::Vector2i getSize() {
        return sf::Vector2i(width, height);
    }

    sf::FloatRect getBoundaries() {
        return boundaries;
    }

    bool isAlive() {
        return alive;
    }

    bool hasWon() {
        return won;
    }

    int getRemainingTiles() {
        return remainingTiles;
    }

    // Game functions
    void newGame() {
        newGame(width, height, bombs);
    }

	void newGame(int width, int height, int bombs) {
        this->width = width;
        this->height = height;
        this->bombs = bombs;

        // Set game states
        alive = true;
        won = false;

        // Reset tiles
        tiles.clear();
        tiles.resize(height * width);

        // Insert unset tiles
        for (int y = 0; y < height; y++)
        {
            for (int x = 0; x < width; x++)
            {
                insertTile(Tile(11, sf::Vector2i(x, y)));
            }
        }

        // Place bombs
        for (int i = 0; i < bombs; i++)
        {
            int randWidth = std::rand() % (width);
            int randHeight = std::rand() % (height);
            insertTile(Tile(10, sf::Vector2i(randWidth, randHeight)));
        }

        // Set tiles
        for (int y = 0; y < height; y++)
        {
            for (int x = 0; x < width; x++)
            {
                Tile &tile = getTile(sf::Vector2i(x, y));

                if (tile.isUnset()) {
                    int ab = getAdjacentBombsCount(tile);
                    insertTile(Tile(ab, sf::Vector2i(x, y)));
                }
            }
        }

        // Set tiles counter
        remainingTiles = calculateRemainingTiles();
	}

    int getAdjacentBombsCount(Tile &tile) {
        int bombs = 0;

        for (int i = std::max(tile.index.x - 1, 0); i <= std::min(width - 1, tile.index.x + 1); i++)
        {
            for (int j = std::max(tile.index.y - 1, 0); j <= std::min(height - 1, tile.index.y + 1); j++)
            {
                if (getTile(sf::Vector2i(i, j)).isBomb()) {
                    bombs++; 
                }
            }
        }
        return bombs;
    }

    int getAdjacentFlagsCount(Tile& tile) {
        int flags = 0;

        for (int i = std::max(tile.index.x - 1, 0); i <= std::min(width - 1, tile.index.x + 1); i++)
        {
            for (int j = std::max(tile.index.y - 1, 0); j <= std::min(height - 1, tile.index.y + 1); j++)
            {
                if (getTile(sf::Vector2i(i, j)).isFlagged()) {
                    flags++;
                }
            }
        }
        return flags;
    }

    int revealAdjacent(Tile& tile) {
        int flags = 0;

        for (int i = std::max(tile.index.x - 1, 0); i <= std::min(width - 1, tile.index.x + 1); i++)
        {
            for (int j = std::max(tile.index.y - 1, 0); j <= std::min(height - 1, tile.index.y + 1); j++)
            {
                Tile& tile = getTile(sf::Vector2i(i, j));
                unfold(tile);
            }
        }
        return flags;
    }

    void unfold(Tile &tile) {

        if (!tile.isShowable()) {
            return;
        }

        if (tile.isBomb()) {
            revealBombs();
            alive = false;
            return;
        }

        tile.show();
        remainingTiles--;

        // If the tile is blank, reveal its adjacent cells.
        if (tile.getType() == 0) {
            for (int i = std::max(tile.index.x - 1, 0); i <= std::min(width - 1, tile.index.x + 1); i++) {
                for (int j = std::max(tile.index.y - 1, 0); j <= std::min(height - 1, tile.index.y + 1); j++) {
                    unfold(getTile(sf::Vector2i(i, j)));
                }
            }
        }
    }

    void revealBombs() {
        for (int y = 0; y < height; y++)
        {
            for (int x = 0; x < width; x++)
            {
                Tile &tile = getTile(sf::Vector2i(x, y));
                if (tile.isBomb()) {
                    tile.show();
                }
            }
        }
    }

    int calculateRemainingTiles() {
        int r = 0;
        for (int y = 0; y < height; y++)
        {
            for (int x = 0; x < width; x++)
            {
                Tile &tile = getTile(sf::Vector2i(x, y));
                if (!tile.isShown() && !tile.isBomb()) { r++; }
            }
        }
        return r;
    }

    // Event handling
    void onClick(sf::Event::MouseButtonEvent mouseButton) {

        if (!(mouseButton.x > boundaries.left && mouseButton.x < boundaries.left + boundaries.width) || !(mouseButton.y > boundaries.top && mouseButton.y < boundaries.top + boundaries.height)) { return; }

        if (!alive) { return; }

        int tileX = std::floor((mouseButton.x - boundaries.left) / tileSize);
        int tileY = std::floor((mouseButton.y - boundaries.top) / tileSize);

        Tile& tile = getTile(sf::Vector2i(tileX, tileY));

        // Left click bombfield
        if (mouseButton.button == sf::Mouse::Left)
        {
            if (!tile.isShowable()) { return; }
            unfold(tile);
        }

        // Right click bombfield
        else if (mouseButton.button == sf::Mouse::Right)
        {
            if (tile.isShown()) { return; }
            tile.toggleFlag();
        }

        // Middle click bombfield
        else if (mouseButton.button == sf::Mouse::Middle)
        {
            if (tile.getType() == 0) { return; }
            if (tile.getType() != getAdjacentFlagsCount(tile)) { return; }
            revealAdjacent(tile);
        }
    }

    // Update loop (each frame)
    void update() {
        if (remainingTiles == 0) {
            alive = false;
            won = true;
        }
    }

    // Rendering
    void render(sf::RenderWindow& window) {

        for (int y = 0; y < height; y++)
        {
            for (int x = 0; x < width; x++)
            {
                Tile tile = getTile(sf::Vector2i(x, y));
                tile.render(window, tileSize, sf::Vector2i(x * tileSize + boundaries.left, y * tileSize + boundaries.top), textures);
            }
        }
    }
};