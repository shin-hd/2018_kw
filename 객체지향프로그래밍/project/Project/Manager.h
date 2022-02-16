#pragma once
#include "Contctlist.h"
#include "DepartmentList.h"
#include "Gradelist.h"
#include "Namelist.h"
#include "StudentIDlist.h"

#include <fstream>

// Command.txt�κ��� ��ɾ �а� �ٸ� class����
// �̿��Ͽ� ��ɾ��� ��ü���� ������ �����ϴ� Class
class Manager {
private:
	ContctList contctlist;
	DepartmentList departmentlist;
	GradeList gradelist;
	NameList namelist;
	StudentIDList IDlist;
public:
	void READ_COMMAND();
	bool LOAD();
	bool ADD();
	bool UPDATE();
	bool MODIFY_DEPARTMENT(char before[], char after[]);
	bool DELETE_DEPARTMENT(char department[]);
	void PRINT();
	void PRINT(char department[]);
	void PRINT_STUDENT_ID();
	void PRINT_CONTACT();
	void FIND_NAME(char name[]);
	bool SAVE(char fileName[]);
};