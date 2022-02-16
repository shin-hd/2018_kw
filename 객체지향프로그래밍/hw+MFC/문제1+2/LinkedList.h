#pragma once
#include <iostream>

using std::ostream;

namespace kw
{
	template<typename T>
	class Node
	{
	public:
		T               mData;
		Node<T>*	mNextNode;

		Node(const T& data)
			:
			mData(data),
			mNextNode(NULL)
		{
		}

		Node(const T& data, Node<T>* nextNode)
			:
			mData(data),
			mNextNode(nextNode)
		{
		}

		Node()
			:
			mData(NULL),
			mNextNode(NULL)
		{
		}
	};

	template <typename T>
	class LinkedList
	{

	private:
		Node<T>*	        mHead;
		unsigned int		mSize;

	public:
		LinkedList();
		~LinkedList();

		virtual T				get(const int index) const;
		virtual bool			set(const int index, const T& data);

		virtual bool			insert(const T& data);
		virtual bool			insert(const int index, const T& data);

		virtual bool			insertHead(const T& data);

		virtual bool			pop();
		virtual bool			pop(const int index);

		virtual unsigned int    size()	const {
			return mSize;
		}
		virtual bool			empty() const {
			return !mHead;
		}

		virtual void			clear();

		virtual bool			sort();
		virtual bool			reverse();

		friend ostream& operator<<(ostream& os, const LinkedList<T>& data)
		{
			if (data.mHead == NULL)
			{
				os << "This linked list is empty." << endl;
			}
			else
			{
				os << "------------------------------------" << endl;
				for (int i = 0; i < data.size(); i++) {
					os << "idx: " << i << ", data: " << data.get(i) << endl;
				}
				os << "------------------------------------" << endl;
			}

			return os;
		}
	};

	template<typename T>
	LinkedList<T>::LinkedList()
	{
		mHead = NULL;
		mSize = 0;
	}

	template<typename T>
	LinkedList<T>::~LinkedList()
	{
		delete mHead;
	}

	// get data in the index
	template <typename T>
	T LinkedList<T>::get(const int index) const {
		Node<T> *temp = new Node<T>;
		temp = mHead->mNextNode;
		for (int i = 0; i < index; i++) {
			temp = temp->mNextNode;
		} // pointing node of index
		return temp->mData;
	}

	// set data at the index
	template <typename T>
	bool LinkedList<T>::set(const int index, const T& data) {
		Node<T> *temp = new Node<T>;
		temp = mHead->mNextNode;
		for (int i = 0; i < index; i++) {
			temp = temp->mNextNode;
		} // pointing node of index
		temp->mData = data;
		return 0;
	}

	// insert data at the tail
	template <typename T>
	bool LinkedList<T>::insert(const T& data) {
		if (mHead == NULL) {
			insertHead(data);
			return 0;
		} // linkedlist is not exist

		Node<T> *insert = new Node<T>;
		Node<T> *cur = new Node<T>;
		insert->mData = data;
		cur = mHead;

		while (cur->mNextNode) {
			cur = cur->mNextNode;
		} // pointing tail
		cur->mNextNode = insert;
		mSize++;
		return 0;
	}

	// insert data at the index
	template <typename T>
	bool LinkedList<T>::insert(const int index, const T& data) {
		if (index >= mSize) {
			cout << "index is too big" << endl;
			return 1;
		} // index exceeds size

		Node<T> *pre = new Node<T>;
		Node<T> *cur = new Node<T>;
		Node<T> *insert = new Node<T>;

		insert->mData = data;
		pre = mHead;
		cur = mHead->mNextNode;
		for (int i = 0; i < index; i++) {
			pre = cur;
			cur = cur->mNextNode;
		} // pointing node of index
		insert->mNextNode = pre->mNextNode;
		pre->mNextNode = insert;
		mSize++;
		return 0;
	}

	// insert head when head is null
	template <typename T>
	bool LinkedList<T>::insertHead(const T& data) {
		Node<T> *head = new Node<T>;
		Node<T> *node = new Node<T>;
		node->mData = data;
		mHead = head;
		head->mNextNode = node;
		mSize = 1;
		return 0;
	}

	// pop data of tail
	template <typename T>
	bool LinkedList<T>::pop() {
		if (empty()) {
			cout << "LinkedList is Empty" << endl;
			return 1;
		} // linkedlist has no data
		Node<T> *pre = new Node<T>;
		Node<T> *cur = new Node<T>;
		cur = mHead;
		while (cur->mNextNode) {
			pre = cur;
			cur = cur->mNextNode;
		} // pointing tail
		pre->mNextNode = NULL;
		delete cur;
		mSize--;
		return 0;
	}

	template <typename T>
	bool LinkedList<T>::pop(const int index) {
		if (empty()) {
			cout << "LinkedList is Empty" << endl;
			return 1;
		} // linkedlist has no data
		if (index >= mSize) {
			cout << "index is too big" << endl;
			return 1;
		} // index exceeds size
		Node<T> *pre = new Node<T>;
		Node<T> *cur = new Node<T>;
		pre = mHead;
		cur = pre->mNextNode;
		for (int i = 0; i < index; i++) {
			pre = cur;
			cur = cur->mNextNode;
		} // pointing node of index
		pre->mNextNode = cur->mNextNode;
		delete cur;
		mSize--;
		return 0;
	}

	// clear linkedlist by deleting all nodes
	template <typename T>
	void LinkedList<T>::clear() {
		Node<T> *pre = new Node<T>;
		Node<T> *cur = new Node<T>;
		cur = mHead;
		while (cur) {
			pre = cur;
			cur = cur->mNextNode;
			delete pre;
		}
		delete cur;
		mHead = NULL;
		mSize = 0;
	}

	// sorting linkedlist by insertion sort algorithm
	template <typename T>
	bool LinkedList<T>::sort() {
		Node<T> *pre = new Node<T>;
		Node<T> *cur = new Node<T>;
		Node<T> *insert = new Node<T>;
		Node<T> *pre_cmp = new Node<T>;
		Node<T> *cmp = new Node<T>;
		pre = mHead->mNextNode;
		cur = pre->mNextNode;
		for (int i = 1; i < mSize; i++) {
			cmp = mHead->mNextNode;
			pre_cmp = mHead;
			insert = cur;
			if (cur->mNextNode != NULL) // cur is not tail
				cur = cur->mNextNode;
			for (int j = 0; j < i; j++) {
				if (cmp->mData > insert->mData) {
					pre->mNextNode = insert->mNextNode;
					insert->mNextNode = cmp;
					pre_cmp->mNextNode = insert;
					break;
				} // insertion
				// set cmp and pre_cmp
				pre_cmp = cmp;
				cmp = cmp->mNextNode;
			}
			// set pre
			if (pre->mNextNode != cur)
				pre = pre->mNextNode;
		}
		return 0;
	}

	// seversing linkedlist
	template <typename T>
	bool LinkedList<T>::reverse() {
		Node<T> *pre = new Node<T>;
		Node<T> *cur = new Node<T>;
		Node<T> *post_rev = new Node<T>;
		Node<T> *reverse = new Node<T>;
		cur = mHead->mNextNode->mNextNode;
		reverse = mHead->mNextNode;
		reverse->mNextNode = NULL;
		for (int i = 0; i < mSize - 1; i++) {
			post_rev = reverse;
			reverse = cur; // cur was pre_rev
			if (cur->mNextNode != NULL)
				cur = cur->mNextNode; // if cur is tail, loop will end.
			reverse->mNextNode = post_rev;
		}
		mHead->mNextNode = reverse;
		return 0;
	}
}