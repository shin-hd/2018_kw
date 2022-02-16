#pragma once
#include <iostream>

// 학년 노드의 정보를 가지는 Class
class GradeNode {
public:
	int grade;
	GradeNode *Pleft;

	GradeNode();
	virtual ~GradeNode();
};
