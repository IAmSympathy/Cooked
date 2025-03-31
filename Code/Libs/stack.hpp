#include <cassert>

template <class TYPE>
class stack
{
private:
	struct cellule
	{
		TYPE 	  element;	// élément ds la cellule
		cellule* next; 		// pointeur vers prochaine cellule

		cellule(const TYPE& e, cellule* n)
		{
			element = e;
			next = n;
		}
	};
	cellule* _top;		// 1er élément de la pile

	inline cellule* createCell(cellule * cellPtr) {

		if (cellPtr == nullptr) { // J'ai fini de créer les cellules
			return nullptr;
		}
		return new cellule(cellPtr->element, createCell(cellPtr->next));
	}

public:
	stack();			// constructeurr & destructeurr
	~stack();

	void push(const TYPE& e); //ajoute un nouveau dessus
	TYPE pop(); //enlève le dessus
	bool empty() const; //si la pile est vide
	void clear(); //vide la pile

	const stack<TYPE>& operator=(const stack& s); //affectateur
	bool operator==(const stack& s)const; //comparaison de 2 piles

	int size() const; //retourne le nb d’élément
	const TYPE& top() const; //retourne le dessus, mais dépile pas
	TYPE& top(); //retourne le dessus, mais en setteur
};

template<class TYPE>
stack<TYPE>::stack() {
	_top = nullptr;
}

template<class TYPE>
inline stack<TYPE>::~stack(){	delete _top;
	_top = nullptr;
}

template<class TYPE>
void stack<TYPE>::push(const TYPE& e) {
	_top = new cellule(e, _top);
}

template<class TYPE>
TYPE stack<TYPE>::pop() {
	assert(_top != nullptr);

	TYPE tempVal = _top->element;
	cellule* tempPtr = _top->next;

	delete _top;
	_top = tempPtr;

	return tempVal;
}

template<class TYPE>
bool stack<TYPE>::empty() const{
	return (_top == nullptr);
}

template<class TYPE>
void stack<TYPE>::clear() {
	while (_top != nullptr) {
		pop();
	}
}

template<class TYPE>
bool stack<TYPE>::operator==(const stack<TYPE>& autreStack) const {
	cellule* cellPtr1 = _top;
	cellule* cellPtr2 = autreStack._top;

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
inline int stack<TYPE>::size() const{
	int sizeCount = 0;
	cellule* sizing = _top;

	while (sizing != nullptr) {
		sizeCount++;
		sizing = sizing->next;
	}

	return sizeCount;
}

template<class TYPE>
inline const TYPE& stack<TYPE>::top() const{
	assert(_top != nullptr);
	return _top -> element;;
}

template<class TYPE>
inline TYPE& stack<TYPE>::top(){
	assert(_top != nullptr);
	return _top->element;
}

template<class TYPE>
const stack<TYPE>& stack<TYPE>::operator=(const stack<TYPE>& autreStack) {
	if (this == &autreStack) {
		return *this;
	}
	clear();
	_top = createCell(autreStack._top);
	
	/*
	cellule* cellPtr1 = nullptr;
	cellule* cellPtr2 = autreStack._top;

	if (cellPtr2 != nullptr) {
		_top = new cellule(cellPtr2->element, nullptr);
		cellPtr1 = _top;
	}

	while (cellPtr2 != nullptr) {
		cellPtr1->next = new cellule(cellPtr2->element, nullptr);
		cellPtr1 = cellPtr1->next;
		cellPtr2 = cellPtr2->next;
	}
	*/

	return *this;
}