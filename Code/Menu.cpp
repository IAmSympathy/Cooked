#include "Menu.h"

Menu::Menu()
{
	//background image
	_backgroundTexture->loadFromFile("asset/mainMenu_notFinished.png");
	_background.setSize(sf::Vector2f(1920, 1080));
	_background.setTexture(_backgroundTexture);

	//font
	_font.loadFromFile("asset/font/Roboto-Black.ttf");

	//sound for the button

	//_sonButton->loadFromFile("asset/ButtonSound.wav");
	_sonButton->loadFromFile("asset/ButtonSound2.ogg");
}

Menu::~Menu()
{
	//delete tout les pointeurs
	delete _backgroundTexture;
	_backgroundTexture = nullptr;

	delete _sonButton;
	_sonButton = nullptr;

	delete[] _button;
	_button = nullptr;
}

void Menu::initializeMainMenu()
{
	_backgroundTexture->loadFromFile("asset/mainMenu_notFinished.png");
	//besoin de 3 button
	_nbButton = 3;
	_button = new Button[_nbButton];

	//menu state 0 pour le main menu
	_currentMenu = 0;

	//setup des buttons
	for (int i = 0; i < _nbButton; i++) {
		//position
		_button[i]._rectangle.setSize(sf::Vector2f(460, 100));
		_button[i]._rectangle.setPosition(sf::Vector2f(756, 420 + (i * 130)));
		//texte
		_button[i]._texte.setFont(_font);
		_button[i]._texte.setCharacterSize(75);
		//state
		_button[i].setState(0);
		//son
		_button[i]._highlightedSound->setBuffer(*_sonButton);
	}
	_button[0]._texte.setString("PLAY");
	_button[0].setState(1);
	_button[0].centerTexte();
	_button[1]._texte.setString("OPTION");
	_button[1].centerTexte();
	_button[2]._texte.setString("EXIT");
	_button[2].centerTexte();

}

//gere aussi la soundtrack qui joue
void Menu::initializeSettingMenu()
{

	//A changer le 
	_backgroundTexture->loadFromFile(GFX_MENU_BACKGROUND2);
	_background.setSize(sf::Vector2f(1920, 1080));
	_background.setTexture(_backgroundTexture);

	//besoin de 4 button
	_nbButton = 4;
	_button = new Button[_nbButton];

	//menu state 1 pour le menu option
	_currentMenu = 1;

	//setup des buttons
	for (int i = 0; i < _nbButton; i++) {
		//position
		_button[i]._rectangle.setSize(sf::Vector2f(460, 100));
		_button[i]._rectangle.setPosition(sf::Vector2f(756, 425 + (i * 130)));
		//texte
		_button[i]._texte.setFont(_font);
		_button[i]._texte.setCharacterSize(45);
		//state
		_button[i].setState(0);
		//son
		_button[i]._highlightedSound->setBuffer(*_sonButton);
	}
	//button difficulty
	_button[0].setState(1);
	_button[0].setMinMaxValue(1, 5);
	_button[0].setValue(3);
	_button[0]._stringBase = "DIFFICULTY  < ";
	_button[0]._texte.setString(_button[0]._stringBase + std::to_string(_button[0].getValue()) + " >");
	_button[0].centerTexte();

	//button son
	_button[1].setMinMaxValue(0, 1);
	_button[1].setValue(1);
	_button[1]._stringBase = "SOUND < ";
	_button[1]._texte.setString(_button[1]._stringBase + std::to_string(_button[1].getValue()) + " >");
	_button[1].centerTexte();

	//button soundtrack
	_button[2].setMinMaxValue(0, 4);
	_button[2].setValue(0);
	_button[2]._stringBase = "SOUNDTRACK < ";
	_button[2]._texte.setString(_button[2]._stringBase + std::to_string(_button[2].getValue()) + " >");
	_button[2].centerTexte();

	//button return
	_button[3]._stringBase = "RETURN";
	_button[3]._texte.setString(_button[3]._stringBase);
	_button[3].centerTexte();
}

