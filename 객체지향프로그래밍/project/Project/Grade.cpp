#include "Grade.h"

GradeNode::GradeNode() :grade(0), Pleft(NULL) {}
GradeNode::~GradeNode() {
	delete Pleft;
}