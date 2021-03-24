#pragma once


class Bombfield {

private:

    int height = 10;
    int width = 10;
    int bombs = 10;
    sf::Texture textures;

	std::vector<Tile> tiles;

    Tile _getTile(sf::Vector2i position) {
        return tiles.at(position.y * width + position.x);
    }

    void _setTile(sf::Vector2i position, Tile tile) {
        tiles.at(position.y * width + position.x) = tile;
    }

public:
    Bombfield() {

    }

	void create(int height, int width, int bombs, sf::Texture textures) {
        this->height = height;
        this->width = width;
        this->bombs = bombs;
        this->textures = textures;
	}

	void generate() {
        // Reset tiles
        tiles.clear();
        tiles.resize(height * width);

        // Place bombs
        for (int i = 0; i < bombs; i++)
        {
            int randHeight = std::rand() % (height);
            int randWidth = std::rand() % (width);

            insertTile(Tile(10, sf::Vector2i(randWidth, randHeight)));
        }

        // Assign tiles
        for (int y = 0; y < height; y++)
        {
            for (int x = 0; x < width; x++)
            {
                Tile tile = getTile(sf::Vector2i(x, y));

                if (tile.isBomb()) {
                    continue;
                }

                int ab = getAdjacentBombs(tile);
                insertTile(Tile(ab, sf::Vector2i(x, y)));
            }
        }
	}

    int getAdjacentBombs(Tile tile) {
        int bombs = 0;

        for (int i = std::max(tile.position.x - 1, 0); i <= std::min(width - 1, tile.position.x + 1); i++)
        {
            for (int j = std::max(tile.position.y - 1, 0); j <= std::min(height - 1, tile.position.y + 1); j++)
            {
                if (getTile(sf::Vector2i(i, j)).isBomb()) { bombs++; }
            }
        }
        return bombs;
    }

    void unfold(Tile tile, bool chain) {
        tile.show();

        // Chaining
        if (chain) {
            if (tile.getType() == 0) {
                for (int i = std::max(tile.position.x - 1, 0); i <= std::min(width - 1, tile.position.x + 1); i++) {
                    for (int j = std::max(tile.position.y - 1, 0); j <= std::min(height - 1, tile.position.y + 1); j++) {
                        unfold(getTile(sf::Vector2i(i, j)), true);
                    }
                }
            }
        }
    }

    void revealBombs() {
        for (int y = 0; y < height; y++)
        {
            for (int x = 0; x < width; x++)
            {
                Tile tile = getTile(sf::Vector2i(x, y));
                if (tile.isBomb()) {
                    tile.show();
                }
            }
        }
    }

    int getRemainingTiles() {
        int r = 0;
        for (int y = 0; y < height; y++)
        {
            for (int x = 0; x < width; x++)
            {
                Tile tile = getTile(sf::Vector2i(x, y));
                if (!tile.isShown() && !tile.isBomb()) { r++; }
            }
        }
        return r;
    }

    sf::Vector2i getSize() {
        return sf::Vector2i(width, height);
    }

    Tile getTile(sf::Vector2i position) {
        return _getTile(position);
    }

    void insertTile(Tile tile) {
        _setTile(tile.position, tile);
    }

    void render(sf::RenderWindow& window, sf::Vector2i position, int tile_size) {
        // Render tiles
        for (int y = 0; y < height; y++)
        {
            for (int x = 0; x < width; x++)
            {
                Tile tile = getTile(sf::Vector2i(x, y));
                tile.render(window, sf::Vector2f(tile_size, tile_size), sf::Vector2f(x * tile_size + position.x, y * tile_size + position.y), textures);
            }
        }
    }
};