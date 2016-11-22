struct Node
{
    Node* prev;
    Node* next;
    int key;
};

void insert(Node** l, int newKey)
{
    Node* newNode = new Node();
    newNode->key = newKey;

    if (*l == nullptr)
    {
        *l = newNode;
        (*l)->next = nullptr;
        (*l)->prev = nullptr;

        return;
    }

    newNode->next = *l;
    newNode->prev = nullptr;

    (*l)->prev = newNode;

    (*l) = newNode;
}

Node* search(Node* l, int key)
{
    Node* n = l;
    while (n != nullptr && n->key != key)
    {
        n = n->next;
    }

    return n;
}

void remove(Node** l, int key)
{
    Node* node = search(*l, key);
    if (node == nullptr)
    {
        return;
    }

    if (node->prev != nullptr)
    {
        node->prev->next = node->next;
    }
    else
    {
        // First element deleted. Change the head.
        *l = node->next;
    }

    if (node->next != nullptr)
    {
        node->next->prev = node->prev;
    }    

    delete node;
    node = nullptr;
}

int main()
{
    Node* l = nullptr;
    insert(&l, 3);
    insert(&l, 6);
    insert(&l, 2);

    Node* n = search(l, 6);

    remove(&l, 6);
    remove(&l, 2);
    remove(&l, 3);

    return 0;
}