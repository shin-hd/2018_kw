#include "Graph.h"
#include "Stack.h"
#include "MinHeap.h"
#include <set>
#include <algorithm>
using namespace std;

#define DFS_FIRST_PATH

Graph::Graph()
{
    // TODO: implement
	m_pVHead = NULL;
	m_vSize = 0;
}
Graph::~Graph()
{
    // TODO: implement
	Clear();
}

void Graph::AddVertex(int vertexKey) {
	Vertex* newVertex = new Vertex(vertexKey);
	
	Vertex* prevVertex = NULL;
	Vertex* currentVertex = m_pVHead;
	while (currentVertex) { // get Vertex of startVertexKey
		if (currentVertex->GetKey() > vertexKey)
			break;
		prevVertex = currentVertex;
		currentVertex = currentVertex->GetNext();
	}
	if (prevVertex == NULL)	// empty graph
		m_pVHead = newVertex;
	else {
		newVertex->SetNext(currentVertex);
		prevVertex->SetNext(newVertex);
	}
	m_vSize++;
}

void Graph::AddEdge(int startVertexKey, int endVertexKey, int weight) {
	Vertex* currentVertex = m_pVHead;
	while (currentVertex) { // get Vertex of startVertexKey
		if (currentVertex->GetKey() == startVertexKey)
			break;
		currentVertex = currentVertex->GetNext();
	}
	if (currentVertex == NULL)
		return;	// not exist startVertex
	
	currentVertex->AddEdge(endVertexKey, weight);
}

Vertex* Graph::FindVertex(int key) {
	Vertex* currentVertex = m_pVHead;
	while (currentVertex) {
		if (currentVertex->GetKey() == key) break;
		currentVertex = currentVertex->GetNext();
	}
	return currentVertex;
}

int Graph::Size() const {
	return m_vSize;
}

void Graph::Clear() {
	delete m_pVHead;
}

void Graph::Print(ofstream& fout) {
	if (m_pVHead == NULL)
		throw 2;	// GraphNotExist

	Vertex* currentVertex = m_pVHead;
	while (currentVertex) {
		Edge* currentEdge = currentVertex->GetHeadOfEdge();
		for (int i = 0; i < m_vSize; i++) {
			if (currentEdge != NULL && currentEdge->GetKey() == i) {	// print edge weight, if i is key
				fout << currentEdge->GetWeight() << " ";
				currentEdge = currentEdge->GetNext();
			}
			else
				fout << "0 ";	// print 0, if edge is not exist
		}
		fout << endl;
		currentVertex = currentVertex->GetNext();
	}
}

bool Graph::IsNegativeEdge() {
	Vertex* currentVertex = m_pVHead;
	while (currentVertex) {
		Edge* currentEdge = currentVertex->GetHeadOfEdge();
		while (currentEdge) {
			if (currentEdge->GetKey() < 0)
				return true;	// has negative edge
			currentEdge = currentEdge->GetNext();
		}
		currentVertex = currentVertex->GetNext();
	}
	return false;	// has only positive edge
}

vector<int> Graph::FindPathDfs(int startVertexKey, int endVertexKey) {
	if (m_pVHead == NULL)
		throw 2;	// GraphNotExist
	if (startVertexKey >= Size() || startVertexKey < 0 || endVertexKey >= Size() || endVertexKey < 0 )
		throw 1;	// InvalidVertexKey
	if (IsNegativeEdge())
		throw 3;	// InvalidAlgorithm
	
	vector<int> resultVector;

	Stack<pair<Vertex*, int>> DfsStack; // key, weight
	bool* visitedVertex = new bool[m_vSize];
	for (int i = 0; i < m_vSize; i++) { // initialize
		visitedVertex[i] = false;
	}
	visitedVertex[startVertexKey] = true;

	int key = startVertexKey;
	Edge* currentEdge = NULL;
	int weight = 0;
	
	Vertex* currentVertex = FindVertex(key);
	DfsStack.Push(make_pair(currentVertex, 0)); // psh startVertex, 0

	while(!DfsStack.IsEmpty()){
		currentVertex = DfsStack.Top().first;
		weight += DfsStack.Top().second; // weight
		DfsStack.Pop();
		key = currentVertex->GetKey();
		visitedVertex[key] = true;	// visit

		resultVector.insert(resultVector.begin(), key);
		if (key == endVertexKey) break;	// find vertex

		currentEdge = currentVertex->GetHeadOfEdge();

		int i = 0;
		while (currentEdge) {	// Push unvisited vertex
			if (visitedVertex[currentEdge->GetKey()] == false) {
				DfsStack.Push(make_pair(FindVertex(currentEdge->GetKey()), currentEdge->GetWeight()));
				i++;
			}
			currentEdge = currentEdge->GetNext();
		}

		if (i == 0) { // has no edge
			key = resultVector.front();
			resultVector.erase(resultVector.begin());
			weight -= GetKeyEdge(FindVertex(resultVector.front()), key)->GetWeight();
		}
	}
	delete[] visitedVertex;

	resultVector.push_back(weight);
	return resultVector;
}

