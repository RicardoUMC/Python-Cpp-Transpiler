%{
#include <stdio.h>
#include "tokens.h"
%}

%start program

%token INTEGER FLOAT STRING NAME
%token FOR WHILE IF ELSE DEF RETURN
%token INDENT DEDENT NEWLINE

%%

[0-9]+ {
    yylval = atoi(yytext);
    return INTEGER;
}

[0-9]+\.[0-9]+ {
    yylval = atof(yytext);
    return FLOAT;
}

'\''([^'\\']|\\.)*'\''|\"([^"\\"]|\\.)*\" {
    yylval = strdup(yytext);
    return STRING;
}

[a-zA-Z_][a-zA-Z0-9_]* {
    yylval = strdup(yytext);
    return NAME;
}

"for" {
    return FOR;
}

"while" {
    return WHILE;
}

"if" {
    return IF;
}

"else" {
    return ELSE;
}

"def" {
    return DEF;
}

"return" {
    return RETURN;
}

"\n" {
    return NEWLINE;
}

" " {
    return INDENT;
}

"\t" {
    return INDENT;
}

"\t" {
    return DEDENT;
}

[ \t\n] ;

%%

int yywrap() {
    return 1;
}
