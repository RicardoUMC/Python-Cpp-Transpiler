/**
 * @file compilador.cpp
 * @author Ricardo Uriel Mora Campos (rurimoca@gmail.com)
 * @brief Transpiler from Python code to C++ code.
 * @version 0.1
 * @date 2022-09-7
 *
 * @copyright Copyright (c) 2022
 *
 */

#include <iostream>
#include <iterator>
#include <algorithm>
#include <fstream>
#include <vector>
#include <list>
#include <string>
#include <regex>

using namespace std;

const regex regex_comment("(.*)#(.*)");
const regex regex_idents("[\\s]{4}(.*)");
const regex regex_tabs("¬+(.*)");

struct node
{
    int line;
    string token;
    string type;
    node *next;
};

typedef node *nodep_t;
typedef vector<string> strvec_t;

const strvec_t keywords{"False", "None", "True", "and", "as", "assert", "async", "await", "break", "class", "continue", "def", "del", "elif", "else", "except", "finally", "for", "from", "global", "if", "import", "in", "is", "lambda", "nonlocal", "not", "or", "pass", "raise", "return", "try", "while", "with", "yield"};

strvec_t var_names, function_names;

void createVector(vector<string> &lines);
void printVector(vector<string> &lines);

void lexicalAnalysis(vector<string> &lines, vector<node> &tokens, vector<int> &identations);
void syntacticAnalysis(vector<string> &lines);
void semanticAnalysis(vector<string> &lines);

void removeIdents(string &lines, vector<int> &identations);
void generateTokens(string &lines);

/**
 * @brief The function `createVector` takes a vector of strings as an argument and fills it with the lines of
 * a text file
 *
 * @return The vector is being returned.
 */
int main(void)
{
    vector<string> Lines;
    vector<node> Tokens;
    vector<int> Identations;

    createVector(Lines);
    lexicalAnalysis(Lines, Tokens, Identations);

    // printVector(Lines);
    return 0;
}

/**
 * @brief printVector Function takes a vector of strings and prints each string in the vector on a new line
 *
 * @param lines a vector of strings that contains the lines of the file
 */
void printVector(vector<string> &lines)
{
    for (auto i = lines.cbegin(); i != lines.cend(); i++)
        cout << *i << endl;
}

/**
 * @brief createVector Opens a file, reads it line by line, and stores each line in a vector
 *
 * @param lines vector of strings
 */
void createVector(vector<string> &lines)
{
    ifstream file;
    string buffer;

    file.open("./ProyectoFinal.txt", ios::in);

    if (file.fail())
    {
        cout << "Error al abrir el fichero." << endl;
        exit(-1);
    }

    while (!file.eof())
    {
        getline(file, buffer);

        if (regex_match(buffer, regex_comment))
        {
            stringstream input_stringstream(buffer);
            getline(input_stringstream, buffer, '#');
        }

        lines.push_back(buffer);
    }
}

void lexicalAnalysis(vector<string> &lines, vector<node> &tokens, vector<int> &identations)
{
    // for_each(lines.begin(), lines.end(), removeIdents);

    for (int i = 0; i < lines.size(); i++)
    {
        removeIdents(lines.at(i), identations);
    }


    /* Printing the lines of the file and the identation of each line. */
    for (int i = 0; i < lines.size(); i++)
    {
        cout << lines.at(i) << ":" << identations.at(i) << endl;
    }
}

void syntacticAnalysis(vector<string> &lines)
{
}

void semanticAnalysis(vector<string> &lines)
{
}

/**
 * @brief removeIdents removes the identation of the code recursively
 *
 * @param lines The string that will be modified.
 */
void removeIdents(string &lines, vector<int> &identations)
{
    int count = 0;

    while (lines[0] == ' ' && lines[1] == ' ' && lines[2] == ' ' && lines[3] == ' ')
    {
        count++;

        int i;
        string auxiliar = "";
        for (i = 4; i < lines.size(); i++)
            auxiliar += lines[i];

        lines = auxiliar;
    }

    identations.push_back(count);

    while (count > 0) 
    {
        lines = "->" + lines;
        count--;
    }
}

void generateTokens(string &lines)
{
    if (regex_match(lines, regex_tabs)) 
    {
        if (lines[0] == ' ')
        {
            cout << "ERROR: Line begin with space(s)." << endl;
            exit(-1);
        }
        
        for (int i = 0; i < lines.size() - 1; i++)
        {
            // if (lines[i] == ' ')
        }
    }

    else 
    {
        if (lines[0] == ' ') 
        {
            cout << "ERROR: Line begin with space(s)." << endl;
            exit(-1);
        }

        for (int i = 0; i < lines.size() - 1; i++)
        {   
            if (lines[i] == ' ');
        }
    }
    nodep_t token = new(node);
}
