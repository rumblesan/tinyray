#include <stdio.h>
#include <stdlib.h>

#include "ast-print.h"
#include "ast.h"
#include "bclib/list.h"

#define DEPTH 2

void indent(int i) {
    printf("%*s", i, " ");
}

void ast_print(Block *block) {
    ast_block_print(block, 0);
}

void ast_block_print(Block *block, int indentation) {
    indent(indentation);
    printf("AST Block with %d elements\n", list_count(block->elements));

    LIST_FOREACH(block->elements, first, next, cur) {
        ast_element_print(cur->value, indentation + DEPTH);
    }
}

void ast_element_print(Element *element, int indentation) {
    switch(element->elementType) {
        case VARDEFINITIONEL:
            ast_vardef_print(element->varDefinition, indentation + DEPTH);
            break;
        case APPLICATIONEL:
            ast_application_print(element->application, indentation + DEPTH);
            break;
    }
}

void ast_vardef_print(VarDefinition *vardef, int indentation) {
    indent(indentation);
    printf("Var Definition: %s\n", vardef->name->data);
    ast_expression_print(vardef->expression, indentation + DEPTH);
}

void ast_application_print(Application *application, int indentation) {
    indent(indentation);
    printf("Application\n");
    ast_arg_list_print(application->args, indentation + DEPTH);
}

void ast_arg_list_print(List *args, int indentation) {
    indent(indentation);
    printf("%d args\n", list_count(args));
    LIST_FOREACH(args, first, next, cur) {
        ast_expression_print(cur->value, indentation + DEPTH);
    }
}

void ast_expression_print(Expression *expression, int indentation) {
    indent(indentation);
    printf("Expression\n");
    switch(expression->expressionType) {
        case APPLICATIONEXPR:
            ast_application_print(expression->application, indentation + DEPTH);
            break;
        case NUMBEREXPR:
            ast_number_print(expression->number, indentation + DEPTH);
            break;
        case STRINGEXPR:
            ast_string_print(expression->string, indentation + DEPTH);
            break;
        case VARIABLEEXPR:
            ast_variable_print(expression->variable, indentation + DEPTH);
            break;
        case LAMBDAEXPR:
            ast_lambda_print(expression->lambda, indentation + DEPTH);
            break;
    }
}

void ast_number_print(Number *number, int indentation) {
    indent(indentation);
    printf("Number: %f\n", number->value);

}

void ast_string_print(String *string, int indentation) {
    indent(indentation);
    printf("String: %s\n", string->value->data);

}

void ast_variable_print(Variable *variable, int indentation) {
    indent(indentation);
    printf("Variable: %s\n", variable->name->data);
}

void ast_lambda_print(Lambda *lambda, int indentation) {
    indent(indentation);
    printf("Lambda: %d args\n", list_count(lambda->arg_names));
    indent(indentation + DEPTH);
    bstring name;
    LIST_FOREACH(lambda->arg_names, first, next, cur) {
        name = cur->value;
        printf("%s  ", bdata(name));
    }
}


