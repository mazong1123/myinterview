#include <iostream>
#include <vector>

struct Node
{
	Node* left;
	Node* right;
	Node* p;
	int v;
};

Node* search(Node* tree, int value)
{
	Node* c = tree;
	while (c != nullptr && c->v != value)
	{
		if (value < c->v)
		{
			c = c->left;
		}
		else
		{
			c = c->right;
		}
	}

	return c;
}

Node* min(Node* tree)
{
	if (tree == nullptr)
	{
		return nullptr;
	}

	while (tree->left != nullptr)
	{
		tree = tree->left;
	}

	return tree;
}
Node* max(Node* tree)
{
	if (tree == nullptr)
	{
		return nullptr;
	}

	while (tree->right != nullptr)
	{
		tree = tree->right;
	}

	return tree;
}

Node* predecessor(Node* node)
{
	if (node == nullptr)
	{
		return node;
	}

	Node* c = nullptr;
	Node* p = node->left;
	if (p != nullptr)
	{
		do
		{
			c = p;
			p = p->right;
		} while (p != nullptr);

		return c;
	}

	p = node->p;
	c = node;
	while (p != nullptr && p->left == c)
	{
		c = p;
		p = p->p;
	}

	return p;
}

Node* successor(Node* node)
{
	if (node == nullptr)
	{
		return nullptr;
	}

	Node* successor = node->right;
	if (successor != nullptr)
	{
		while (successor->left != nullptr)
		{
			successor = successor->left;
		}
	}
	else
	{
		successor = node->p;
		while (successor != nullptr && successor->right == node)
		{
			node = successor;
			successor = node->p;
		}
	}

	return successor;
}

void insert(Node** root, Node* newNode)
{
	if (newNode == nullptr)
	{
		return;
	}

	if (root == nullptr || *root == nullptr)
	{
		*root = newNode;
		newNode->p = nullptr;

		return;
	}

	Node* current = *root;
	Node* temp = current;

	while (current != nullptr)
	{
		temp = current;
		if (newNode->v < current->v)
		{
			current = current->left;
		}
		else
		{
			current = current->right;
		}
	};

	newNode->p = temp;
	if (newNode->v < temp->v)
	{
		temp->left = newNode;
	}
	else
	{
		temp->right = newNode;
	}
}

void remove(Node** tree, Node* node)
{
	if (node == nullptr)
	{
		return;
	}

	if (node->left == nullptr)
	{
		if (node->p == nullptr)
		{
			*tree = node->right;
			if (node->right != nullptr)
			{
				node->right->p = nullptr;
			}
		}
		else
		{
			if (node->p->right == node)
			{
				node->p->right = node->right;
			}
			else
			{
				node->p->left = node->right;
			}

			if (node->right != nullptr)
			{
				node->right->p = node->p;
			}
		}
	}
	else if (node->right == nullptr)
	{
		if (node->p == nullptr)
		{
			*tree = node->left;
			if (node->left != nullptr)
			{
				node->left->p = nullptr;
			}
		}
		else
		{
			if (node->p->right == node)
			{
				node->p->right = node->left;
			}
			else
			{
				node->p->left = node->left;
			}

			if (node->left != nullptr)
			{
				node->left->p = node->p;
			}
		}

	}
	else
	{
		// Find successor.
		Node* temp = node->right;
		Node* c = temp->left;
		while (c != nullptr)
		{
			temp = c;
			c = c->left;
		}

		if (temp->p == node)
		{
			if (node->p == nullptr)
			{
				*tree = temp;
				if (temp != nullptr)
				{
					temp->p = nullptr;
				}
			}
			else
			{
				if (node->p->right == node)
				{
					node->p->right = temp;
				}
				else
				{
					node->p->left = temp;
				}

				if (temp != nullptr)
				{
					temp->p = node->p;
				}
			}
			temp->left = node->left;
			node->left->p = temp;
		}
		else
		{
			temp->p->left = temp->right;
			if (temp->right != nullptr)
			{
				temp->right->p = temp->p;
			}

			if (node->p == nullptr)
			{
				*tree = temp;
			}
			else if (node->p->right == node)
			{
				node->p->right = temp;
			}
			else
			{
				node->p->left = temp;
			}

			if (temp != nullptr)
			{
				temp->p = node->p;
			}

			temp->left = node->left;
			node->left->p = temp;

			temp->right = node->right;
			node->right->p = temp;
		}
	}
}


int main()
{
	Node* tree = nullptr;
	std::vector<int> input = { 15, 6, 18, 3, 7, 17, 20, 2, 4, 13, 9 };
	for (auto iter = input.begin(); iter != input.end(); ++iter)
	{
		Node* n = new Node();
		n->v = *iter;

		insert(&tree, n);
	}

	// Search
	Node* s = search(tree, 15);
	std::cout << "search result : " << s->v << std::endl;

	// Min
	Node* minNode = min(tree);
	std::cout << "min result : " << minNode->v << std::endl;

	// Max
	Node* maxNode = max(tree);
	std::cout << "max result : " << maxNode->v << std::endl;

	// Successor
	Node* successorNode = successor(s);
	if (successorNode != nullptr)
	{
		std::cout << "successor of " << s->v << " is " << successorNode->v << std::endl;
	}
	else
	{
		std::cout << "No successor of " << s->v << std::endl;
	}

	// Precessor
	Node* predecessorNode = predecessor(s);
	if (predecessorNode != nullptr)
	{
		std::cout << "predecessor of " << s->v << " is " << predecessorNode->v << std::endl;
	}
	else
	{
		std::cout << "No predecessor of " << s->v << std::endl;
	}

	// Remove
	remove(&tree, s);

	// Release allocated memories of the tree.
	Node* c = tree;
	Node* p = nullptr;
	while (c != nullptr)
	{
		p = c;
		if (c->left != nullptr)
		{
			c = c->left;
		}
		else if (c->right != nullptr)
		{
			c = c->right;
		}
		else
		{
			p = c->p;
			if (p == nullptr)
			{
				delete c;
				c = nullptr;
				continue;
			}

			if (c->v < p->v)
			{
				p->left = nullptr;
			}
			else
			{
				p->right = nullptr;
			}

			delete c;
			c = p;
		}
	}

	return 0;
}
