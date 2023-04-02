#pragma once

#include <SFML/Graphics.hpp>

enum Direction{north, east, south, west};

class Player
{
private:

	//variables
	int xPosition;
	int yPosition;
	int xSize;
	int ySize;
	Direction direction;
	int xVelocity;
	int yVelocity;
	int velocityMax;

	bool hasCrowbar;
	bool hasCrowbarUpgrade;
	bool hasKey;
	bool hasTorch;

	sf::Texture playerTexture;
	sf::Sprite playerSprite;

	//private functions
	void setTexture();

public:
	//constructors
	Player();

	//getters
	int getXPosition();
	int getYPosition();
	int getXSize();
	int getYSize();
	Direction getDirection();
	bool haveCrowbar();
	bool haveCrowbarUpgrade();
	bool haveKey();
	bool haveTorch();

	//setters
	void setXPosition(int x);
	void setYPosition(int y);
	void incrementXVelocity(int v);
	void incrementYVelocity(int v);
	void stop();
	void obtainCrowbar();
	void obtainCrowbarUpgrade();
	void obtainKey();
	void obtainTorch();

	//public functions
	sf::Sprite getSprite();
	void move(int maxX, int maxY);
};

