/**
 * @file compilador.cpp
 * @author Ricardo Uriel Mora Campos (rurimoca@gmail.com)
 * @brief Transpiler from Python code to C++ code.
 * @version 1.0
 * @date 2022-09-7
 *
 * @copyright Copyright (c) 2022
 *
 */

#include "hash.hpp"
#include <iostream>
#include <iterator>
#include <algorithm>
#include <fstream>
#include <vector>
#include <string>
#include <regex>

using namespace std;

const regex regex_comment("(.*)#(.*)");
const regex regex_idents("[\\s]{4}(.*)");
const regex regex_tabs("¬+(.*)");
const regex regex_int("[\\d]+");
const regex regex_float("[\\d]+(.)[\\d]+");

struct node
{
    int line;
    string literal;
    string type;
    string valor;
};

typedef node *nodep_t;
typedef vector<string> strvec_t;

const strvec_t keywords{"False", "None", "True", "and", "as", "assert", "async", "await", "break", "class", "continue", "def", "del", "elif", "else", "except", "finally", "for", "from", "global", "if", "import", "in", "is", "lambda", "nonlocal", "not", "or", "pass", "raise", "return", "try", "while", "with", "yield"};

strvec_t var_names, function_names;

void createVector(vector<string> &lines);
void printVector(vector<string> &lines);

void lexicalAnalysis(vector<string> &lines, HashTable &table, vector<int> &identations);
void syntacticAnalysis(vector<string> &lines);
void semanticAnalysis(vector<string> &lines);

void removeIdents(string &lines, vector<int> &identations);
int generateTokens(const int num_line, string &line, HashTable &table);

/**
 * @brief The function `createVector` takes a vector of strings as an argument and fills it with the lines of
 * a text file
 *
 * @return The vector is being returned.
 */
