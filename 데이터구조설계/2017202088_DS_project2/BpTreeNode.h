#ifndef _BpTreeNode_H_
#define _BpTreeNode_H_

#include "StockData.h"

class BpTreeNode {
private:
	BpTreeNode * pParent;
	BpTreeNode *pMostLeftChild;

public:
	BpTreeNode() {
		pParent = NULL;
		pMostLeftChild = NULL;
	}

	void setMostLeftChild(BpTreeNode *pN) { pMostLeftChild = pN; }
	void setParent(BpTreeNode *pN) { pParent = pN; }

	BpTreeNode *getParent() { return pParent; }
	BpTreeNode *getMostLeftChild() { return pMostLeftChild; }

	virtual ~BpTreeNode() {}

	virtual void setNext(BpTreeNode *pN) {}
	virtual void setPrev(BpTreeNode *pN) {}
	virtual BpTreeNode *getNext() { return NULL; }
	virtual BpTreeNode *getPrev() { return NULL; }

	virtual void insertIndexMap(double, BpTreeNode *) {}
	virtual void insertDataMap(double, vector<pair<int, StockData *>>) {}
	virtual void deleteMap(double) {}
	virtual map<double, vector<pair<int, StockData *>>> *getDataMap() { return NULL; }
	virtual map<double, BpTreeNode *> *getIndexMap() { return NULL; }
};

#endif
