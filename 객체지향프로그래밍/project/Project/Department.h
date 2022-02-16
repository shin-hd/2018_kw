#pragma once
#include "Node.h"

// 학과 노드의 정보를 가지는 Class
class DepartmentNode :public Node {
public:
	char de_name[32];

	DepartmentNode() :Node(), de_name("") {}
	~DepartmentNode() {}
};