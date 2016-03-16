%code requires {
#include "ast.h"
#include "bclib/list.h"
}

%{

#include <stdio.h>
#include <string.h>

#include "parser.h"
#include "y.tab.h"
#include "lex.yy.h"

void yyerror(yyscan_t scanner, Block **ast, const char *str) {
    fprintf(stderr, "error: %s\n", str);
}

int parse(Block **ast, FILE *fp) {

    yyscan_t scanner;

    yylex_init(&scanner);
    yyset_in(fp, scanner);

    int parseResult = yyparse(scanner, ast);

    yylex_destroy(scanner);

    return parseResult;
}

%}

%define parse.error verbose
%define api.pure full
%lex-param {void *scanner}
%parse-param {void *scanner} {Block **ast}

%union {
    Block         *blockNode;
    List          *elementsNode;
    Element       *elementNode;
    Application   *applicationNode;
    List          *argListNode;
    VarDefinition *varDefNode;
    Expression    *expressionNode;
    Number        *numberNode;
    Variable      *variableNode;
    Identifier    *identifier;
    double        number;
}

%token DEFINE
%token OPAREN
%token CPAREN
%token<number> NUMBER
%token<identifier> IDENTIFIER
%type<blockNode> body
%type<elementsNode> elements
%type<elementNode> element
%type<applicationNode> application
%type<argListNode> argList
%type<varDefNode> vardefinition
%type<expressionNode> expression
%type<variableNode> variable

%%
body: elements
    {
        Block *block = ast_block_create($1);
        *ast = block;
        $$ = block;
    }
    ;

elements: %empty
        {
            $$ = list_create();
        }
        | elements element
        {
            $$ = list_push($1, $2);
        }
        ;

element: application
       {
           $$ = ast_application_element($1);
       }
       | vardefinition
       {
           $$ = ast_vardefinition_element($1);
       }
       ;

application: OPAREN IDENTIFIER argList CPAREN
           {
               $$ = ast_application_create($2, $3);
           }
           ;

argList: %empty
       {
           $$ = list_create();
       }
       | argList expression
       {
           $$ = list_push($1, $2);
       }
       ;


vardefinition: OPAREN DEFINE IDENTIFIER expression CPAREN
          {
               $$ = ast_vardef_create($3, $4);
          }
          ;

expression: variable
          {
              $$ = ast_variable_expression($1);
          }
          | NUMBER
          {
              $$ = ast_number_expression(
                  ast_number_create($1)
              );
          }
          | application
          {
              $$ = ast_application_expression($1);
          }
          ;

variable: IDENTIFIER
        {
            $$ = ast_variable_create($1);
        }
        ;
%%
