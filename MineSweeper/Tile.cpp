#include "Tile.h"

Tile::Tile(void) {}

Tile::Tile(int type, sf::Vector2i index) {
	this->type = type;
	this->index = index;
}

void Tile::setType(int type) {
	this->type = type;
}

int Tile::getType() {
	return this->type;
}

void Tile::toggleFlag() {
	this->flagged = !this->flagged;
}

bool Tile::isFlagged() {
	return this->flagged;
}

bool Tile::isUnset() {
	return type == 11;
}

bool Tile::isEmpty() {
	return type == 0;
}

bool Tile::isError() {
	return type == 11;
}

bool Tile::isNumber() {
	return type > 0 && type < 9;
}

bool Tile::isBomb() {
	return type == 10;
}

bool Tile::isShowable() {
	return !shown && !flagged;
}

bool Tile::isShown() {
	return shown;
}

void Tile::show() {
	flagged = false;
	shown = true;
}

void Tile::render(sf::RenderWindow& window, float size, sf::Vector2f position, sf::Texture& textures) {
	display.setSize(sf::Vector2f(size, size));
	display.setPosition(position);
	display.setTexture(&textures);

	if (shown) {
		display.setTextureRect(tile_texture_boundaries.at(type));
	}
	else if (flagged) {
		display.setTextureRect(tile_texture_boundaries.at(13));
	}
	else {
		display.setTextureRect(tile_texture_boundaries.at(12));
	}
	window.draw(display);
}