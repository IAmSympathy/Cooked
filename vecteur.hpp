#pragma once
#include <cassert>
#include <iostream>

template <class TYPE>
class vecteur {
	private:
		TYPE *_pTab;
		int _dim;

	public:
		vecteur();
		vecteur(int dim);
		~vecteur();

		// Ajoutez des méthodes ici au fur et à mesure que
		// vous avancez votre laboratoire sur le vecteur.

		vecteur(const vecteur<TYPE>& vecteur);

		void print(std::ostream& output);
		void push_back(int nb);
		int size();
		void resize(int dim);
		void clear();
		TYPE& at(int index);
		vecteur<TYPE>& swap(vecteur<TYPE>& v);

		TYPE& operator[](int index);
		vecteur<TYPE>& operator=(vecteur<TYPE>& v);
		vecteur<TYPE> operator+(const vecteur<TYPE>&v);
		vecteur<TYPE>& operator+=(const vecteur<TYPE>& v);
		bool operator==(vecteur<TYPE> v);

		template <class TYPE>
		friend void swap(vecteur<TYPE>& v1, vecteur<TYPE>& v2);
};

template <class TYPE>
std::ostream& operator<<(std::ostream& output, vecteur<TYPE> v);


template <class TYPE>
vecteur<TYPE>::vecteur() {
	_pTab = nullptr;
	_dim = 0;
}
template <class TYPE>
vecteur<TYPE>::vecteur(int dim) {
	assert(dim >= 0);
	_pTab = new TYPE[dim];
	_dim = dim;
}
template <class TYPE>
vecteur<TYPE>::~vecteur() {
	clear();
}

template <class TYPE>
vecteur<TYPE>::vecteur(const vecteur<TYPE>& vecteur)
{
	_dim = vecteur._dim;
	_pTab = new TYPE[_dim];
	for (int i = 0; i < vecteur._dim; i++)
	{
		*(_pTab + i) = *(vecteur._pTab + i);
	}
}

template <class TYPE>
void vecteur<TYPE>::print(std::ostream& output)
{
	for (int i = 0; i < _dim; i++)
	{
		output << *(*(_pTab + i));
	}
}

template <class TYPE>
void vecteur<TYPE>::push_back(int nb)
{
	TYPE* table;
	table = new TYPE[_dim + 1];

	//Copie
	for (int i = 0; i < _dim; i++)
	{
		*(table + i) = *(_pTab + i);
	}
	//Ajout de la valeur
	*(table + (_dim)) = nb;

	//Transfer dans le vecteur d'origine
	_dim += 1;
	delete[] _pTab;
	_pTab = table;


	table = nullptr;
	//delete table;
}

template <class TYPE>
int vecteur<TYPE>::size()
{
	return _dim;
}

template <class TYPE>
void vecteur<TYPE>::resize(int dim)
{
	assert(dim >= 0);

	if (dim != _dim)
	{
		TYPE* table = new TYPE[dim];
		if (dim < _dim) {
			TYPE* table = new TYPE[dim];
			for (int i = 0; i < dim; i++)
			{
				*(table + i) = *(_pTab + i);
			}
		}
		else if (dim > _dim) {
			TYPE* table = new TYPE[dim];
			for (int i = 0; i < _dim; i++)
			{
				*(table + i) = *(_pTab + i);
			}
		}

		delete[] _pTab;
		_pTab = table;
		_dim = dim;
	}
}

template <class TYPE>
void vecteur<TYPE>::clear()
{
	delete[] _pTab;
	_pTab = NULL;
	_dim = 0;
}

template <class TYPE>
TYPE& vecteur<TYPE>::at(int index)
{
	assert(index >= 0 && index <= _dim);
	return *(_pTab + index);
}

template <class TYPE>
vecteur<TYPE>& vecteur<TYPE>::swap(vecteur<TYPE>& v)
{
	std::swap(_pTab, v.pTab);
	std::swap(_dim, v._dim);
	return *this;
}

template <class TYPE>
TYPE& vecteur<TYPE>::operator[](int index)
{
	return this->at(index);
}

template <class TYPE>
vecteur<TYPE>& vecteur<TYPE>::operator=(vecteur<TYPE>& v)
{
	vecteur* ptr1 = this;
	vecteur* ptr2 = &v;

	if (ptr1 != ptr2)
	{
		resize(v.size());
		for (int i = 0; i < _dim; i++)
		{
			*(_pTab + i) = v.at(i);
		}
	}

	return *this;
}

template <class TYPE>
vecteur<TYPE> vecteur<TYPE>::operator+(const vecteur<TYPE>& v)
{
	int newDim = _dim + v._dim;
	vecteur<TYPE> temp(newDim);

	for (int i = 0; i < newDim; i++)
	{
		if (i < _dim)
			*(temp._pTab + i) = *(_pTab + i);
		else
			*(temp._pTab + i) = *(v._pTab + i - _dim);
	}
	return temp;
}

template <class TYPE>
vecteur<TYPE>& vecteur<TYPE>::operator+=(const vecteur<TYPE>& v)
{
	vecteur<TYPE> temp;
	temp = *this;
	vecteur<TYPE> tempTwo = temp + v;

	*this = tempTwo;
	return *this;
}

template <class TYPE>
bool vecteur<TYPE>::operator==(vecteur<TYPE> v)
{
	if (_dim != v.size())
		return false;
	else {
		for (int i = 0; i < _dim; i++)
		{
			if (*(_pTab + i) != v.at(i))
				return false;
		}
	}

	return true;
}

template <class TYPE>
void swap(vecteur<TYPE>& v1, vecteur<TYPE>& v2)
{
	std::swap(v1._dim, v2._dim);
	std::swap(v1._pTab, v2._pTab);
}

template <class TYPE>
std::ostream& operator<<(std::ostream& output, vecteur<TYPE> v)
{
	v.print(output);
	return output;
}