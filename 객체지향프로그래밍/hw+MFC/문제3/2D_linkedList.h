#pragma once
#include <iostream>
#include <string>
using namespace std;

class wordNode {
public:
	string word;
	wordNode* nextWord;

	wordNode() :word(""), nextWord(NULL) {}
	wordNode(string word) :word(word), nextWord(NULL) {}
	wordNode(string word, wordNode* next) :word(word), nextWord(next) {}
	~wordNode() {}
};

class alphabetNode {
public:
	char alphabet;
	wordNode* head;
	alphabetNode* nextAlp;

	alphabetNode() :nextAlp(NULL), head(NULL), alphabet(NULL) {}
	alphabetNode(char alphabet) :alphabet(alphabet), head(NULL), nextAlp(NULL) {}
	alphabetNode(char alphabet, alphabetNode* next) :alphabet(alphabet), head(NULL), nextAlp(next) {}
	~alphabetNode() {}
};

class LinkedList {
private:
	alphabetNode* head;

public:
	LinkedList(); // initialize by inserting a~z
	~LinkedList() {
		delete head;
	}
	
	virtual string getLinkedList()const;
	virtual string getWord(wordNode* head)const; // get words inserted in LinkedList

	virtual bool insertWord(string word); // find alphabetNode which is inserted by word
	virtual bool insertWord(wordNode* head, string word); // inserting func
	virtual bool sort(); // call sort func from 'a' to 'z'
	virtual bool sort(wordNode* head); // sorting func

	// operator overloading
	// print 2D-LinkedList
	friend ostream& operator<<(ostream& os, const LinkedList& data)
	{
		if (data.head == NULL)
		{
			os << "This linked list is empty." << endl;
		}
		else
		{
			os << data.getLinkedList() << endl;
		}
		return os;
	}
};

// constructor
LinkedList::LinkedList() {
	alphabetNode* node = new alphabetNode;
	head = node;
	char ch;

	// fill alphabetNodes with a to z
	for (ch = 'a'; ch <= 'z'; ch++) {
		node->nextAlp = new alphabetNode;
		node = node->nextAlp;
		node->alphabet = ch;
		if (ch != 'z') // if ch is 'z', dose not alloc
			node->nextAlp = new alphabetNode;
	}
}

string LinkedList::getLinkedList() const {
	if (head == NULL) {
		return "";
	} // if head is null, end getLinkedList.
	
	string result = "";
	alphabetNode* node = new alphabetNode;
	node = head;
	
	// add all result at string
	while(node->nextAlp) {
		node = node->nextAlp;
		result += node->alphabet + getWord(node->head) + "\n";
	}
	return result;
}

// get words inserted in LinkedList
string LinkedList::getWord(wordNode* head) const {
	if (head == NULL) {
		return "";
	} // if head is null, end getWord.
	
	string words = "";
	wordNode* node = new wordNode;
	node = head->nextWord;
	
	// add all words at string
	while(node) {
		words += " -> " + node->word;
		node = node->nextWord;
	}
	return words;
}

// find alphabetNode which will be inserted
bool LinkedList::insertWord(string word) {
	char ch = word.at(0);
	alphabetNode* node = new alphabetNode;
	node = head->nextAlp;
	while(node) {
		if (ch == node->alphabet) { // if word's first charactor is same as alphabetNode's alphabet
			if (node->head == NULL)
				node->head = new wordNode;
			insertWord(node->head, word); // real insertion
			return 0;
		}
		node = node->nextAlp;
	}
	cout << "Error has occured in insertWord" << endl;
	return 1; // first charactor is not alphabet
}

// insert word to node
bool LinkedList::insertWord(wordNode* head, string word) {
	wordNode* node = new wordNode;
	wordNode* insert = new wordNode;
	node = head;
	insert->word = word;
	while (node->nextWord) {
		node = node->nextWord;
	} // node would be last node
	node->nextWord = insert;
	return 0;
}

// call sort func from 'a' to 'z'
bool LinkedList::sort() {
	alphabetNode* node = new alphabetNode;
	node = head->nextAlp;
	// sort from a to b
	while(node) {
		sort(node->head);
		node = node->nextAlp;
	}
	return 0;
}

// insertion sort all data in wordlist
bool LinkedList::sort(wordNode* head) {
	if (head == NULL || head->nextWord == NULL) {
		return 0;
	}
	wordNode *pre = new wordNode;
	wordNode *cur = new wordNode;
	wordNode *insert = new wordNode;
	wordNode *pre_cmp = new wordNode;
	wordNode *cmp = new wordNode;
	pre = head->nextWord;
	cur = pre->nextWord;
	while (cur) {
		insert = cur;
		if (cur != NULL)
			cur = cur->nextWord;
		pre_cmp = head;
		cmp = head->nextWord;
		while (cmp->word != insert->word) {
			if (insert->word < cmp->word) {
				pre->nextWord = insert->nextWord;
				insert->nextWord = cmp;
				pre_cmp->nextWord = insert;
				break;
			}
			pre_cmp = cmp;
			cmp = cmp->nextWord;
		} // insertion
		if (pre->nextWord != cur) {
			pre = pre->nextWord;
		}
	}

	return 0;
}