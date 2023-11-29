/*
 * Tareas TC1031.
 * Programación de estructuras de datos y algoritmos fundamentales
 * Grupo: 602
 * Profesor: Benjamín Valdés Aguirre.
 * Nombre: Emanuel Josué Vega González.
 * ID: A01710366.
 * 
 * Tarea 6: Árbol Heap.
 * 
 * Implementación de un Min Heap
 * 
 */

#ifndef HEAP_H_
#define HEAP_H_

#include <string>
#include <sstream>
#include <iostream>
#include <exception>
#include <cstdio>

using namespace std;

/*********** Exception ***********/
class Exception : public std::exception {
protected:
	std::string text;

public:
	Exception() throw(): text("Basic exception"){};
	~Exception() throw(){};
	virtual const char* what() const throw(){return text.c_str();};
};	

class RangeError : public Exception {
public:
	RangeError() throw(){
		text = std::string("RangeError");};
};

class OutOfMemory : public Exception {
public:
	OutOfMemory() throw(){
		text = std::string("OutOfMemory");};
};

class IndexOutOfBounds : public Exception {
public:
	IndexOutOfBounds() throw(){
	text = std::string("IndexOutOfBounds");};
};

class NoSuchElement : public Exception {
public:
	NoSuchElement() throw(){
		text = std::string("NoSuchElement");};
};

class IllegalAction : public Exception {
public:
	IllegalAction() throw(){
		text = std::string("IllegalAction");};
};

class Overflow : public Exception {
public:
	Overflow() throw(){
		text = std::string("Overflow");};
};

/****************Heap****************/
template <class T>
class Heap {
private:
	T *data;
	unsigned int siz;
	unsigned int count;
	unsigned int parent(unsigned int) const;
	unsigned int left(unsigned int) const;
	unsigned int right(unsigned int) const;
	void heapify(unsigned int);
	void swap(unsigned int, unsigned int);

public:
	Heap(unsigned int) ;
	~Heap();
	bool empty() const;
	bool full() const;
	void push(T) ;
	T pop() ;
	void clear();
	string toString() const;
    unsigned int size(){return count;};
	T top(){return data[0];};
};

template <class T>
Heap<T>::Heap(unsigned int sze)  {
	siz = sze;
	data = new T[siz];
	if (data == 0) {
		throw OutOfMemory();
	}
	count = 0;
}

template <class T>
Heap<T>::~Heap() {
	delete [] data;
	data = 0;
	siz = 0;
	count = 0;
}


template <class T>
bool Heap<T>::empty() const {
	return (count == 0);
}
template <class T>
bool Heap<T>::full() const {
	return (count == siz);
}
template <class T>
unsigned int Heap<T>::parent(unsigned int pos) const {
	return (pos - 1) / 2;
}

template <class T>
unsigned int Heap<T>::left(unsigned int pos) const {
	return ((2 * pos) + 1);
}

template <class T>
unsigned int Heap<T>::right(unsigned int pos) const {
	return ((2 * pos) + 2);
}

template <class T>
void Heap<T>::swap(unsigned int i, unsigned int j) {
	T aux = data[i];
	data[i] = data[j];
	data[j] = aux;
}
template <class T>
void Heap<T>::heapify(unsigned int pos) {
	unsigned int le = left(pos);
	unsigned int ri = right(pos);
	unsigned int min = pos;
	if (le <= count && data[le] < data[min]) {
		min = le;
	}
	if (ri <= count && data[ri] < data[min]) {
		min = ri;
	}
	if (min != pos) {
		swap(pos, min);
		heapify(min);
	}
}

template <class T>
void Heap<T>::push(T val)  {
	unsigned int pos;
	if (full()) {
		throw Overflow();
	}

	pos = count;
	count++;
	while (pos > 0 && val < data[parent(pos)]) {
		data[pos] = data[parent(pos)];
		pos = parent(pos);
	}
	data[pos] = val;
}

template <class T>
T Heap<T>::pop()  {
	if (empty()) {
		throw NoSuchElement();
	}
	T aux = data[0];

	data[0] = data[--count];
	heapify(0);
	return aux;
}
template <class T>
void Heap<T>::clear() {
	count = 0;
}

template <class T>
string Heap<T>::toString() const {
	stringstream aux;
	aux << "[";	for (unsigned int i = 0; i < count; i++) {
		if (i != 0) {
			aux << " ";
		} aux << data[i];
	} aux << "]";
	return aux.str();
}

#endif /* HEAP_H_ */