#include "Game.h"

int main() {

	Game game;

	//Game loops
	while (game.isRunning()) {
		//hasStarted separates the main menu from the game itself
		if (game.hasStarted()) {
			game.update();
			game.render();
		}
		else {
			game.menu();
		}
	}
	return 0;
}