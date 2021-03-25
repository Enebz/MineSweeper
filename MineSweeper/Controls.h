#pragma once

class Controls {

private:

	Minesweeper &minesweeper;
	sf::FloatRect boundaries;
	sf::RectangleShape display;

public:

	Controls(Minesweeper &minesweeper_, sf::FloatRect boundaries) 
		: minesweeper(minesweeper_)
	{
		this->boundaries = boundaries;
	}

	void onClick(sf::Event::MouseButtonEvent mouseButton) {
		if (!(mouseButton.x > boundaries.left&& mouseButton.x < boundaries.left + boundaries.width) || !(mouseButton.y > boundaries.top&& mouseButton.y < boundaries.top + boundaries.height)) { return; }
	
		minesweeper.newGame();
	
	}

	void render(sf::RenderWindow& window) {
		display.setSize(sf::Vector2f(boundaries.width, boundaries.height));
		display.setPosition(sf::Vector2f(boundaries.left, boundaries.top));

		if (minesweeper.isAlive()) {
			display.setFillColor(sf::Color(200, 200, 100));
		}

		else if (minesweeper.hasWon()) {
			display.setFillColor(sf::Color(100, 200, 100));
		}

		else {
			display.setFillColor(sf::Color(200, 100, 100));
		}

		window.draw(display);
	}
};