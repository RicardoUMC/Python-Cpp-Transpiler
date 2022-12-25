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

    HashNode(string key, int value);
};

class HashTable
{
private:
    HashNode **table;

public:
    HashTable();
    int hash(string key);
    void insert(string key, int value);
    int search(string key);
};
