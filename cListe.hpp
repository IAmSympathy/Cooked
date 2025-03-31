#pragma once

#include <cassert>
#include <iostream>

template <class TYPE>
class cListe {
private:
	struct cellule {
		TYPE _element; // Contenu de la cellule
		cellule* _suivant; // Pointeur vers la cellule précédente
		cellule* _precedent; // Pointeur vers la cellule suivante

		cellule(const TYPE& element, cellule* suivant, cellule* precedent) {
			_element = element;
			_suivant = suivant;
			_precedent = precedent;
		}
	};

	cellule* _premier; // Pointeur vers la première cellule
	cellule* _courant; // Pointeur sur la cellule courante

	cListe(const cListe& listeObj); // Constructeur de copie désactivé
	int recursive(cellule* index) const;
public:
	cListe(); // Constructeur
	~cListe(); // Destructeur
	void vide(); // Supprime (désalloue) toutes les cellules de la liste
	void debut(); // Positionne courant au début de la liste, soit sur la première cellule. Si la liste est vide,
	// courant devient nullptr.
	void fin(); // Positionne courant à la fin de la liste, soit sur nullptr
	void precedent(); // Positionne courant sur la cellule précédente. Si courant pointe la première cellule de la
	// liste, il continue de pointer cette cellule.
	void suivant(); // Positionne courant sur la cellule suivante. Si courant vaut nullptr, alors il reste à nullptr.
	bool estVide() const; // Retourne vrai si la liste est vide et faux sinon
	bool estDebut() const; // Retourne vrai si courant est au début de la liste et faux sinon
	bool estFin() const; // Retourne vrai si courant est à la fin de la liste et faux sinon
	TYPE& contenu() const; // Retourne l'élément contenu dans la cellule pointée par courant. Si la liste est vide ou
	// si courant = nullptr, il faut faire planter le programme.
	void affiche(std::ostream& sortie) const; // Affiche tous les éléments de la liste séparés par des espaces
	void insere(const TYPE& element); // Insère une nouvelle cellule contenant l'élément reçu en paramètre d'entrée et ce,
	// avant la cellule pointée par courant ou à la fin de la liste si courant = nullptr
	void supprime(); // Supprime (désalloue) la cellule pointée par courant. Si la liste est vide ou si courant = nullptr,
	// il faut faire planter le programme.
	void sort();
	int tailleIterative() const; // Retourne ne nombre de cellules de la liste de manière itérative (avec une boucle)
	int tailleRecursive() const; // Retourne ne nombre de cellules de la liste de manière récursive (sans boucle)
	bool recherche(const TYPE& element); // Vérifie si l’élément reçu en paramètre d’entrée est présent dans une des
	bool rechercheKill(const TYPE& element); // Vérifie si l’élément reçu en paramètre d’entrée est présent dans une des
	// cellules de la liste. // Si oui, courant est positionné sur cette cellule et
	// on retourne true. Sinon, on retourne false.
	const cListe& operator=(const cListe& listeObj); // Affectateur
};

template<class TYPE>
std::ostream& operator<<(std::ostream& sortie, const cListe<TYPE>& listeObj); // Appelle la méthode affiche()


/**********************************************************************************/
/* COMPLÉTEZ LES MÉTHODES CI-DESSOUS SELON LES COMMENTAIRES ET L'ÉNONCÉ D'EXAMEN. */
/**********************************************************************************/


template<class TYPE>
inline int cListe<TYPE>::recursive(cellule* index) const {
	if (index == _premier)
		return 0;

	index = index->_suivant;
	int somme = 1;

	return somme += recursive(index);
}

template<class TYPE>
cListe<TYPE>::cListe() {
	_premier = nullptr;
	_courant = nullptr;
}

template<class TYPE>
cListe<TYPE>::~cListe() {
	vide();
}

template<class TYPE>
void cListe<TYPE>::vide() {
	debut();
	while (!estVide())
		supprime();
}

template<class TYPE>
void cListe<TYPE>::debut() {
	_courant = _premier;
}

template<class TYPE>
void cListe<TYPE>::fin() {
	_courant = _premier->_precedent->_precedent;
}

template<class TYPE>
void cListe<TYPE>::precedent() {
	_courant = _courant->_precedent;
}

template<class TYPE>
void cListe<TYPE>::suivant() {
	_courant = _courant->_suivant;
}

template<class TYPE>
bool cListe<TYPE>::estVide() const {
	return	(_premier == nullptr);
}

template<class TYPE>
bool cListe<TYPE>::estDebut() const {
	return (_courant == _premier);
}

template<class TYPE>
bool cListe<TYPE>::estFin() const {
	return (_courant == _premier->_precedent);
}

template<class TYPE>
TYPE& cListe<TYPE>::contenu() const {
	assert(!estVide());
	assert(_courant != nullptr);

	return _courant->_element;
}

template <class TYPE>
void cListe<TYPE>::affiche(std::ostream& sortie) const {
	if (estVide())
		sortie << "Vide";
	else {
		cellule* tempPtr = _premier;

		do {
			sortie << tempPtr->_element << " ";
			tempPtr = tempPtr->_suivant;
		} while (tempPtr != _premier);
	}
}

