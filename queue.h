/*
 * queue.h
 *
 *  Created on: Apr 17, 2019
 *      Author: dgv130030
 */

#ifndef QUEUE_H_
#define QUEUE_H_
#include <iostream>
#include <cstddef>
#include <cassert>
 //using namespace std;

template <class Type>
class queue;

template <class Type>
class queueEntry
{
	friend class queue<Type>;

protected:
	Type 				dataValue;
	queueEntry<Type>* pNext;

	queueEntry(const Type& newData, queueEntry<Type>* newNext = nullptr) {
		dataValue = newData;
		pNext = newNext;
	}
	virtual ~queueEntry() {

	}
	virtual void next(queueEntry<Type>* pNext) {
		this->pNext = pNext;
	}
	virtual queueEntry<Type>* next() {
		return pNext;
	}
	virtual Type& data() {
		return dataValue;
	}
	virtual const Type& data() const {
		return dataValue;
	}
};

template <class Type>
class queue
{

private:
	queueEntry<Type>* pFront;
	queueEntry<Type>* pEnd;
	std::size_t count;
public:
	queue();
	virtual ~queue() {
		clear();
	}
	queue(const queue& other);
	const queue& operator=(const queue& rhs) {
		if (rhs.pFront) {
			clear();
			queueEntry<Type>* temp = rhs.pFront;
			while (temp) {
				push(temp->data());
				temp = temp->next();
			}
		}
		return *this;
	}
	const Type& front() const {
		assert(pFront != nullptr);
		return pFront;
	}
	Type& front() {
		return pFront->data();
	}

	const Type& back() const {
		assert(pEnd != nullptr);
		return pEnd;
	}
	Type& back() {
		return pEnd->data();
	}
	bool empty() const {
		if (count == 0) {
			return true;
		}
		else {
			return false;
		}
	}
	std::size_t size() const {
		return count;
	}
	void push(const Type& value);
	void pop();
	void clear();
	void debug() const;
	void debug(std::ostream& out) const;
	// used by applications using the queue to work with all
	//  of the items in the queue from end to front.
	void traverse(void (*applicationFunction) (const Type& nextItem));
};

template<class Type>
queue<Type>::queue() {
	count = 0;
	pFront = nullptr;
	pEnd = nullptr;
}

template<class Type>
queue<Type>::queue(const queue& rhs) {
	*this = rhs;
}

template<class Type>
void queue<Type>::clear() {
	queueEntry<Type>* temp;
	while (pFront != nullptr) {
		temp = pFront->next();
		delete pFront;
		pFront = temp;
	}
	count = 0;
	pEnd = nullptr;
}

template<class Type>
void queue<Type>::push(const Type& value) {
	queueEntry<Type>* newNode;
	newNode = new queueEntry<Type>(value);
	if (pEnd == nullptr) {
		pFront = newNode;
	}
	else {
		pEnd->next(newNode);
	}
	pEnd = newNode;
	count++;
}

template<class Type>
void queue<Type>::pop() {
	queueEntry<Type>* oldFront;
	if (count == 0) {
		return;
	}
	oldFront = pFront;
	pFront = oldFront->next();
	delete oldFront;
	if (pFront == nullptr) {
		pEnd = nullptr;
	}
	count--;
}

template<class Type>
void queue<Type>::traverse(void (*applicationFunction) (const Type& nextItem)) {
	queueEntry<Type>* temp;
	temp = pFront;
	while (temp->next() != nullptr) {
		applicationFunction(temp->data());
		temp = temp->next();
	}
}

template<class Type>
void queue<Type>::debug() const
{
	debug(std::cout);
}

template<class Type>
void queue<Type>::debug(std::ostream& out) const
{
	{
		out << "Number of items in queue: " << count << std::endl;
		out << "Front of queue is entry @" << pFront << std::endl;
		out << "End of queue is entry @" << pEnd << std::endl;
		out << std::endl;

		queueEntry<Type>* pNext = pFront;

		while (pNext != nullptr)
		{
			out << "@" << pNext << ", next @" << pNext->next() << ", data = " << pNext->data() << std::endl;
			pNext = pNext->next();
		}
	}
}
#endif /* QUEUE_H_ */