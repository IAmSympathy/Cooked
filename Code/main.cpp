#include <SFML/Graphics.hpp>
#include <cstdlib>
#include "definitions.h"
#include "Player.h"
#include "Game.h"
#include "Station.h"
#include "Menu.h"

using namespace sf;

int main() {

	srand(time(NULL));

	Event event;
	Player player;
	Game game;

	game.start();


	return 0;
}
