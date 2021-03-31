#ifndef CONTROLS_H
#define CONTROLS_H

#include <SFML/Graphics.hpp>
#include "Minesweeper.h"
#include "Button.h"

class Controls {

private:

	Minesweeper &minesweeper;
	sf::FloatRect box;
	sf::Texture& textures;
	sf::RectangleShape display;

	Button startButton = Button(sf::FloatRect(minesweeper.getBox().width / 2 - 16, 16, 32, 32));

	Button easy = Button(sf::FloatRect(16, 24, 16, 16));
	Button normal = Button(sf::FloatRect(32, 24, 16, 16));
	Button hard = Button(sf::FloatRect(48, 24, 16, 16));

	std::map<int, sf::IntRect> texture_boundaries = {
		// Buttons
		{1, sf::IntRect(384, 128, 128, 128)}, // Alive
		{2, sf::IntRect(384, 256, 128, 128)}, // Won
		{3, sf::IntRect(384, 384, 128, 128)}, // Dead
	};
	
public:

	Controls(Minesweeper& minesweeper, sf::Texture& textures, sf::Vector2f position);

	sf::FloatRect& getBox();

	void pollEvents(sf::Event event);

	void render(sf::RenderWindow& window);
};

#endif