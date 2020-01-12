
#include <iostream>
#include <stack>



template <typename K, typename V>
class Dictionary final
{
private:
	static const bool RED = true;
	static const bool BLACK = false;
	
	class Node {
	public:
		K key;
		V val;
		Node* left, * right;
		bool color;
		Node(K key, V val);
	};
	class Iterator
	{
		friend class Dictionary<K, V>;
	public:
		Iterator(Dictionary<K, V>& dict);;
		void Reset();

		const K& key() const;;
		const V& get() const;;;
		void set(const V& value);;
		void next();;
		void prev();;
		bool hasNext() const;;
		bool hasPrev() const;;
	private:
		Node* current;
		std::stack<Node*> nextStack;
		std::stack<Node*> prevStack;
		int count;
		Dictionary<K, V>& dict;
		
	};

	static bool isRed(Node* nod);

	Node* rotateLeft(Node* h);

	Node* rotateRight(Node* h);

	static void flipColors(Node* h);

	Node* moveRedLeft(Node* h);

	Node* moveRedRight(Node* h);

	Node* fixUp(Node* h);

	Node* minNode(Node* h);

	Node* deleteMin(Node* h);

	Node* insert(Node* h, const K& key, const V& val);

	Node* remove(Node* h, const K& key);

	void recursivePrint(const Node* h) const;

	void recursiveDelete(const Node* h) const;

	Node* getRoot();
	Node* root;
	int dictSize;


public:

	Dictionary();;
	Dictionary(const Dictionary&) = delete;
	Dictionary& operator=(const Dictionary&) = delete;
	~Dictionary();;
	void traverse() const;

	V& search(const K& key);

	bool contains(const K& key);;
	void put(const K& key, const V& value);;
	void remove(const K& key);;
	const V& operator[](const K& key) const;;
	V& operator[](const K& key);;
	int size() const;;
	Iterator iterator();

	Iterator iterator() const;
};


template <typename K, typename V>
Dictionary<K, V>::Node::Node(K key, V val)
{
	this->key = key;
	this->val = val;
	this->color = RED;
	this->right = nullptr;
	this->left = nullptr;
}

template <typename K, typename V>
Dictionary<K, V>::Iterator::Iterator(Dictionary<K, V>& dict): dict(dict)
{
	nextStack = std::stack<Node*>();
	prevStack = std::stack<Node*>();
	current = dict.root;
	count = 0;
	Reset();
}

template <typename K, typename V>
void Dictionary<K, V>::Iterator::Reset()
{
	current = dict.root;
	if (current == nullptr)
	{
		return;
	}
	while (!nextStack.empty())
	{
		nextStack.pop();
	}

	nextStack.push(nullptr);

	while (!prevStack.empty())
	{
		prevStack.pop();
	}
	prevStack.push(dict.root);
	count = 0;
}

template <typename K, typename V>
const K& Dictionary<K, V>::Iterator::key() const
{
	return current->key;
}

template <typename K, typename V>
const V& Dictionary<K, V>::Iterator::get() const
{
	return current->val;
}

template <typename K, typename V>
void Dictionary<K, V>::Iterator::set(const V& value)
{
	current->val = value;
}

template <typename K, typename V>
void Dictionary<K, V>::Iterator::next()
{
	if (current == nullptr) return;

	if (current != dict.root)
	{
		prevStack.push(current);
	}
	if (current->right != nullptr)
	{
		nextStack.push(current->right);
	}
	if (current->left != nullptr)
	{
		current = current->left;
	}
	else
	{
		current = nextStack.top();
		nextStack.pop();
	}
	count++;
}

template <typename K, typename V>
void Dictionary<K, V>::Iterator::prev()
{
	current = prevStack.top();
	prevStack.pop();
	count--;
}

template <typename K, typename V>
bool Dictionary<K, V>::Iterator::hasNext() const
{
	return (count) < dict.dictSize - 1;
}

template <typename K, typename V>
bool Dictionary<K, V>::Iterator::hasPrev() const
{
	return current != dict.root;
}

template <typename K, typename V>
bool Dictionary<K, V>::isRed(Node* nod)
{
	if (nod == nullptr) return false;
	return (nod->color);
}

template <typename K, typename V>
typename Dictionary<K, V>::Node* Dictionary<K, V>::rotateLeft(Node* h)
{
	Node* x = h->right;
	h->right = x->left;
	x->left = h;
	x->color = h->color;
	h->color = RED;
	return x;
}

template <typename K, typename V>
typename Dictionary<K, V>::Node* Dictionary<K, V>::rotateRight(Node* h)
{
	Node* x = h->left;
	h->left = x->right;
	x->right = h;
	x->color = h->color;
	h->color = RED;
	return x;
}

template <typename K, typename V>
void Dictionary<K, V>::flipColors(Node* h)
{
	h->color = !h->color;
	h->left->color = !h->left->color;
	h->right->color = !h->right->color;
}

template <typename K, typename V>
typename Dictionary<K, V>::Node* Dictionary<K, V>::moveRedLeft(Node* h)
{
	flipColors(h);
	if (isRed(h->right->left))
	{
		h->right = rotateRight(h->right);
		h = rotateLeft(h);
		flipColors(h);
	}
	return h;
}

