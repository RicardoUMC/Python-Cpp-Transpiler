#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <regex>

using namespace std;

void createVector(vector<string> &lines);
void printVector(vector<string> &lines);

int main(void) {
    
    vector<string> Lines;

    createVector(Lines);
    printVector(Lines);

    return 0;
}

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

void printVector(vector<string> &lines) {
    int i = 0;
    for (i; i < lines.size(); i++) {
        cout << lines[i] << endl;
    }  
}