vector<int> Graph::FindShortestPathDijkstraUsingSet(int startVertexKey, int endVertexKey) {
	if (m_pVHead == NULL)
		throw 2;	// GraphNotExist
	if (startVertexKey >= Size() || startVertexKey < 0 || endVertexKey >= Size() || endVertexKey < 0 )
		throw 1;	// InvalidVertexKey
	if (IsNegativeEdge())
		throw 3;	// InvalidAlgorithm

	set<pair<int, int>> dijkstraSet;
	
	Edge* startVertexEdge = FindVertex(startVertexKey)->GetHeadOfEdge();
	bool* s = new bool[m_vSize];
	int* dist = new int[m_vSize];
	int* prev = new int[m_vSize];

	for (int i = 0; i < m_vSize; i++) { // initialize
		s[i] = false;
		if (startVertexEdge != NULL && startVertexEdge->GetKey() == i) {
			dist[i] = startVertexEdge->GetWeight();
			prev[i] = startVertexKey;
			startVertexEdge = startVertexEdge->GetNext();
		}
		else
			dist[i] = 10000000 + i;	// 10 milion // LARGE number
		dijkstraSet.insert(make_pair(dist[i], i));
	}
	s[startVertexKey] = true;
	dijkstraSet.erase(make_pair(dist[startVertexKey], startVertexKey));
	dist[startVertexKey] = 0;
	prev[startVertexKey] = 0;
	dijkstraSet.insert(make_pair(dist[startVertexKey], startVertexKey));

	for (int i = 0; i < m_vSize - 2; i++) {
		int u = dijkstraSet.begin()->second;// get minimum path vertex
		dijkstraSet.erase(dijkstraSet.begin());
		s[u] = true;

		Edge* edge = FindVertex(u)->GetHeadOfEdge();
		while (edge != NULL) {
			int w = edge->GetKey();
			if (s[w] == false) {			// unvisited vertex w
				if (dist[w] > dist[u] + edge->GetWeight()) {
					dijkstraSet.erase(make_pair(dist[w], w));
					dist[w] = dist[u] + edge->GetWeight();		// update dist
					prev[w] = u;								// update prev
					dijkstraSet.insert(make_pair(dist[w], w));	// update key(MinWeight)
				}
			}
			edge = edge->GetNext();
		}
	}

	vector<int> resultVector;
	for (int i = endVertexKey; i != startVertexKey; i = prev[i]) {
		resultVector.push_back(i);
	}
	resultVector.push_back(startVertexKey);
	resultVector.push_back(dist[endVertexKey]);

	delete[] s;
	delete[] dist;
	delete[] prev;

	return resultVector;
}

vector<int> Graph::FindShortestPathDijkstraUsingMinHeap(int startVertexKey, int endVertexKey) {
	if (m_pVHead == NULL)
		throw 2;	// GraphNotExist
	if (startVertexKey >= Size() || startVertexKey < 0 || endVertexKey >= Size() || endVertexKey < 0 )
		throw 1;	// InvalidVertexKey
	if (IsNegativeEdge())
		throw 3;	// InvalidAlgorithm

	MinHeap<int, int> dijkstraHeap; // weight, key

	Edge* startVertexEdge = FindVertex(startVertexKey)->GetHeadOfEdge();
	bool* s = new bool[m_vSize];
	int* dist = new int[m_vSize];
	int* prev = new int[m_vSize];

	for (int i = 0; i < m_vSize; i++) { // initialize
		s[i] = false;
		if (startVertexEdge != NULL && startVertexEdge->GetKey() == i) {
			dist[i] = startVertexEdge->GetWeight();
			prev[i] = startVertexKey;
			startVertexEdge = startVertexEdge->GetNext();
		}
		else
			dist[i] = 10000000 + i;	// 10 milion // LARGE number
		dijkstraHeap.Push(dist[i], i);
	}
	s[startVertexKey] = true;
	dist[startVertexKey] = 0;
	prev[startVertexKey] = 0;
	dijkstraHeap.DecKey(dist[startVertexKey], 0);

	for (int i = 0; i < m_vSize - 2; i++) {
		int u = dijkstraHeap.Top().second;	// get key of minimum path vertex
		dijkstraHeap.Pop();
		s[u] = true;
		
		Edge* edge = FindVertex(u)->GetHeadOfEdge();
		while (edge != NULL) {
			int w = edge->GetKey();
			if (s[w] == false) {			// unvisited vertex w
				if (dist[w] > dist[u] + edge->GetWeight()) {
					dijkstraHeap.DecKey(w, dist[u] + edge->GetWeight());	// update key(MinWeight)
					dist[w] = dist[u] + edge->GetWeight();						// update dist
					prev[w] = u;												// update prev
				}
			}
			edge = edge->GetNext();
		}
	}

	vector<int> resultVector;
	for (int i = endVertexKey; i != startVertexKey; i = prev[i]) {
		resultVector.push_back(i);
	}
	resultVector.push_back(startVertexKey);
	resultVector.push_back(dist[endVertexKey]);

	delete[] s;
	delete[] dist;
	delete[] prev;

	return resultVector;
}

