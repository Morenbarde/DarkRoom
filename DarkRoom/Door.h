#pragma once

#include <SFML/Graphics.hpp>


class Door
{
private:
	sf::Texture doorImage;
	sf::Sprite doorSprite;

	bool doorClosed;
	bool doorLocked;

public:
	//constructors/destructors
	Door();

	//getters
	sf::Sprite getDoorSprite();

	//setters
	void setPosition(float x, float y);
	void unlock();

	//public functions
	bool toggleDoor();
};

