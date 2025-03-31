#include "UserInterface.h"

UserInterface::UserInterface()
{
	LoadFont();

	_levelLabel.setString("SHIFT");
	_levelLabel.setFont(font);
	_levelLabel.setPosition(1690, 90);
	_levelLabel.setCharacterSize(32);

	_level.setString("00");
	_level.setFont(font);
	_level.setPosition(1740, 140);
	_level.setCharacterSize(32);

	_timeLabel.setString("TIME");
	_timeLabel.setFont(font);
	_timeLabel.setPosition(1700, 350);
	_timeLabel.setCharacterSize(32);

	_time.setString("03:00");
	_time.setFont(font);
	_time.setPosition(1685, 400);
	_time.setCharacterSize(32);

	_inventoryLabel.setString("HELD");
	_inventoryLabel.setFont(font);
	_inventoryLabel.setPosition(23, 90);
	_inventoryLabel.setCharacterSize(32);


	_currentStation.setString("STEAK");
	_currentStation.setFont(font);
	_currentStation.setPosition(23, 600);
	_currentStation.setCharacterSize(32);

	_currentStationLabel.setString("STATION");
	_currentStationLabel.setFont(font);
	_currentStationLabel.setPosition(23, 840);
	_currentStationLabel.setCharacterSize(32);
	LoadTextures();
	SetCurrentStation(14);
	_station.setPosition(23, 736);
	_station.scale(5, 5);
}

UserInterface::~UserInterface()
{
	delete _currentStationTexture;
	_currentStationTexture = nullptr;
}

bool UserInterface::LoadTextures()
{
	_station.setTextureRect(_rectSprite);
	if (!_currentStationTexture->loadFromFile(STATION_SPRITESHEET_LOCATION))
		return false;
	_station.setTexture(_currentStationTexture);

}

bool UserInterface::LoadFont()
{
	if (!font.loadFromFile(FONT_LOCATION))
		return false;
}

void UserInterface::SetLevel(int level)
{
	string levelText = "0";
	if (level > 9)
		_level.setString(to_string(level));
	else {
		levelText.append(to_string(level));
		_level.setString(levelText);
	}
}

void UserInterface::SetCurrentStation(int ingredient)
{
	_rectSprite = IntRect(1, ingredient * STATION_HEIGHT + ingredient + 1, STATION_WIDTH, STATION_HEIGHT);
	_station.setSize(Vector2f(STATION_WIDTH, STATION_HEIGHT));
	_station.setOrigin(0, STATION_HEIGHT / 2);

	switch (ingredient) {
	case 0:
		_currentStation.setString("STEAK");
		break;
	case 1:
		_currentStation.setString("BREAD");
		break;
	case 2:
		_currentStation.setString("TOMATO");
		break;
	case 3:
		_currentStation.setString("LETTUCE");
		break;
	case 4:
		_currentStation.setString("ONION");
		break;
	case 5:
		_currentStation.setString("MUSHROOM");
		break;
	case 6:
		_currentStation.setString("PEPPER");
		break;
	case 7:
		_currentStation.setString("PEPPERONI");
		break;
	case 8:
		_currentStation.setString("CHEESE");
		break;
	case 9:
		_currentStation.setString("DOUGH");
		break;
	case 10:
		_currentStation.setString("OLIVE");
		break;
	case 11:
		_currentStation.setString("CHEESE");
		break;
	case 12:
		_currentStation.setString("TRASH");
		break;
	case 13:
		_currentStation.setString("CUSTOMER");
		_station.setSize(Vector2f(STATION_PLATE_WIDTH, STATION_HEIGHT));
		_rectSprite = IntRect(1, 430, STATION_PLATE_WIDTH, STATION_HEIGHT);
		break;
	case 14:
		_currentStation.setString("CUSTOMER");
		_station.setSize(Vector2f(STATION_PLATE_SMALL_WIDTH, STATION_PLATE_SMALL_HEIGHT));
		_rectSprite = IntRect(1, 463, STATION_PLATE_SMALL_WIDTH, STATION_PLATE_SMALL_HEIGHT);
		_station.setOrigin(0, STATION_PLATE_SMALL_HEIGHT / 2);
		break;
	default:
		_currentStation.setString("NO");
		_station.setSize(Vector2f(0, 0));
	}
	_station.setTextureRect(_rectSprite);
}

void UserInterface::UpdateTime(float currentTime)
{
	int nbMin = currentTime / 60;
	int nbSeconds = currentTime - 60 * nbMin;

	string secondes = "0";

	if (nbSeconds < 10)
		secondes.append(to_string(nbSeconds));
	else
		secondes = to_string(nbSeconds);

	_time.setString("0" + to_string(nbMin) + ":" + secondes);
}

void UserInterface::draw(sf::RenderWindow& window)
{
	window.draw(_levelLabel);
	window.draw(_level);
	window.draw(_timeLabel);
	window.draw(_time);
	window.draw(_inventoryLabel);
	window.draw(_currentStationLabel);
	window.draw(_currentStation);
	window.draw(_station);
}
