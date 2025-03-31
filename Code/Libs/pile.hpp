#pragma once
#include <cassert>

template <class TYPE>
class pile
{
private:
	struct cellule
	{
		TYPE 	  element;	// �l�ment ds la cellule
		cellule* next; 		// pointeur vers prochaine cellule

		cellule(const TYPE& e, cellule* n)
		{
			element = e;
			next = n;
		}
	};
	cellule* _top;		// 1er �l�ment de la pile

	inline cellule* createCell(cellule * cellPtr) {

		if (cellPtr == nullptr) { // J'ai fini de cr�er les cellules
			return nullptr;
		}
		return new cellule(cellPtr->element, createCell(cellPtr->next));
	}

public:
	pile();			// constructeurr & destructeurr
	~pile();

	void push(const TYPE& e); //ajoute un nouveau dessus
	TYPE pop(); //enl�ve le dessus
	bool empty() const; //si la pile est vide
	void clear(); //vide la pile

	const pile<TYPE>& operator=(const pile& s); //affectateur
	bool operator==(const pile& s)const; //comparaison de 2 piles

	int size() const; //retourne le nb d��l�ment
	const TYPE& top() const; //retourne le dessus, mais d�pile pas
	TYPE& top(); //retourne le dessus, mais en setteur
};

template<class TYPE>
pile<TYPE>::pile() {
	_top = nullptr;
}

template<class TYPE>
inline pile<TYPE>::~pile(){	delete _top;
	_top = nullptr;
}

template<class TYPE>
void pile<TYPE>::push(const TYPE& e) {
	_top = new cellule(e, _top);
}

template<class TYPE>
TYPE pile<TYPE>::pop() {
	assert(_top != nullptr);

	TYPE tempVal = _top->element;
	cellule* tempPtr = _top->next;

	delete _top;
	_top = tempPtr;

	return tempVal;
}

template<class TYPE>
bool pile<TYPE>::empty() const{
	return (_top == nullptr);
}

template<class TYPE>
void pile<TYPE>::clear() {
	while (_top != nullptr) {
		pop();
	}
}

template<class TYPE>
bool pile<TYPE>::operator==(const pile<TYPE>& autrepile) const {
	cellule* cellPtr1 = _top;
	cellule* cellPtr2 = autrepile._top;

	while (cellPtr1 != nullptr && cellPtr2 != nullptr) {

		if (cellPtr1->element != cellPtr2->element) {
			return false;
		}

		cellPtr1 = cellPtr1->next;
		cellPtr2 = cellPtr2->next;	
	}

	return (cellPtr1 == cellPtr2);
}

template<class TYPE>
inline int pile<TYPE>::size() const{
	int sizeCount = 0;
	cellule* sizing = _top;

	while (sizing != nullptr) {
		sizeCount++;
		sizing = sizing->next;
	}

	return sizeCount;
}

template<class TYPE>
inline const TYPE& pile<TYPE>::top() const{
	assert(_top != nullptr);
	return _top -> element;;
}

template<class TYPE>
inline TYPE& pile<TYPE>::top(){
	assert(_top != nullptr);
	return _top->element;
}

template<class TYPE>
const pile<TYPE>& pile<TYPE>::operator=(const pile<TYPE>& autrepile) {
	if (this == &autrepile) {
		return *this;
	}
	clear();
	_top = createCell(autrepile._top);
	
	
	cellule* cellPtr1 = nullptr;
	cellule* cellPtr2 = autrepile._top;

	if (cellPtr2 != nullptr) {
		_top = new cellule(cellPtr2->element, nullptr);
		cellPtr1 = _top;
	}

	while (cellPtr2 != nullptr) {
		cellPtr1->next = new cellule(cellPtr2->element, nullptr);
		cellPtr1 = cellPtr1->next;
		cellPtr2 = cellPtr2->next;
	}
	

	return *this;
}