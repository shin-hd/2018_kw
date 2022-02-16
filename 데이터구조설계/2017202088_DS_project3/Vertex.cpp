#include "Vertex.h"

Vertex::Vertex() {
	m_size = 0;
	m_pEHead = NULL;
	m_pNext = NULL;
}

Vertex::Vertex(int key) {
	m_size = 0;
	m_pEHead = NULL;
	m_pNext = NULL;
	m_key = key;
}

Vertex::~Vertex() {
	Clear();
}

void Vertex::SetNext(Vertex* pNext) {
	m_pNext = pNext;
}

int Vertex::GetKey() const {
	return m_key;
}

Vertex* Vertex::GetNext() const {
	return m_pNext;
}

int Vertex::Size() const {
	return m_size;
}

void Vertex::AddEdge(int edgeKey, int weight) {
	Edge* newEdge = new Edge(edgeKey, weight);
	Edge* currentEdge = m_pEHead;
	
	if (currentEdge == NULL)
		m_pEHead = newEdge;
	else {
		while (true) {
			if (currentEdge->GetNext() == NULL) {
				currentEdge->SetNext(newEdge);
				break;
			}
			currentEdge = currentEdge->GetNext();
		}
	}
}

Edge* Vertex::GetHeadOfEdge() const {
	return m_pEHead;
}

void Vertex::Clear() {
	delete m_pNext;
	delete m_pEHead;
}