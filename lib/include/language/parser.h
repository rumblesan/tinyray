#ifndef __tray_lang_parser_h__
#define __tray_lang_parser_h__

#include <stdio.h>

#include "language/ast.h"

int parse(Block **block, FILE *fp);

#endif
