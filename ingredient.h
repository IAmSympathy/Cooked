#pragma once

#include <stack>
#include <assert.h>
#include <iostream>
#include <SFML/Graphics.hpp>
#include "definitions.h"


//Ingredient sert a créer des ingrédients individuellement pour éventuellement faire un stack (un repas)
class Ingredient {
protected:
	int _ingredientValue = 0,
		value = 0,
		_xPos = 0,
		_yPos = 0;
	sf::Sprite _ingredient;
	sf::Texture* _spriteSheet = new sf::Texture; 
	std::map<int, sf::IntRect> _sprites; //tableau associatif

public:
	Ingredient(int ingredientValue);
	~Ingredient();

	void loadSpriteSheet(); //permet de load le spritesheet de tous les sprite recquis
	void loadSprite(); //load la table associatif (map)

	void rotate(int quadrant); //pour la pizza, le sprite tourne de bord pour rentrer dans le bon quart de pizza

	void setPosition(int xPos, int yPos); // met la position la ou souhaite 
	int getValue();

	void display(); //retourne le sprite qu'on veut afficher et met la texture
	void Draw(sf::RenderWindow& window);

	sf::Sprite& getSprite();

	bool operator!=(const Ingredient& autreI);
};

