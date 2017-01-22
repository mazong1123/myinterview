#include <iostream>
#include <vector>

struct Node
{
	Node* left;
	Node* right;
	Node* p;
	int v;
};

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

int main()
{
	Node* tree = nullptr;
	std::vector<int> input = { 2, 252, 401, 398, 330, 344, 397, 363 };
	for (auto iter = input.begin(); iter != input.end(); ++iter)
	{
		Node* n = new Node();
		n->v = *iter;

		insert(&tree, n);
	}

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
