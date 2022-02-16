#pragma once
#include "Department.h"
#include "Name.h"
#include <string>
#include <fstream>

// Department node의 Linked list를 가지는 Class
class DepartmentList {
private:
	DepartmentNode *Phead;

public:
	DepartmentList() :Phead(NULL) {}
	~DepartmentList() {
		delete Phead;
	}

	bool insert(char department[]);
	bool pop(char department[]);
	bool modify_department(char before[], char after[]);
	bool sort();
	bool sort_Ascend();
	bool insertStudent(NameNode* insert, char department[]);
	bool nameSort_Ascend();
	bool nameSort_Descend();
	void print();
	void print(char deoartment[]);
	bool save(char fileName[]);
	bool changeDep(char before[], char after[], char name[], int grade, char studentID[], char contact[]);
	char* getDep(char name[]);
};