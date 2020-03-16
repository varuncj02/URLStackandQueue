/*
 * stack.h
 *
 *  Created on: Apr 8, 2019
 *      Author: dgv130030
 */

#ifndef STACK_H_
#define STACK_H_

#include <cstddef>
#include <cassert>
#include <iostream>
 //using namespace std;

template <class Type>
class stack;

template <class Type>
class stackEntry
{
	friend class stack<Type>;
protected:
	Type              dataValue;
	stackEntry<Type>* pNext;

	stackEntry(const Type& newData, stackEntry<Type>* newNext = nullptr) {
		dataValue = newData;
		pNext = newNext;
	}
	//stackEntry(const Type& newData);
	virtual ~stackEntry() {

	}
	virtual void next(stackEntry<Type>* pNext);
	virtual Type& data() {
		return dataValue;
	}
	virtual const Type& data() const {
		return dataValue;
	}
	virtual stackEntry<Type>* next() {
		return pNext;
	}
};


template <class Type>
void stackEntry<Type>::next(stackEntry<Type>* pNext) {
	this->pNext = pNext;
}

template <class Type>
class stack
{
private:
	std::size_t counter;
	stackEntry<Type>* pTop;
public:
	stack();
	stack(const stack& other);
	const stack& operator=(const stack& rhs) {
		if (rhs.pTop) {
			clear();
			stackEntry<Type>* tempNode = rhs.pTop;
			while (tempNode) {
				push(tempNode->data());
				tempNode = tempNode->next();
			}
		}
		return *this;
	}
	virtual ~stack() {
		clear();
	}
	const Type& top() const {
		assert(pTop != nullptr);
		return pTop;
	}
	Type& top() {
		return pTop->data();
	}
	bool empty() const {
		if (counter == 0) {
			return true;
		}
		else {
			return false;
		}
	}
	std::size_t size() const {
		return counter;
	}
	void push(const Type& value);
	void pop();
	void clear();
	void debug() const;
	void debug(std::ostream& out) const;
};

template <class Type>
stack<Type>::stack() {
	counter = 0;
	pTop = nullptr;
}

template <class Type>
stack<Type>::stack(const stack& other) {
	/*stackEntry<Type>* tempVar;
	for (tempVar = other.top; tempVar != nullptr; tempVar = tempVar->next()) {

	}
	counter = other.counter;
	top = other.top;*/
	*this = other;
}

template <class Type>
void stack<Type>::push(const Type& value) {
	stackEntry<Type>* item = new stackEntry<Type>(value);
	//pTop->next(item);
	item->next(pTop);
	pTop = item;
	//pTop = item;
	counter++;
}

template <class Type>
void stack<Type>::pop() {
	stackEntry<Type>* oldTop;
	if (pTop == nullptr) {
		return;
	}
	oldTop = pTop;
	pTop = oldTop->next();
	delete oldTop;
	counter--;
}

template <class Type>
void stack<Type>::clear() {
	stackEntry<Type>* entry;
	while (pTop != nullptr) {
		entry = pTop->next();
		delete pTop;
		pTop = entry;
	}
	counter = 0;
}

template <class Type>
void stack<Type>::debug() const
{
	debug(std::cout);
}

template <class Type>
void stack<Type>::debug(std::ostream& out) const
{
	{
		out << "Number of items in stack: " << counter << std::endl;
		out << "Top of stack is entry @" << pTop << std::endl;

		stackEntry<Type>* pNext = pTop;

		while (pNext != nullptr)
		{
			out << "@" << pNext << ", next @" << pNext->next() << ", data = " << pNext->data() << std::endl;
			pNext = pNext->next();
		}
	}
}

#endif /* STACK_H_ */
