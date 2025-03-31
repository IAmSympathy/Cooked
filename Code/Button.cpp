#include "Button.h"

Button::Button() {

}

Button::~Button()
{
	delete _highlightedSound;
	_highlightedSound = nullptr;
}

int Button::getState()
{
	return _state;
}

int Button::getValue()
{
	return _value[0];
}

void Button::setState(int state)
{
	if (state == GREY) {
		_state = GREY;
		_texte.setFillColor(texteGrey);
		_rectangle.setFillColor(grey);
	}
	else {
		_timer.restart();
		_state = HIGHLIGHTED;
		_texte.setFillColor(sf::Color::Black);
		_rectangle.setFillColor(sf::Color::White);
		_highlightedSound->play();
	}
}

void Button::setMinMaxValue(int minValue, int maxValue)
{
	_value[0] = minValue;//commence la valeur minimum possible
	_value[1] = minValue;//min value possible
	_value[2] = maxValue;//la maximum valeur possible;
}

int Button::getMaxValue()
{
	return _value[2];
}

void Button::setValue(int value)
{
	_value[0] = value;
}

int Button::nextValue()
{
	if (_timerValue.getElapsedTime().asSeconds() > 0.2) {
		if (_value[0] != _value[2]) {
			_value[0] += 1;
		}
		else {
			_value[0] = _value[1];
		}
		_timerValue.restart();
	}
	return _value[0];
}

void Button::centerTexte()
{
	_texte.setPosition(_rectangle.getPosition().x + (_rectangle.getSize().x / 2) - (_texte.getLocalBounds().width / 2), //centrer position X
		_rectangle.getPosition().y + (_rectangle.getSize().y / 2)  - (_texte.getLocalBounds().height));//centrer position Y
}


void Button::draw(sf::RenderWindow& window)
{
	window.draw(_rectangle);
	window.draw(_texte);
}




