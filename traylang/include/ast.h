#ifndef AST_H
#define AST_H

#include "bclib/list.h"
#include "bclib/bstrlib.h"

struct Block;
struct Expression;

typedef struct tagbstring Identifier;

/* Number Literal AST Node */
typedef struct Number {

    double value;

} Number;

Number *ast_number_create(double value);

void ast_number_cleanup(Number *number);

/* String Literal AST Node */
typedef struct String {

    bstring value;

} String;

String *ast_string_create(bstring value);

void ast_string_cleanup(String *string);

/* Lambda AST Node */
typedef struct Lambda {

    List *arg_names;

    struct Block *body;

} Lambda;

Lambda *ast_lambda_create(List *arg_names, struct Block *body);

void ast_lambda_cleanup(Lambda *lambda);

/* Variable AST Node */
typedef struct Variable {

    bstring name;

} Variable;

Variable *ast_variable_create(bstring name);

void ast_variable_cleanup(Variable *variable);

/* Application AST Node */
typedef struct Application {

    struct Expression *expr;

    List *args;

} Application;

Application *ast_application_create(struct Expression *expr, List *args);

void ast_application_cleanup(Application *application);

/* Expression AST Node */
typedef enum {APPLICATIONEXPR, NUMBEREXPR, STRINGEXPR, VARIABLEEXPR, LAMBDAEXPR} ExpressionType;

typedef struct Expression {

    ExpressionType expressionType;

    union {
        Application *application;
        Number *number;
        String *string;
        Variable *variable;
        Lambda *lambda;
    };

} Expression;

Expression *ast_expression_create();

void ast_expression_cleanup(Expression *expression);

Expression *ast_application_expression(Application *application);

Expression *ast_number_expression(Number *number);

Expression *ast_string_expression(String *string);

Expression *ast_variable_expression(Variable *variable);

Expression *ast_lambda_expression(Lambda *lambda);


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
