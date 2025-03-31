#include "ingredient.h"

Ingredient::Ingredient(int ingredientValue)
{
	assert(ingredientValue >= 0 && ingredientValue <= TOTAL_CONDIMENTS_AMOUNT);
	_ingredientValue = ingredientValue;
	loadSpriteSheet();
	loadSprite();
	display();
}

void Ingredient::loadSpriteSheet()
{

	if (!_spriteSheet->loadFromFile(RECIPES_SPRITESHEET_LOCATION)) {
		std::cout << "Error: Could not load the sprite sheet!" << std::endl;
	}
}

void Ingredient::loadSprite()
{
	_sprites[UNDEFINED_VALUE] = sf::IntRect(0, 0, 0, 0);
	_sprites[PIZZA_DOUGH] = sf::IntRect(1, 1, 26, 24);
	_sprites[TOMATO_SAUCE] = sf::IntRect(1, 26, 26, 24);
	_sprites[CHEESE] = sf::IntRect(1, 51, 26, 24);
	_sprites[PEPPERONI] = sf::IntRect(1, 76, 26, 24);
	_sprites[OLIVE] = sf::IntRect(1, 101, 26, 24);
	_sprites[ONION] = sf::IntRect(1, 126, 26, 24);
	_sprites[MUSHROOM] = sf::IntRect(1, 151, 26, 24);
	_sprites[PEPPER] = sf::IntRect(1, 176, 26, 24);
	_sprites[BREAD] = sf::IntRect(28, 22, 20, 4);
	_sprites[BREADBOTTOM] = sf::IntRect(28, 1, 20, 5);
	_sprites[CHEESE_SLICE] = sf::IntRect(28, 7, 20, 2);
	_sprites[STEAK] = sf::IntRect(28, 13, 20, 4);
	_sprites[TOMATO] = sf::IntRect(28, 10, 20, 2);
	_sprites[LETTUCE] = sf::IntRect(28, 18, 20, 3);
}

void Ingredient::rotate(int quadrant)
{
	switch (quadrant) {
	case 1:
		break;
	case 2:
		_xPos += 8 * INGREDIENT_MULTIPLIER;
		break;
	case 3:
		_yPos += 8 * INGREDIENT_MULTIPLIER;
		break;
	case 4:
		_xPos += 8 * INGREDIENT_MULTIPLIER;
		_yPos += 8 * INGREDIENT_MULTIPLIER;
		break;
	default:
		break;
	}
	setPosition(_xPos, _yPos);
}



void Ingredient::setPosition(int xPos, int yPos)
{
	//assert(xPos >= 0 && xPos <= 1080 && yPos >= 0 && yPos <= 1920);
	_xPos = xPos;
	_yPos = yPos;
	_ingredient.setPosition(_xPos, _yPos);

}

int Ingredient::getValue()
{
	return _ingredientValue;
}



void Ingredient::display()
{
	if (_sprites.find(_ingredientValue) != _sprites.end()) {
		_ingredient.setTextureRect(_sprites[_ingredientValue]);
		_ingredient.setTexture(*_spriteSheet);
		if (_ingredientValue == CHEESE_SLICE || _ingredientValue == TOMATO) {
			_ingredient.setScale(SPRITE_SIZE_MULTIPLIER, SPRITE_SIZE_MULTIPLIER * 1.3);
		}
		else if (_ingredientValue == BREAD || _ingredientValue == BREADBOTTOM) {
			_ingredient.setScale(SPRITE_SIZE_MULTIPLIER / 1.2, SPRITE_SIZE_MULTIPLIER);
		}
		//else if (_ingredientValue == )
		else {
			_ingredient.setScale(SPRITE_SIZE_MULTIPLIER, SPRITE_SIZE_MULTIPLIER);//3, 3
		}


	}
}

void Ingredient::Draw(sf::RenderWindow& window)
{
	window.draw(_ingredient);
}

sf::Sprite& Ingredient::getSprite()
{
	return _ingredient;
}

bool Ingredient::operator!=(const Ingredient& autreI)
{
	return _ingredientValue != autreI._ingredientValue;
}

Ingredient::~Ingredient()
{
	_ingredientValue = 0;
	value = 0;
	_xPos = 0;
	_yPos = 0;
}
