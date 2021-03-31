#include "Button.h"


Button::Button(sf::FloatRect box) {
	this->box = box;
}

sf::FloatRect& Button::getBox() {
	return box;
}

sf::RectangleShape& Button::getDisplay() {
	return display;
}

void Button::setLabel(sf::String label) {
	this->label = label;
}

bool Button::isClicked() {
	return (isMouseOver()) && (sf::Mouse::isButtonPressed(sf::Mouse::Left));
}

bool Button::isMouseOver() {
	sf::Vector2i mousePos = sf::Mouse::getPosition();
	return isPointInside((sf::Vector2f)mousePos);
}

bool Button::isPointInside(sf::Vector2f point) {
	return (point.x > box.left && point.x < box.left + box.width) && (point.y > box.top && point.y < box.top + box.height);
}

void Button::render(sf::RenderWindow& window) {
	display.setSize(sf::Vector2f(box.width, box.height));
	display.setPosition(sf::Vector2f(box.left, box.top));
	window.draw(display);
}