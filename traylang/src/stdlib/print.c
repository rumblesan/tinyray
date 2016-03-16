#include <stdio.h>

#include "interpreter.h"
#include "stdlib/print.h"
#include "bclib/list.h"

void print_value(DataValue *data) {
    double *v;
    switch(data->type) {
        case CAMERA:
            printf("Camera\n");
            break;
        case COLOUR:
            printf("Colour\n");
            break;
        case CONFIG:
            printf("Config\n");
            break;
        case FUNCTION:
            printf("Function\n");
            break;
        case LIGHT:
            printf("Light\n");
            break;
        case LIST:
            printf("List\n");
            break;
        case NOTHING:
            printf("Nothing\n");
            break;
        case NUMBER:
            v = data->value;
            printf("%f\n", *v);
            break;
        case SCENE:
            printf("Scene\n");
            break;
        case SHAPE:
            printf("Shape\n");
            break;
        case TEXTURE:
            printf("Texture\n");
            break;
        case VECTOR:
            printf("Vector\n");
            break;
        default:
            printf("Something else\n");
            break;
    }
}

DataValue *print(List *args) {
    DataValue *arg1 = list_get(args, 0);
    print_value(arg1);
    return datavalue_create(NOTHING, NULL);
}

