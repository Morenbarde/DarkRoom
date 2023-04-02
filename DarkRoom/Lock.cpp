#include "Lock.h"

Lock::Lock()
{
	this->locked = true;
}

void Lock::unlock() {
	this->locked = false;
}

bool Lock::unlocked() {
	return !this->locked;
}