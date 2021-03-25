#pragma once

class Tile {

private:
	int type = 11;
	bool shown = false;
	bool flagged = false;
	bool error = false;

	sf::RectangleShape display_tile;

	std::map<int, sf::IntRect> tile_texture_boundaries = {
		// Types
		{1, sf::IntRect(0, 0, 127, 127)},
		{2, sf::IntRect(128, 0, 127, 127)},
		{3, sf::IntRect(0, 128, 127, 127)},
		{4, sf::IntRect(128, 128, 127, 127)},
		{5, sf::IntRect(0, 256, 127, 127)},
		{6, sf::IntRect(128, 256, 127, 127)},
		{7, sf::IntRect(0, 384, 127, 127)},
		{8, sf::IntRect(128, 384, 127, 127)},
		{0, sf::IntRect(256, 128, 127, 127)}, // Open
		{10, sf::IntRect(256, 0, 127, 127)}, // Bomb
		{11, sf::IntRect(384, 0, 127, 127)}, // Unset

		// States
		{12, sf::IntRect(256, 256, 127, 127)}, // Unchecked
		{13, sf::IntRect(256, 384, 127, 127)}, // Flag
	};

public:

	sf::Vector2i index;

	Tile(void) {
	}

	Tile(int type, sf::Vector2i index) {
		this->type = type;
		this->index = index;
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

	bool isUnset() {
		return type == 11;
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

	void render(sf::RenderWindow& window, int size, sf::Vector2i position, sf::Texture &textures) {
		display_tile.setSize(sf::Vector2f(size, size));
		display_tile.setPosition((sf::Vector2f) position);
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