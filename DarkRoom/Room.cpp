#include "Room.h"

void Room::update()
{
	this->mousePosWindow = sf::Mouse::getPosition(*this->window);
	this->mousePosView = this->window->mapPixelToCoords(this->mousePosWindow);
	//Meant to make room stay in center if window size changes. 
	//TODO, Not currently working, but it still works with the default size.
	this->roomXLocation = ((this->window->getSize().x - roomWidth) / 2.0);
	this->roomYLocation = ((this->window->getSize().y - roomHeight) / 2.0);
	this->floorplanSprite.setPosition(sf::Vector2f(this->roomXLocation, this->roomYLocation));
	this->escapeDoor->setPosition(this->roomXLocation + 200, this->roomYLocation - 100);

	if (this->keyCovered == true) {
		this->keySprite.scale(0, 0);
	}

	//checks if an interactible object is clicked on
	if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
		if (!this->mouseheld) {
			this->mouseheld = true;
			this->doorSprite = this->escapeDoor->getDoorSprite();
			if (this->doorSprite.getGlobalBounds().contains(this->mousePosView) && playerCloseEnough(*this->player, this->doorSprite)) 
			{
				if (!this->escapeDoor->toggleDoor()) {
					this->lockedText.setString("Door is Locked, find a key");
					this->clock.restart();
				}
				else {
					this->lockedText.setString("Door Opened!");
					this->clock.restart();
					this->solved = true;
				}
			} 
			else if (this->torchSprite.getGlobalBounds().contains(this->mousePosView)
				&& playerCloseEnough(*this->player, this->torchSprite))
			{
				this->lockedText.setString("Obtained a Torch!");
				this->clock.restart();
				this->torchSprite.setScale(0, 0);
				this->player->obtainTorch();
			}
			else if (this->crowbarSprite.getGlobalBounds().contains(this->mousePosView) 
			&& playerCloseEnough(*this->player, this->crowbarSprite)) 
			{
				if (!this->player->haveCrowbar()) {
					this->lockedText.setString("Obtained a Crowbar!");
					this->player->obtainCrowbar();
					this->clock.restart();

					int randX = (rand() % (this->roomWidth)) + 100;
					int randY = (rand() % (this->roomHeight)) + 100;
					this->crowbarSprite.setPosition(randX, randY);
				}
				else if (!this->player->haveCrowbarUpgrade()) {
					this->lockedText.setString("Obtained a Crowbar Upgrade!");
					this->crowbarSprite.setScale(0, 0);
					this->clock.restart();
					this->crackScale = 2;
				}

				
			} 
			else if (this->keySprite.getGlobalBounds().contains(this->mousePosView) 
				&& playerCloseEnough(*this->player, this->keySprite) && !keyCovered) 
			{
				this->lockedText.setString("Obtained a Key!");
				this->player->obtainKey();
				this->escapeDoor->unlock();
				this->clock.restart();
				this->keySprite.setScale(0, 0);
				this->keySprite.setPosition(2000, 2000);
			} 
			else if (player->haveCrowbar()) 
			{
				this->crackSprite = sf::Sprite(crackTexture);
				this->crackSprite.setPosition(this->mousePosView.x - 25, this->mousePosView.y - 25);
				this->crackSprite.setScale(this->crackScale, this->crackScale);
				this->HitSprites.push_back(this->crackSprite);
				if (this->crackSprite.getGlobalBounds().contains(this->keySprite.getPosition())) {
					this->keyCovered = false;
					this->keySprite.setScale(1, 1);
					this->lockedText.setString("Key Found!");
					this->clock.restart();
				}
			}
		}
	} else {
		this->mouseheld = false;
	}

	//If enough time has passed since the door was clicked on, the text will dissapear
	this->time = clock.getElapsedTime();
	if (this->time > sf::seconds(3.0f)) {
		this->lockedText.setString("");
	}
}

void Room::generateObjects()
{
	this->solved = false;
	//Starts RNG for item placement
	srand(std::time(NULL));
	int randX;
	int randY;

	//sets all objects located inside the room
	this->escapeDoor = new Door();
	this->escapeDoor->setPosition(this->roomXLocation + 200, this->roomYLocation - 100);

	//Text, will notify certain info during the game
	this->lockedText.setString("");
	this->lockedText.setCharacterSize(100);
	this->lockedText.setFillColor(sf::Color::White);
	this->lockedText.setStyle(sf::Text::Bold | sf::Text::Underlined);
	this->lockedText.setPosition(500, -25);
	this->font.loadFromFile("Fonts/CloisterBlack.ttf");
	this->lockedText.setFont(this->font);

	randX = (rand() % (this->roomWidth)) + 100;
	randY = (rand() % (this->roomHeight)) + 100;
	this->crowbar.loadFromFile("Images/Crowbar.png");
	this->crowbarSprite.setTexture(this->crowbar);
	crowbarSprite.setPosition(randX, randY);

	this->crackScale = 1;

	randX = (rand() % (this->roomWidth)) + 100;
	randY = (rand() % (this->roomHeight)) + 100;
	this->key.loadFromFile("Images/Key.png");
	this->keySprite.setTexture(this->key);
	this->keySprite.setPosition(randX, randY);
	this->keyCovered = true;

	randX = (rand() % (this->roomWidth)) + 100;
	randY = (rand() % (this->roomHeight)) + 100;
	this->torch.loadFromFile("Images/Torch.png");
	this->torchSprite.setTexture(this->torch);
	this->torchSprite.setPosition(randX, randY);

	this->crackTexture.loadFromFile("Images/Cracks.png");
}

bool Room::playerCloseEnough(Player player, sf::Sprite sprite) {
	return std::abs(player.getXPosition() - sprite.getPosition().x) < 
		200 && std::abs(player.getYPosition() - sprite.getPosition().y) < 200;
}

Room::Room(sf::RenderWindow& gameWindow, Player& player)
{
	//Room works closely with the window and player, so it recieves a pointer to them
	this->window = &gameWindow;
	this->player = &player;

	this->gameHasStarted = false;

	mouseheld = false;

	this->floorplan.loadFromFile("Images/DarkRoom_Floorplan.png");
	this->floorplanSprite.setTexture(this->floorplan);
	
	//gets the size of the room's floorplan
	this->roomWidth = this->floorplan.getSize().x;
	this->roomHeight = this->floorplan.getSize().y;

	this->generateObjects();

	this->update();

}

sf::Text Room::draw()
{
	//Draws the room and all objects in the room;
	if (gameHasStarted) {
		this->update();
	}
	this->window->draw(floorplanSprite);
	this->window->draw(this->escapeDoor->getDoorSprite());
	for (int i = 0; i < this->HitSprites.size(); i++) {
		this->window->draw(this->HitSprites[i]);
	}
	this->window->draw(this->torchSprite);
	this->window->draw(this->crowbarSprite);
	this->window->draw(this->keySprite);

	return this->lockedText;

}

bool Room::roomSolved()
{
	return this->solved;
}

void Room::startGame()
{
	this->gameHasStarted = true;
}
