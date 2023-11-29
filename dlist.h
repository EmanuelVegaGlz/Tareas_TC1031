/*
 * Tareas TC1031.
 * Programación de estructuras de datos y algoritmos fundamentales
 * Grupo: 602
 * Profesor: Benjamín Valdés Aguirre.
 * Nombre: Emanuel Josué Vega González.
 * ID: A01710366.
 * 
 * Tarea 4:Lista doblemente encadenada
 */

#ifndef DLIST_H_
#define DLIST_H_

#include <string>
#include <sstream>
using namespace std;

/*********** Exception ***********/
class Exception : public exception {
protected:
	string text;

public:
	Exception() throw();
	~Exception() throw();
	virtual const char* what() const throw();
};

Exception::Exception() throw ()
	: text("Basic exception") {
}

Exception::~Exception() throw () {}

const char* Exception::what() const throw() {
	return text.c_str();
}

class RangeError : public Exception {
public:
	RangeError() throw(){
		text = string("RangeError");};
};

class OutOfMemory : public Exception {
public:
	OutOfMemory() throw(){
		text = string("OutOfMemory");};
};

class IndexOutOfBounds : public Exception {
public:
	IndexOutOfBounds() throw(){
	text = string("IndexOutOfBounds");};
};

class NoSuchElement : public Exception {
public:
	NoSuchElement() throw(){
		text = string("NoSuchElement");};
};

class IllegalAction : public Exception {
public:
	IllegalAction() throw(){
		text = string("IllegalAction");};
};

class Overflow : public Exception {
public:
	Overflow() throw(){
		text = string("Overflow");};
};

/*********** Class ***********/

template <class T> class DList;

template <class T>
class DLink {
private:
	DLink(T);
	DLink(T, DLink<T>*, DLink<T>*);
	DLink(const DLink<T>&);

	T	    value;
	DLink<T> *previous;
	DLink<T> *next;

	friend class DList<T>;
};

template <class T>
DLink<T>::DLink(T val) : value(val), previous(0), next(0) {}

template <class T>
DLink<T>::DLink(T val, DLink *prev, DLink* nxt) : value(val), previous(prev), next(nxt) {}

template <class T>
DLink<T>::DLink(const DLink<T> &source) : value(source.value), previous(source.previous), next(source.next) {}

template <class T>
class DList {
public:
	DList();
	DList(const DList<T>&);
	~DList();

    bool empty() const;
	void clear();
	void addFirst(T);
	void insertion(T);
    int  search(T) const;
    void update(unsigned int, T);
    T    removeFirst();
    T    deleteAt(unsigned int);
    
    string toStringForward();
    string toStringBackward();

private:
	DLink<T> *head;
	DLink<T> *tail;
	int 	 size;
};

template <class T>
DList<T>::DList() : head(0), tail(0), size(0) {}

template <class T>
DList<T>::DList(const DList<T> &source){
	DLink<T> *p, *q;

	if (source.empty()) {
		size = 0;
		head = 0;
		tail = 0;
	} else {
		p = source.head;
		head = new DLink<T>(p->value);
		if (head == 0) {
			throw OutOfMemory();
		}
		q = head;

		p = p->next;
		while(p != 0) {
			q->next = new DLink<T>(p->value, q, 0);
			if (q->next == 0) {
				throw OutOfMemory();
			}
			p = p->next;
			q = q->next;
		}
		size = source.size;
	}
}

template <class T>
DList<T>::~DList() {
	clear();
}

// Metodos

template <class T>
bool DList<T>::empty() const {
	return (head == 0 && tail == 0);
}

template <class T>
void DList<T>::clear() {
	DLink<T> *p, *q;

	p = head;
	while (p != 0) {
		q = p->next;
		delete p;
		p = q;
	}
	head = 0;
	tail = 0;
	size = 0;
}

template <class T>
void DList<T>::addFirst(T val){
	DLink<T> *newLink;

	newLink = new DLink<T>(val);
	if (newLink == 0) {
		throw OutOfMemory();
	}

	if (empty()) {
		head = newLink;
		tail = newLink;
	} else {
		newLink->next = head;
		head->previous = newLink;
		head = newLink;
	}
	size++;
}

template <class T>
void DList<T>::insertion(T val){
    DLink<T> *newLink = new DLink<T>(val);
	if (newLink == 0) {
		throw OutOfMemory();
	}

	if (empty()) {
		head = newLink;
		tail = newLink;
	} else {
		tail->next = newLink;
		newLink->previous = tail;
		tail = newLink;
	}
	size++;
}

template <class T>
int DList<T>::search(T val) const {
	int index = 0;
	DLink<T> *p = head;

	while (p != 0) {
		if (p->value == val) {
			return index;
		}
		index++;
		p = p->next;
	}
	return -1;
}

template <class T>
void DList<T>::update(unsigned int index, T val) {
    int pos;
    DLink<T> *p;

    if (index < 0 || index >= size) {
        throw IndexOutOfBounds();
    }

    p = head;
    pos = 0;
    while (pos != index) {
        p = p->next;
        pos++;
    }
    p->value = val;
}

template <class T>
T DList<T>::removeFirst()  {
	T val;
	DLink<T> *p;

	if (empty()) {
		throw NoSuchElement();
	}

	p = head;
	val = p->value;

	if (head == tail) {
		head = 0;
		tail = 0;
	} else {
		head = p->next;
		p->next->previous = 0;
	}
	delete p;
	size--;

	return val;
}

template <class T>
T DList<T>::deleteAt(unsigned int index) {
	int pos;
	T val;
	DLink<T> *p;

	if (index < 0 || index >= size) {
		throw IndexOutOfBounds();
	}

	if (index == 0) {
		return removeFirst();
	}

	p = head;
	pos = 0;
	while (pos != index) {
		p = p->next;
		pos++;
	}

	val = p->value;
	p->previous->next = p->next;
	if (p->next != 0) {
		p->next->previous = p->previous;
	}
	size--;

	delete p;

	return val;
}

template <class T>
string DList<T>::toStringForward() {
    stringstream aux;
    DLink<T> *p;

    p = head;
    aux << "[";
    while (p != 0) {
        aux << p->value;
        if (p->next != 0) {
            aux << ", ";
        }
        p = p->next;
    }
    aux << "]";
    return aux.str();
}

template <class T>
string DList<T>::toStringBackward() {
    stringstream aux;
    DLink<T> *p;

    p = tail;
    aux << "[";
    while (p != 0) {
        aux << p->value;
        if (p->previous != 0) {
            aux << ", ";
        }
        p = p->previous;
    }
    aux << "]";
    return aux.str();
}

#endif /* DLIST_H_ */