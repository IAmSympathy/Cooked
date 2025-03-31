/*====================================
// Filename : Game.cpp
// Description : This file contains the implementation of the Game class
//				 which contains the game's logic and the interaction between actors
// Author : Cedrik Caron, Samy Larochelle, Samit Adelyer
// Date : November 27th 2024
====================================*/

#include "game.h"
#include <unordered_set>


//Game::~Game()
//{
//
//}

Game::Game()
{

	//set size
	_background.setPosition(WINDOW_SCREEN_WIDTH / 2, WINDOW_SCREEN_HEIGHT / 2);
	_background.setSize(sf::Vector2f(WINDOW_SCREEN_WIDTH, WINDOW_SCREEN_HEIGHT));
	_background.setOrigin(WINDOW_SCREEN_WIDTH / 2, WINDOW_SCREEN_HEIGHT / 2);

	_foreground.setPosition(WINDOW_SCREEN_WIDTH / 2, WINDOW_SCREEN_HEIGHT / 2);
	_foreground.setSize(sf::Vector2f(BACKGROUND_WIDTH * 0.9, BACKGROUND_HEIGHT * 0.9));
	_foreground.setOrigin(BACKGROUND_WIDTH * 0.9 / 2, BACKGROUND_HEIGHT * 0.9 / 2);

	//load background
	initialiseWindow();
	_soundtrack.loadSoundtrack(_soundtrackValue);
	LoadBackground(_level);
	LoadSounds();


}

void Game::initialiseWindow() // genere le window
{
	sf::VideoMode mode(WINDOW_SCREEN_WIDTH, WINDOW_SCREEN_HEIGHT);
	_window.create(mode, "Cooked!");
	_window.setFramerateLimit(60);

}

void Game::initialise(int mealType) //initialise avant de jouer la game
{
	int amountOfStations = 0;
	if (mealType == HAMBURGER) {
		_availableIngredients.push(BREAD);
		_availableIngredients.push(TOMATO);
		_availableIngredients.push(LETTUCE);
		_availableIngredients.push(CHEESE_SLICE);
		_availableIngredients.push(STEAK);
		amountOfStations = 5;
	}
	else {
		_availableIngredients.push(PIZZA_DOUGH);
		_availableIngredients.push(TOMATO);
		_availableIngredients.push(CHEESE);
		_availableIngredients.push(ONION);
		_availableIngredients.push(MUSHROOM);
		_availableIngredients.push(PEPPER);
		_availableIngredients.push(PEPPERONI);
		_availableIngredients.push(OLIVE);
		amountOfStations = 8;
	}
	setSpawnInterval();

	createStations(amountOfStations, _availableIngredients);
}

void Game::createStations(int amountOfStations, std::stack<int> availableIngredients)
{
	std::unordered_set<int> takenPositions;

	for (int i = 0; i < amountOfStations + 1; i++) {
		int randomPosition = rand() % (11 + 1 - 0) + 0;
		while (takenPositions.find(randomPosition) != takenPositions.end()) {
			randomPosition = rand() % (11 + 1 - 0) + 0;
		}
		takenPositions.insert(randomPosition);
		if (i == amountOfStations) {
			Station newTrash(STATION_TRASH, randomPosition);
			stationsList.insere(newTrash);
			break;
		}

		Station newStation(availableIngredients.top(), randomPosition);
		availableIngredients.pop();
		stationsList.insere(newStation);
	}

	stationsList.sort();

}

void Game::createPlate(int position, int type, int nbFile)
{
	Station plate1(type, position, nbFile);
	stationsList.insere(plate1);
}


void Game::Play(int mealType)
{
	_instructionTime.restart();
	sf::Event event;
	sf::Color bgColor(90, 46, 29);
	_levelTime.restart();
	_levelMaxTime = seconds(180);
	_userInterface.SetLevel(_level);
	_soundtrack.toggleSondtrack(true);

	initialise(mealType);
	while (_window.isOpen()) {
		while (_window.pollEvent(event)) {
			if (event.type == sf::Event::Closed)
				_window.close();
		}

		if (_interaction) { //si interaction == vrai, on va comparer la pile du cook avec celui de la commande

			interactionWithCook(stationsList.contenu().GetPlateContent());
		}
		if (GetCurrentTime() <= 0) {
			updateFinLevelMenu();
			Reset();
			finLevelMenu();
		}


		clientManager();
		InputHandling(event, mealType);
		_player.IdleAnimation();
		_window.clear(bgColor);

		if (!bIsGameClosed)
			Draw();

		if (_instructionTime.getElapsedTime() > _timeInstruction && !bInstructionOver) {
			bInstructionOver = true;
			_levelTime.restart();
		}
		if (_instructionTime.getElapsedTime() < _timeInstruction && _level == 1) {
			drawInstructions();
		}
		else {
			createClients(mealType);
			_userInterface.UpdateTime(GetCurrentTime());
		}

		_window.display();
	}
}


