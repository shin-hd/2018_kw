#include "AVLTree.h"

AVLTree::AVLTree(ofstream *fout) {
	root = NULL;
	make_heap(vHeap.begin(), vHeap.end(), compare);
	this->fout = fout;
}

AVLTree::~AVLTree() {
	delete root;
}

bool AVLTree::Insert(StockData *pSto) {
	AVLNode *pNew = new AVLNode;
	pNew->setSD(pSto);
	char *pName = pSto->getName();
	int rotation = 0;

	if (root == NULL) {
		root = pNew;
		return true;
	}

	AVLNode *a = root,      // a-node
			*pa = NULL,     // parent of a
			*p = root,      // moves through the tree
			*pp = NULL,		// parent of p
			*rootSub = NULL;

	while (p != NULL) {
		if (p->getBF() != 0) {
			a = p;
			pa = pp;
		}
		if (strcmp(pName, p->getSD()->getName()) < 0) { // pName < p.getName
			pp = p;
			p = p->getLeft();
		}                                                    // take left branch
		else if (strcmp(pName, p->getSD()->getName()) > 0) { // pName > p.getName
			pp = p;
			p = p->getRight();
		} // take right branch
		else {
			p->setSD(pSto);
			pNew->setSD(NULL);
			delete pNew;
			return true;
		} // k is already in tree, update StockData
	}

	// Insert and rebalance
	if (strcmp(pName, pp->getSD()->getName()) < 0)
		pp->setLeft(pNew);
	else
		pp->setRight(pNew);

	int degree;
	AVLNode *b,	// child of a
			*c;	// child of b

	if (strcmp(pName, a->getSD()->getName()) > 0) { // pName > a.getName
		b = p = a->getRight();
		degree = -1;
	}
	else {
		b = p = a->getLeft();
		degree = 1;
	}

	while (p != pNew) {
		if (strcmp(pName, p->getSD()->getName()) > 0) { // right h++
			p->setBF(-1);
			p = p->getRight();
		}
		else { // left h++
			p->setBF(1);
			p = p->getLeft();
		}
	}

	// tree is balanced
	if (a->getBF() == 0 || a->getBF() + degree == 0) {
		a->setBF(a->getBF() + degree);
		return true;
	}

	// unbalaced
	if (degree == 1) {       // left
		if (b->getBF() == 1) { // LL
			a->setLeft(b->getRight());
			b->setRight(a);
			a->setBF(0);
			b->setBF(0);
			rootSub = b; // b is new root of subtree
		}
		else {       // LR
			c = b->getRight();
			b->setRight(c->getLeft());
			a->setLeft(c->getRight());
			c->setLeft(b);
			c->setRight(a);
			switch (c->getBF()) { // set BF
			case 0:
				b->setBF(0);
				a->setBF(0);
				break;
			case 1:
				a->setBF(-1);
				b->setBF(0);
				break;
			case -1:
				b->setBF(1);
				a->setBF(0);
				break;
			}
			c->setBF(0);
			rootSub = c; // c is the new root of the subtree
		}
	}
	else {                  // right
		if (b->getBF() == -1) { // RR
			a->setRight(b->getLeft());
			b->setLeft(a);
			a->setBF(0);
			b->setBF(0);
			rootSub = b; // b is new root of subtree
		}
		else {       // RL
			c = b->getLeft();
			b->setLeft(c->getRight());
			a->setRight(c->getLeft());
			c->setRight(b);
			c->setLeft(a);
			switch (c->getBF()) { // set BF
			case 0:
				b->setBF(0);
				a->setBF(0);
				break;
			case 1:
				b->setBF(-1);
				a->setBF(0);
				break;
			case -1:
				a->setBF(1);
				b->setBF(0);
				break;
			}
			c->setBF(0);
			rootSub = c; // c is the new root of the subtree
		}
	}

	// Subtree with root b has been rebalanced
	if (pa == NULL)
		root = rootSub;
	else if (a == pa->getLeft())
		pa->setLeft(rootSub);
	else
		pa->setRight(rootSub);
	return true;
}

bool AVLTree::Print() {
	if (!root) // tree is empty
		return false;
	
	// Ascending Print using Inorder traversal
	stack<AVLNode *> s;
	AVLNode *currentNode = root;
	
	ofstream flog("log.txt", ios::app);
	flog << "======== PRINT ========" << endl;
	while (true) {
		while (currentNode) {
			s.push(currentNode);
			currentNode = currentNode->getLeft();
		} // take left branch and push

		// stack is empty
		if (s.empty())
			break;

		currentNode = s.top();
		s.pop();
		printStockInfo(currentNode->getSD());
		currentNode = currentNode->getRight();
	}
	flog << "========================" << endl;
	flog.close();

	return true;
}

bool AVLTree::Search(char *name) {
	AVLNode *pCur = root;

	while (pCur) {
		if (strcmp(name, pCur->getSD()->getName()) < 0) // name < pCur.getName
			pCur = pCur->getLeft();
		else if (strcmp(name, pCur->getSD()->getName()) > 0) // name > pCur.getName
			pCur = pCur->getRight();
		else
			break;
	}

	if (pCur == NULL) // name StokData is not exist
		return false;
	
	StockData *pSD = pCur->getSD(); // pSD is StockData of name
	
	// print
	ofstream flog("log.txt", ios::app);
	flog << "======== SEARCH ========" << endl;
	printStockInfo(pSD);
	flog << "========================" << endl;
	flog.close();
	
	// push heap
	vHeap.push_back(make_pair(make_pair(pSD->getEarning(), pSD->getStockID()), pSD));
	push_heap(vHeap.begin(), vHeap.end(), compare);

	return true;
}

bool AVLTree::Rank() {
	if (vHeap.empty()) // empty heap
		return false;

	StockData *pSto;

	ofstream flog("log.txt", ios::app);
	flog << "======== RANK ========" << endl;
	while (!vHeap.empty()) {
		pSto = vHeap.front().second;					// get StockData
		pop_heap(vHeap.begin(), vHeap.end(), compare);	// heap pop
		vHeap.pop_back();								// vector heap pop
		printStockInfo(pSto);							// print StockData
	}
	flog << "========================" << endl;
	flog.close();

	return true;
}

void AVLTree::printStockInfo(StockData *pStockData) {
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
