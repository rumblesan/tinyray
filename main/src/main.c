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
#include "colours.h"
#include "tracing.h"

#include "libs/lodepng.h"

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

void render_png(Scene *scene, char* output_file)
{
    int width  = scene->canvas->width;
    int height = scene->canvas->height;

    Colour **data = scene->canvas->data;

    Colour colour;

    unsigned err;

    unsigned char* image = malloc(width * height * 4);

    for (int y = 0; y < height; y++) {
        for (int x = 0; x < width; x++) {
            // Fix image being upside down
            // We trace from bottom left to top right
            // Logepng goes topleft to bottom right
            int yc = (height - 1) - y;
            colour = data[x][y];
            image[4 * width * yc + 4 * x + 0] = (uint8_t)colour.red;
            image[4 * width * yc + 4 * x + 1] = (uint8_t)colour.green;
            image[4 * width * yc + 4 * x + 2] = (uint8_t)colour.blue;
            image[4 * width * yc + 4 * x + 3] = (uint8_t)colour.alpha;
        }
    }

    err = lodepng_encode32_file(output_file, image, width, height);

    if (err) {
        printf("error %u: %s\n", err, lodepng_error_text(err));
    }
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
    interpreter_set_variable(interpreter, bfromcstr("print"), datavalue_create(FUNCTION, print));
    interpreter_set_variable(interpreter, bfromcstr("add"), datavalue_create(FUNCTION, add));
    interpreter_set_variable(interpreter, bfromcstr("sub"), datavalue_create(FUNCTION, sub));

    interpreter_set_variable(interpreter, bfromcstr("config"), datavalue_create(FUNCTION, config));
    interpreter_set_variable(interpreter, bfromcstr("camera"), datavalue_create(FUNCTION, camera));
    interpreter_set_variable(interpreter, bfromcstr("col"), datavalue_create(FUNCTION, col));
    interpreter_set_variable(interpreter, bfromcstr("vec"), datavalue_create(FUNCTION, vec));
    interpreter_set_variable(interpreter, bfromcstr("texture"), datavalue_create(FUNCTION, texture));
    interpreter_set_variable(interpreter, bfromcstr("pointlight"), datavalue_create(FUNCTION, pointlight));
    interpreter_set_variable(interpreter, bfromcstr("ambientlight"), datavalue_create(FUNCTION, ambientlight));
    interpreter_set_variable(interpreter, bfromcstr("triangle"), datavalue_create(FUNCTION, triangle));
    interpreter_set_variable(interpreter, bfromcstr("sphere"), datavalue_create(FUNCTION, sphere));
    interpreter_set_variable(interpreter, bfromcstr("plane"), datavalue_create(FUNCTION, plane));
    interpreter_set_variable(interpreter, bfromcstr("rayscene"), datavalue_create(FUNCTION, rayscene));

    interpreter_set_variable(interpreter, bfromcstr("list"), datavalue_create(FUNCTION, list));
    interpreter_set_variable(interpreter, bfromcstr("append"), datavalue_create(FUNCTION, append));

    DataValue *output = interpret(interpreter, ast);

    if (interpreter->error == 1) {
        printf("Error whilst interpreting: %s", interpreter->err_message->data);
        return 1;
    }
    if (output->type == SCENE) {
        printf("Rendering\n");
        rays_calc(output->value);
        render_png(output->value, "output.png");
        scene_cleanup(output->value);
    } else {
        print_output(output);
        printf("No scene output so not rendering\n");
    }

    return 0;
}

