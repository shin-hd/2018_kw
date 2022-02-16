#pragma once
#include <iostream>

// 학번 노드의 정보를 가지는 Class
class StudentIDNode {
public:
	char studentid[32];
	StudentIDNode *Pfront;

	StudentIDNode();
	virtual ~StudentIDNode();
};