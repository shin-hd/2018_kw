#include "StudentID.h"

StudentIDNode::StudentIDNode() :studentid(""), Pfront(NULL) {}
StudentIDNode::~StudentIDNode() {
	delete Pfront;
}