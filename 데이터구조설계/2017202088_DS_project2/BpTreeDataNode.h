#ifndef _BPTREEDATANODE_H_
#define _BPTREEDATANODE_H_

#include "BpTreeNode.h"

class BpTreeDataNode : public BpTreeNode {
private:
	map<double, vector<pair<int, StockData *>>> mapData; // earning, (ID, data)
	BpTreeNode *pNext;
	BpTreeNode *pPrev;

public:
	BpTreeDataNode() {
		pNext = NULL;
		pPrev = NULL;
	}

	void setNext(BpTreeNode *pN) { pNext = pN; }
	void setPrev(BpTreeNode *pN) { pPrev = pN; }
	BpTreeNode *getNext() { return pNext; }
	BpTreeNode *getPrev() { return pPrev; }

	void insertDataMap(double avgGrade, vector<pair<int, StockData *>> m) {
		mapData.insert(make_pair(avgGrade, m));
	}

	void deleteMap(double n) {
		mapData.erase(n);
	}

	map<double, vector<pair<int, StockData *>>> *getDataMap() { return &mapData; }
};

#endif
