/*====================================
// Filename : Client.h
// Description : Class  Client contient tout les informations pour creer des clients
// Author : Cedrik Caron
// Date : November 29th 2024
====================================*/

#pragma once
#include "SFML/Graphics.hpp"
#include "SFML/Audio.hpp"
#include "definitions.h"
#include "commande.h"

#define CLIENT_WIDTH 40
#define CLIENT_HEIGHT 48


class Client
{
private:
	enum state {
		CONTENT,
		NEUTRE,
		FACHE
	};
	state _currentState = CONTENT;
	sf::Clock _horlogePatienceEnSeconde;
	float _tempsPatienceEnSeconde = 0;
	Order _commandeDeClient;
	int _nbFile = 0;

	//sprite
	sf::RectangleShape _client;
	sf::Texture* _texture = new sf::Texture;
	sf::IntRect _rectSprite[6];

	//aniamtion
	sf::SoundBuffer* _newClientBuffer = new sf::SoundBuffer;
	sf::Sound* _newClient = new sf::Sound;
	sf::Clock _clock;
	sf::Time _time;

	int _SpriteXLocation = 1;
	int _SpriteYLocation = 1;
	int _mealType = UNDEFINED_VALUE;
	int _currentFrameIndex = 0;
	bool _bFirstForwardCycle = true;
	bool _bFirstBackwardCycle = false;
	bool _bSecondForwardCycle = false;
	bool _bSecondBackwardCycle = false;

public:
	Client();
	Client(int mealType);
	Client(float tempsPatienceEnSeconde, int position, int mealType = 0);//temp de patience, commande, la satation de 1 a 5
	~Client();

	void setTempPatienceEnSeconde(float temps);
	void setCommande(Order commande);
	void setPosition(int position);

	float getTempsRestant();//donne le temps restant avant que le client perde patiance
	Order& getCommande();
	int getPosition();
	int GetMealType();


	void animation();
	void loadTexture();
	void playSound();

	void spawn();
	void updateClient();//caller a tout les frames
	void draw(sf::RenderWindow& window);

};

