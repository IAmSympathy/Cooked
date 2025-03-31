#include "Client.h"

Client::Client()
{
}

Client::Client(int mealType)
{
	assert(mealType == UNDEFINED_VALUE || mealType == PIZZA || mealType == HAMBURGER);
	_mealType = _mealType;
	_commandeDeClient.initialise(mealType);
	loadTexture();

}

Client::Client(float tempsPatienceEnSeconde, int position, int mealType)//temp de patience, commande, la satation de 1 a 5
{
	_nbFile = position;
	_tempsPatienceEnSeconde = tempsPatienceEnSeconde;
	_mealType = _mealType;
	_commandeDeClient.initialise(mealType);

	_newClientBuffer->loadFromFile(SFX_NEW_ORDER_LOCATION);
	_newClient->setBuffer(*_newClientBuffer);

	_client.scale(SPRITE_SIZE_MULTIPLIER, SPRITE_SIZE_MULTIPLIER);
	_client.setSize(sf::Vector2f(CLIENT_WIDTH, CLIENT_HEIGHT));
	_client.setOrigin(CLIENT_WIDTH / 2, CLIENT_HEIGHT / 2);

	loadTexture();
}

Client::~Client()
{
}

void Client::setTempPatienceEnSeconde(float temps)
{
	_tempsPatienceEnSeconde = temps;
}

void Client::setCommande(Order commande)
{
	_commandeDeClient = commande;
}

void Client::setPosition(int position)
{
	_nbFile = position;
}

float Client::getTempsRestant()
{
	return _tempsPatienceEnSeconde - _horlogePatienceEnSeconde.getElapsedTime().asSeconds();
}

Order& Client::getCommande()
{
	return _commandeDeClient;
}

int Client::getPosition()
{
	return _nbFile;
}

int Client::GetMealType()
{
	return _mealType;
}

void Client::draw(sf::RenderWindow& window)
{
	window.draw(_client);
}



void Client::animation()
{
	_time = _clock.getElapsedTime();

	//Idle animation - if the animation is over it will repeat
	if (_time.asMilliseconds() >= 450.0f)
	{
		_client.setTextureRect(_rectSprite[_currentFrameIndex]);
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
		_client.setTextureRect(_rectSprite[_currentFrameIndex]);

		_clock.restart();
	}
}


void Client::loadTexture()
{


	for (int i = 0; i < 6; i++)
	{
		_rectSprite[i] = sf::IntRect(i + _SpriteXLocation + CLIENT_WIDTH * i, _SpriteYLocation, CLIENT_WIDTH, CLIENT_HEIGHT);
	}

	_client.setTextureRect(_rectSprite[0]);
	if (!_texture->loadFromFile(CLIENT_SPRITESHEET_LOCATION))
		return;
	_client.setTexture(_texture);
}

void Client::playSound()
{
	_newClient->play();
}

void Client::spawn()
{
	_newClient->play();
	_horlogePatienceEnSeconde.restart();
	_client.setPosition(sf::Vector2f(POSITION_CLIENT_X + _nbFile * ESPACE_ENTRE_STATION_CLIENT, POSITION_CLIENT_Y));
}

void Client::updateClient()
{
	animation();
	if (getTempsRestant() < _tempsPatienceEnSeconde / 3.0) {
		_SpriteYLocation = 99;
		_currentState = FACHE;
	}
	else if (getTempsRestant() < (_tempsPatienceEnSeconde / 3.0) * 2) {
		_SpriteYLocation = 50;
		_currentState = NEUTRE;
	}


	for (int i = 0; i < 6; i++)
	{
		_rectSprite[i] = sf::IntRect(i + _SpriteXLocation + CLIENT_WIDTH * i, _SpriteYLocation, CLIENT_WIDTH, CLIENT_HEIGHT);
	}
	_client.setTextureRect(_rectSprite[_currentFrameIndex]);
}
