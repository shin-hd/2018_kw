#pragma once
#include "Contact.h"

// 번호 노드의 Linked list를 가지는 Class
class ContctList {
private:
	ContactNode* Phead;

public:
	ContctList() :Phead(NULL) {}
	~ContctList() {
		delete Phead;
	}

	ContactNode* getHead()const;
	void setHead(ContactNode* head);
	bool sort();
	bool check(char contact[]);
};