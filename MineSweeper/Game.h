#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>
#include "Tile.h"
#include "Bombfield.h"


class Game {
public:
    sf::RenderWindow window;

    int header_size = 64;

    Bombfield tiles;
    sf::Texture textures;
    bool alive = true;
    int remaining;

    Game(int width, int height, int bombs)
    {
        // Create window
        window.create(sf::VideoMode(32 * width, 32 * height + header_size), "Minesweeper!", sf::Style::Close);

        // Load textures
        if (!textures.loadFromFile("C:\\tiles.png"))
        {
            std::cerr << "failed to load image" << std::endl;
            exit(1);
        }

        tiles.create(width, height, bombs, textures);
    }

    void run() {
        init();
        while (window.isOpen()) {
            update();
            render();
        }
    }    

    void init()
    {
        // Respawn
        alive = true;

        // New map
        tiles.generate();
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

                    int tileX = std::floor(event.mouseButton.x / 32);
                    int tileY = std::floor((event.mouseButton.y - header_size) / 32);

                    Tile tile = tiles.getTile(sf::Vector2i(tileX, tileY));

                    // Left click tile
                    if (event.mouseButton.button == sf::Mouse::Left)
                    {
                        if (!tile.isShowable()) { break; }
                        if (tile.isBomb()) {
                            tiles.revealBombs();
                            alive = false;
                            return;
                        }

                        tiles.unfold(tile, true);
                    }

                    // Right click tile
                    else if (event.mouseButton.button == sf::Mouse::Right)
                    {
                        if (tile.isShown()) { break; }
                        tile.toggleFlag();
                    }
                }
            }
        }

        // Refresh remainging tiles
        remaining = tiles.getRemainingTiles();

        if (remaining == 0)
        {
            alive = false;
        }
    }

    void render() {
        window.clear(sf::Color(100, 100, 100));

        // Render header
        sf::RectangleShape header;
        header.setSize(sf::Vector2f(tiles.getSize().x * 32, header_size));
        header.setFillColor(sf::Color(150, 150, 75));
        window.draw(header);

        tiles.render(window, sf::Vector2i(0, header_size), 32);

        window.display();
    }
};