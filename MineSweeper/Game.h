#pragma once

#include "Controls.h"
#include "Minesweeper.h"
#include <cmath>

class Game {

private:
  int width = 50;
  int height = 25;
  int bombs = std::floor((width * height) / 8);

public:
  sf::RenderWindow window;
  sf::FloatRect visibleArea;

  sf::Texture textures;

  int tileSize = 32;
  int headerSize = 64;

  Minesweeper minesweeper = Minesweeper(
      tileSize, textures,
      sf::FloatRect(0, headerSize, tileSize *width, tileSize *height));
  ;
  Controls controls =
      Controls(minesweeper, sf::FloatRect(0, 0, tileSize *width, headerSize));

  Game() {
    int in_width;
    int in_height;
    int in_bombs;

    std::cout << "Width: ";
    std::cin >> in_width;
    std::cout << std::endl;

    std::cout << "Height: ";
    std::cin >> in_height;
    std::cout << std::endl;

    std::cout << "Bombs: ";
    std::cin >> in_bombs;
    std::cout << std::endl;

    if (bombs > in_width * in_height) {
      bombs = in_width * in_height - 1;
    }

    this->width = in_width;
    this->height = in_height;
    this->bombs = in_bombs;
    // Set visible area
    visibleArea =
        sf::FloatRect(0, 0, tileSize * width, tileSize * height + headerSize);

    // Create window
    window.create(sf::VideoMode(visibleArea.width, visibleArea.height),
                  "Minesweeper!", sf::Style::Close);

    // Load textures
    if (!textures.loadFromFile("tiles.png")) {
      std::cerr << "failed to load image" << std::endl;
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

  void init() { minesweeper.newGame(width, height, bombs); }

  void update() {
    sf::Event event;
    while (window.pollEvent(event)) {
      switch (event.type) {
      case sf::Event::Closed:
        window.close();
        break;

      case sf::Event::Resized:
        visibleArea = sf::FloatRect(0, 0, event.size.width, event.size.height);
        window.setView(sf::View(visibleArea));
        break;

      case sf::Event::MouseButtonPressed:

        // Register events
        minesweeper.onClick(event.mouseButton);
        controls.onClick(event.mouseButton);
      }
    }

    minesweeper.update();
  }

  void render() {
    window.clear(sf::Color(100, 100, 100));
    controls.render(window);
    minesweeper.render(window);
    window.display();
  }
};
