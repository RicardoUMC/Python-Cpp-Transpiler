#include "hash.hpp"
#include <iostream>
#include <string>
#include <cstdint>

using namespace std;

HashNode::HashNode(const int &line, string &lexem, string &type)
{
    this->line = line;
    this->lexem = lexem;
    this->type = type;
    this->next = nullptr;
}