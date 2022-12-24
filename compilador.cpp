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
};

typedef node *nodep_t;
typedef vector<string> strvec_t;

const strvec_t keywords{"False", "None", "True", "and", "as", "assert", "async", "await", "break", "class", "continue", "def", "del", "elif", "else", "except", "finally", "for", "from", "global", "if", "import", "in", "is", "lambda", "nonlocal", "not", "or", "pass", "raise", "return", "try", "while", "with", "yield"};

strvec_t var_names, function_names;

void createVector(vector<string> &lines);
void printVector(vector<string> &lines);

void lexicalAnalysis(vector<string> &lines, vector<nodep_t> &tokens, vector<int> &identations);
void syntacticAnalysis(vector<string> &lines);
void semanticAnalysis(vector<string> &lines);

void removeIdents(string &lines, vector<int> &identations);
int generateTokens(const int num_line, string &line, vector<nodep_t> &tokens);
int addToken(const int num_line, string &token, string type, vector<nodep_t> &tokens);

/**
 * @brief The function `createVector` takes a vector of strings as an argument and fills it with the lines of
 * a text file
 *
 * @return The vector is being returned.
 */
int main(void)
{
    vector<string> Lines;
    vector<nodep_t> Tokens;
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

void lexicalAnalysis(vector<string> &lines, vector<nodep_t> &tokens, vector<int> &identations)
{
    int i;
    for (i = 0; i < lines.size(); i++)
    {
        removeIdents(lines.at(i), identations);
        generateTokens(i + 1, lines.at(i), tokens);
    }

    /* Printing the lines of the file and the identation of each line. */
    // for (i = 0; i < tokens.size(); i++)
    // {
    //     cout << "[line:" << tokens[i]->line << " token:" << tokens[i]->literal << " type:" << tokens[i]->type << "]" << endl;
    // }

    int linea = 1;
    cout << "1 -- ";
    for (i = 0; i < tokens.size(); i++)
    {
        if (tokens[i]->line != linea)
        {
            cout << endl;
            linea = tokens[i]->line;
            cout << linea << " -- ";
        }
        cout << tokens[i]->type << "(" << tokens[i]->literal << ") ";
    }
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
 * @brief It takes a line of text, and breaks it up into tokens
 *
 * @param num_line The line number of the line being processed.
 * @param lines a string that contains the line of code.
 * @param tokens vector of tokens.
 */
int generateTokens(const int num_line, string &line, vector<nodep_t> &tokens)
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
                        addToken(num_line, buffer, "_INT_", tokens);

                    else if (regex_match(buffer, regex_float))
                        addToken(num_line, buffer, "_FLOAT_", tokens);

                    else addToken(num_line, buffer, "_VAR_ID_", tokens);
                }

                buffer = line[i++];
                addToken(num_line, buffer, "_COMA_", tokens);

                while (line[i] == ' ')
                    i++;
            }

            else if (line[i] == '.')
            {
                if (buffer != "")
                    addToken(num_line, buffer, "_VAR_ID_", tokens);

                buffer = line[i++];
                addToken(num_line, buffer, "_DOT_", tokens);

                while (line[i] == ' ')
                    i++;
            }

            else if (line[i] == '(')
            {
                if (buffer != "")
                    addToken(num_line, buffer, "_FUNC_ID_", tokens);

                buffer = line[i++];
                addToken(num_line, buffer, "_OPEN_PAR_", tokens);

                while (line[i] == ' ')
                    i++;
            }

            else if (line[i] == ')')
            {
                if (buffer != "")
                {
                    if (regex_match(buffer, regex_int))
                        addToken(num_line, buffer, "_INT_", tokens);

                    else if (regex_match(buffer, regex_float))
                        addToken(num_line, buffer, "_FLOAT_", tokens);

                    else addToken(num_line, buffer, "_VAR_ID_", tokens);
                }

                buffer = line[i++];
                addToken(num_line, buffer, "_CLOSE_PAR_", tokens);

                while (line[i] == ' ')
                    i++;
            }

            else if (line[i] == '[')
            {
                if (buffer != "")
                    addToken(num_line, buffer, "_ARRAY_ID_", tokens);

                buffer = line[i++];
                addToken(num_line, buffer, "_OPEN_BRACKET_", tokens);

                while (line[i] == ' ')
                    i++;
            }

            else if (line[i] == ']')
            {
                if (buffer != "" && tokens[tokens.size() - 1]->type == "_OPEN_BRACKET_")
                    addToken(num_line, buffer, "_VAR_ID_", tokens);

                if (buffer != "")
                    addToken(num_line, buffer, "_ARRAY_VALUE_", tokens);

                buffer = line[i++];
                addToken(num_line, buffer, "_CLOSE_BRACKET_", tokens);

                while (line[i] == ' ')
                    i++;
            }

            else if (line[i] == '=')
            {
                if (buffer != "")
                    addToken(num_line, buffer, "_VAR_ID_", tokens);

                buffer = line[i++];
                addToken(num_line, buffer, "_OPERATOR_", tokens);

                while (line[i] == ' ')
                    i++;
            }

            else if (line[i] == '+' || line[i] == '-' || line[i] == '/' || line[i] == '*')
            {
                if (buffer != "") 
                {
                    if (regex_match(buffer, regex_int))
                        addToken(num_line, buffer, "_INT_", tokens);

                    else if (regex_match(buffer, regex_float))
                        addToken(num_line, buffer, "_FLOAT_", tokens);

                    addToken(num_line, buffer, "_VAR_ID_", tokens);
                }

                buffer = line[i++];
                addToken(num_line, buffer, "_OPERATOR_", tokens);

                while (line[i] == ' ')
                    i++;
            }

            else if (line[i] == ':')
            {
                buffer = line[i++];
                addToken(num_line, buffer, "_NEW_BLOCK_", tokens);

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

                addToken(num_line, buffer, "_STRING_", tokens);

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
            addToken(num_line, buffer, "_INT_", tokens);
            continue;
        }

        else if (regex_match(buffer, regex_float))
        {
            addToken(num_line, buffer, "_FLOAT_", tokens);
            continue;
        }

        bool added = false;
        for (key_i = 0; key_i < keywords.size(); key_i++)
        {
            if (buffer == keywords[key_i])
            {
                string type = "_" + keywords[key_i] + "_";
                addToken(num_line, buffer, type, tokens);
                added = true;

                while (line[i] == ' ')
                    i++;

                i--;
                break;
            }
        }

        if (!added)
        {
            addToken(num_line, buffer, "_VAR_ID_", tokens);

            while (line[i] == ' ')
                i++;

            i--;
        }
    }

    return 0;
}

int addToken(const int num_line, string &token, string type, vector<nodep_t> &tokens)
{
    nodep_t aux_token;
    aux_token = new (node);
    aux_token->line = num_line;
    aux_token->type = type;
    aux_token->literal = token;
    tokens.push_back(aux_token);
    token = "";

    return 0;
}
