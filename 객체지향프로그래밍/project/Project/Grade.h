#pragma once
#include <iostream>

// �г� ����� ������ ������ Class
class GradeNode {
public:
	int grade;
	GradeNode *Pleft;

	GradeNode();
	virtual ~GradeNode();
};
