#include <vector>

struct Node
{
	Node* left;
	Node* right;
	int v;
	Node* p;
	int color;
};

Node* nilNode;

void leftRotate(Node** tree, Node* node)
{
	Node* y = node->right;
	if (y == nilNode)
	{
		return;
	}

	node->right = y->left;
	if (y->left != nilNode)
	{
		y->left->p = node;
	}

	y->left = node;

	if (node->p == nilNode)
	{
		*tree = y;
	}
	else if (node->p->left == node)
	{
		node->p->left = y;
	}
	else
	{
		node->p->right = y;
	}



	y->p = node->p;
	node->p = y;
}

void rightRotate(Node** tree, Node* node)
{
	Node* y = node->left;
	if (y == nilNode)
	{
		return;
	}

	node->left = y->right;
	if (y->right != nilNode)
	{
		y->right->p = node;
	}

	y->right = node;
	if (node->p == nilNode)
	{
		*tree = y;
	}
	else if (node->p->left == node)
	{
		node->p->left = y;
	}
	else
	{
		node->p->right = y;
	}

	y->p = node->p;
	node->p = y;
}

void insertFixUp(Node** tree, Node* node)
{
	Node* z = node;
	while (z->p->color == 1)
	{
		if (z->p->p->left == z->p)
		{
			if (z->p->p->right->color == 1)
			{
				z->p->color = 0;
				z->p->p->color = 1;
				z->p->p->right->color = 0;
				z = z->p->p;
			}
			else
			{
				if (z == z->p->right)
				{
					// A zigzag path.
					z = z->p;
					leftRotate(tree, z);
				}

				z->p->color = 0;
				z->p->p->color = 1;
				rightRotate(tree, z->p->p);
			}
		}
		else
		{
			if (z->p->p->left->color == 1)
			{
				z->p->color = 0;
				z->p->p->color = 1;
				z->p->p->left->color = 0;
				z = z->p->p;
			}
			else
			{
				if (z == z->p->left)
				{
					// A zigzag path.
					z = z->p;
					rightRotate(tree, z);
				}

				z->p->color = 0;
				z->p->p->color = 1;
				leftRotate(tree, z->p->p);
			}
		}
	}

	(*tree)->color = 0;
}

void insert(Node** tree, Node* node)
{
	if (node == nullptr)
	{
		return;
	}

	if (*tree == nullptr)
	{
		*tree = node;
		node->p = nilNode;
	}
	else
	{
		Node* c = *tree;
		Node* p = c->p;
		while (c != nilNode)
		{
			p = c;
			if (node->v < c->v)
			{
				c = c->left;
			}
			else
			{
				c = c->right;
			}
		}

		node->p = p;
		if (node->v < p->v)
		{
			p->left = node;
		}
		else
		{
			p->right = node;
		}
	}

	insertFixUp(tree, node);
}

int main()
{
	nilNode = new Node();
	nilNode->color = 0; // Black.

	Node* tree = nullptr;
	std::vector<int> input = { 11, 2, 14, 1, 7, 15, 5, 8 };
	for (size_t i = 0; i < input.size(); ++i)
	{
		Node* newNode = new Node();
		newNode->color = 1;
		newNode->right = nilNode;
		newNode->left = nilNode;
		newNode->v = input[i];

		insert(&tree, newNode);
	}

	// Insert a new node.
	Node* newOne = new Node();
	newOne->v = 4;
	newOne->color = 1;
	insert(&tree, newOne);

	delete nilNode;
	nilNode = nullptr;

	return 0;
}
