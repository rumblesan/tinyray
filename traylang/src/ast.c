#include <stdlib.h>

#include "ast.h"
#include "bclib/list.h"
#include "bclib/bstrlib.h"

/* Block AST Node */
Block *ast_block_create(List *elements) {
    Block *block = malloc(sizeof(Block));
    block->elements = elements;
    return block;
}

void ast_block_cleanup(Block *block) {
    LIST_FOREACH(block->elements, first, next, cur) {
        ast_element_cleanup(cur->value);
    }
    free(block);
}

/* Element AST Node */
Element *ast_element_create() {
    Element *element = malloc(sizeof(Element));
    return element;
}

void ast_element_cleanup(Element *element) {
    switch(element->elementType) {
        case VARDEFINITIONEL:
            ast_vardef_cleanup(element->varDefinition);
            break;
        case APPLICATIONEL:
            ast_application_cleanup(element->application);
            break;
    }
    free(element);
}

Element *ast_application_element(Application *application) {
    Element *element = ast_element_create();
    element->elementType = APPLICATIONEL;
    element->application = application;
    return element;
}

Element *ast_vardefinition_element(VarDefinition *varDefinition) {
    Element *element = ast_element_create();
    element->elementType = VARDEFINITIONEL;
    element->varDefinition = varDefinition;
    return element;
}

/* Application AST Node */
Application *ast_application_create(Expression *expr, List *args) {
    Application *application = malloc(sizeof(Application));
    application->expr = expr;
    application->args = args;

    return application;
}

void ast_application_cleanup(Application *application) {
    ast_expression_cleanup(application->expr);
    bstring argname;
    LIST_FOREACH(application->args, first, next, cur) {
        argname = cur->value;
        bdestroy(argname);
    }
    list_destroy(application->args);
    free(application);
}

/* Variable Definition AST Node */
VarDefinition *ast_vardef_create(bstring name, Expression *expression) {
    VarDefinition *varDef = malloc(sizeof(VarDefinition));
    varDef->name = name;
    varDef->expression = expression;

    return varDef;
}

void ast_vardef_cleanup(VarDefinition *vardef) {
    bdestroy(vardef->name);
    ast_expression_cleanup(vardef->expression);
    free(vardef);
}

/* Expression AST Node */
Expression *ast_expression_create() {
    Expression *expression = malloc(sizeof(Expression));
    return expression;
}

void ast_expression_cleanup(Expression *expression) {
    switch(expression->expressionType) {
        case APPLICATIONEXPR:
            ast_application_cleanup(expression->application);
            break;
        case NUMBEREXPR:
            ast_number_cleanup(expression->number);
            break;
        case STRINGEXPR:
            ast_string_cleanup(expression->string);
            break;
        case VARIABLEEXPR:
            ast_variable_cleanup(expression->variable);
            break;
        case LAMBDAEXPR:
            ast_lambda_cleanup(expression->lambda);
            break;
    }
    free(expression);
}

Expression *ast_application_expression(Application *application) {
    Expression *expression = ast_expression_create();
    expression->expressionType = APPLICATIONEXPR;
    expression->application = application;
    return expression;
}

Expression *ast_number_expression(Number *number) {
    Expression *expression = ast_expression_create();
    expression->expressionType = NUMBEREXPR;
    expression->number = number;
    return expression;
}

Expression *ast_string_expression(String *string) {
    Expression *expression = ast_expression_create();
    expression->expressionType = STRINGEXPR;
    expression->string = string;
    return expression;
}

Expression *ast_variable_expression(Variable *variable) {
    Expression *expression = ast_expression_create();
    expression->expressionType = VARIABLEEXPR;
    expression->variable = variable;
    return expression;
}

Expression *ast_lambda_expression(Lambda *lambda) {
    Expression *expression = ast_expression_create();
    expression->expressionType = LAMBDAEXPR;
    expression->lambda = lambda;
    return expression;
}

/* Number Literal AST Node */
Number *ast_number_create(double value) {
    Number *number = malloc(sizeof(Number));
    number->value = value;

    return number;
}

void ast_number_cleanup(Number *number) {
    free(number);
}

/* String Literal AST Node */
String *ast_string_create(bstring value) {
    String *string = malloc(sizeof(String));
    string->value = value;

    return string;
}

void ast_string_cleanup(String *string) {
    bdestroy(string->value);
    free(string);
}

/* Variable AST Node */
Variable *ast_variable_create(bstring name) {
    Variable *variable = malloc(sizeof(Variable));
    variable->name = name;

    return variable;
}

void ast_variable_cleanup(Variable *variable) {
    bdestroy(variable->name);
    free(variable);
}

/* Lambda AST Node */
Lambda *ast_lambda_create(List *arg_names, Block *body) {
    Lambda *lambda = malloc(sizeof(Lambda));
    lambda->arg_names = arg_names;
    lambda->body = body;
    return lambda;
}

void ast_lambda_cleanup(Lambda *lambda) {
    bstring argname;
    LIST_FOREACH(lambda->arg_names, first, next, cur) {
        argname = cur->value;
        bdestroy(argname);
    }
    ast_block_cleanup(lambda->body);
    free(lambda);
}

