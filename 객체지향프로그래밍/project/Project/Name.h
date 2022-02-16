#pragma once
#include "Node.h"
#include "Contact.h"
#include "Grade.h"
#include "StudentID.h"

// 이름 노드의 정보를 가지는 Class
// Node로 상속받은 위-아래 주소로 department 연결
// Node로 상속받은 앞-뒤 주소로 name 연결
class NameNode :public Node {
public:
	char name[32];
	ContactNode *Pright;
	GradeNode *Pleft;
	StudentIDNode *Pfront;

	NameNode() :Node(), name(""), Pright(NULL), Pleft(NULL), Pfront(NULL) {}
	virtual ~NameNode() {}
};