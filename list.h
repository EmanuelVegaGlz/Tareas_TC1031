/*
 * Tareas TC1031.
 * Programación de estructuras de datos y algoritmos fundamentales
 * Grupo: 602
 * Profesor: Benjamín Valdés Aguirre.
 * Nombre: Emanuel Josué Vega González.
 * ID: A01710366.
 * 
 * Tarea 3: Lista ligada simple
 */

#include <sstream>
#include <string>
#include <exception>


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

template <class T> class List;
template <class T>
class Link {
private:
	Link(T);
	Link(T, Link<T>*);
	Link(const Link<T>&);

	T	    value;
	Link<T> *next;

	friend class List<T>;
};

template <class T>
Link<T>::Link(T val) : value(val), next(0) {}

template <class T>
Link<T>::Link(T val, Link* nxt) : value(val), next(nxt) {}

template <class T>
Link<T>::Link(const Link<T> &source) : value(source.value), next(source.next) {}

template <class T>
class List {
public:
	List();
	List(const List<T>&) ;
	~List();

	bool empty() const;
	void clear();
    void addFirst(T) ;
	void insertion(T) ;
    int  search(T) const;
    void update(unsigned int, T);
    T    deleteAt(int);

	string toString() const;

private:
	Link<T> *head;
	int 	size;
};

template <class T>
List<T>::List() : head(0), size(0) {}

template <class T>
List<T>::List(const List<T> &source)  {
	Link<T> *p, *q;

	if (source.empty()) {
		size = 0;
		head = 0;
	} else {
		p = source.head;
		head = new Link<T>(p->value);
		if (head == 0) {
			throw OutOfMemory();
		}
		q = head;

		p = p->next;
		while(p != 0) {
			q->next = new Link<T>(p->value);
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
List<T>::~List() {
	clear();
}

template <class T>
bool List<T>::empty() const {
	return (head == 0);
}

template <class T>
void List<T>::clear() {
	Link<T> *p, *q;

	p = head;
	while (p != 0) {
		q = p->next;
		delete p;
		p = q;
	}
	head = 0;
	size = 0;
}

template <class T>
void List<T>::addFirst(T val)  {
	Link<T> *newLink;

	newLink = new Link<T>(val);
	if (newLink == 0) {
		throw OutOfMemory();
	}
	newLink->next = head;
	head = newLink;
	size++;
}

template <class T>
void List<T>::insertion(T val)  {
	Link<T> *newLink, *p;

	newLink = new Link<T>(val);
	if (newLink == 0) {
		throw OutOfMemory();
	}

	if (empty()) {
		addFirst(val);
		return;
	}

	p = head;
	while (p->next != 0) {
		p = p->next;
	}

	newLink->next = 0;
	p->next = newLink;
	size++;
}

template <class T>
int List<T>::search(T val) const {
	Link<T> *p;
    int i = 0;
   	p = head;
	while (p != 0) {
		if (p->value == val) {
			return i;
		}
		p = p->next;
        i++;
	}
	return -1; 

}

template <class T>
void List<T>::update(unsigned int index, T val) {
    int pos;
    Link<T> *p;

    if (index < 0 || index >= size) {
        throw IndexOutOfBounds();
    }

    if (index == 0) {
        head->value = val;
        return;
    }

    p = head;
    pos = 0;
    while (pos != index) {
        p = p->next;
        pos++;
    }

    p->value = val;

	return;
}

template <class T>
T List<T>::deleteAt(int index) {
    int pos;
    Link<T> *p, *temp;
	T val;

    if (index < 0 || index >= size) {
        throw IndexOutOfBounds();
    }

	if (index == 0) {
        temp = head;
        head = head->next;
        val = temp->value;
        delete temp;
        size--;
        return val;
    }

 	p = head;
    pos = 0;
    while (pos != index - 1) {
        p = p->next;
        pos++;
    }

    temp = p->next;
    val = temp->value;
    p->next = temp->next;
    delete temp;
    size--;

    return val;
}

template <class T>
string List<T>::toString() const {
	stringstream aux;
	Link<T> *p;

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