/*====================================
// Filename : Station.h
// Description : This file contains the definitions of the Station class
//				 which contains the Station's XXXXX
// Author : Samy Larochelle
// Date : November 28th 2024
====================================*/
#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <iostream>
#include <stack>
#include "Ingredient.h"
#include "definitions.h"



#define STEAK_STATION_DOWN_WIDTH 36

class Station
{
private:
	int _ingredient = STEAK;
	int _position = 0;
	int _direction = LEFT;
	int _nbFile = UNDEFINED_VALUE;

	//Plate
	std::stack<Ingredient> _content;


	sf::RectangleShape _station;
	sf::Texture* _texture = new sf::Texture;
	sf::IntRect _rectSprite;


	sf::SoundBuffer _bufferSFXPlace;
	sf::Sound _sfxPlace;

public:
	//Constructors
	Station();
	Station(int ingredient, int position, int nbFile = 0);


	//Load ressources
	bool LoadTextures();

	//PLATE
	std::stack<Ingredient> TakeContent();
	void AddContent(std::stack<Ingredient> stack);

	//Getters
	sf::RectangleShape GetStation() const;
	int GetIngredientID() const;
	std::stack<Ingredient>& GetPlateContent();
	std::stack<Ingredient> TakeTopPlateContent();
	std::stack<Ingredient> GetIngredientAsStack() const;
	int GetDirection() const;
	int GetPosition() const;
	int getStation() const;
	int getFile();
	sf::Vector2f GetSpritePosition();

	//Others
	void Draw(sf::RenderWindow& window);

	bool operator==(const Station& other) const;
};

