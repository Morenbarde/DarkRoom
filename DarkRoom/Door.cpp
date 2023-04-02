#include "Door.h"

Door::Door()
{
	this->doorImage.loadFromFile("Images/Door.png");
	this->doorSprite.setTexture(this->doorImage);
	this->doorSprite.setTextureRect(sf::IntRect(0, 0, 50, 100));

	this->doorClosed = true;
	this->doorLocked = true;
}

sf::Sprite Door::getDoorSprite()
{
	return this->doorSprite;
}

void Door::setPosition(float x, float y)
{
	this->doorSprite.setPosition(x, y);
}

void Door::unlock()
{
	this->doorLocked = false;
}

bool Door::toggleDoor()
{
	if (!this->doorLocked) {
		if (this->doorClosed) {
			doorClosed = false;
			this->doorSprite.setTextureRect(sf::IntRect(50, 0, 50, 100));
		}
		else {
			doorClosed = true;
			this->doorSprite.setTextureRect(sf::IntRect(0, 0, 50, 100));
		}
		return true;
	}
	else {
		return false;
	}
}


