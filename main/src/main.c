#include <stdio.h>
#include <stdlib.h>

#include "dbg.h"


#include "bclib/bstrlib.h"

#include "parser.h"
#include "ast.h"
#include "interpreter.h"
#include "ast-print.h"

#include "langfuncs/tracescene.h"

#include "stdlib/print.h"
#include "stdlib/math.h"
#include "stdlib/list.h"

#include "scene.h"
#include "tracing.h"

#include "img_export.h"


DataValue *print_output(DataValue *value) {
    if (value == NULL) {
        printf("Could not print NULL output\n");
        return NULL;
    }
    printf("Result: ");
    List *list = list_create();
    list_push(list, value);
    print(list);
    list_destroy(list);
    return value;
}

int main(int argc, char *argv[]) {

    if (argc != 2) {
        printf("Need to have 1 argument\nHave %d\n", (argc - 1));
        return 0;
    }

    char *input_file = argv[1];

    FILE *fp = fopen(input_file, "r");
    if (fp == NULL) {
        printf("Could not open file %s\n", input_file);
        return 0;
    }

    Block *ast;

    int parseResult = parse(&ast, fp);

    fclose(fp);

    if (parseResult) {
        printf("Error during parsing");
        return 1;
    } else {
        printf("Parsed\n");
    }

    Interpreter *interpreter = interpreter_create();
    if (interpreter == NULL) {
        log_err("Could not create interpreter");
        return 1;
    }
    interpreter_set_variable(interpreter, bfromcstr("print"), datavalue_function(print));
    interpreter_set_variable(interpreter, bfromcstr("add"), datavalue_function(add));
    interpreter_set_variable(interpreter, bfromcstr("sub"), datavalue_function(sub));

    interpreter_set_variable(interpreter, bfromcstr("config"), datavalue_function(config));
    interpreter_set_variable(interpreter, bfromcstr("camera"), datavalue_function(camera));
    interpreter_set_variable(interpreter, bfromcstr("col"), datavalue_function(col));
    interpreter_set_variable(interpreter, bfromcstr("vec"), datavalue_function(vec));
    interpreter_set_variable(interpreter, bfromcstr("texture"), datavalue_function(texture));
    interpreter_set_variable(interpreter, bfromcstr("pointlight"), datavalue_function(pointlight));
    interpreter_set_variable(interpreter, bfromcstr("ambientlight"), datavalue_function(ambientlight));
    interpreter_set_variable(interpreter, bfromcstr("triangle"), datavalue_function(triangle));
    interpreter_set_variable(interpreter, bfromcstr("sphere"), datavalue_function(sphere));
    interpreter_set_variable(interpreter, bfromcstr("plane"), datavalue_function(plane));
    interpreter_set_variable(interpreter, bfromcstr("rayscene"), datavalue_function(rayscene));

    interpreter_set_variable(interpreter, bfromcstr("list"), datavalue_function(list));
    interpreter_set_variable(interpreter, bfromcstr("append"), datavalue_function(append));

    DataValue *output = interpret(interpreter, ast);

    if (interpreter->error == 1) {
        printf("Error whilst interpreting: %s", interpreter->err_message->data);
        return 1;
    }
    if (output->type == CDATA) {
        printf("Rendering\n");
        rays_calc(output->value);
        render_png(output->value, bfromcstr("output.png"));
        scene_cleanup(output->value);
    } else {
        print_output(output);
        printf("No scene output so not rendering\n");
    }

    return 0;
}

