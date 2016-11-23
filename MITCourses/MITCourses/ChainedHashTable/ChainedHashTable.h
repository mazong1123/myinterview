#ifndef CHAINED_HASH_TABLE_H_
#define CHAINED_HASH_TABLE_H_

#include <vector>
#include <string>
#include <functional>
#include <stdexcept>

struct Node
{
    std::string key;
    std::string value;
    Node* next;
    Node* prev;
};

class ChainedHashTable
{
public:
    ChainedHashTable();
    ~ChainedHashTable();

    void set(const std::string& key, const std::string& value);

    std::string get(const std::string& key);

    void remove(const std::string& key);

private:
    size_t hash(const std::string& key);
    const Node* searchNodeByKey(const Node* firstNode, const std::string& key);

    std::vector<Node*> m_ht;
    std::size_t m_htSize;
    std::size_t m_prime;
};

ChainedHashTable::ChainedHashTable()
{
    this->m_htSize = 3;
    this->m_prime = 2;
    m_ht.resize(this->m_htSize, nullptr);
}

ChainedHashTable::~ChainedHashTable()
{
    for (auto it = this->m_ht.begin(); it != this->m_ht.end(); ++it)
    {
        if (*it != nullptr)
        {
            delete *it;
            *it = nullptr;
        }
    }
}

inline void ChainedHashTable::set(const std::string & key, const std::string& value)
{
    size_t index = hash(key);
    Node* firstNode = this->m_ht[index];
    const Node* n = this->searchNodeByKey(firstNode, key);
    if (n == nullptr)
    {
        Node* newNode = new Node();
        newNode->key = key;
        newNode->value = value;
        newNode->next = firstNode;
        newNode->prev = nullptr;

        if (firstNode != nullptr)
        {
            firstNode->prev = newNode;
        }

        this->m_ht[index] = newNode;

        return;
    }

    // Key already exists.
    const_cast<Node*>(n)->value = value;
}

inline std::string ChainedHashTable::get(const std::string & key)
{
    Node* firstNode = this->m_ht[hash(key)];
    const Node* n = this->searchNodeByKey(firstNode, key);
    if (n == nullptr)
    {
        throw std::invalid_argument("Key does not exist.");
    }

    return n->value;
}

inline void ChainedHashTable::remove(const std::string & key)
{
    size_t index = hash(key);
    Node* firstNode = this->m_ht[index];
    const Node* n = this->searchNodeByKey(firstNode, key);
    if (n == nullptr)
    {
        return;
    }

    if (n->prev == nullptr)
    {
        this->m_ht[index] = n->next;

        if (n->next != nullptr)
        {
            n->next->prev = nullptr;
        }
    }
    else if (n->next == nullptr && n->prev != nullptr)
    {
        n->prev->next = nullptr;
    }
    else
    {
        n->next->prev = n->prev;
        n->prev->next = n->next;
    }

    delete n;
    n = nullptr;
}

inline const Node* ChainedHashTable::searchNodeByKey(const Node* firstNode, const std::string& key)
{
    const Node* n = firstNode;
    while (n != nullptr && n->key != key)
    {
        n = n->next;
    }

    return n;
}

inline size_t ChainedHashTable::hash(const std::string & key)
{
    size_t prehash = std::hash<std::string>{}(key);

    return prehash % this->m_prime;
}

#endif // !CHAINED_HASH_TABLE_H_

