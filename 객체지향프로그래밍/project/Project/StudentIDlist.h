#pragma once
#include "StudentID.h"

// �й� ����� Linked list�� ������ class
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