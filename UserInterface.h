#pragma once
#include "SFML/Graphics.hpp"
#include "SFML/Audio.hpp"
#include "definitions.h"

using namespace::std;
using namespace::sf;

class UserInterface
{
private:
	//Attributes
	sf::Font font;

	sf::Text _level;
	sf::Text _levelLabel;

	sf::Text _inventoryLabel;
	sf::Texture _inventoryContent;

	sf::Text _currentStation;
	sf::Text _currentStationLabel;

	sf::RectangleShape _station;
	sf::Texture* _currentStationTexture = new sf::Texture;
	sf::IntRect _rectSprite;


	sf::Text _time;
	sf::Text _timeLabel;
public:
	UserInterface();
	~UserInterface();

	bool LoadTextures();
	bool LoadFont();

	//Setters
	void SetLevel(int level);
	void SetCurrentStation(int ingredient);
	void UpdateTime(float currentTime);

	void draw(sf::RenderWindow& window);
};

