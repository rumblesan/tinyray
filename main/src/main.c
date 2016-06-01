#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#include "dbg.h"

#include "traylang/traylang.h"
#include "traylang/traylang_ffi.h"

#include "langfuncs/tracescene.h"

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


    TrayLang *tray = traylang_init();
    check(tray, "Could not init traylang");

    traylang_add_function(tray, "config", config);
    traylang_add_function(tray, "camera", camera);
    traylang_add_function(tray, "col", col);
    traylang_add_function(tray, "vec", vec);
    traylang_add_function(tray, "texture", texture);
    traylang_add_function(tray, "pointlight", pointlight);
    traylang_add_function(tray, "ambientlight", ambientlight);
    traylang_add_function(tray, "triangle", triangle);
    traylang_add_function(tray, "sphere", sphere);
    traylang_add_function(tray, "plane", plane);
    traylang_add_function(tray, "rayscene", rayscene);
    traylang_add_function(tray, "trace", trace_scene);

    int result = traylang_interpret_file(tray, fp);

    check(
        result == 0,
        "Error whilst interpreting"
    );

    traylang_cleanup(tray);

    fclose(fp);

    return 0;
error:
    return 1;
}

