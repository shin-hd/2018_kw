#include "BpTree.h"
#include <algorithm>

BpTree::BpTree(ofstream *fout, int order) {
	root = NULL;
	this->order = order;
	this->fout = fout;
}

BpTree::~BpTree() {
	delete root;
}

void BpTree::Insert(StockData *pSto) {
	double key = pSto->getEarning();      // key = Earning
	vector<pair<int, StockData *>> value; // value = map< id, stock data* >
	value.push_back(make_pair(pSto->getStockID(), pSto));

	if (root == NULL) { // empty B+ tree
		BpTreeNode *pDataNode = new BpTreeDataNode;
		pDataNode->insertDataMap(key, value);
		root = pDataNode;
		return;
	}

	BpTreeNode *pDataNode = searchDataNode(key); // seach data node with key

	map<double, vector<pair<int, StockData *>>> *m = pDataNode->getDataMap();

	if (m->find(key) == m->end()) { // key is not exist
		// insert and split
		m->insert(make_pair(key, value));
		if (exceedDataNode(pDataNode))
			splitDataNode(pDataNode);
	}
	else { // key is exist
		// insert value in mapData vector
		vector<pair<int, StockData *>> mData = m->find(key)->second;	// data vector

		mData.push_back(value[0]);	// push value in data vector
		sort(mData.begin(), mData.end());	// sort data vector
	}
}

BpTreeNode *BpTree::searchDataNode(double n) {
	BpTreeNode *pCur = root;
	map<double, BpTreeNode *>::iterator itIndex; // index iterator

	while (pCur->getMostLeftChild() != NULL) {
		itIndex = pCur->getIndexMap()->begin();

		if (n < itIndex->first) { // mostleft
			pCur = pCur->getMostLeftChild();
		}
		else {
			while (true) {
				itIndex++; // next iterator
				if (itIndex == pCur->getIndexMap()->end() || n < itIndex->first) { // end or lesser
					itIndex--; // prev iterator
					pCur = itIndex->second; // get child
					break;
				}
			}
		}
	}

	return pCur;
}

void BpTree::splitDataNode(BpTreeNode *pDataNode) {
	int splitPosition_data = ceil((order - 1) / 2.0) + 1;

	map<double, vector<pair<int, StockData *>>> *mapData = pDataNode->getDataMap();		// map data
	map<double, vector<pair<int, StockData *>>>::iterator itMapData = mapData->begin();	// map iterator

	double midID;														// split node's first ID
	BpTreeDataNode *child = new BpTreeDataNode;							// new child node
	BpTreeIndexNode* parent = (BpTreeIndexNode*)pDataNode->getParent();	// parent indexnode

	vector<double> keyVector;

	// set child
	for (int i = 1; i < splitPosition_data; i++) {
		itMapData++;
	}
	midID = itMapData->first; // set mid ID
	for (int i = splitPosition_data; itMapData != mapData->end(); i++) {
		child->insertDataMap(itMapData->first, itMapData->second); // fill new child
		keyVector.push_back(itMapData->first);
		itMapData++;
	}

	// erase data
	while (!keyVector.empty()) {
		mapData->erase(keyVector.back());
		keyVector.pop_back();
	}

	// set data link
	BpTreeNode *nextDataNode = pDataNode->getNext();
	if (nextDataNode) {
		nextDataNode->setPrev(child);
		child->setNext(nextDataNode);
	}
	pDataNode->setNext(child);
	child->setPrev(pDataNode);


	if (parent) { // parent is exist
		parent->insertIndexMap(midID, child);
		child->setParent(parent);
		if (exceedIndexNode(parent)) // parent shoud be split
			splitIndexNode(parent);
	}
	else {
		BpTreeIndexNode* parent = new BpTreeIndexNode;
		child->setParent(parent);
		parent->setMostLeftChild(pDataNode);
		pDataNode->setParent(parent);
		parent->insertIndexMap(midID, child); // new parent
		root = parent; // renew root
	}
}

