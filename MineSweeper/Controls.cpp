#include "Controls.h"

Controls::Controls(Minesweeper& minesweeper, sf::Texture& textures, sf::Vector2f position)
	: minesweeper(minesweeper), textures(textures)
{
	this->box = sf::FloatRect(position.x, position.y, minesweeper.getBox().width, 64);
	startButton.getDisplay().setTexture(&textures);
	easy.getDisplay().setFillColor(sf::Color(100, 255, 100));
	normal.getDisplay().setFillColor(sf::Color(200, 255, 100));
	hard.getDisplay().setFillColor(sf::Color(255, 100, 100));
}

sf::FloatRect& Controls::getBox() {
	return box;
}

void Controls::pollEvents(sf::Event event) {

	switch (event.type) {
	case sf::Event::MouseButtonPressed:
		if (!(event.mouseButton.x > box.left && event.mouseButton.x < box.left + box.width) || !(event.mouseButton.y > box.top && event.mouseButton.y < box.top + box.height)) { return; }
		if (!event.mouseButton.button == sf::Mouse::Button::Left) { return; }
		if (startButton.isPointInside(sf::Vector2f((float)event.mouseButton.x, (float)event.mouseButton.y))) {
			minesweeper.newGame();
		}
		if (easy.isPointInside(sf::Vector2f((float)event.mouseButton.x, (float)event.mouseButton.y))) {
			minesweeper.newGame(9, 9, 10);
		}
		if (normal.isPointInside(sf::Vector2f((float)event.mouseButton.x, (float)event.mouseButton.y))) {
			minesweeper.newGame(16, 16, 40);
		}
		if (hard.isPointInside(sf::Vector2f((float)event.mouseButton.x, (float)event.mouseButton.y))) {
			minesweeper.newGame(30, 16, 99);
		}
		break;

	case sf::Event::Resized:
		this->box = sf::FloatRect(box.left, box.top, minesweeper.getBox().width, 64);
		startButton.getBox() = sf::FloatRect(minesweeper.getBox().width / 2 - 16, 16, 32, 32);
	}
}

void Controls::render(sf::RenderWindow& window) {
	display.setSize(sf::Vector2f(box.width, box.height));
	display.setPosition(sf::Vector2f(box.left, box.top));

	if (minesweeper.isAlive()) {
		display.setFillColor(sf::Color(200, 200, 100));
		startButton.getDisplay().setTextureRect(texture_boundaries.at(1));
	}
	else if (minesweeper.hasWon()) {
		display.setFillColor(sf::Color(100, 200, 100));
		startButton.getDisplay().setTextureRect(texture_boundaries.at(2));
	}
	else {
		display.setFillColor(sf::Color(200, 100, 100));
		startButton.getDisplay().setTextureRect(texture_boundaries.at(3));
	}


	window.draw(display);
	startButton.render(window);
	easy.render(window);
	normal.render(window);
	hard.render(window);
}