#ifndef _BPTREEINDEXNODE_H_
#define _BPTREEINDEXNODE_H_

#include "BpTreeNode.h"

class BpTreeIndexNode : public BpTreeNode {
private:
	map<double, BpTreeNode *> mapIndex; // earning, node element

public:
	BpTreeIndexNode() {}
	~BpTreeIndexNode() {}

	void insertIndexMap(double n, BpTreeNode *pN) {
		mapIndex.insert(make_pair(n, pN));
	}

	void deleteMap(double n) {
		mapIndex.erase(n);
	}

	map<double, BpTreeNode *> *getIndexMap() { return &mapIndex; }
};

#endif