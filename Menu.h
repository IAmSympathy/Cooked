/*====================================
// Filename : Button.h
// Description : Class Menu initialise les menu: main menu, option et menu de fin.
// Author : Cedrik Caron
// Date : November 27th 2024
====================================*/

#pragma once
#include "Button.h"
#include "SoundtrackManager.h"


class Menu
{
private:
	//state
	int _currentMenu = 0;//0 main menu, 1 option, 2 end screen
	int _currentButton = 0;

	//le text pour les instructions dans le main menu
	sf::Text _instruction;

	//background + texture
	sf::RectangleShape _background;
	sf::Texture* _backgroundTexture = new sf::Texture;
	sf::Font _font;

	//button
	Button* _button = nullptr;//pointeur vers le tableau de button pour les differents menu
	int _nbButton = 0;

	//son
	sf::SoundBuffer* _sonButton = new sf::SoundBuffer;

public:
	Menu();
	~Menu();

	void initializeMainMenu();
	void initializeSettingMenu();
	void initializeEndLevelMenu();

	int getCurrentMenu();
	int getCurrentButton();
	int getCurrentButtonValue();
	int getButtonValue(int buttonNumber);

	void setScore(int score);
	void setClientServie(int nbClient);
	void setClientPerdu(int clientPerdu);

	void buttonDown();
	void buttonUp();
	int buttonEnter();
	void draw(sf::RenderWindow& window);//put in the render call
};