vector<int> Graph::FindShortestPathBellmanFord(int startVertexKey, int endVertexKey) {
	if (m_pVHead == NULL)
		throw 2;	// GraphNotExist
	if (startVertexKey >= Size() || startVertexKey < 0 || endVertexKey >= Size() || endVertexKey < 0 )
		throw 1;	// InvalidVertexKey
	
	Edge* startVertexEdge = FindVertex(startVertexKey)->GetHeadOfEdge();
	int* dist = new int[m_vSize];
	int* prev = new int[m_vSize];

	for (int i = 0; i < m_vSize; i++) {	// initialize
		if (startVertexEdge != NULL && startVertexEdge->GetKey() == i) {
			dist[i] = startVertexEdge->GetWeight();
			prev[i] = startVertexKey;
			startVertexEdge = startVertexEdge->GetNext();
		}
		else 
			dist[i] = 10000000 + i;	// 10 milion // LARGE number
	}
	dist[startVertexKey] = 0;
	prev[startVertexKey] = 0;

	for (int k = 2; k <= m_vSize; k++) {
		/*
		for (int v = 0; v < m_vSize; v++) {
			if (v == startVertexKey) continue;
			for (int w = 0; w < m_vSize; w++) {
				Edge* edge = GetKeyEdge(FindVertex(w), v);
				if (edge != NULL) {	// has <w,v> edge
					if (dist[v] > dist[w] + edge->GetWeight()) {
						prev[v] = w;							// update prev[v]
						dist[v] = dist[w] + edge->GetWeight();	// update dist[v]
						if (k == m_vSize) { // graph has negative cycle, if dist can be updated in 
							throw 4;
						}
					}
				}
			}
		}
		*/
		for (int w = 0; w < m_vSize; w++) { // throw vertex w
			Edge* edge = FindVertex(w)->GetHeadOfEdge();
			while (edge != NULL) {
				int key = edge->GetKey();	// key is updated vertex
				if (dist[key] > dist[w] + edge->GetWeight()) {
					prev[key] = w;								// update prev[v]
					dist[key] = dist[w] + edge->GetWeight();	// update dist[v]
					if (k == m_vSize) { // graph has negative cycle, if dist can be updated in 
						throw 4;
					}
				}
				edge = edge->GetNext();
			}

		}
	}
	
	vector<int> resultVector;
	for (int i = endVertexKey; i != 0; i = prev[i]) {
		resultVector.push_back(i);
	}
	resultVector.push_back(dist[endVertexKey]);

	delete[] dist;
	delete[] prev;
	return resultVector;
}

vector<vector<int> > Graph::FindShortestPathFloyd() {
	if (m_pVHead == NULL)
		throw 2;	// GraphNotExist
	
	vector<vector<int>> resultVector;
	Vertex* currentVertex = m_pVHead;
	for (int j = 0; j < m_vSize; j++) {	// initialize
		vector<int> edgeVector;
		Edge* currentEdge = currentVertex->GetHeadOfEdge();
		for (int i = 0; i < m_vSize; i++) {
			if (currentEdge != NULL && currentEdge->GetKey() == i) {
				edgeVector.push_back(currentEdge->GetWeight());
				currentEdge = currentEdge->GetNext();
			}
			else if(j == i)
				edgeVector.push_back(0);
			else
				edgeVector.push_back(10000000);	// LARGE
		}
		resultVector.push_back(edgeVector);
		currentVertex = currentVertex->GetNext();
	}

	// Floyd
	for (int k = 0; k < m_vSize; k++) {
		for (int i = 0; i < m_vSize; i++) {
			for (int j = 0; j < m_vSize; j++) {
				if (resultVector[i][j] > resultVector[i][k] + resultVector[k][j])
					resultVector[i][j] = resultVector[i][k] + resultVector[k][j];
			}
		}
	}

	// if v to v path is negative
	// graph has negative cycle
	for (int i = 0; i < m_vSize; i++) {
		if (resultVector[i][i] < 0)
			throw 4;
	}

	return resultVector;
}

