#include "Game.h"

Game::Game()
{
    // Create window
    windowSize = sf::Vector2u((unsigned int)minesweeper.getBox().width, (unsigned int)(minesweeper.getBox().height + controls.getBox().height));
    window.create(sf::VideoMode(windowSize.x, windowSize.y), "Minesweeper!", sf::Style::Default);

    // Load textures
    if (!textures.loadFromFile("textures.png"))
    {
        std::cerr << "failed to load textures.png" << std::endl;
        exit(EXIT_FAILURE);
    }
}

void Game::run() {
    init();
    while (window.isOpen()) {
        update();
        render();
    }
}

void Game::init()
{
    minesweeper.newGame();
}

void Game::update() {
    // Window poll events
    sf::Event event;
    while (window.pollEvent(event))
    {
        controls.pollEvents(event);
        minesweeper.pollEvents(event);
        switch (event.type)
        {
        case sf::Event::Closed:
            window.close();
            break;

        case sf::Event::Resized:
            sf::FloatRect visibleArea(0, 0, (float)event.size.width, (float)event.size.height);
            window.setView(sf::View(visibleArea));
            break;
        }

    }

    // Update components
    minesweeper.update();

    windowSize = sf::Vector2u((unsigned int)(minesweeper.getBox().width), (unsigned int)(minesweeper.getBox().height + controls.getBox().height));
    window.setSize(windowSize);
}

void Game::render() {
    window.clear(sf::Color(100, 100, 100));

    // Render components
    controls.render(window);
    minesweeper.render(window);

    window.display();
}
