%{
#include <stdio.h>
%}

%token INTEGER FLOAT STRING NAME
%token FOR WHILE IF ELSE DEF RETURN
%token INDENT DEDENT NEWLINE

%start program

%%

program:
    | program statement
    ;

statement:
    | simple_stmt
    | compound_stmt
    ;

simple_stmt:
    | small_stmt NEWLINE
    | small_stmt ';' NEWLINE
    | small_stmt ';' small_stmt NEWLINE
    ;

small_stmt:
    | expr_stmt
    | flow_stmt
    | import_stmt
    | global_stmt
    | nonlocal_stmt
    | assert_stmt
    ;

expr_stmt:
    | testlist_star_expr
    | testlist_star_expr augassign testlist
    | testlist_star_expr '=' testlist_star_expr
    ;

augassign:
    | '+='
    | '-='
    | '*='
    | '/='
    | '%='
    | '&='
    | '|='
    | '^='
    | '<<='
    | '>>='
    | '**='
    | '//='
    ;

flow_stmt:
    | break_stmt
    | continue_stmt
    | return_stmt
    | raise_stmt
    | yield_stmt
    ;

break_stmt:
    | BREAK
    ;

continue_stmt:
    | CONTINUE
    ;

return_stmt:
    | RETURN testlist_star_expr
    ;

raise_stmt:
    | RAISE
    | RAISE test
    | RAISE test ',' test
    | RAISE test ',' test ',' test
    ;

yield_stmt:
    | yield_expr
    ;

import_stmt:
    | import_name
    | import_from
    ;

import_name:
    | IMPORT dotted_as_names
    ;

import_from:
    | FROM dotted_name IMPORT '*'
    | FROM dotted_name IMPORT '(' import_as_names ')'
    | FROM dotted_name IMPORT import_as_names
    ;

import_as_name:
    | NAME
    | NAME AS NAME
    ;

dotted_as_name:
    | dotted_name
    | dotted_name AS NAME
    ;

import_as_names:
    | import_as_name
    | import_as_names ',' import_as_name
    ;

dotted_as_names:
    | dotted_as_name
    | dotted_as_names ',' dotted_as_name
    ;

dotted_name:
    | NAME
    | dotted_name '.' NAME
    ;

global_stmt:
    | GLOBAL NAME
    | GLOBAL NAME_list
    ;