void BpTree::splitIndexNode(BpTreeNode *pIndexNode) {
	int splitPosition_index = ceil(order / 2.0);

	map<double, BpTreeNode*> *mapIndex = pIndexNode->getIndexMap();		// map index
	map<double, BpTreeNode*>::iterator itMapIndex = mapIndex->begin();	// map iterator

	double midID;															// split node's first ID
	BpTreeIndexNode *child = new BpTreeIndexNode;							// new child node
	BpTreeIndexNode* parent = (BpTreeIndexNode*)pIndexNode->getParent();	// parent indexnode

	vector<double> keyVector;

	// set child
	for (int i = 1; i < splitPosition_index; i++) {
		itMapIndex++;
	}
	midID = itMapIndex->first; // set mid ID
	child->setMostLeftChild(itMapIndex->second);
	keyVector.push_back(itMapIndex->first); // push key
	itMapIndex++;
	for (int i = splitPosition_index; itMapIndex != mapIndex->end(); i++) {
		child->insertIndexMap(itMapIndex->first, itMapIndex->second); // fill child
		keyVector.push_back(itMapIndex->first);
		itMapIndex++;
	}

	// erase data
	while (!keyVector.empty()) {
		mapIndex->erase(keyVector.back()); // delete elements which are split
		keyVector.pop_back();
	}

	if (parent) { // parent is exist
		parent->insertIndexMap(midID, child);
		child->setParent(parent);
		if (exceedIndexNode(parent)) // parent should be split
			splitIndexNode(parent);
	}
	else {
		BpTreeIndexNode* parent = new BpTreeIndexNode;
		child->setParent(parent);
		parent->setMostLeftChild(pIndexNode);
		pIndexNode->setParent(parent);
		parent->insertIndexMap(midID, child); // new parent
		root = parent; // renew root
	}
}

bool BpTree::exceedDataNode(BpTreeNode *pDataNode) {
  map<double, vector<pair<int, StockData *>>> *m = pDataNode->getDataMap();

  if (m->size() > order - 1)
    return true;
  else
    return false;
}

bool BpTree::exceedIndexNode(BpTreeNode *pIndexNode) {
	map<double, BpTreeNode *> *m = pIndexNode->getIndexMap();

	if (m->size() > order - 1)
		return true;
	else
		return false;
}

bool BpTree::Print() {
	if (!root)
		return false;

	BpTreeNode* currentNode = root;	// start at root

	while (currentNode->getIndexMap()) { // find most right data node
		map<double, BpTreeNode*>::reverse_iterator itMapIndex = currentNode->getIndexMap()->rbegin();	// map reverse iterator
		currentNode = itMapIndex->second;
	}

	ofstream flog("log.txt", ios::app);
	flog << "======== PRINT ========" << endl;
	while (currentNode) {
		map<double, vector<pair<int, StockData *>>>::reverse_iterator itMapData;
		itMapData = currentNode->getDataMap()->rbegin(); // get map reverse iterator of dataNode's map

		while (itMapData != currentNode->getDataMap()->rend()) { // get vector iterator of map's stockData
			vector<pair<int, StockData*>> dataVector = itMapData->second;
			vector<pair<int, StockData *>>::iterator itDataVector = dataVector.begin();
			itMapData++;

			while (itDataVector != dataVector.end()) { // print stock data
				printStockInfo(itDataVector->second);
				itDataVector++;
			}
		}
		currentNode = currentNode->getPrev();
	}
	flog << "========================" << endl;
	flog.close();

	return true;
}

bool BpTree::Search(double a, double b) {
	if (a<-1.00 || b>100.00 || a > b)
		return false;
	
	BpTreeNode* dataNode = searchDataNode(b);
	if (!dataNode)
		return false; // cannot find data

	map<double, vector<pair<int, StockData *>>> *mapData = dataNode->getDataMap();
	map<double, vector<pair<int, StockData *>>>::reverse_iterator itMapData;
	vector<pair<int, StockData*>>::iterator itDataVector;
	
	ofstream flog("log.txt", ios::app);
	itMapData = mapData->rbegin(); // set iterator of map 

	while (itMapData->first > b) {
		if (itMapData->first < a) // no data in range
			return false;
		++itMapData;
		if (itMapData == mapData->rend())
			return false;
	}

	if (itMapData == mapData->rend()) // end of iierator
		return false;

	flog << "======== SEARCH ========" << endl;
	while (itMapData->first <= b && itMapData->first >= a) { // in range
		itDataVector = itMapData->second.begin();

		while (itDataVector != itMapData->second.end()) { // print data in vector
			printStockInfo(itDataVector->second);
			itDataVector++;
		}

		itMapData++;
		if (itMapData == mapData->rend()) { // all data of dataNode are printed
			dataNode = dataNode->getPrev();	 // get prev data node
			mapData = dataNode->getDataMap();
			itMapData = mapData->rbegin();
		}
	}
	flog << "========================" << endl;
	flog.close();

	return true;
}

void BpTree::printStockInfo(StockData *pStockData) {
	ofstream flog("log.txt", ios::app);
	flog.setf(ios::fixed);
	flog.precision(2);
	flog << pStockData->getStockID() << " " << pStockData->getName() << " "
		<< pStockData->getEarning() << endl;
	flog << "시가: " << pStockData->getOpening_Price() << endl;
	flog << "종가: " << pStockData->getClosing_Price() << endl;
	flog << "거래량: " << pStockData->getVolume() << endl;
	flog << "수익률: " << pStockData->getEarning() << endl << endl;
	flog.close();
}

bool operator <(const pair<int, StockData *> &a, pair<int, StockData *> &b) {
	return a.first < b.first;
}