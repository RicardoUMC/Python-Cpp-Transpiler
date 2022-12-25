%{
#include <iostream>
#include <string>
#include <cstdio>
using namespace st;

// Declaración de las funciones que se implementarán más adelante
int yylex();
int yyerror(const char*);

// Estructura que se utilizará para almacenar el resultado del análisis
struct Node {
  string value;
  Node* left;
  Node* right;
};

// Variable global que se utilizará para almacenar el resultado del análisis
Node* root;

%}

// Definición de los tokens que se reconocerán en el análisis léxico
%token NUMBER
%token ADDITION
%token SUBTRACTION
%token MULTIPLICATION
%token DIVISION

// Reglas de producción de la gramática del lenguaje
%start expression

%%

expression:
  // Regla para reconocer una expresión numérica
  | NUMBER { root = new Node{$1, nullptr, nullptr}; }

  // Reglas para reconocer una expresión aritmética simple
  | expression ADDITION expression
    {
      root = new Node{"+", $1, $3};
      delete $1;
      delete $3;
    }
  | expression SUBTRACTION expression
    {
      root = new Node{"-", $1, $3};
      delete $1;
      delete $3;
    }
  | expression MULTIPLICATION expression
    {
      root = new Node{"*", $1, $3};
      delete $1;
      delete $3;
    }
  | expression DIVISION expression
    {
      root = new Node{"/", $1, $3};
      delete $1;
      delete $3;
    }
;

// Función que se utilizará para mostrar un mensaje de error en caso de que ocurra un error
int yyerror(const char* message) {
  cout << "Error: " << message << endl;
  return 1;
}

// Función principal que se encargará de ejecutar el análisis léxico y sintáctico
int main() {
  yyparse();
  return 0;
}
