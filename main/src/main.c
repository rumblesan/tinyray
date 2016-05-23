#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#include "dbg.h"

#include "parser.h"
#include "interpreter.h"
#include "interpreter_funcs.h"

#include "langfuncs/tracescene.h"

#include "stdlib/print.h"
#include "stdlib/math.h"
#include "stdlib/list.h"

int main(int argc, char *argv[]) {

    char *input_file = NULL;
    int debug_mode = 0;
    int c;

    while ((c = getopt(argc, argv, "di:")) != -1) {
        switch(c) {
            case 'i':
                input_file = optarg;
                break;
            case 'd':
                debug_mode = 1;
                break;
        }
    }

    check(input_file, "Need to supply input scene file path");

    FILE *fp = fopen(input_file, "r");
    check(fp, "Could not open file %s", input_file);

    Block *ast;

    int parseResult = parse(&ast, fp);

    fclose(fp);

    check(parseResult == 0, "Error during parsing");

    printf("Parsed input scene file: %s\n", input_file);

    Interpreter *interpreter = interpreter_create();
    check(interpreter, "Could not create interpreter");

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
    interpreter_set_variable(interpreter, bfromcstr("trace"), datavalue_function(trace_scene));

    interpreter_set_variable(interpreter, bfromcstr("list"), datavalue_function(list));
    interpreter_set_variable(interpreter, bfromcstr("append"), datavalue_function(append));

    interpreter_set_debug(interpreter, debug_mode);

    interpret(interpreter, ast);

    check(
        interpreter->error == 0,
        "Error whilst interpreting: %s", interpreter->err_message->data
    );

    return 0;
error:
    return 1;
}