void Menu::initializeEndLevelMenu()
{
	_backgroundTexture->loadFromFile(GFX_MENU_END_BACKGROUND);
	_background.setSize(sf::Vector2f(1920, 1080));
	_background.setTexture(_backgroundTexture);

	_nbButton = 4;
	_button = new Button[_nbButton];

	//menu state 2 pour la fin de level
	_currentMenu = 2;

	//setup des buttons
	for (int i = 0; i < _nbButton; i++) {
		//position
		_button[i]._rectangle.setSize(sf::Vector2f(460, 100));
		_button[i]._rectangle.setPosition(sf::Vector2f(756, 420 + (i * 130)));
		//texte
		_button[i]._texte.setFont(_font);
		_button[i]._texte.setCharacterSize(75);
		//state
		_button[i].setState(0);
		//son
		_button[i]._highlightedSound->setBuffer(*_sonButton);
	}

	//button next
	_button[0].setState(1);
	_button[0]._stringBase = "NEXT";
	_button[0]._texte.setString(_button[0]._stringBase);
	_button[0].centerTexte();

	//Le score en cash
	_button[1].setState(1);
	_button[1]._stringBase = "0$";
	_button[1]._texte.setString(_button[1]._stringBase);
	_button[1].centerTexte();

	//Client servie
	_button[2].setState(1);
	_button[2]._stringBase = "0";
	_button[2]._texte.setString(_button[2]._stringBase);
	_button[2].centerTexte();

	//Client perdu de patience
	_button[3].setState(1);
	_button[3]._stringBase = "0";
	_button[3]._texte.setString(_button[3]._stringBase);
	_button[3].centerTexte();
}

int Menu::getCurrentMenu()
{
	return _currentMenu;
}

int Menu::getCurrentButton()
{
	return _currentButton;
}

int Menu::getCurrentButtonValue()
{
	return _button[_currentButton].getValue();
}

int Menu::getButtonValue(int buttonNumber)
{
	return _button[buttonNumber].getValue();
}

//utilise seulement pour le menu apres un level
void Menu::setScore(int score)
{
	if (_currentMenu == 2) {//verificaiton qu'on est dans le menu stat
		_button[1]._stringBase = "Cash: " + std::to_string(score);
		_button[1]._texte.setString(_button[1]._stringBase);
		_button[1].centerTexte();
	}
}

void Menu::setClientServie(int nbClient)
{
	if (_currentMenu == 2) {//verificaiton qu'on est dans le menu stat
		_button[2]._stringBase = "Servie: " + std::to_string(nbClient);
		_button[2]._texte.setString(_button[2]._stringBase);
		_button[2].centerTexte();
	}
}

void Menu::setClientPerdu(int clientPerdu)
{
	if (_currentMenu == 2) {//verificaiton qu'on est dans le menu stat
		_button[3]._stringBase = "Perdu: " + std::to_string(clientPerdu);
		_button[3]._texte.setString(_button[3]._stringBase);
		_button[3].centerTexte();
	}
}

void Menu::buttonDown()
{
	if (_currentButton < _nbButton - 1 && _button[_currentButton]._timer.getElapsedTime().asSeconds() >= 0.2) {
		if (_currentMenu != 2) {//un jack pour evite de pouvoir bouger dans le menu next level aka _currentMenu = 2
			_button[_currentButton].setState(0);
			_currentButton += 1;
			_button[_currentButton].setState(1);
		}

	}
}

void Menu::buttonUp()
{
	if (_currentButton != 0 && _button[_currentButton]._timer.getElapsedTime().asSeconds() >= 0.2) {
		_button[_currentButton].setState(0);
		_currentButton -= 1;
		_button[_currentButton].setState(1);
	}
}

int Menu::buttonEnter()
{
	if (_button[_currentButton].getMaxValue() > 0) {//si le boutton a une valeur augment la valeur et update la valeur affiche
		_button[_currentButton].nextValue();
		_button[_currentButton]._texte.setString(_button[_currentButton]._stringBase + std::to_string(_button[_currentButton].getValue()) + " >");
	}
	return _currentButton;

}


void Menu::draw(sf::RenderWindow& window)//call in the draw phase need the current window
{
	//draw backgroud
	window.draw(_background);

	//draw buttons
	for (int i = 0; i < _nbButton; i++) {
		window.draw(_button[i]._rectangle);
		window.draw(_button[i]._texte);
	}

	window.draw(_instruction);
}
