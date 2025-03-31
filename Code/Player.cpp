/*====================================
// Filename : Player.h
// Description : This file contains the implementation of the Player class
//				 which contains the player's movements, animations
// Author : Samy Larochelle
// Date : November 28th 2024
====================================*/

#include "Player.h"
using namespace sf;
using namespace std;

Player::Player()
{
	_player.scale(SPRITE_SIZE_MULTIPLIER, SPRITE_SIZE_MULTIPLIER);
	_player.setPosition(WINDOW_SCREEN_WIDTH / 2, WINDOW_SCREEN_HEIGHT / 2 + 150);
	_player.setSize(Vector2f(PLAYER_WIDTH, PLAYER_HEIGHT));
	_player.setOrigin(PLAYER_WIDTH / 2, PLAYER_HEIGHT / 2);

	LoadTextures();
	LoadSounds();
}

void Player::Move(sf::Vector2f stationPosition, int direction)
{
	ChangeDirection(direction);
	switch (direction) {

	case LEFT:
		_player.setPosition(stationPosition.x + 110, stationPosition.y - 20);
		break;
	case RIGHT:
		_player.setPosition(stationPosition.x - 110, stationPosition.y - 20);
		break;
	case DOWN:
		_player.setPosition(stationPosition.x, stationPosition.y - 100);
		break;
	case UP:
		_player.setPosition(stationPosition.x, stationPosition.y + 50);
		break;
	}
}

bool Player::LoadTextures()
{

	for (int i = 0; i < 6; i++)
	{
		_rectSprite[i] = IntRect(i + _SpriteXLocation + PLAYER_WIDTH * i, _SpriteYLocation, PLAYER_WIDTH, PLAYER_HEIGHT);
	}

	_player.setTextureRect(_rectSprite[0]);
	if (!_texture.loadFromFile(PLAYER_SPRITESHEET_LOCATION))
		return false;
	_player.setTexture(&_texture);
}

bool Player::LoadSounds()
{
	if (!_bufferSFXTrash.loadFromFile(SFX_PLAYER_TRASH_LOCATION))
		return false;

	if (!_bufferSFXInteract.loadFromFile(SFX_PLAYER_INTERACT_LOCATION))
		return false;

	_sfxTrash.setBuffer(_bufferSFXTrash);
	_sfxInteract.setBuffer(_bufferSFXInteract);
}

void Player::ChangeDirection(int direction)
{
	switch (direction)
	{
	case DOWN:
		_SpriteYLocation = 1;
		break;
	case UP:
		_SpriteYLocation = 119;
		break;
	case LEFT:
		_SpriteYLocation = 60;
		break;
	case RIGHT:
		_SpriteYLocation = 178;
		break;
	}
	for (int i = 0; i < 6; i++)
	{
		_rectSprite[i] = IntRect(i + _SpriteXLocation + PLAYER_WIDTH * i, _SpriteYLocation, PLAYER_WIDTH, PLAYER_HEIGHT);
	}
	_player.setTextureRect(_rectSprite[_currentFrameIndex]);
}

void Player::IdleAnimation()
{
	_time = _clock.getElapsedTime();

	//Idle animation - if the animation is over it will repeat
	if (_time.asMilliseconds() >= 450.0f)
	{
		_player.setTextureRect(_rectSprite[_currentFrameIndex]);
		if (_currentFrameIndex == 2 && _bFirstForwardCycle) { //If the first forward animation cycle is over (3 first frames), starts the first backward animation cycle
			_bFirstForwardCycle = false;
			_bFirstBackwardCycle = true;
		}
		if (_currentFrameIndex == 0 && _bFirstBackwardCycle) { // If the first backward animation cycle is over (back to frame 0), starts the second forward cycle (sets the current frame to frame 2)
			_bFirstBackwardCycle = false;
			_bSecondForwardCycle = true;
			_currentFrameIndex = 2;
		}

		if (_currentFrameIndex == 5 && _bSecondForwardCycle) { //If the second forward animation cycle is over (3 first frames), starts the first backward animation cycle
			_bSecondForwardCycle = false;
			_bSecondBackwardCycle = true;
		}
		if (_currentFrameIndex == 3 && _bSecondBackwardCycle) { // If the second backward animation cycle is over (back to frame 3), restart (starts first animation cycle and sets the current frame to 0)
			_bSecondBackwardCycle = false;
			_bFirstForwardCycle = true;
			_currentFrameIndex = -1;
		}

		//Moves the current frame index depending on the cycle type
		if (_bFirstForwardCycle || _bSecondForwardCycle) // Foward Cycle
			_currentFrameIndex++;
		else if (_bFirstBackwardCycle || _bSecondBackwardCycle) { // Backward Cycle
			_currentFrameIndex--;
		}
		_player.setTextureRect(_rectSprite[_currentFrameIndex]);

		_clock.restart();
	}
}

std::stack<Ingredient> Player::TrashHeldMeal(bool bWithSound)
{
	if (bWithSound)
		_sfxTrash.play();
	std::stack<Ingredient> heldMeal = _heldMeal;
	while (!_heldMeal.empty())
		_heldMeal.pop();
	return heldMeal;
}

void Player::PushToHeldMeal(std::stack<Ingredient> stack)
{
	_sfxInteract.play();

	if (_heldMeal.empty())
		_heldMeal = stack;
}

std::stack<Ingredient>& Player::GetHeldMeal()
{
	return _heldMeal;
}

void Player::Draw(sf::RenderWindow& window)
{
	window.draw(_player);


	if (!_heldMeal.empty()) {
		Ingredient temp(_heldMeal.top().getValue());
		temp.getSprite().setScale(SPRITE_SIZE_MULTIPLIER * 2.4, SPRITE_SIZE_MULTIPLIER * 2.4);
		temp.setPosition(50, 160);
		temp.Draw(window);
	}
}
