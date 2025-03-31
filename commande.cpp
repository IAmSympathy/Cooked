#include "commande.h"

Order::Order()
{
}

void Order::initialise(int typeOfMeal)
{
	assert(_typeOfMeal == UNDEFINED_VALUE || _typeOfMeal == PIZZA || _typeOfMeal == HAMBURGER);
	setMealType(typeOfMeal);
	createMeal();

}

void Order::createMeal()
{
	assert(_typeOfMeal == UNDEFINED_VALUE || _typeOfMeal == PIZZA || _typeOfMeal == HAMBURGER);

	switch (_typeOfMeal) {
	case UNDEFINED_VALUE:
		_typeOfMeal = randomize(PIZZA, HAMBURGER);
		createMeal();
		break;
	case PIZZA:
		createPizza();
		break;
	case HAMBURGER:
		createHamburger();
		break;
	}

}

void Order::createPizza()
{
	_meal.push(Ingredient(PIZZA_DOUGH));
	bool bHasTomatoSauce = rand() % 2;
	if (bHasTomatoSauce)
		_meal.push(Ingredient(TOMATO_SAUCE));
	bool bHasCheese = rand() % 2;
	if (bHasCheese)
		_meal.push(CHEESE);

	pushRandomPizzaDressing();

	setReward();

}

void Order::createHamburger()
{
	_meal.push(Ingredient(BREADBOTTOM));

	pushRandomHamburgerDressing();

	_meal.push(Ingredient(BREAD));

	setReward();
}

void Order::pushRandomPizzaDressing()
{
	assert(_typeOfMeal == PIZZA);
	int randomNumberDressing = rand() % MAX_DRESSING_PIZZA + 1;
	int randomDressing = 02;

	for (int i = 0; i < randomNumberDressing; i++) {
		randomDressing = randomize(PIZZA_DRESSING_CHOICES);
		Ingredient temp(allPizzaDressing[randomDressing]);
		temp.rotate(i);
		_meal.push(temp);
		_meal.top().rotate(i);
	}

}

void Order::pushRandomHamburgerDressing()
{
	assert(_typeOfMeal == HAMBURGER);
	int randomNumberDressing = rand() % MAX_DRESSING_HAMBURGER + 1;
	int randomDressingNum;

	for (int i = 0; i < randomNumberDressing; i++) {
		randomDressingNum = randomize(HAMBURGER_DRESSING_CHOICES);//
		Ingredient randomDressing(allHumbergerDressing[randomDressingNum]);
		_meal.push(randomDressing);
	}

}

void Order::setReward()
{
	assert(_meal.size() > 0);
	int reward = _meal.size() * REWARD_MULTIPLIER;
	_reward = reward;
}

void Order::setMealType(int typeOfMeal)
{
	assert(typeOfMeal == PIZZA || typeOfMeal == HAMBURGER || typeOfMeal == UNDEFINED_VALUE);

	_typeOfMeal = typeOfMeal;
}

int Order::getMealType()
{
	return _typeOfMeal;
}

int Order::getReward() const
{
	return _reward;
}

int Order::randomize(int max, int min)//
{
	assert(min < max && min >= 0 && max > 0);
	return rand() % max + min;
}

std::stack<Ingredient>& Order::display()
{
	return _meal;
}



const bool Order::compare(std::stack<Ingredient>& autrePile)
{
	std::cout << "ca passe dans pile";
	std::stack<Ingredient> mealCopy = _meal;       // Copie de _meal
	std::stack<Ingredient> autrePileCopy = autrePile; // Copie de autrePile
	std::stack<Ingredient> reverse;


	if (mealCopy.size() != autrePileCopy.size()) {
		return false;
	}

	if (_typeOfMeal == PIZZA) {
		while (!autrePileCopy.empty()) {
			reverse.push(autrePileCopy.top());
			autrePileCopy.pop();
		}


		while (!mealCopy.empty()) {
			if (mealCopy.top() != reverse.top()) {
				return false;
			}
			mealCopy.pop();
			reverse.pop();
		}

		return true; // Les piles sont identiques
	}
	else {
		while (!mealCopy.empty()) {
			if (mealCopy.top() != autrePileCopy.top()) {
				return false;
			}
			mealCopy.pop();
			autrePileCopy.pop();
		}
	}

	return true;
}

Order::~Order()
{
	_reward = 0;
	_typeOfMeal = 0;
}
