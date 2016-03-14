#ifndef AST_H
#define AST_H

#include "bclib/list.h"
#include "bclib/bstrlib.h"

typedef struct tagbstring Identifier;

/* Number Literal AST Node */
typedef struct Number {

    double value;

} Number;

Number *ast_number_create(double value);

void ast_number_cleanup(Number *number);

/* Variable AST Node */
typedef struct Variable {

    bstring name;

} Variable;

Variable *ast_variable_create(bstring name);

void ast_variable_cleanup(Variable *variable);

/* Application AST Node */
typedef struct Application {

    bstring name;

    List *args;

} Application;

Application *ast_application_create(bstring name, List *args);

void ast_application_cleanup(Application *application);

/* Expression AST Node */
typedef enum {APPLICATIONEXPR, NUMBEREXPR, VARIABLEEXPR} ExpressionType;

typedef struct Expression {

    ExpressionType expressionType;

    union {
        Application *application;
        Number *number;
        Variable *variable;
    };

} Expression;

Expression *ast_expression_create();

void ast_expression_cleanup(Expression *expression);

Expression *ast_application_expression(Application *application);

Expression *ast_number_expression(Number *number);

Expression *ast_variable_expression(Variable *variable);


/* Variable Definition AST Node */
typedef struct VarDefinition {

    bstring name;

    Expression *expression;

} VarDefinition;

VarDefinition *ast_vardef_create(bstring name, Expression *expression);

void ast_vardef_cleanup(VarDefinition *vardef);


/* Element AST Node */
typedef enum {VARDEFINITIONEL, APPLICATIONEL} ElementType;

typedef struct Element {

    ElementType elementType;

    union {
        Application   *application;
        VarDefinition *varDefinition;
    };

} Element;

Element *ast_element_create();

void ast_element_cleanup(Element *element);

Element *ast_application_element(Application *application);

Element *ast_vardefinition_element(VarDefinition *vardefinition);


/* Block AST Node */
typedef struct Block {

    List *elements;

} Block;

Block *ast_block_create(List *nodes);

void ast_block_cleanup(Block *block);


#endif