void Game::drawPizza(std::stack<Ingredient>& meal, int xPos, int yPos, sf::RenderWindow& window, bool fromScreen)
{
	std::stack<Ingredient> reverse;

	int compteurQuadrant = 1;

	if (fromScreen) {
		std::stack<Ingredient> temp = meal;
		while (!temp.empty()) { //on reverse la pile
			Ingredient ingredient = temp.top();
			reverse.push(ingredient);
			temp.pop();
		}
	}
	else {
		reverse = meal;
	}

	while (!reverse.empty()) {
		if (reverse.top().getValue() == PIZZA_DOUGH || reverse.top().getValue() == TOMATO_SAUCE || reverse.top().getValue() == CHEESE) {
			reverse.top().setPosition(xPos, yPos);
			reverse.top().Draw(window);
			reverse.pop();
		}
		else {
			reverse.top().setPosition(xPos, yPos);
			reverse.top().rotate(compteurQuadrant);
			reverse.top().Draw(window);
			reverse.pop();
			compteurQuadrant++;
		}
	}
}


void Game::drawBurger(std::stack<Ingredient>& meal, int xPos, int yPos, sf::RenderWindow& window) {
	// Creer une copie de la pile pour ne pas modifier l'original
	std::stack<Ingredient> reverseStack = meal;
	std::vector<Ingredient> ingredients;

	// Inverser l'ordre des ingredients tout en les preservant
	while (!reverseStack.empty()) {
		Ingredient temp = reverseStack.top();
		ingredients.push_back(temp);
		reverseStack.pop();
	}
	int currentY = yPos;
	for (size_t i = 0; i < ingredients.size(); ++i) {
		// Positionner l'ingredient avec un decalage vertical progressif
		if (ingredients[i].getValue() == BREAD) {
			ingredients[i].setPosition(xPos + 6, currentY - 4);
		}
		else if (ingredients[i].getValue() == BREADBOTTOM) {
			ingredients[i].setPosition(xPos + 6, currentY - 7);
		}
		else {
			ingredients[i].setPosition(xPos, currentY);
		}
		if (ingredients[i].getValue() == STEAK) {
			ingredients[i].setPosition(xPos, currentY - 3);
		}

		ingredients[i].Draw(window);

		currentY -= ingredients[i].getSprite().getGlobalBounds().height - 1.3;
	}
}


