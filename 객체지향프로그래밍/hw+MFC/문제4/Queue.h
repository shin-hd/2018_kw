#pragma once
#include <iostream>
#include <cstdlib>
#include <time.h>
#include <string>
using namespace std;

class Card {
public:
	string shape;
	int number;
	Card* nextCard;

	Card() :shape(""), number(0), nextCard(NULL) {}
	~Card() {}
};

class Queue {
private:
	int maxSize; // maximum size
	int curSize; // current size
	Card* head;
	int cardIndex[4][13]; // 4(shape) * 13(number)

public:
	Queue() :maxSize(0), curSize(0), head(NULL), cardIndex() {}
	~Queue() {
		delete head;
	}

	virtual void printMenu()const; // print Queue Menu
	virtual void showAll()const; // print Queue
	virtual void setSize() {
		cout << "Size : ";
		cin >> maxSize;
	} // set maximum size
	virtual bool setCard(Card* card);

	virtual void IsEmpty()const { // report Empty
		if (!head || !head->nextCard )
			cout << "Queue is Empty" << endl << endl;
	}
	virtual void IsFull()const { // report Full
		if (maxSize == curSize)
			cout << "Queue is Full" << endl << endl;
	}
	virtual bool Pop(); // delete pregenerated data
	virtual bool Push(); // generate new data and add tail
};

// print Queue Menu
void Queue::printMenu()const {
	cout << "----------------------" << endl;
	cout << "Queue Size : " << maxSize << endl;
	cout << "1. Generate Card." << endl;
	cout << "2. Delete Card." << endl;
	cout << "3. Show all card." << endl;
	cout << "4. End" << endl;
	cout << "----------------------" << endl;
}

// print Queue
void Queue::showAll()const {
	if (!head || !head->nextCard) {
		IsEmpty();
		return;
	}
	Card* card = head->nextCard;
	cout << card->shape << card->number;
	while (card->nextCard) {
		card = card->nextCard;
		cout << " / " << card->shape << card->number;
	}
	cout << endl << endl;
}

// genetate card shape and number
bool Queue::setCard(Card* card) {
	int i, j, k = 0;
	int shape;
	int number;

	// generate random numbers
	srand((unsigned int)time(NULL));
	shape = rand() % 4;
	number = rand() % 13;
	
	// compare card with pregenerated card
	// if card is already exist, shape+1 or number+1
	for (i = 0; i < 13; i++) {
		for (j = 0; j < 4; j++) {
			if (cardIndex[(int)shape][number] != 1)
				break;
			shape = (shape + 1) % 4;
		}
		if (cardIndex[(int)shape][number] != 1) {
			cardIndex[(int)shape][number] = 1;
			k = 1;
			break;
		}
		number = (number + 1) % 13;
	}
	
	if (i = 12 && j == 3 && k) {
		cout << "All cards are used" << endl;
		return 1;
	} // no card that can use is remained (4 x 13)

	card->number = ++number;
	switch (shape) {
	case 0:
		card->shape = "♥"; // ♥
		break;
	case 1:
		card->shape = "♠"; // ♠
		break;
	case 2:
		card->shape = "♣"; //♣
		break;
	case 3:
		card->shape = "◆"; // ♦
		break;
	}
	return 0;
}

// delete pregenerated data
bool Queue::Pop() {
 	if (!head || !head->nextCard) {
		IsEmpty();
		return 0;
	}
	Card* pop = new Card;
	pop = head->nextCard;
	head->nextCard = pop->nextCard;
	cout << pop->shape << pop->number << " is popped" << endl;
	delete pop;
	
	curSize--;
	IsEmpty();
	cout << endl;
	return 0;
}

// generate new data and add tail
bool Queue::Push() {
	if (maxSize == curSize) {
		IsFull();
		return 1;
	}
	Card* push = new Card;
	Card* cur = new Card;
	setCard(push);
	if (!head)
		head = cur;
	else
		cur = head;
	while (cur->nextCard) {
		cur = cur->nextCard;
	}
	cur->nextCard = push;
	curSize++;
	cout << endl;
	return 0;
}