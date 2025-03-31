/*====================================
// Filename : Button.h
// Description : Class  button utilise dans la class menu pour creer des menu
// Author : Cedrik Caron
// Date : November 27th 2024
====================================*/

#pragma once
#include "SFML/Graphics.hpp"
#include "SFML/Audio.hpp"
#include "SFML/System/Clock.hpp"


class Button
{
private:
	enum state {
		GREY,
		HIGHLIGHTED
	};
	sf::Color grey = sf::Color(sf::Uint8(205), sf::Uint8(205), sf::Uint8(205), sf::Uint8(245));
	sf::Color texteGrey = sf::Color(sf::Uint8(80), sf::Uint8(80), sf::Uint8(80), sf::Uint8(255));
	state _state = GREY;
	int _value[3] = { 0,0,0 };//current value, min, max :utilise pour les buttons avec des valeur comme son

public:
	//Le texte est dans le publique sa evite de reimplementer tout les methods pour texte
	sf::Text _texte;// texte centre dans le rectangle du button
	sf::RectangleShape _rectangle;
	sf::Sound* _highlightedSound = new sf::Sound;//joue le son quant le state devient highlighted
	sf::Clock _timer,_timerValue;
	std::string _stringBase = "";
	

	Button();
	~Button();

	int getState();
	int getValue();
	int getMaxValue();

	void setValue(int value);
	void setState(int state);
	void setMinMaxValue(int minValue, int maxValue);
	int nextValue();//continue a la prochaine valeur du button

	void centerTexte();
	void draw(sf::RenderWindow& window);
};

