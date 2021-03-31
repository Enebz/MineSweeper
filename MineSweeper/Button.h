#ifndef BUTTON_H
#define BUTTON_H

#include <SFML/Graphics.hpp>

class Button {
private:
	sf::FloatRect box;
	sf::String label;
	sf::RectangleShape display;
	
public:
	Button(sf::FloatRect box);

	sf::FloatRect& getBox();

	sf::RectangleShape& getDisplay();

	void setLabel(sf::String label);

	bool isClicked();

	bool isMouseOver();

	bool isPointInside(sf::Vector2f point);

	void render(sf::RenderWindow& window);
};

#endif