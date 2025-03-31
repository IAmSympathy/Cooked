#pragma once

#include <stack>
#include <assert.h>
#include <iostream>
#include "ingredient.h"

//les Orders determine aléatoirement la commande du client
class Order
{
private:
	int _reward = 0; //recompense lorsqu'on finit la commande
	int _typeOfMeal = UNDEFINED_VALUE; // 1= pizza, 2=hamburger, 0= undefined
	std::stack<Ingredient> _meal;
	int allPizzaDressing[PIZZA_DRESSING_CHOICES] = { ONION, PEPPER, PEPPERONI, OLIVE, MUSHROOM }; //a changer si on rajouter un ingredient
	int allHumbergerDressing[HAMBURGER_DRESSING_CHOICES] = { TOMATO, LETTUCE, CHEESE_SLICE, STEAK }; // a changer si on rajoute un ingredient

public:
	Order();
	void initialise(int typeOfMeal = 0);
	void createMeal(); //redirige vers pizza ou hamburger 
	void createPizza(); //remplit la pile _meal
	void createHamburger(); // remplit la pile _meal
	void pushRandomPizzaDressing(); //remplit de facon random les dressings du _meal
	void pushRandomHamburgerDressing(); //remplit de facon random les dressings du _meal
	void setReward(); //ajuste le prix en fonction du nombre de dressings
	void setMealType(int typeOfMeal = 0);
	int getMealType();
	int getReward() const;
	int randomize(int max, int min = 0); //simple fonction de randomize

	std::stack<Ingredient>& display(); //va etre utilisé pour display dans game

	const bool compare(std::stack<Ingredient>& autrePile); // compare la commande du client avec 
	~Order();
};