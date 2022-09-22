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
#include <fstream>
#include <vector>
#include <string>
#include <regex>

using namespace std;

typedef vector<string> strvec_t;

const strvec_t keywords { "False", "None", "True", "and", "as", "assert", "async", "await", "break", "class", "continue", "def", "del", "elif", "else", "except", "finally", "for", "from", "global", "if", "import", "in", "is", "lambda", "nonlocal", "not", "or", "pass", "raise", "return", "try", "while", "with", "yield"};

strvec_t var_names, function_names;

void createVector(vector<string> &lines);
void printVector(vector<string> &lines);

void lexicalAnalysis(vector<string> &lines);
void sytacticAnalysis(vector<string> &lines);
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
    printVector(Lines);

    return 0;
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
        lines.push_back(buffer);
    }

}

/**
 * @brief printVector Function takes a vector of strings and prints each string in the vector on a new line
 *
 * @param lines a vector of strings that contains the lines of the file
 */
void printVector(vector<string> &lines) {
    int i = 0;
    for (i; i < lines.size(); i++) {
        cout << lines[i] << endl;
    }  
}

void lexicalAnalysis(vector<string> &lines) {

}

void sytacticAnalysis(vector<string> &lines) {

}

void semanticAnalysis(vector<string> &lines) {

}
