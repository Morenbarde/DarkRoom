#include "Player.h"

#include <iostream>

void Player::setTexture()
{
	//Loads the 2 player files based on whether the player is facing left or right
	if (this->direction == east) {
		this->playerTexture.loadFromFile("Images/Player_Right.png");
	}
	else if (this->direction == west) {
		this->playerTexture.loadFromFile("Images/Player_Left.png");
	}

	//updates the texture
	this->playerSprite.setTexture(this->playerTexture);
	this->playerSprite.setPosition(this->xPosition, this->yPosition);
	this->playerSprite.setScale(2, 2);
}

Player::Player()
{
	//sets player variables when an instance of the player class is made
	this->direction = east;
	this->xPosition = 795;
	this->yPosition = 385;
	this->xSize = 64;
	this->ySize = 96;
	this->xVelocity = 0;
	this->yVelocity = 0;
	this->velocityMax = 2;

	this->hasCrowbar = false;
	this->hasCrowbarUpgrade = false;
	this->hasKey = false;
	this->hasTorch = false;

	this->setTexture();
}

int Player::getXPosition()
{
	return this->xPosition;
}

int Player::getYPosition()
{
	return this->yPosition;
}

int Player::getXSize()
{
	return this->xSize;
}

int Player::getYSize()
{
	return this->ySize;
}

Direction Player::getDirection()
{
	return this->direction;
}

//These functions return whether the player has achieved certain upgrades
bool Player::haveCrowbar() {
	return this->hasCrowbar;
}
bool Player::haveCrowbarUpgrade()
{
	return this->hasCrowbarUpgrade;
}
bool Player::haveKey() {
	return this->hasKey;
}
bool Player::haveTorch()
{
	return this->hasTorch;
}

void Player::setXPosition(int x)
{
	this->xPosition = x;
}

void Player::setYPosition(int y)
{
	this->yPosition = y;
}

void Player::incrementXVelocity(int v)
{
	//updates the velocity in the X direction, while limiting it to a maximum value
	while (this->xVelocity <= velocityMax && this->xVelocity >= -velocityMax) {
		this->xVelocity += v * velocityMax;
	}
}

void Player::incrementYVelocity(int v)
{
	//updates the velocity in the Y direction, while limiting it to a maximum value
	while (this->yVelocity <= velocityMax && this->yVelocity >= -velocityMax) {
		this->yVelocity += v * velocityMax;
	}
}

void Player::stop()
{
	//Removes all velocity from the player
	this->xVelocity = 0;
	this->yVelocity = 0;
}

//Gives the player certain upgrades
void Player::obtainCrowbar() {
	this->hasCrowbar = true;
}
void Player::obtainCrowbarUpgrade()
{
	this->hasCrowbarUpgrade = true;
}
void Player::obtainKey() {
	this->hasKey = true;
}
void Player::obtainTorch()
{
	this->hasTorch = true;
}

sf::Sprite Player::getSprite()
{
	//returns the player's sprite to be drawn
	return this->playerSprite;
}

void Player::move(int maxX, int maxY)
{
	//updates the player direction based on velocity
	if (xVelocity > 0) this->direction = east;
	if (xVelocity < 0) this->direction = west;

	//updates the player position based on velocity
	this->xPosition += this->xVelocity;
	this->yPosition += this->yVelocity;

	//Limits the player's movement to the walls of the room
	if (xPosition <= 100) {
		this->xVelocity = 0;
		this->xPosition = 100;
	}
	else if (xPosition >= maxX - 100 - xSize) {
		this->xVelocity = 0;
		this->xPosition = maxX - 100 - xSize;
	}
	if (yPosition <= 50) {
		this->yVelocity = 0;
		this->yPosition = 50;
	}
	else if (yPosition >= maxY - 100 - ySize) {
		this->yVelocity = 0;
		this->yPosition = maxY - 100 - ySize;
	}

	//Updates the player's sprite
	this->setTexture();
	this->playerSprite.setPosition(this->xPosition, this->yPosition);
	
	

}
