#pragma once


class Bombfield {

private:

    int height;
    int width;
    int bombs;

	std::vector<Tile> tiles;

    Tile _getTile(int x, int y) {
        try
        {
            return tiles.at(y * width + x);
        }
        catch (const std::out_of_range&)
        {
            return Tile(11);
        }
    }

    void _setTile(int x, int y, Tile tile) {
        tiles.at(y * width + x) = tile;
    }

public:
	Bombfield() {

	}

	Bombfield(int height, int width, int bombs) {
		
	}

	void generate() {
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
                if (getTile(x, y).isBomb()) {
                    continue;
                }

                int ab = getAdjacentBombs(x, y);
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
                if (getTile(i, j).isBomb()) { bombs++; }
            }
        }
        return bombs;
    }

    Tile getTile(int x, int y) {
        return _getTile(x, y);
    }

    void insertTile(Tile tile) {
        _setTile(tile.position.x, tile.position.y, tile);
    }
};