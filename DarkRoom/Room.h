#pragma once

#include <SFML/Graphics.hpp>
#include <iostream>
#include <ctime>

#include "Door.h"
#include "Player.h"

class Room
{
private:
	sf::RenderWindow* window;
	Player* player;

	int roomWidth;
	int roomHeight;
	int roomXLocation;
	int roomYLocation;

	sf::Vector2i mousePosWindow;
	sf::Vector2f mousePosView;

	sf::Texture crackTexture;
	sf::Sprite crackSprite;
	std::vector<sf::Sprite> HitSprites;
	int crackScale;

	sf::Clock clock;
	sf::Time time;

	bool mouseheld;

	bool solved;

	bool gameHasStarted;

	//Objects in the Room
	Door* escapeDoor;
	sf::Sprite doorSprite;

	sf::Texture floorplan;
	sf::Sprite floorplanSprite;

	sf::Font font;
	sf::Text lockedText;

	sf::Texture key;
	sf::Sprite keySprite;
	bool keyCovered;

	sf::Texture crowbar;
	sf::Sprite crowbarSprite;

	sf::Texture torch;
	sf::Sprite torchSprite;

	void update();
	void generateObjects();

	bool playerCloseEnough(Player player, sf::Sprite sprite);

public:
	//Constructors and Destructors
	Room(sf::RenderWindow& window, Player& player);
	sf::Text draw();

	//getters
	bool roomSolved();

	//setters
	void startGame();
};

