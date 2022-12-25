#include "hash.hpp"
#include <iostream>
#include <string>
#include <cstdint>

using namespace std;

const int TABLE_SIZE = 128;

struct HashNode
{
    string key;
    int value;
    HashNode *next;

    HashNode(string key, int value)
    {
        this->key = key;
        this->value = value;
        this->next = nullptr;
    }
};

class HashTable
{
private:
    HashNode **table;

public:
    HashTable()
    {
        table = new HashNode *[TABLE_SIZE]();
    }

    int hash(string key)
    {
        uint32_t seed = 0;
        for (char c : key)
        {
            seed = seed * 31 + c;
        }

        return seed % TABLE_SIZE;
    }

    void insert(string key, int value)
    {
        int index = hash(key);
        HashNode *node = new HashNode(key, value);
        node->next = table[index];
        table[index] = node;
    }

    int search(string key)
    {
        int index = hash(key);
        HashNode *node = table[index];
        while (node != nullptr && node->key != key)
        {
            node = node->next;
        }
        if (node == nullptr)
        {
            return -1; // Key not found
        }
        return node->value;
    }
};

