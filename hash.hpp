#include <iostream>
#include <string>
#include <cstdint>
#include <iomanip>

using namespace std;

const int TABLE_SIZE = 128;

struct HashNode
{
    int line;
    string lexem;
    string type;
    string value = "0";
    HashNode *next;

    HashNode(const int &line, string &lexem, string &type);
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

    int hash(string &lexem)
    {
        uint32_t seed = 0;
        for (char c : lexem)
        {
            seed = seed * 31 + c;
        }

        return seed % TABLE_SIZE;
    }

    void insert(const int &num_line, string &lexem, string type)
    {
        int index = hash(lexem);
        HashNode *node = new HashNode(num_line, lexem, type);
        node->next = table[index];
        table[index] = node;
        lexem = "";
    }

    HashNode *search(string lexem)
    {
        int index = hash(lexem);
        HashNode *node = table[index];
        while (node != nullptr && node->lexem != lexem)
        {
            node = node->next;
        }
        if (node == nullptr)
        {
            return NULL; // lexem not found
        }
        return node;
    }

    void printTable(void)
    {
        cout << setw(10) << "INDEX" << setw(40) << "TOKEN" << setw(15) << "TYPE" << setw(15) << "VALUE" << endl;
        for (int i = 0; i < TABLE_SIZE; i++)
        {
            cout << setw(10) << i;

            HashNode *node = table[i];
            while (node != nullptr)
            {
                // cout << "Lexem: " << node->lexem << ", Value: " << node->value << endl;
                cout << setw(40) << node->lexem << setw(15) << node->type << setw(15) << node->value;
                
                if (node->next != nullptr) cout << "\n" << setw(10) << " ";

                node = node->next;
            }
            if (node == nullptr) cout << endl;
        }
    }
};