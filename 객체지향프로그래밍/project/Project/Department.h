#pragma once
#include "Node.h"

// �а� ����� ������ ������ Class
class DepartmentNode :public Node {
public:
	char de_name[32];

	DepartmentNode() :Node(), de_name("") {}
	~DepartmentNode() {}
};