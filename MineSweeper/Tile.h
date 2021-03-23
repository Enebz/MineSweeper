#pragma once
#include <SFML/Graphics.hpp>

class Tile {

private:
	int type;
	bool shown = false;
	bool flagged = false;
	bool error = false;

	

public:

	sf::Vector2i position;

	Tile(int type) {
		if (type == 11) {
			error = true;
		}
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

	void check() {
		flagged = false;
		shown = true;
	}



};