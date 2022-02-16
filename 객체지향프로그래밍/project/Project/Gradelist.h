#pragma once
#include "Grade.h"

// 학년 노드의 Linked list를 가지는 Class
class GradeList {
private:
	GradeNode* Phead;

public:
	GradeList();
	~GradeList();
	void setHead(GradeNode* head);
	GradeNode* getHead()const;
};