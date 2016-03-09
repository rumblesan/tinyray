%{
#include "y.tab.h"
%}

%option 8bit reentrant bison-bridge
%option nounput noinput
%option warn noyywrap

%%

"def"                         return DEFINE;

"("                           return OPAREN;
")"                           return CPAREN;
"["                           return OPAREN;
"]"                           return CPAREN;

[0-9]+('.'[0-9]+)?            yylval->number = atof(yytext); return NUMBER;
"+"                           yylval->identifier = strdup(yytext); return IDENTIFIER;
"-"                           yylval->identifier = strdup(yytext); return IDENTIFIER;
"*"                           yylval->identifier = strdup(yytext); return IDENTIFIER;
"/"                           yylval->identifier = strdup(yytext); return IDENTIFIER;
[a-zA-Z]+[a-zA-Z0-9]*         yylval->identifier = strdup(yytext); return IDENTIFIER;

[ \t\n]+                      /* ignore whitespace */;
%%
