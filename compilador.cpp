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

typedef vector<string> strvec_t;

const strvec_t keywords { "False", "None", "True", "and", "as", "assert", "async", "await", "break", "class", "continue", "def", "del", "elif", "else", "except", "finally", "for", "from", "global", "if", "import", "in", "is", "lambda", "nonlocal", "not", "or", "pass", "raise", "return", "try", "while", "with", "yield"};

strvec_t var_names, function_names;

void createVector(vector<string> &lines);
void printVector(vector<string> &lines);

void lexicalAnalysis(vector<string> &lines);
void sytacticAnalysis(string lines);
void semanticAnalysis(vector<string> &lines);

/**
 * @brief The function `createVector` takes a vector of strings as an argument and fills it with the lines of
 * a text file
 * 
 * @return The vector is being returned.
 */
int main(void) {
    
    vector<string> Lines;

    createVector(Lines);
    // printVector(Lines);
    lexicalAnalysis(Lines);

    return 0;
}

/**
 * @brief printVector Function takes a vector of strings and prints each string in the vector on a new line
 *
 * @param lines a vector of strings that contains the lines of the file
 */
void printVector(vector<string> &lines) {
    for (auto i = lines.cbegin(); i != lines.cend(); i++)
        cout << *i << endl;  
}

/**
 * @brief createVector Opens a file, reads it line by line, and stores each line in a vector
 * 
 * @param lines vector of strings
 */
void createVector(vector<string> &lines) {
    ifstream file;
    string buffer; 

    file.open("./ProyectoFinal.txt", ios::in);

    if (file.fail()) {
        cout << "Error al abrir el fichero." << endl;
        exit(-1);
    }

    while (!file.eof()) {
        
        getline(file, buffer);

        if (regex_match(buffer, regex_comment)) {
            stringstream input_stringstream(buffer);
            getline(input_stringstream, buffer, '#');
        }

        lines.push_back(buffer);
    }

}

void lexicalAnalysis(vector<string> &lines) {

    for_each(lines.begin(), lines.end(), sytacticAnalysis);

    // if (regex_match(buffer, regex_idents))
    // {
    //     buffer = "%" + buffer;
    // }

}

void sytacticAnalysis(string lines) {
    // cout << std::regex_replace(lines, regex_idents, "%");
    string result;

    if (regex_match(lines, regex_idents)) {
        regex_replace(inserter(lines, lines.begin()), lines.begin(), lines.end(), regex_idents, "%");
    }

    cout << lines << endl;
}

void semanticAnalysis(vector<string> &lines) {

}
