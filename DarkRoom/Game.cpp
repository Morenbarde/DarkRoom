#include "Game.h"

/*
	This Class Is the main class for managing the game. 
	It manages and renders objects onto the window, and communicates between game objects
*/

void Game::initVariables()
{
	this->windowWidth = 1800;
	this->windowHeight = 1000;
	this->mouseheld = false;
}

void Game::initWindow()
{
	//Initializes the variables and stylings for the window
	this->videoMode.height = this->windowHeight;
	this->videoMode.width = this->windowWidth;

	this->window = new sf::RenderWindow(this->videoMode, "DarkRoom", sf::Style::Titlebar | sf::Style::Close);
	this->window->setFramerateLimit(60);
}

void Game::initPlayer()
{
	this->player = new Player();
}

void Game::initRoom()
{
	this->room = new Room(*this->window, *this->player);
}

void Game::initMenu()
{
	//This function contains all formatting fot the main menu
	this->font.loadFromFile("Fonts/CloisterBlack.ttf");

	this->MenuTitle.setFont(font);
	this->MenuTitle.setString("DarkRoom");
	this->MenuTitle.setCharacterSize(150);
	this->MenuTitle.setStyle(sf::Text::Bold);
	this->textX = (this->windowWidth / 2) - (this->MenuTitle.getCharacterSize()*2);
	this->MenuTitle.setPosition(this->textX, 25);

	this->startText.setFont(font);
	this->startText.setString("Start Game");
	this->startText.setCharacterSize(50);
	this->startText.setStyle(sf::Text::Bold);
	this->startText.setPosition(50, 400);

	this->startButton.setFillColor(sf::Color::Black);
	this->startButton.setSize(sf::Vector2f(300, 100));
	this->startButton.setPosition(35, 385);

	this->quitText.setFont(font);
	this->quitText.setString("Quit Game");
	this->quitText.setCharacterSize(50);
	this->quitText.setStyle(sf::Text::Bold);
	this->quitText.setPosition(50, 550);

	this->quitButton.setFillColor(sf::Color::Black);
	this->quitButton.setSize(sf::Vector2f(300, 100));
	this->quitButton.setPosition(35, 535);

}

Game::Game()
{
	//Calls all initializing functions when an instance of Game is created
	this->initVariables();
	this->initWindow();
	this->initPlayer();
	this->initRoom();
	this->initMenu();

	this->gameStarted = false;
}

Game::~Game()
{
	this->window->close();
}

const bool Game::isRunning()
{
	//Returns the status of the window
	return this->window->isOpen();
}

bool Game::hasStarted()
{
	//Returns the status of the game
	return this->gameStarted;
}

void Game::pollMenuEvents()
{
	//This is a seperate pollMenu for the main menu, to prevent interaction with game objects
	this->mousePosWindow = sf::Mouse::getPosition(*this->window);
	this->mousePosView = this->window->mapPixelToCoords(this->mousePosWindow);

	while (this->window->pollEvent(this->event))
	{
		switch (this->event.type)
		{
		case sf::Event::Closed:
			this->window->close();
			break;
		}
		//registers pressing the buttons on the main menu
		if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
			if (!this->mouseheld) {
				this->mouseheld = true;
				if (this->startButton.getGlobalBounds().contains(this->mousePosView)) {
					this->gameStarted = true;
					this->room->startGame();
				} else if (this->quitButton.getGlobalBounds().contains(this->mousePosView)) {
					this->window->close();
				}
			}
		}
		else {
			this->mouseheld = false;
		}
	} 
}

void Game::pollEvents()
{
	//This function recieves and reacts to user input, and communicates relavent information to game objects.
	while (this->window->pollEvent(this->event))
	{
		switch (this->event.type)
		{
		case sf::Event::Closed:
			this->window->close();
			break;
		}
		//Stops movement if a movement key is released.
		if (this->event.type == sf::Event::KeyReleased) {
			if (event.key.code == sf::Keyboard::Up || event.key.code == sf::Keyboard::Down
				|| event.key.code == sf::Keyboard::W || event.key.code == sf::Keyboard::S ||
				event.key.code == sf::Keyboard::Right || event.key.code == sf::Keyboard::Left
				|| event.key.code == sf::Keyboard::A || event.key.code == sf::Keyboard::D) {
				this->player->stop();
			}
		}
		//Sets the Player's velocity based on  keys pressed.
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up) || sf::Keyboard::isKeyPressed(sf::Keyboard::W)) {
			this->player->incrementYVelocity(-1);
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right) || sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {
			this->player->incrementXVelocity(1);
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down) || sf::Keyboard::isKeyPressed(sf::Keyboard::S)) {
			this->player->incrementYVelocity(1);
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left) || sf::Keyboard::isKeyPressed(sf::Keyboard::A)) {
			this->player->incrementXVelocity(-1);
		}
	}
}

void Game::updatePlayer()
{
	//moves the player based on their velocity
	this->player->move(windowWidth, windowHeight);
}

void Game::renderWindow()
{
	this->window->clear(sf::Color::Black);
}

void Game::menu()
{
	//Renders the window elements, also renders starting game screen as background
	this->render();
	this->pollMenuEvents();
	this->window->draw(this->MenuTitle);
	this->window->draw(this->startButton);
	this->window->draw(this->startText);
	this->window->draw(this->quitButton);
	this->window->draw(this->quitText);
	this->window->display();
}

void Game::update()
{
	//Updates game objects
	this->pollEvents();
	this->updatePlayer();
	if (this->room->roomSolved()) {
		this->gameStarted = false;
		this->initVariables();
		this->initPlayer();
		this->initRoom();
		this->initMenu();
	}
}

void Game::render()
{
	//This funtion renders the window and all objects on it.
	this->renderWindow();

	//renders the room
	this->textDrawable = this->room->draw();

	//renders the player
	this->window->draw(this->player->getSprite());


	//This obscures the players vision, to add a little challenge
	this->darkness.create(this->windowWidth, this->windowHeight);
	this->darkness.clear(sf::Color::Black);

	this->light.setFillColor(sf::Color(0, 0, 0, 100));
	this->lightRadius = 80;
	if (this->player->haveTorch()) {
		lightRadius *= 3;
		this->light.setFillColor(sf::Color(139, 64, 0, 100));
	}
	this->light.setRadius(lightRadius);
	this->light.setOrigin(lightRadius, lightRadius);
	this->light.setPosition(this->player->getXPosition()+this->player->getXSize()/2, 
		this->player->getYPosition() + this->player->getYSize()/2);

	this->darkness.draw(light, sf::BlendNone);
	this->darkness.display();
	
	this->vision.setTexture(this->darkness.getTexture());
	this->vision.setPosition(0, 0);
	this->window->draw(this->vision);



	this->window->draw(this->textDrawable);


	if (this->gameStarted) {
		this->window->display();
	}
}
