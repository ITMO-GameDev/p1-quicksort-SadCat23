#pragma once
#include "LRB_tree.h"

//////////////
//Dictionary//
//////////////
template <typename K, typename V>
class Dictionary final
{
public:

	Dictionary();

	~Dictionary();

	int getSize() const;

	void put(const K& key, const V& value);

	bool contains(const K& key);

	void remove(const K& key);


	const V& operator[](const K& key) const;

	V& operator[](const K& key);

	

	class Iterator
	{
	public:

		Iterator(LLRBTree<K, V>& llrbTreeRef);

		void next();

		void prev();

		bool hasNext() const;

		bool hasPrev() const;
		
		const K& key() const;

		const V& get() const;

		void set(const V& value);


	private:

		LLRBTree<K, V>& Tree_ref;

		typename LLRBTree<K, V>::Node* iterator_currentNode;

		typename LLRBTree<K, V>::Node* iterator_rootNode;

		typename LLRBTree<K, V>::Node* iterator_lastNode;

		bool FLAG_canDown;
	};

	Iterator iterator();

	const Iterator iterator() const;

private:

	LLRBTree<K, V> TREE;

	int size;
};

template <typename K, typename V>
Dictionary<K, V>::Dictionary()
{
	size = 0;
}

template <typename K, typename V>
Dictionary<K, V>::~Dictionary()
{
}

template <typename K, typename V>
void Dictionary<K, V>::put(const K& key, const V& value)
{
	TREE.insert(key, value);
	++size;
}

template <typename K, typename V>
void Dictionary<K, V>::remove(const K& key)
{
	if (contains(key))
	{
		TREE.remove(key);
		--size;
	}
}

template <typename K, typename V>
bool Dictionary<K, V>::contains(const K& key)
{
	return TREE.search(key) != nullptr;
}

template <typename K, typename V>
const V& Dictionary<K, V>::operator[](const K& key) const
{
	V* searchedElement = TREE.search(key);

	if (searchedElement != nullptr)
	{
		return *searchedElement;
	}

	return *new V();
}

template <typename K, typename V>
V& Dictionary<K, V>::operator[](const K& key)
{
	V* setterElement = TREE.search(key);

	if (setterElement != nullptr)
	{
		return *setterElement;
	}

	V& defaultValue = *new V();

	TREE.insert(key, defaultValue);

	return defaultValue;
}

template <typename K, typename V>
int Dictionary<K, V>::getSize() const
{
	return size;
}

////////////
//Iterator//
////////////


template <typename K, typename V>
Dictionary<K, V>::Iterator::Iterator(LLRBTree<K, V>& llrbTreeRef) : Tree_ref(llrbTreeRef)
{
	iterator_currentNode = llrbTreeRef.root;
	iterator_rootNode = llrbTreeRef.root;

	iterator_lastNode = iterator_currentNode;

	while (iterator_lastNode->right != nullptr)
	{
		iterator_lastNode = iterator_lastNode->right;
	}

	if (iterator_lastNode->left != nullptr)
	{
		iterator_lastNode = iterator_lastNode->left;
	}

	FLAG_canDown = true;
}


template <typename K, typename V>
typename Dictionary<K, V>::Iterator Dictionary<K, V>::iterator()
{
	return *(new Iterator(this->TREE));
}

template <typename K, typename V>
const typename Dictionary<K, V>::Iterator Dictionary<K, V>::iterator() const
{
	return *(new Iterator(this->TREE));
}

template <typename K, typename V>
void Dictionary<K, V>::Iterator::next()
{
	if (FLAG_canDown)
	{
		if (iterator_currentNode->left != nullptr)
		{
			iterator_currentNode = iterator_currentNode->left;
		}
		else
		{
			FLAG_canDown = false;
		}
	}

	if (!FLAG_canDown)
	{
		while (true)
		{
			typename LLRBTree<K, V>::Node* tmp = iterator_currentNode;

			if (iterator_currentNode == iterator_rootNode)
			{
				break;
			}

			iterator_currentNode = iterator_currentNode->parent;

			if (iterator_currentNode->right != nullptr && iterator_currentNode->right != tmp)
			{
				break;
			}
		}

		if (iterator_currentNode == iterator_rootNode)
		{
			iterator_rootNode = iterator_currentNode->right;
		}

		iterator_currentNode = iterator_currentNode->right;

		FLAG_canDown = true;
	}
}

template <typename K, typename V>
void Dictionary<K, V>::Iterator::prev()
{
	if (iterator_currentNode == iterator_currentNode->parent->left)
	{
		iterator_currentNode = iterator_currentNode->parent;
	}
	else
	{
		if (iterator_currentNode->parent->left == nullptr)
		{
			iterator_currentNode = iterator_currentNode->parent;
		}
		else
		{
			iterator_currentNode = iterator_currentNode->parent->left;

			while (iterator_currentNode->right != nullptr)
			{
				iterator_currentNode = iterator_currentNode->right;
			}
		}
	}
}

template <typename K, typename V>
const K& Dictionary<K, V>::Iterator::key() const
{
	return iterator_currentNode->key;
}

template <typename K, typename V>
const V& Dictionary<K, V>::Iterator::get() const
{
	return iterator_currentNode->val;
}

template <typename K, typename V>
void Dictionary<K, V>::Iterator::set(const V& value)
{
	iterator_currentNode->val = value;
}



template <typename K, typename V>
bool Dictionary<K, V>::Iterator::hasNext() const
{
	return iterator_currentNode != iterator_lastNode;
}

template <typename K, typename V>
bool Dictionary<K, V>::Iterator::hasPrev() const
{
	return iterator_currentNode != Tree_ref.root;
}




