#pragma once
#include <SFML/Graphics.hpp>

class Tile {

private:
	int type;
	bool shown = false;
	bool flagged = false;
	bool error = false;

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

public:

	sf::Vector2i position;

	Tile() {

	}

	Tile(int type, sf::Vector2i position) {
		this->type = type;
		this->position = position;
	}

	void setType(int type) {
		this->type = type;
	}

	int getType() {
		return this->type;
	}

	void toggleFlag() {
		this->flagged = !this->flagged;
	}

	bool isFlagged() {
		return this->flagged;
	}

	bool isEmpty() {
		return type == 0;
	}

	bool isError() {
		return type == 11;
	}

	bool isNumber() {
		return type > 0 && type < 9;
	}

	bool isBomb() {
		return type == 10;
	}

	bool isShowable() {
		return !shown && !flagged;
	}

	bool isShown() {
		return shown;
	}

	void show() {
		flagged = false;
		shown = true;
	}

	void render(sf::RenderWindow& window, sf::Vector2f size, sf::Vector2f position, sf::Texture textures) {
		sf::RectangleShape display_tile;
		display_tile.setSize(size);
		display_tile.setPosition(position);
		display_tile.setTexture(&textures);
		
		if (shown) {
			display_tile.setTextureRect(tile_texture_boundaries.at(type));
		}

		else if (flagged) {
			display_tile.setTextureRect(tile_texture_boundaries.at(13));
		}

		else {
			display_tile.setTextureRect(tile_texture_boundaries.at(12));
		}

		
		
		
		window.draw(display_tile);
	}



};