template <typename K, typename V>
typename Dictionary<K, V>::Node* Dictionary<K, V>::moveRedRight(Node* h)
{
	flipColors(h);
	if (isRed(h->left->left))
	{
		h = rotateRight(h);
		flipColors(h);
	}
	return h;
}

template <typename K, typename V>
typename Dictionary<K, V>::Node* Dictionary<K, V>::fixUp(Node* h)
{
	if (isRed(h->right) && !isRed(h->left)) h = rotateLeft(h);
	if (isRed(h->left) && isRed(h->left->left)) h = rotateRight(h);
	if (isRed(h->left) && isRed(h->right)) flipColors(h);
	return h;
}

template <typename K, typename V>
typename Dictionary<K, V>::Node* Dictionary<K, V>::minNode(Node* h)
{
	return (h->left == nullptr) ? h : minNode(h->left);
}

template <typename K, typename V>
typename Dictionary<K, V>::Node* Dictionary<K, V>::deleteMin(Node* h)
{
	if (h->left == nullptr) return nullptr;
	if (!isRed(h->left) && !isRed(h->left->left))
		h = moveRedLeft(h);
	h->left = deleteMin(h->left);
	return fixUp(h);
}

template <typename K, typename V>
typename Dictionary<K, V>::Node* Dictionary<K, V>::insert(Node* h, const K& key, const V& val)
{
	if (h == nullptr)
	{
		Node* valu = new Node(key, val);
		dictSize++;
		return valu;
	}
	if (key == h->key) h->val = val;
	else if (key < h->key) h->left = insert(h->left, key, val);
	else h->right = insert(h->right, key, val);

	h = fixUp(h);

	return h;
}

template <typename K, typename V>
typename Dictionary<K, V>::Node* Dictionary<K, V>::remove(Node* h, const K& key)
{
	if (key < h->key)
	{
		if (!isRed(h->left) && !isRed(h->left->left))
			h = moveRedLeft(h);
		h->left = remove(h->left, key);
	}
	else
	{
		if (isRed(h->left))
			h = rotateRight(h);
		if (key == h->key && h->right == nullptr)
		{
			dictSize--;
			return nullptr;
		}
		if (!isRed(h->right) && !isRed(h->right->left))
			h = moveRedRight(h);
		if (key == h->key)
		{
			Node* mn = minNode(h->right);
			h->val = mn->val;
			h->key = mn->key;
			h->right = deleteMin(h->right);
			dictSize--;
			delete mn;
		}
		else
		{
			h->right = remove(h->right, key);
		}
	}

	return fixUp(h);
}

template <typename K, typename V>
void Dictionary<K, V>::recursivePrint(const Node* h) const
{
	if (h == nullptr)
		return;
	recursivePrint(h->left);
	std::cout << h->key << "=" << h->val << std::endl;
	recursivePrint(h->right);
}

template <typename K, typename V>
void Dictionary<K, V>::recursiveDelete(const Node* h) const
{
	if (h == nullptr)
		return;
	recursiveDelete(h->left);
	recursiveDelete(h->right);
	delete h;
}

template <typename K, typename V>
typename Dictionary<K, V>::Node* Dictionary<K, V>::getRoot()
{
	return root;
}

template <typename K, typename V>
Dictionary<K, V>::Dictionary()
{
	root = nullptr;
	dictSize = 0;
}

template <typename K, typename V>
Dictionary<K, V>::~Dictionary()
{
	recursiveDelete(root);
}

template <typename K, typename V>
void Dictionary<K, V>::traverse() const
{
	recursivePrint(root);
}

template <typename K, typename V>
V& Dictionary<K, V>::search(const K& key)
{
	Node* x = root;
	while (x != nullptr)
	{
		if (key == x->key) return x->val;
		else if (key < x->key) x = x->left;
		else x = x->right;
	}
	auto none = V();
	return none;
}

template <typename K, typename V>
bool Dictionary<K, V>::contains(const K& key)
{
	Node* x = root;
	while (x != nullptr)
	{
		if (key == x->key) return true;
		else if (key < x->key) x = x->left;
		else x = x->right;
	}
	return false;
}

template <typename K, typename V>
void Dictionary<K, V>::put(const K& key, const V& value)
{
	root = insert(root, key, value);
	root->color = BLACK;
}

template <typename K, typename V>
void Dictionary<K, V>::remove(const K& key)
{
	if (!contains(key)) return;
	root = remove(root, key);
	root->color = BLACK;
}

template <typename K, typename V>
const V& Dictionary<K, V>::operator[](const K& key) const
{
	if (!contains(key))
	{
		auto none = V();
		return none;
	};
	return search(key);
}

template <typename K, typename V>
V& Dictionary<K, V>::operator[](const K& key)
{
	if (!contains(key)) put(key, V());
	return search(key);
}

template <typename K, typename V>
int Dictionary<K, V>::size() const
{
	return dictSize;
}

template <typename K, typename V>
typename Dictionary<K, V>::Iterator Dictionary<K, V>::iterator()
{
	Iterator iterator(*this);
	return iterator;
}

template <typename K, typename V>
typename Dictionary<K, V>::Iterator Dictionary<K, V>::iterator() const
{
	Iterator iterator(*this);
	return iterator;
}
