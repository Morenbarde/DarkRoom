#pragma once

#include <SFML/Graphics.hpp>

class Lock
{
private:
	bool locked;

public:
	//constructors
	Lock();

	void unlock();

	//getters
	bool unlocked();
};

