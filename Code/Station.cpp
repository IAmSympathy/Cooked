/*====================================
// Filename : Station.cpp
// Description : This file contains the implementation of the Station class
//				 which contains the Station's spawning logic
// Author : Samy Larochelle
// Date : November 28th 2024
====================================*/
#include "Station.h"
#include <random>
using namespace sf;
using namespace std;

Station::Station()
{
	_rectSprite = IntRect(1, _ingredient * (_ingredient + STATION_HEIGHT), STATION_WIDTH, STATION_HEIGHT);
	LoadTextures();
}
Station::Station(int ingredient, int position, int nbFile)
{
	_position = position;
	if (position < 3) {
		_direction = LEFT;
		_station.setPosition(378, 540);
		_station.move(0, (position * STATION_HEIGHT * 1.2f) * SPRITE_SIZE_MULTIPLIER + 40);
	}
	else if (position < 9) {
		_direction = DOWN;
		_station.setPosition(532, 959);
		_station.move(((position - 3) * STATION_WIDTH * 1.2f) * SPRITE_SIZE_MULTIPLIER, 0);
	}
	else  if (position < 12) {
		_direction = RIGHT;
		_station.setPosition(1542, 710);
		_station.move(0, -1 * ((position - 10) * STATION_HEIGHT * 1.2f) * SPRITE_SIZE_MULTIPLIER);
	}

	if (ingredient == STATION_PLATE || ingredient == STATION_PLATE_SMALL) {
		_direction = UP;
		_station.setPosition((position - 21) * -206.55 + 1372, 405);
	}

	_ingredient = ingredient;
	_station.scale(SPRITE_SIZE_MULTIPLIER, SPRITE_SIZE_MULTIPLIER);

	_station.setSize(Vector2f(STATION_WIDTH, STATION_HEIGHT));
	_station.setOrigin(STATION_WIDTH / 2, STATION_HEIGHT / 2);
	_rectSprite = IntRect(1, _ingredient * STATION_HEIGHT + _ingredient + 1, STATION_WIDTH, STATION_HEIGHT);

	if (ingredient == STATION_PLATE) {
		_station.setSize(Vector2f(STATION_PLATE_WIDTH, STATION_HEIGHT));
		_station.setOrigin(STATION_PLATE_WIDTH / 2, STATION_HEIGHT / 2);
		_rectSprite = IntRect(1, 430, STATION_PLATE_WIDTH, STATION_HEIGHT);
	}
	else if (ingredient == STATION_PLATE_SMALL) {
		_station.setSize(Vector2f(STATION_PLATE_SMALL_WIDTH, STATION_PLATE_SMALL_HEIGHT));
		_station.setOrigin(STATION_PLATE_SMALL_WIDTH / 2, STATION_PLATE_SMALL_HEIGHT / 2);
		_rectSprite = IntRect(1, 463, STATION_PLATE_SMALL_WIDTH, STATION_PLATE_SMALL_HEIGHT);
	}

	//Change the sprite's orientation depending on where it is located on the counter
	switch (_direction) {
	case RIGHT:
		_station.scale(-1.f, 1.f);
		break;
	case DOWN:
		if (_ingredient == STEAK) { //If the station is a steak station, rotates it to the left and crops it to remove the 3D part of the sprite
			_station.setRotation(-90.f);
			_station.setSize(Vector2f(STEAK_STATION_DOWN_WIDTH, STATION_HEIGHT));
			_rectSprite.width = STEAK_STATION_DOWN_WIDTH;
		}
		else { // Randomly decides if the station is oriented towards the left or the right
			bool bRotated = rand() % (1 + 1 - 0) + 0;
			if (bRotated) {
				_station.scale(-1.f, 1.f);
			}
		}
	}

	LoadTextures();

	_nbFile = nbFile;
}


bool Station::LoadTextures()
{
	_station.setTextureRect(_rectSprite);
	if (!_texture->loadFromFile(STATION_SPRITESHEET_LOCATION))
		return false;
	_station.setTexture(_texture);
}


std::stack<Ingredient> Station::TakeContent()
{
	std::stack<Ingredient> tempContent = _content;
	while (!_content.empty())
		_content.pop();

	return tempContent;
}

void Station::AddContent(std::stack<Ingredient> stack)
{
	_sfxPlace.play();
	std::stack<Ingredient> tempStack1 = _content;
	std::stack<Ingredient> tempStack2 = stack;
	std::stack<Ingredient> resultat;

	while (!tempStack1.empty()) {
		resultat.push(tempStack1.top());
		tempStack1.pop();
	}

	while (!tempStack2.empty()) {
		resultat.push(tempStack2.top());
		tempStack2.pop();
	}

	std::stack<Ingredient> final;

	while (!resultat.empty()) {
		final.push(resultat.top());
		resultat.pop();
	}

	_content = final;
}

sf::RectangleShape Station::GetStation() const
{
	return _station;
}

int Station::GetIngredientID() const
{
	return _ingredient;
}

std::stack<Ingredient>& Station::GetPlateContent()
{
	return _content;
}

std::stack<Ingredient> Station::TakeTopPlateContent()
{

	std::stack<Ingredient> reversed;
	while (!_content.empty()) {
		reversed.push(_content.top());
		_content.pop();
	}

	std::stack<Ingredient> bottom;
	bottom.push(reversed.top());
	reversed.pop();

	while (!reversed.empty()) {
		_content.push(reversed.top());
		reversed.pop();
	}

	return bottom;
}

std::stack<Ingredient> Station::GetIngredientAsStack() const
{
	Ingredient ingredient(_ingredient);
	stack<Ingredient> stack;
	stack.push(ingredient);
	return stack;
}

int Station::GetDirection() const
{
	return _direction;
}

int Station::GetPosition() const
{
	return _position;
}

int Station::getStation() const
{
	return _nbFile;
}

int Station::getFile()
{
	return _nbFile;
}

sf::Vector2f Station::GetSpritePosition()
{
	return _station.getPosition();
}

void Station::Draw(sf::RenderWindow& window)
{
	window.draw(_station);
}

bool Station::operator==(const Station& other) const
{
	return _position == other._position
		&& _ingredient == other._ingredient;
}