void Game::InputHandling(sf::Event event, int mealType) //meal type pour la tomato sauce
{
	static bool bLeftIsHeld = false;
	static bool bRightIsHeld = false;
	static bool bSpaceIsHeld = false;

	// If a direction key is pressed : changes the direction that the player is looking towards to
	//Movement

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::A) || sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) {
		if (!bLeftIsHeld) {
			bLeftIsHeld = true;
			stationsList.suivant();
			_player.Move(stationsList.contenu().GetSpritePosition(), stationsList.contenu().GetDirection());
			_userInterface.SetCurrentStation(stationsList.contenu().GetIngredientID());
		}
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::D) || sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {
		if (!bRightIsHeld) {
			bRightIsHeld = true;
			stationsList.precedent();
			_player.Move(stationsList.contenu().GetSpritePosition(), stationsList.contenu().GetDirection());
			_userInterface.SetCurrentStation(stationsList.contenu().GetIngredientID());
		}
	}

	//Interact
	std::cout << _clockEnter.getElapsedTime().asSeconds() << endl;
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Enter) && (stationsList.contenu().GetIngredientID() == STATION_PLATE_SMALL || stationsList.contenu().GetIngredientID() == STATION_PLATE) && _clockEnter.getElapsedTime().asSeconds() > 1) {
		_clockEnter.restart();
		_interaction = true;
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space)) {
		if (!bSpaceIsHeld) {
			bSpaceIsHeld = true;
			if (stationsList.contenu().GetIngredientID() == STATION_TRASH) {
				if (!_player.GetHeldMeal().empty())
					_player.TrashHeldMeal(true);
			}
			else if (stationsList.contenu().GetIngredientID() == STATION_PLATE || stationsList.contenu().GetIngredientID() == STATION_PLATE_SMALL) { //If the station is a plate
				if (_player.GetHeldMeal().empty()) { //If the player's inventory is empty
					if (!(stationsList.contenu().GetPlateContent().empty())) {// And the plate has content in it
						_player.PushToHeldMeal(stationsList.contenu().TakeTopPlateContent()); //Push plate content to player inventory
					}

				}
				else {
					if (_player.GetHeldMeal().top().getValue() == BREAD && !(stationsList.contenu().GetPlateContent().empty())) { // juste pour le top bread xd
						_player.GetHeldMeal().pop();
						stack<Ingredient> temp = _player.GetHeldMeal();
						temp.push(Ingredient(BREADBOTTOM));
						_player.PushToHeldMeal(temp);
						stationsList.contenu().AddContent(_player.TrashHeldMeal(false));
					}
					else {
						stationsList.contenu().AddContent(_player.TrashHeldMeal(false)); // If the player's inventory has something in it, push it to the plate
						_sfxOrderPlace.play();
					}
				}
			}
			else if (_player.GetHeldMeal().empty()) {//Take ingredient from station if player's inventory is empty

				if (stationsList.contenu().GetIngredientAsStack().top().getValue() == TOMATO && mealType == PIZZA) { // juste pour le tomato sauce xd
					stack<Ingredient> temp;
					temp.push(Ingredient(TOMATO_SAUCE));
					_player.PushToHeldMeal(temp);
				}
				else {
					_player.PushToHeldMeal(stationsList.contenu().GetIngredientAsStack());
				}
			}
		}
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::P)) { //Debug end level keybind
		updateFinLevelMenu();
		Reset();
		finLevelMenu();
	}
	if (event.type == sf::Event::KeyReleased) {
		switch (event.key.code) {
		case sf::Keyboard::A:
		case sf::Keyboard::Left:
			bLeftIsHeld = false;
			break;
		case sf::Keyboard::D:
		case sf::Keyboard::Right:
			bRightIsHeld = false;
			break;
		case sf::Keyboard::Space:
			bSpaceIsHeld = false;
			break;
		case sf::Keyboard::Enter:
			_interaction = false;
			break;
		}
	}
}

void Game::drawInstructions()
{
	_carreInstruction.setSize(sf::Vector2f(1150, 500));
	_carreInstruction.setPosition(sf::Vector2f(370, 350));
	_carreInstruction.setFillColor(sf::Color(0, 0, 0, 150));

	sf::Font font;
	font.loadFromFile(FONT_LOCATION);
	_instruction.setPosition(sf::Vector2f(390, 370));
	_instruction.setString("CONTROLS:\n\nCHANGE STATION\n- A, D OR ARROW KEYS\n\nPICK UP AND DROP AN INGREDIENT\n- SPACE\n\nSEND AN ORDER\n- ENTER\n\nOBJECTIVE:\n\nCOMPLETE THE ORDERS BEFORE\nTHE CUSTOMERS LOSE PATIENCE!");
	_instruction.setFont(font);
	_instruction.setCharacterSize(30);

	_window.draw(_carreInstruction);
	_window.draw(_instruction);
}

void Game::start()
{
	//initialise les menus
	_mainMenu.initializeMainMenu();
	_setting.initializeSettingMenu();
	_finLevel.initializeEndLevelMenu();

	//vas au menu principale
	mainMenu();

}

float Game::GetCurrentTime()
{
	return _levelMaxTime.asSeconds() - _levelTime.getElapsedTime().asSeconds();
}


bool Game::LoadSounds()
{
	if (!_bufferSFXOrderMissed.loadFromFile(SFX_ORDER_MISSED_LOCATION))
		return false;

	_sfxOrderMissed.setBuffer(_bufferSFXOrderMissed);
	_sfxOrderMissed.setVolume(10);

	if (!_bufferSFXOrderSend.loadFromFile(SFX_SEND_ORDER_LOCATION))
		return false;

	_sfxOrderSend.setBuffer(_bufferSFXOrderSend);

	if (!_bufferSFXEndLevel.loadFromFile(SFX_ENDGAME_LOCATION))
		return false;

	_sfxEndLevel.setBuffer(_bufferSFXEndLevel);

	if (!_bufferSFXOrderPlace.loadFromFile(SFX_ORDER_PLACE))
		return false;

	_sfxOrderPlace.setBuffer(_bufferSFXOrderPlace);
}