template<class TYPE>
void cListe<TYPE>::insere(const TYPE& element) {
	std::cout << "J'INSERE " << std::endl;
	if (estVide()) { //Si la liste ne contien aucune cellule
		_premier = new cellule(element, nullptr, nullptr);
		_premier->_precedent = _premier;
		_premier->_suivant = _premier;
		_courant = _premier;
	}
	else if (_courant == _premier) { //Si le courant est placé sur la premeire cellule
		_courant->_precedent->_suivant = new cellule(element, _courant, _courant->_precedent);
		_premier = _courant->_precedent->_suivant;
		_courant->_precedent = _premier;
	}
	else if (_courant == nullptr) {
		_premier->_precedent = new cellule(element, _premier, _premier->_precedent);
		_premier->_precedent->_precedent->_suivant = _premier->_precedent;
	}
	//else if (_courant->_suivant == _courant) { //Si la liste ne contient qu'1 cellule
	//	_courant->_precedent = new cellule(element, _courant, _courant);
	//	_premier = _courant->_precedent;
	//	_courant->_suivant = _premier;
	//}
	else { //Si la liste contient 2 ou plus cellules
		_courant->_precedent->_suivant = new cellule(element, _courant, _courant->_precedent);
		_courant->_precedent = _courant->_precedent->_suivant;
	}
}

template<class TYPE>
void cListe<TYPE>::supprime() {
	assert(_premier != nullptr);
	cellule* tempPtr = _courant;

	if (_courant->_suivant == _courant) { //Si il reste 1 seule cellule	
		_courant = nullptr;
		_premier = nullptr;
	}
	else if (_courant->_suivant == _premier) { // Si on supprime la dernière cellule
		_courant->_suivant->_precedent = _courant->_precedent;
		_courant->_precedent->_suivant = _courant->_suivant;
		_courant = _courant->_precedent; // Courant = le "nouveau dernier"
	}
	else { //Si on supprime une cellule se retrouvant entre deux autres ceullules
		_courant->_suivant->_precedent = _courant->_precedent;
		_courant->_precedent->_suivant = _courant->_suivant;
		_courant = _courant->_suivant;
	}

	delete tempPtr;
}

template<class TYPE>
inline void cListe<TYPE>::sort()
{
	std::vector<TYPE> sortedElements;
	cellule* tempPtr = _premier;

	do {
		sortedElements.push_back(tempPtr->_element);
		tempPtr = tempPtr->_suivant;
	} while (tempPtr != _premier);

	std::sort(sortedElements.begin(), sortedElements.end(), [](const TYPE& a, const TYPE& b) {
		return a.GetPosition() < b.GetPosition();
		});

	vide();

	for (const TYPE& element : sortedElements) {
		insere(element);
	}
}

template<class TYPE>
int cListe<TYPE>::tailleIterative() const {
	if (_premier == nullptr)
		return 0;
	if (_courant->_suivant == _courant)
		return 1;

	cellule* tempPtr = _premier;
	int compteur = 0;

	do {
		tempPtr = tempPtr->_suivant;
		compteur++;
	} while (tempPtr != _premier);

	return compteur;
}

template<class TYPE>
int cListe<TYPE>::tailleRecursive() const {
	if (_premier == nullptr)
		return 0;
	int somme = 1;

	cellule* tempPtr = _premier->_suivant;

	somme += recursive(tempPtr);

	return somme;
}

template <class TYPE>
bool cListe<TYPE>::recherche(const TYPE& element) {
	assert(_premier != nullptr);

	cellule* tempPtr = _courant;

	do {
		if (tempPtr->_element == element) {
			_courant = tempPtr;
			return true;
		}
		tempPtr = tempPtr->_suivant;
	} while (tempPtr != _courant);

	return false;
}

template <class TYPE>
bool cListe<TYPE>::rechercheKill(const TYPE& element) {
	assert(_premier != nullptr);

	cellule* tempPtr = _courant;
	cellule* tempPtr2 = _courant;

	do {
		if (tempPtr->_element == element) {
			_courant = tempPtr;
			supprime();
			_courant = tempPtr2;
			return true;
		}
		tempPtr = tempPtr->_suivant;
	} while (tempPtr != _courant);

	return false;
}

template <class TYPE>
const cListe<TYPE>& cListe<TYPE>::operator=(const cListe<TYPE>& listeObj) {
	if (this == &listeObj)
		return *this;

	vide();

	cellule* tempPtr = listeObj._premier;
	int compteur = 0;
	//Copie
	do {
		fin();
		insere(tempPtr->_element);
		tempPtr = tempPtr->_suivant;
	} while (tempPtr != listeObj._premier);

	//Trouver _courrant
	do {
		compteur++;
		tempPtr = tempPtr->_suivant;
	} while (tempPtr != listeObj._courant);
	//Assigner _courant
	_courant = _premier;
	for (int i = 0; i < compteur; i++) {
		_courant = _courant->_suivant;
	}

	return *this;
}

template<class TYPE>
std::ostream& operator<<(std::ostream& sortie, const cListe<TYPE>& listeObj) {
	listeObj.affiche(sortie);
	return sortie;
}