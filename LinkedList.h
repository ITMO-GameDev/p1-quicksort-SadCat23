#pragma once
template <class T>
class LinkedList
{
public:
	struct Node
	{
		T data;
		Node* next;
	};

	Node* head;

public:
	LinkedList() = default;

	void insert(Node* previousNode, Node* newNode);
	void remove(Node* previousNode, Node* deleteNode);
};
