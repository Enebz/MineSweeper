#ifndef TILE_H
#define TILE_H

#include <SFML/Graphics.hpp>

class Tile {

private:
	int type = 11;
	bool shown = false;
	bool flagged = false;
	bool error = false;

	sf::RectangleShape display;

	std::map<int, sf::IntRect> tile_texture_boundaries = {
		// Types
		{1, sf::IntRect(0, 0, 128, 128)},
		{2, sf::IntRect(128, 0, 128, 128)},
		{3, sf::IntRect(0, 128, 128, 128)},
		{4, sf::IntRect(128, 128, 128, 128)},
		{5, sf::IntRect(0, 256, 128, 128)},
		{6, sf::IntRect(128, 256, 128, 128)},
		{7, sf::IntRect(0, 384, 128, 128)},
		{8, sf::IntRect(128, 384, 128, 128)},
		{0, sf::IntRect(256, 128, 128, 128)}, // Open
		{10, sf::IntRect(256, 0, 128, 128)}, // Bomb
		{11, sf::IntRect(384, 0, 128, 128)}, // Unset

		// States
		{12, sf::IntRect(256, 256, 128, 128)}, // Unchecked
		{13, sf::IntRect(256, 384, 128, 128)}, // Flag
	};

public:

	sf::Vector2i index;

	Tile(void);

	Tile(int type, sf::Vector2i index);

	void setType(int type);

	int getType();

	void toggleFlag();

	bool isFlagged();

	bool isUnset();

	bool isEmpty();

	bool isError();

	bool isNumber();

	bool isBomb();

	bool isShowable();

	bool isShown();

	void show();

	void render(sf::RenderWindow& window, float size, sf::Vector2f position, sf::Texture& textures);
};

#endif