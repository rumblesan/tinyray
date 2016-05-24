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

    interpreter_set_variable(interpreter, bfromcstr("print"), object_function(interpreter, print));
    interpreter_set_variable(interpreter, bfromcstr("add"), object_function(interpreter, add));
    interpreter_set_variable(interpreter, bfromcstr("sub"), object_function(interpreter, sub));

    interpreter_set_variable(interpreter, bfromcstr("config"), object_function(interpreter, config));
    interpreter_set_variable(interpreter, bfromcstr("camera"), object_function(interpreter, camera));
    interpreter_set_variable(interpreter, bfromcstr("col"), object_function(interpreter, col));
    interpreter_set_variable(interpreter, bfromcstr("vec"), object_function(interpreter, vec));
    interpreter_set_variable(interpreter, bfromcstr("texture"), object_function(interpreter, texture));
    interpreter_set_variable(interpreter, bfromcstr("pointlight"), object_function(interpreter, pointlight));
    interpreter_set_variable(interpreter, bfromcstr("ambientlight"), object_function(interpreter, ambientlight));
    interpreter_set_variable(interpreter, bfromcstr("triangle"), object_function(interpreter, triangle));
    interpreter_set_variable(interpreter, bfromcstr("sphere"), object_function(interpreter, sphere));
    interpreter_set_variable(interpreter, bfromcstr("plane"), object_function(interpreter, plane));
    interpreter_set_variable(interpreter, bfromcstr("rayscene"), object_function(interpreter, rayscene));
    interpreter_set_variable(interpreter, bfromcstr("trace"), object_function(interpreter, trace_scene));

    interpreter_set_variable(interpreter, bfromcstr("list"), object_function(interpreter, list));
    interpreter_set_variable(interpreter, bfromcstr("append"), object_function(interpreter, append));

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

