#pragma once

#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/Audio.hpp>
#include <SFML/System.hpp>
#include <SFML/Network.hpp>

#include "Player.h"
#include "Room.h"

class Game
{
private:
	//Main Menu Variables
	sf::RectangleShape startButton;
	sf::RectangleShape quitButton;
	int textX;
	int textY;
	sf::Text startText;
	sf::Text quitText;
	sf::Text MenuTitle;
	sf::Font font;

	//variables
	sf::RenderWindow* window;
	sf::VideoMode videoMode;
	sf::Event event;

	sf::RenderTexture darkness;
	sf::CircleShape light;

	sf::Sprite lightSprite;
	int lightRadius;

	sf::Sprite vision;

	sf::Text textDrawable;

	int windowWidth;
	int windowHeight;

	Player* player;

	Room* room;

	bool gameStarted;

	bool mouseheld;
	sf::Vector2i mousePosWindow;
	sf::Vector2f mousePosView;

	//private functions
	void initVariables();
	void initWindow();
	void initPlayer();
	void initRoom();
	void initMenu();

public:
	//Constructors and Deconstructors
	Game();
	virtual ~Game();

	//getters
	const bool isRunning();
	bool hasStarted();

	//update functions
	void pollMenuEvents();

	void pollEvents();
	void updatePlayer();


	//render functions
	void renderWindow();

	//updates and renders the window
	void menu();
	void update();
	void render();
};

