#pragma once
#include "StudentID.h"

// 학번 노드의 Linked list를 가지는 class
class StudentIDList {
private:
	StudentIDNode* Phead;

public:
	StudentIDList() :Phead(NULL) {}
	~StudentIDList() {
		delete Phead;
	}

	void setHead(StudentIDNode* head);
	StudentIDNode* getHead()const;
	bool sort();
	bool check(char studentID[]);
};