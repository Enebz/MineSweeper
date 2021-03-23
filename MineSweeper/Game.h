#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>
#include "Tile.h"
#include "Bombfield.h"


class Game {
public:
    sf::RenderWindow window;

    sf::Texture tile_textures;

    sf::Font font;

    bool alive = true;

    const int header_size = 64;
    const int tile_size = 32;
    const int width;
    const int height;
    const int bombs;

    int remaining;

    Bombfield tiles;

    Game(int width, int height, int bombs)
        : width(width), height(height), bombs(bombs)
    {
        // Create window
        window.create(sf::VideoMode(tile_size * width, tile_size * height + header_size), "Minesweeper!", sf::Style::Close);

        // Load textures
        if (!tile_textures.loadFromFile("D:\\tiles.png"))
        {
            std::cerr << "failed to load image" << std::endl;
            exit(1);
        }

        // Load fonts
        if (!font.loadFromFile("D:\\poppins.ttf"))
        {
            std::cerr << "failed to load font" << std::endl;
            exit(1);
        }
    }

    void run() {
        init();
        while (window.isOpen()) {
            update();
            render();
        }
    }

    Tile getTile(int x, int y) {
        try
        {
            return tiles.at(y * width + x);
        }
        catch (const std::out_of_range&)
        {
            return 11;
        }

    }

    void setTile(int x, int y, Tile tile) {
        tiles.at(y * width + x) = tile;
    }



    void unfold(int x, int y, bool chain) {

        Tile tile = getTile(x, y);
        tile.check();

        // Chaining
        if (chain) {
            if (tile.getType() == 0) {
                for (int i = std::max(x - 1, 0); i <= std::min(width - 1, x + 1); i++) {
                    for (int j = std::max(y - 1, 0); j <= std::min(height - 1, y + 1); j++) {
                        unfold(i, j, true);
                    }
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
                int tileVal = getDisplayTile(x, y).type;
                int displayVal = getDisplayTile(x, y).type;
                if (displayVal == 12 && tileVal != 10) { r++; }
            }
        }
        return r;
    }

    void revealBombs() {
        for (int y = 0; y < height; y++)
        {
            for (int x = 0; x < width; x++)
            {
                if (getTile(x, y).isBomb()) {
                    setDisplayTile(x, y, 10);
                }
            }
        }
    }

    

    void init()
    {

        // Respawn
        alive = true;

        // New random
        std::srand(std::time(NULL));

        // New map
        tiles.generate();

        

        // Variables
        remaining = getRemainingTiles();
    }

    void update() {
        sf::Event event;
        while (window.pollEvent(event))
        {
            switch (event.type)
            {
            case sf::Event::Closed:
                window.close();
                break;

            case sf::Event::MouseButtonPressed:

                // If clicked header
                if (event.mouseButton.y <= header_size) {
                    init();
                    return;
                }

                else {

                    if (!alive) { break; }

                    int tileX = std::floor(event.mouseButton.x / tile_size);
                    int tileY = std::floor((event.mouseButton.y - header_size) / tile_size);

                    // Left click tile
                    if (event.mouseButton.button == sf::Mouse::Left)
                    {
                        if (!isCheckable(tileX, tileY)) { break; }
                        if (isBomb(tileX, tileY)) {
                            revealBombs();
                            alive = false;
                            return;
                        }

                        unfold(tileX, tileY, true);
                    }

                    // Right click tile
                    else if (event.mouseButton.button == sf::Mouse::Right)
                    {
                        if (isChecked(tileX, tileY)) { break; }

                        toggleFlag(tileX, tileY);
                    }
                }
            }
        }

        // Refresh remainging tiles
        remaining = getRemainingTiles();

        if (remaining == 0)
        {
            alive = false;
        }
    }

    void render() {
        window.clear(sf::Color(100, 100, 100));

        // Render header
        sf::RectangleShape header;
        header.setSize(sf::Vector2f(width * tile_size, header_size));
        header.setFillColor(sf::Color(150, 150, 75));
        window.draw(header);



        // Render tiles
        for (int y = 0; y < height; y++)
        {
            for (int x = 0; x < width; x++)
            {
                int display_tile_val = getDisplayTile(x, y);

                sf::RectangleShape display_tile;
                display_tile.setSize(sf::Vector2f(tile_size, tile_size));
                display_tile.setPosition(sf::Vector2f(x * tile_size, y * tile_size + header_size));
                display_tile.setTexture(&tile_textures);
                if (tile_texture_boundaries.count(display_tile_val)) {
                    display_tile.setTextureRect(tile_texture_boundaries.at(display_tile_val));
                }
                else {
                    display_tile.setTextureRect(tile_texture_boundaries.at(11));
                }

                window.draw(display_tile);
            }
        }

        window.display();
    }

private:
    std::map<int, sf::IntRect> tile_texture_boundaries = {
        {1, sf::IntRect(0, 0, 16, 16)},
        {2, sf::IntRect(16, 0, 16, 16)},
        {3, sf::IntRect(0, 16, 16, 16)},
        {4, sf::IntRect(16, 16, 16, 16)},
        {5, sf::IntRect(0, 32, 16, 16)},
        {6, sf::IntRect(16, 32, 16, 16)},
        {7, sf::IntRect(0, 48, 16, 16)},
        {8, sf::IntRect(16, 48, 16, 16)},
        {0, sf::IntRect(32, 16, 16, 16)}, // Open
        {10, sf::IntRect(32, 0, 16, 16)}, // Bomb
        {11, sf::IntRect(48, 0, 16, 16)}, // No texture
        {12, sf::IntRect(32, 32, 16, 16)}, // Unchecked
        {13, sf::IntRect(32, 48, 16, 16)}, // Flag
    };
};