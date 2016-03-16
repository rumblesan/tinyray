#ifndef AST_DISPLAY_H
#define AST_DISPLAY_H

#include "ast.h"
#include "bclib/list.h"

void ast_print(Block *block);

void ast_block_print(Block *block, int indentation);

void ast_element_print(Element *element, int indentation);

void ast_vardef_print(VarDefinition *vardef, int indentation);

void ast_application_print(Application *application, int indentation);

void ast_arg_list_print(List *list, int indentation);

void ast_expression_print(Expression *expression, int indentation);

void ast_number_print(Number *number, int indentation);

void ast_variable_print(Variable *variable, int indentation);

#endif
