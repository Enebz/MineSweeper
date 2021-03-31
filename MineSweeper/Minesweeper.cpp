#include "Minesweeper.h"

Minesweeper::Minesweeper(int width, int height, int bombs, float tileSize, sf::Texture& textures, sf::Vector2f position)
    : textures(textures)
{
    this->width = width;
    this->height = height;
    this->bombs = bombs;
    this->tileSize = tileSize;
    this->box = sf::FloatRect(position.x, position.y, (float)(tileSize * width), (float)(tileSize * height));
    this->alive = false;
    this->remainingTiles = 0;
    this->won = true;
}


Tile& Minesweeper::getTile(sf::Vector2i index) {
    return tiles.at(index.y * width + index.x);
}

void Minesweeper::insertTile(Tile tile) {
    tiles.at(tile.index.y * width + tile.index.x) = tile;
}

sf::Vector2i Minesweeper::getBoardSize() {
    return sf::Vector2i(width, height);
}

sf::FloatRect& Minesweeper::getBox() {
    return box;
}

bool Minesweeper::isAlive() {
    return alive;
}

bool Minesweeper::hasWon() {
    return won;
}

int Minesweeper::getRemainingTiles() {
    return remainingTiles;
}

void Minesweeper::newGame() {
    newGame(width, height, bombs);
}

void Minesweeper::newGame(int width, int height, int bombs) {
    this->width = width;
    this->height = height;
    this->bombs = bombs;
    this->box = sf::FloatRect(box.left, box.top, (float)(tileSize * width), (float)(tileSize * height));

    alive = true;
    won = false;

    tiles.clear();
    tiles.resize(height * width);

    for (int y = 0; y < height; y++) {
        for (int x = 0; x < width; x++) {
            insertTile(Tile(11, sf::Vector2i(x, y)));
        }
    }

    for (int i = 0; i < bombs; i++) {
        int randWidth = std::rand() % (width);
        int randHeight = std::rand() % (height);
        insertTile(Tile(10, sf::Vector2i(randWidth, randHeight)));
    }

    for (int y = 0; y < height; y++) {
        for (int x = 0; x < width; x++) {
            Tile& tile = getTile(sf::Vector2i(x, y));

            if (tile.isUnset()) {
                int ab = getAdjacentBombsCount(tile);
                insertTile(Tile(ab, sf::Vector2i(x, y)));
            }
        }
    }

    remainingTiles = calculateRemainingTiles();
}

int Minesweeper::getAdjacentBombsCount(Tile& tile) {
    int bombs = 0;
    for (int i = std::max(tile.index.x - 1, 0); i <= std::min(width - 1, tile.index.x + 1); i++) {
        for (int j = std::max(tile.index.y - 1, 0); j <= std::min(height - 1, tile.index.y + 1); j++) {
            if (getTile(sf::Vector2i(i, j)).isBomb()) {
                bombs++;
            }
        }
    }
    return bombs;
}

int Minesweeper::getAdjacentFlagsCount(Tile& tile) {
    int flags = 0;
    for (int i = std::max(tile.index.x - 1, 0); i <= std::min(width - 1, tile.index.x + 1); i++) {
        for (int j = std::max(tile.index.y - 1, 0); j <= std::min(height - 1, tile.index.y + 1); j++) {
            if (getTile(sf::Vector2i(i, j)).isFlagged()) {
                flags++;
            }
        }
    }
    return flags;
}

void Minesweeper::revealAdjacent(Tile& tile) {
    for (int i = std::max(tile.index.x - 1, 0); i <= std::min(width - 1, tile.index.x + 1); i++) {
        for (int j = std::max(tile.index.y - 1, 0); j <= std::min(height - 1, tile.index.y + 1); j++) {
            Tile& tile = getTile(sf::Vector2i(i, j));
            unfold(tile);
        }
    }
}

void Minesweeper::unfold(Tile& tile) {

    if (!tile.isShowable()) {
        return;
    } else if (tile.isBomb()) {
        revealBombs();
        alive = false;
        return;
    }

    tile.show();
    remainingTiles--;

    if (tile.getType() == 0) {
        revealAdjacent(tile);
    }
}

void Minesweeper::revealBombs() {
    for (int y = 0; y < height; y++) {
        for (int x = 0; x < width; x++) {
            Tile& tile = getTile(sf::Vector2i(x, y));
            if (tile.isBomb()) {
                tile.show();
            }
        }
    }
}

int Minesweeper::calculateRemainingTiles() {
    int r = 0;
    for (int y = 0; y < height; y++) {
        for (int x = 0; x < width; x++) {
            Tile& tile = getTile(sf::Vector2i(x, y));
            if (!tile.isShown() && !tile.isBomb()) { r++; }
        }
    }
    return r;
}

void Minesweeper::pollEvents(sf::Event event) {
    switch (event.type) {
    case sf::Event::MouseButtonPressed:

        if (!(event.mouseButton.x > box.left && event.mouseButton.x < box.left + box.width) || !(event.mouseButton.y > box.top && event.mouseButton.y < box.top + box.height)) { return; }

        if (!alive) { return; }

        int tileX = (int)std::floor(((float)event.mouseButton.x - box.left) / tileSize);
        int tileY = (int)std::floor(((float)event.mouseButton.y - box.top) / tileSize);

        Tile& tile = getTile(sf::Vector2i(tileX, tileY));

        // Left click bombfield
        if (event.mouseButton.button == sf::Mouse::Left) {
            if (!tile.isShowable()) { return; }
            unfold(tile);
        }

        // Right click bombfield
        else if (event.mouseButton.button == sf::Mouse::Right) {
            if (tile.isShown()) { return; }
            tile.toggleFlag();
        }

        // Middle click bombfield
        else if (event.mouseButton.button == sf::Mouse::Middle) {
            if (tile.getType() == 0) { return; }
            if (!tile.isShown()) { return; }
            if (tile.getType() != getAdjacentFlagsCount(tile)) { return; }
            revealAdjacent(tile);
        }
        break;
    }
}

void Minesweeper::update() {
    if (remainingTiles == 0) {
        alive = false;
        won = true;
    }
}

void Minesweeper::render(sf::RenderWindow& window) {
    for (int y = 0; y < height; y++) {
        for (int x = 0; x < width; x++) {
            Tile tile = getTile(sf::Vector2i(x, y));
            tile.render(window, tileSize, sf::Vector2f(x * tileSize + box.left, y * tileSize + box.top), textures);
        }
    }
}