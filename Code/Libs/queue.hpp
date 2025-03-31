#include <assert.h>

#pragma once

template <class TYPE>
class queue {
	private:
		struct cellule { // Structure d'une cellule. La file est composée de plusieurs de ces cellules
			TYPE _element; // Donnée enregistrée dans une des cellules de la file
			cellule* _next; // Pointeur vers la prochaine cellule de la file

			// Constructeur d'une cellule (méthode appelée à chaque fois qu'on fait un "new Cellule")
			cellule(const TYPE& element, cellule* next) {
				_element = element;
				_next = next;
			}
		};

		cellule* _queue; // Pointe sur la dernière cellule dont le "next" pointe sur la première
		queue(const queue<TYPE>&); 

	public:
		queue(); // Constructeur qui initialise "_queue" à "nullptr"
		~queue(); // Destructeur qui supprime toutes les cellules de la file

		void clear(); // Méthode qui supprime toutes les cellules de la file
		bool empty() const; // Méthode qui vérifie si la file est vide (retourne true) ou non (retourne false)
		int size() const; // Méthode qui retourne le nombre de cellules que contient la file

		const TYPE& front() const; // Méthode qui retourne l'élément contenu dans la première cellule de la file
		TYPE& front();
		TYPE pop(); // Méthode qui supprime la première cellule de la file et retourne son élément par valeur
		void push(const TYPE&); // Méthode qui ajoute une nouvelle cellule à la fin de la file

		const queue<TYPE>& operator=(const queue<TYPE>&); // Surcharge de l'opérateur = pour copier le contenu
														  // d'une file vers une autre.
};

// CODEZ LES MÉTHODES DE VOTRE FILE ICI.

template<class TYPE>
inline queue<TYPE>::queue(){
	_queue = nullptr;
}

template<class TYPE>
inline queue<TYPE>::~queue(){
	clear();
}

template<class TYPE>
inline void queue<TYPE>::clear(){
	while (!empty()) {
		pop();
	}
}

template<class TYPE>
inline bool queue<TYPE>::empty() const{
	return _queue == nullptr;
}

template<class TYPE>
inline int queue<TYPE>::size() const{
	int count = 0;

	if (!empty()) {
		cellule* tempPtr = _queue->_next;

		do {
			tempPtr = tempPtr->_next;
			count++;
		} while (tempPtr != _queue->_next);
	}

	return count;
}

template<class TYPE>
inline const TYPE& queue<TYPE>::front() const{
	assert(_queue == nullptr);
	return _queue->_next->_element;
}

template<class TYPE>
inline TYPE& queue<TYPE>::front(){
	assert(_queue != nullptr);
	return _queue->_next->_element;
}

template<class TYPE>
inline TYPE queue<TYPE>::pop(){
	assert(_queue != nullptr);
	TYPE tempVal = _queue->_next->_element;;

	if (_queue == _queue->_next) {
		delete _queue;
		_queue = nullptr;
	}
	else {
		cellule* tempPtr = _queue->_next->_next;
		delete _queue->_next;
		_queue->_next = tempPtr;
	}

	return tempVal;
}

template<class TYPE>
inline void queue<TYPE>::push(const TYPE& element){
	if (_queue == nullptr) { // ma file est vide
		//_queue = new cellule(element, nullptr);
		//_queue->_next = _queue;
		_queue->_next = _queue = new cellule(element, nullptr);
	}
	else { // il y a déjà au moins une cellule
		_queue = _queue->_next = new cellule(element, _queue->_next);
	}
}

template<class TYPE>
inline const queue<TYPE>& queue<TYPE>::operator=(const queue<TYPE>& autreFile){
	if (this != &autreFile) {
		clear();

		if (!autreFile.empty()) {
			cellule* tempPtr = autreFile._queue->_next;

			do {
				push(tempPtr->_element);
				tempPtr = tempPtr->_next;
			} while (tempPtr != autreFile._queue->_next);
		}
	}

	return *this;
}