void Game::mainMenu()
{
	sf::Event eventMenu;
	while (_window.isOpen()) {
		while (_window.pollEvent(eventMenu)) {
			if (eventMenu.type == sf::Event::Closed)
				_window.close();
			if (eventMenu.type == sf::Event::KeyPressed) {
				switch (eventMenu.key.code) {
				case sf::Keyboard::W:
				case sf::Keyboard::Up:
					_mainMenu.buttonUp();
					break;
				case sf::Keyboard::S:
				case sf::Keyboard::Down:
					_mainMenu.buttonDown();
					break;
				case sf::Keyboard::Enter:
					switch (_mainMenu.buttonEnter())
					{
					case 0:
						Play();
						break;
					case 1:
						optionMenu();
						break;
					case 2:
						_window.close();
						break;

					default:
						break;
					}

				}
			}
			_window.clear();
			_mainMenu.draw(_window);
			_window.display();
		}
	}

}

void Game::optionMenu()
{
	sf::Event eventMenu;
	while (_window.isOpen()) {
		while (_window.pollEvent(eventMenu)) {
			if (eventMenu.type == sf::Event::Closed)
				_window.close();
			if (eventMenu.type == sf::Event::KeyPressed) {
				switch (eventMenu.key.code) {
				case sf::Keyboard::W:
				case sf::Keyboard::Up:
					_setting.buttonUp();
					break;
				case sf::Keyboard::S:
				case sf::Keyboard::Down:
					_setting.buttonDown();
					break;
				case sf::Keyboard::Enter:
					switch (_setting.buttonEnter())
					{
					case 0:
						_difficulty = _setting.getCurrentButtonValue();
						break;
					case 1:
						_soundtrack.toggleSondtrack(_setting.getCurrentButtonValue());
						break;
					case 2:
						_soundtrack.loadSoundtrack(_setting.getCurrentButtonValue());
						_soundtrack.toggleSondtrack(_setting.getButtonValue(1));
						break;
					case 3:
						mainMenu();
						break;
					}
					break;
				case sf::Keyboard::Escape:
					mainMenu();
					break;
				}
			}
			_window.clear();
			_setting.draw(_window);
			_window.display();
		}
	}

}

void Game::finLevelMenu()
{
	_soundtrack.toggleSondtrack(false);
	_sfxEndLevel.play();
	sf::Event eventMenu;
	while (_window.isOpen()) {
		while (_window.pollEvent(eventMenu)) {
			if (eventMenu.type == sf::Event::Closed) {
				bIsGameClosed = true;
				_window.close();
			}
			if (eventMenu.type == sf::Event::KeyPressed) {
				switch (eventMenu.key.code) {
				case sf::Keyboard::W:
				case sf::Keyboard::Up:
					_finLevel.buttonUp();
					break;
				case sf::Keyboard::S:
				case sf::Keyboard::Down:
					_finLevel.buttonDown();
					break;
				case sf::Keyboard::Enter:
					switch (_finLevel.buttonEnter())
					{
					case 0:
						_level++;
						Play(_level % 2);
						break;
					}
					break;
				case sf::Keyboard::Escape:
					mainMenu();
					break;

				}
			}
			_window.clear();
			_finLevel.draw(_window);
			_window.display();
		}
	}

}

void Game::updateFinLevelMenu()
{
	_finLevel.setScore(_score);
	_finLevel.setClientServie(_clientServie);
	_finLevel.setClientPerdu(_clientPerdu);
}

void Game::Reset()
{
	stationsList.vide();
	_clientServie = _clientPerdu = _score = 0;

	for (int i = 0; i < 5; i++) {
		while (!_client[i].empty())
			_client[i].pop();
	}

	_player.TrashHeldMeal(false);


}


void Game::setSpawnInterval()//multiplicateur qui definit a partir de quand le client spawn, gere la difficult�
{
	_spawnInterval = sf::seconds(DEFAULT_SPAWN_RATES_FOR_CLIENTS / (_difficulty + _level));
}

void Game::createClients(int mealType)
{
	if (_clockSpawnClient.getElapsedTime() >= _spawnInterval) { //gere automatiquement le timing pour faire spawn

		_clockSpawnClient.restart(); //recommence le time

		int randomStation = rand() % 5;

		if (_client[randomStation].empty()) {
			Station currentStation = stationsList.contenu();
			createPlate(PLATE_POSITION_FIVE - randomStation, STATION_PLATE + mealType, randomStation);
			stationsList.sort();
			stationsList.recherche(currentStation);
		}

		_client[randomStation].push(Client(30, randomStation, mealType)); //push un client a une station random


		if (_client[randomStation].size() == 1) {
			_client[randomStation].front().spawn();
		}
	}
}

