#pragma once
#include <string>
#include <fstream>
#include "Contact.h"
#include "Department.h"
#include "Grade.h"
#include "Name.h"
#include "StudentID.h"

// �̸� ����� Linked list�� ������ Class
class NameList {
private:
	NameNode* Phead;

public:
	NameList() :Phead(NULL) {}
	~NameList() {
		delete Phead;
	}
	GradeNode* getGhead();
	StudentIDNode* getIDhead();
	ContactNode* getChead();
	NameNode* insert(char name[], int grade, char studentid[], char contact[]);
	bool pop(char name[]);
	bool sort();
	void get(char name[]);
	void printID();
	void printContct();
	void setSublist();
};