int main(void)
{
    vector<string> Lines;
    HashTable table;
    vector<int> Identations;

    createVector(Lines);
    lexicalAnalysis(Lines, table, Identations);

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

void lexicalAnalysis(vector<string> &lines, HashTable &table, vector<int> &identations)
{
    int i;
    for (i = 0; i < lines.size(); i++)
    {
        removeIdents(lines.at(i), identations);
        generateTokens(i + 1, lines.at(i), table);
    }

    table.printTable();
}

void syntacticAnalysis(vector<string> &lines)
{
}

void semanticAnalysis(vector<string> &lines)
{
}

/**
 * @brief It removes the identations from the code and stores them in a vector
 *
 * @param lines the string that contains the code
 * @param identations vector of ints that will store the identation level of each line.
 */
void removeIdents(string &lines, vector<int> &identations)
{
    int count = 0;

    while (lines[0] == ' ' && lines[1] == ' ' && lines[2] == ' ' && lines[3] == ' ')
    {
        count++;

        int i;
        string buffer = "";
        for (i = 4; i < lines.size(); i++)
            buffer += lines[i];

        lines = buffer;
    }

    identations.push_back(count);

    /*
    while (count > 0)
    {
        lines = "->" + lines;
        count--;
    }
    */
}

/**
 * @brief It takes a line of text, and breaks it up into table
 *
 * @param num_line The line number of the line being processed.
 * @param lines a string that contains the line of code.
 * @param table vector of table.
 */
int generateTokens(const int num_line, string &line, HashTable &table)
{
    if (line[0] == '\0')
        return -1;

    if (line[0] == ' ')
    {
        cout << "ERROR: Line " << num_line << " begin with space(s)." << endl;
        return -4;
    }

    int i, key_i;

    string buffer = "";
    for (i = 0; i < line.size(); i++)
    {
        while (line[i] != ' ' && line[i] != '\0')
        {
            if (line[i] == ',')
            {
                if (buffer != "") 
                {
                    if (regex_match(buffer, regex_int))
                        table.insert(num_line, buffer, "_INT_");

                    else if (regex_match(buffer, regex_float))
                        table.insert(num_line, buffer, "_FLOAT_");

                    else table.insert(num_line, buffer, "_VAR_ID_");
                }

                buffer = line[i++];
                table.insert(num_line, buffer, "_COMA_");

                while (line[i] == ' ')
                    i++;
            }

            else if (line[i] == '.')
            {
                if (buffer != "")
                    table.insert(num_line, buffer, "_VAR_ID_");

                buffer = line[i++];
                table.insert(num_line, buffer, "_DOT_");

                while (line[i] == ' ')
                    i++;
            }

            else if (line[i] == '(')
            {
                if (buffer != "")
                    table.insert(num_line, buffer, "_FUNC_ID_");

                buffer = line[i++];
                table.insert(num_line, buffer, "_OPEN_PAR_");

                while (line[i] == ' ')
                    i++;
            }

            else if (line[i] == ')')
            {
                if (buffer != "")
                {
                    if (regex_match(buffer, regex_int))
                        table.insert(num_line, buffer, "_INT_");

                    else if (regex_match(buffer, regex_float))
                        table.insert(num_line, buffer, "_FLOAT_");

                    else table.insert(num_line, buffer, "_VAR_ID_");
                }

                buffer = line[i++];
                table.insert(num_line, buffer, "_CLOSE_PAR_");

                while (line[i] == ' ')
                    i++;
            }

            else if (line[i] == '[')
            {
                if (buffer != "")
                    table.insert(num_line, buffer, "_ARRAY_ID_");

                buffer = line[i++];
                table.insert(num_line, buffer, "_OPEN_BRACKET_");

                while (line[i] == ' ')
                    i++;
            }

            else if (line[i] == ']')
            {
                if (buffer != "" && table.search("["))
                    table.insert(num_line, buffer, "_VAR_ID_");

                if (buffer != "")
                    table.insert(num_line, buffer, "_ARRAY_VALUE_");

                buffer = line[i++];
                table.insert(num_line, buffer, "_CLOSE_BRACKET_");

                while (line[i] == ' ')
                    i++;
            }

            else if (line[i] == '=')
            {
                if (buffer != "")
                    table.insert(num_line, buffer, "_VAR_ID_");

                buffer = line[i++];
                table.insert(num_line, buffer, "_OPERATOR_");

                while (line[i] == ' ')
                    i++;
            }

            else if (line[i] == '+' || line[i] == '-' || line[i] == '/' || line[i] == '*')
            {
                if (buffer != "") 
                {
                    if (regex_match(buffer, regex_int))
                        table.insert(num_line, buffer, "_INT_");

                    else if (regex_match(buffer, regex_float))
                        table.insert(num_line, buffer, "_FLOAT_");

                    table.insert(num_line, buffer, "_VAR_ID_");
                }

                buffer = line[i++];
                table.insert(num_line, buffer, "_OPERATOR_");

                while (line[i] == ' ')
                    i++;
            }

            else if (line[i] == ':')
            {
                buffer = line[i++];
                table.insert(num_line, buffer, "_NEW_BLOCK_");

                while (line[i] == ' ')
                    i++;
            }

            else if (line[i] == '"')
            {
                buffer += line[i++];
                while (line[i] != '"' && line[i] != '\0')
                    buffer += line[i++];
                    
                if (line[i] != '\0')
                    buffer += line[i++];

                table.insert(num_line, buffer, "_STRING_");

                while (line[i] == ' ')
                    i++;
            }

            else 
                buffer += line[i++];
        }

        if (line[i] == '\0' && buffer == "")
            return 0;

        if (regex_match(buffer, regex_int))
        {
            table.insert(num_line, buffer, "_INT_");
            continue;
        }

        else if (regex_match(buffer, regex_float))
        {
            table.insert(num_line, buffer, "_FLOAT_");
            continue;
        }

        bool added = false;
        for (key_i = 0; key_i < keywords.size(); key_i++)
        {
            if (buffer == keywords[key_i])
            {
                string type = "_" + keywords[key_i] + "_";
                table.insert(num_line, buffer, type);
                added = true;

                while (line[i] == ' ')
                    i++;

                i--;
                break;
            }
        }

        if (!added)
        {
            table.insert(num_line, buffer, "_VAR_ID_");

            while (line[i] == ' ')
                i++;

            i--;
        }
    }

    return 0;
}