void Game::drawClientsMeals()
{
	for (int i = 0; i < 5; i++) { //si liste n'est pas empty, on fait le tour des files(stations) pour dessiner le repas
		if (!_client[i].empty()) {
			if (_client[i].front().getCommande().getMealType() == HAMBURGER) {
				if (i == 1) {
					drawBurger(_client[i].front().getCommande().display(), MEAL_XPOS + ESPACE_ENTRE_BURGER, BURGER_YPOS, _window);// position fictive
				}
				else {
					drawBurger(_client[i].front().getCommande().display(), MEAL_XPOS + (i * ESPACE_ENTRE_BURGER), BURGER_YPOS, _window);// position fictive
				}

			}
			else {
				if (i == 1) {
					drawPizza(_client[i].front().getCommande().display(), MEAL_XPOS + ESPACE_ENTRE_PIZZA, PIZZA_YPOS, _window, true);
				}
				else {
					drawPizza(_client[i].front().getCommande().display(), MEAL_XPOS + (i * ESPACE_ENTRE_PIZZA), PIZZA_YPOS, _window, true); //position fictive
				}

			}
		}
	}
}

bool Game::interactionWithCook(std::stack<Ingredient>& cookMeal) 	//retourne faux si la commande n'est pas bonne
{
	int file = stationsList.contenu().getFile();
	int mealSize = cookMeal.size();
	_sfxOrderSend.play();
	if (!_client[stationsList.contenu().getFile()].empty()) {
		if (_client[(stationsList.contenu().getFile())].front().getCommande().compare(cookMeal)) {
			// player.setMoney()
			_client[(stationsList.contenu().getFile())].pop(); //on enleve le client de la file d'attente, devrait ne plus apparaitre aussi

			//sert a garde la position de gauche en memoire
			stationsList.suivant();
			Station currentStation = stationsList.contenu();
			stationsList.precedent();

			Station plate(STATION_PLATE, PLATE_POSITION_FIVE - (stationsList.contenu().getFile()));
			Station plateSmall(STATION_PLATE_SMALL, PLATE_POSITION_FIVE - (stationsList.contenu().getFile()));

			if (stationsList.contenu().GetPosition() == PLATE_POSITION_FIVE - (stationsList.contenu().getFile())) {
				stationsList.suivant();
				_player.Move(stationsList.contenu().GetSpritePosition(), stationsList.contenu().GetDirection());
			}

			stationsList.rechercheKill(plate);
			stationsList.rechercheKill(plateSmall);
			stationsList.sort();
			stationsList.recherche(currentStation);
			_interaction = false;

			_clientServie++;
			_score += 20 * mealSize;
			cout << "ca passe";

			if (!_client[file].empty()) {
				_client[file].front().spawn();
				_client[file].front().playSound();
				Station currentStation = stationsList.contenu();
				createPlate(PLATE_POSITION_FIVE - file, STATION_PLATE + _client[file].front().getCommande().getMealType(), file);
				stationsList.sort();
				stationsList.recherche(currentStation);
			}

			return true;
		}
		else {
			_client[(stationsList.contenu().getFile())].pop();

			//sert a garde la position de gauche en memoire
			stationsList.suivant();
			Station currentStation = stationsList.contenu();
			stationsList.precedent();

			Station plate(STATION_PLATE, PLATE_POSITION_FIVE - (stationsList.contenu().getFile()));
			Station plateSmall(STATION_PLATE_SMALL, PLATE_POSITION_FIVE - (stationsList.contenu().getFile()));

			if (stationsList.contenu().GetPosition() == PLATE_POSITION_FIVE - (stationsList.contenu().getFile())) {
				stationsList.suivant();
				_player.Move(stationsList.contenu().GetSpritePosition(), stationsList.contenu().GetDirection());
			}

			stationsList.rechercheKill(plate);
			stationsList.rechercheKill(plateSmall);
			stationsList.sort();
			stationsList.recherche(currentStation);
			_interaction = false;

			if (!_client[file].empty()) {
				_client[file].front().spawn();
				_client[file].front().playSound();
				Station currentStation = stationsList.contenu();
				createPlate(PLATE_POSITION_FIVE - file, STATION_PLATE + _client[file].front().getCommande().getMealType(), file);
				stationsList.sort();
				stationsList.recherche(currentStation);
			}
		}

		stationsList.suivant();
		cout << "pas empty";
	}
	else {
		cout << stationsList.contenu().getFile() << endl;
		cout << "alloha!";
		stationsList.suivant();
		_interaction = false;
	}
	return false;
}

