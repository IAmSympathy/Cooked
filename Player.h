/*====================================
// Filename : Player.h
// Description : This file contains the definitions of the Player class
//				 which contains the player's movements and animations
// Author : Samy Larochelle
// Date : November 28th 2024
====================================*/
#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <iostream>
#include "definitions.h"
#include "Station.h"
#include "Ingredient.h"
#include <stack>

#define PLAYER_WIDTH 40
#define PLAYER_HEIGHT 58

class Player
{
private:
	//Attributes
	int _currentDirection = DOWN;
	Station _currentStation;
	std::stack<Ingredient> _heldMeal;

	//Sprite
	sf::RectangleShape _player;
	sf::Texture _texture;
	sf::IntRect _rectSprite[6];

	//Animation Handling
	const int _SpriteXLocation = 1;
	int _SpriteYLocation = 1;
	int _currentFrameIndex = 0;
	bool _bFirstForwardCycle = true;
	bool _bFirstBackwardCycle = false;
	bool _bSecondForwardCycle = false;
	bool _bSecondBackwardCycle = false;

	//Audio
	sf::SoundBuffer _bufferSFXTrash;
	sf::SoundBuffer _bufferSFXInteract;
	sf::Sound _sfxTrash;
	sf::Sound _sfxInteract;

	//Clock		
	sf::Clock _clock;
	sf::Time _time;

public:
	Player();

	//Actions
	void Move(sf::Vector2f stationPosition, int direction);
	void PlaySound(int type);

	//Load ressources
	bool LoadTextures();
	bool LoadSounds();

	//Animations
	void ChangeDirection(int direction);
	void IdleAnimation();

	//Setters
	std::stack<Ingredient> TrashHeldMeal(bool bWithSound);
	void PushToHeldMeal(std::stack<Ingredient> stack);

	//Getters
	std::stack<Ingredient>& GetHeldMeal();


	//Others
	void Draw(sf::RenderWindow& window);
};