Edge* Graph::GetKeyEdge(const Vertex* vertex, const int key) {
	Edge* currentEdge = vertex->GetHeadOfEdge();
	while (currentEdge) {
		if (currentEdge->GetKey() == key) break;
		currentEdge = currentEdge->GetNext();
	}
	return currentEdge;
}

////////////////////
/* MinHeap Method */
////////////////////

template<typename TKey, typename TValue>
void MinHeap<TKey, TValue>::Push(TKey key, TValue value) {
	m_vec.insert(m_vec.begin(), make_pair(key, value)); // push front
	Heapify(0);	// sort
}

template<typename TKey, typename TValue>
void MinHeap<TKey, TValue>::Pop() {
	if (IsEmpty())
		return;
	
	int heapSize = m_vec.size(); // get size

	pair<TKey, TValue> lastE = m_vec[heapSize - 1];	// get last element

	m_vec[0] = lastE;			// root is lastE
	m_vec.pop_back();			// delete last space

	Heapify(0);					// sort
}

template<typename TKey, typename TValue>
pair<TKey, TValue> MinHeap<TKey, TValue>::Top() {
	return m_vec.front();
}

template<typename TKey, typename TValue>
pair<TKey, TValue> MinHeap<TKey, TValue>::Get(TValue target) {
	int heapSize = m_vec.size();
	for (int i = 0; i < heapSize; i++) {
		if (m_vec[i].second == target)
			return m_vec[i];
	}
	return NULL;
}

template<typename TKey, typename TValue>
bool MinHeap<TKey, TValue>::IsEmpty() {
	return m_vec.empty();
}

template<typename TKey, typename TValue>
void MinHeap<TKey, TValue>::DecKey(TValue target, TKey newKey) {
	int heapSize = m_vec.size();
	int i;
	for (i = 0; i < heapSize; i++) { // find target element
		if (m_vec[i].second == target) {
			m_vec[i].first = newKey;	// update new key which is smaller than old
			break;
		}
	}

	while (i > 0) {
		if (m_vec[(i - 1) / 2].first > m_vec[i].first) {
			pair<TKey, TValue> temp = m_vec[(i - 1) / 2];
			m_vec[(i - 1) / 2] = m_vec[i];
			m_vec[i] = temp;
			i = (i - 1) / 2;
		}
		else
			break;
	}
}

template<typename TKey, typename TValue>
void MinHeap<TKey, TValue>::Heapify(int index) {
	int smallest = index;
	
	// left child
	if (index * 2 + 1 < m_vec.size() && m_vec[index * 2 + 1].first < m_vec[smallest].first)
		smallest = index * 2 + 1;
	
	// right child
	if (index * 2 + 2 < m_vec.size() && m_vec[index * 2 + 2].first < m_vec[smallest].first)
		smallest = index * 2 + 2;

	// swap
	if (smallest != index) {
		pair<TKey, TValue> tempE = m_vec[index];
		m_vec[index] = m_vec[smallest];
		m_vec[smallest] = tempE;
		Heapify(smallest); // recursive
	}
}

////////////////////
/*	Stack Method  */
////////////////////

template <typename T>
Stack<T>::Stack() {
	m_pTop = NULL;
}

template <typename T>
Stack<T>::~Stack() {
	while (m_pTop) {
		Pop();
	}
}

template <typename T>
void Stack<T>::Push(T data) {
	StackNode* newNode = new StackNode(data);
	
	if (m_pTop == NULL)
		m_pTop = newNode;
	else {
		newNode->pNext = m_pTop;
		m_pTop = newNode;
	}
}

template <typename T>
void Stack<T>::Pop() {
	if (IsEmpty())
		return;	//error
	
	StackNode* deleteNode = m_pTop;
	m_pTop = deleteNode->pNext;
	delete deleteNode;
}

template <typename T>
T Stack<T>::Top() {
	return m_pTop->Data;
}

template <typename T>
bool Stack<T>::IsEmpty() {
	if (m_pTop == NULL)
		return true;
	return false;
}