void Game::clientManager()
{
	for (int i = 0; i < 5; i++) {
		if (!_client[i].empty() && _client[i].front().getTempsRestant() <= 0) {
			_client[i].pop();
			_sfxOrderMissed.play();
			_clientPerdu++;

			Station currentStation = stationsList.contenu();

			Station plate(STATION_PLATE, PLATE_POSITION_FIVE - i);
			Station plateSmall(STATION_PLATE_SMALL, PLATE_POSITION_FIVE - i);

			if (stationsList.contenu().GetPosition() == PLATE_POSITION_FIVE - i) {
				stationsList.suivant();
				_player.Move(stationsList.contenu().GetSpritePosition(), stationsList.contenu().GetDirection());
			}

			stationsList.rechercheKill(plate);
			stationsList.rechercheKill(plateSmall);
			stationsList.sort();
			stationsList.recherche(currentStation);

			if (!_client[i].empty()) {
				_client[i].front().spawn();
				_client[i].front().playSound();
				Station currentStation = stationsList.contenu();
				createPlate(PLATE_POSITION_FIVE - i, STATION_PLATE + _client[i].front().getCommande().getMealType(), i);
				stationsList.sort();
				stationsList.recherche(currentStation);
			}
		}
		if (!_client[i].empty()) {
			_client[i].front().updateClient();
		}
	}
}

void Game::saveInfo()
{
	std::ofstream monFlux("stats.txt");
	if (monFlux) {
		monFlux << "SCORE : " << _score;
		monFlux << "CLIENT_SERVIE" << _clientServie;
		monFlux << "CLIENT_PERDU" << _clientPerdu;
		monFlux.close();
	}
	else {
		std::cout << "erreur le fichier n'a pas pus etre ouvert";
	}
}



bool Game::LoadBackground(int& level)
{
	std::string LevelBGTexturePath = LEVEL_BACKGROUNDS_LOCATION;
	LevelBGTexturePath += std::to_string(level);
	LevelBGTexturePath += "BG.png";
	std::string LevelFGTexturePath = LEVEL_BACKGROUNDS_LOCATION;
	LevelFGTexturePath += std::to_string(level);
	LevelFGTexturePath += "FG.png";

	if (!_textureBackground.loadFromFile(LevelBGTexturePath))
		return false;
	if (!_textureForeground.loadFromFile(LevelFGTexturePath))
		return false;

	_background.setTexture(&_textureBackground);
	_foreground.setTexture(&_textureForeground);
}

void Game::Draw()
{
	for (int i = 0; i < 5; i++) {
		if (!_client[i].empty())
			_client[i].front().draw(_window);
	}

	_window.draw(_background);

	//Draw Plates
	int tempVal = stationsList.contenu().GetPosition();

	do {
		if (stationsList.contenu().GetIngredientID() == STATION_PLATE) {
			_window.draw(stationsList.contenu().GetStation());
			drawPizza(stationsList.contenu().GetPlateContent(), stationsList.contenu().GetSpritePosition().x - 45, stationsList.contenu().GetSpritePosition().y - 45, _window, false);
		}
		else if (stationsList.contenu().GetIngredientID() == STATION_PLATE_SMALL) {
			_window.draw(stationsList.contenu().GetStation());
			drawBurger(stationsList.contenu().GetPlateContent(), stationsList.contenu().GetSpritePosition().x - 35, stationsList.contenu().GetSpritePosition().y, _window);
		}
		stationsList.suivant();
	} while (tempVal != stationsList.contenu().GetPosition());

	//Player
	_player.Draw(_window);

	//Foreground
	_window.draw(_foreground);


	//Stations
	int tempVal2 = stationsList.contenu().GetPosition();
	do {
		if (!(stationsList.contenu().GetIngredientID() == STATION_PLATE || stationsList.contenu().GetIngredientID() == STATION_PLATE_SMALL))
		{
			_window.draw(stationsList.contenu().GetStation());
		}
		stationsList.suivant();
	} while (tempVal2 != stationsList.contenu().GetPosition());



	//Meals on monitor
	drawClientsMeals();


	_userInterface.draw(_window);


}

