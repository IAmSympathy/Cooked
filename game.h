/*====================================
// Filename : Game.cpp
// Description : This file contains the definitions of the Game class
//				 which contains the game's logic and the interaction between actors
// Author : Cedrik Caron, Samy Larochelle
// Date : November 28th 2024
====================================*/
#pragma once


#include <assert.h>
#include <iostream>
#include "definitions.h"
#include "ingredient.h"
#include "game.h"
#include "Station.h"
#include "Player.h"
#include <stack> //a enlever
#include "queue.hpp" // a enlever
#include "cListe.hpp"
#include "Menu.h"
#include "client.h"
#include "UserInterface.h"
#include <fstream>

#define BACKGROUND_WIDTH 1441
#define BACKGROUND_HEIGHT 1080

class Game {
private:
	//Attributes
	int _level = 1,
		_score = 0,
		_clientServie = 0,//ajoute +1 quand le client est servi
		_clientPerdu = 0,//ajoute +! quand le client pert patience
		_soundtrackValue = 0,
		_difficulty = 3,
		_sound = 0;
	bool _interaction = false;
	Player _player;

	//Menu
	Menu _mainMenu;
	Menu _setting;
	Menu _finLevel;
	SoundtrackManager _soundtrack;//gere les soundtrack qui joue 

	UserInterface _userInterface;


	std::stack<int> _availableIngredients;
	queue<Client> _client[5];
	cListe<Station> stationsList;



	//Sprites
	sf::RenderWindow _window;
	sf::RectangleShape _background;
	sf::Texture _textureBackground;
	sf::RectangleShape _foreground;
	sf::Texture _textureForeground;
	sf::Text _instruction;
	sf::RectangleShape _carreInstruction;


	//Clock		
	sf::Clock _clock;
	sf::Time _time;
	sf::Clock _clockEnter;
	sf::Clock _clockSpawnClient;
	sf::Time _spawnInterval;
	sf::Clock _levelTime;
	sf::Time _levelMaxTime;
	sf::Clock _instructionTime;
	sf::Time _timeInstruction = seconds(20);

	//Audio
	sf::SoundBuffer _bufferSFXOrderMissed;
	sf::Sound _sfxOrderMissed;
	sf::SoundBuffer _bufferSFXOrderSend;
	sf::Sound _sfxOrderSend;

	sf::SoundBuffer _bufferSFXOrderPlace;
	sf::Sound _sfxOrderPlace;

	sf::SoundBuffer _bufferSFXEndLevel;
	sf::Sound _sfxEndLevel;

	bool bInstructionOver = false;
	bool bIsGameClosed = false;

public:
	Game();

	void initialiseWindow();
	void initialise(int mealType); // a faire
	void createStations(int amountOfStations, std::stack<int> availableIngredients);
	void createPlate(int position, int type, int nbFile);
	void Play(int mealType = 0); //BOUCLE PRINCIPALE
	void drawPizza(std::stack<Ingredient>& meal, int xPos, int yPos, sf::RenderWindow& window, bool fromScreen); //dessine une pizza
	void drawBurger(std::stack<Ingredient>& meal, int xPos, int yPos, sf::RenderWindow& window); //dessine un burger
	void InputHandling(sf::Event event, int mealType);
	void drawInstructions();
	void start(); //pour commencer, fait rien de particulier


	float GetCurrentTime();

	void finLevelMenu();
	void updateFinLevelMenu();
	void Reset();
	void mainMenu(); // menu principale, play, setting et quit 
	void optionMenu(); //changer les settings
	void setSpawnInterval(); // set le temps de spawn du client, difficulté est un multiplicateur de intervalle
	void createClients(int mealType = 0); //fait spawn un client aléatoirement dans une des 5 files
	void drawClientsMeals(); //se charge de dessiner tout les meals côté client appelé dans game.draw()
	bool interactionWithCook(std::stack<Ingredient>& cookMeal); //fait la comparaison avec le client et le cook et fait pop client et donne de l'argent au joueur
	void clientManager();
	void saveInfo();//sauvegarde le score du dernier niveau dans un fichier


	//Load ressources
	bool LoadBackground(int& level);
	bool LoadSounds();

	//Others
	void Draw();
};