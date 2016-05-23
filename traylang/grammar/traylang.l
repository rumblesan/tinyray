%{
#include "y.tab.h"
#include "bclib/bstrlib.h"
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

'.*'                          yylval->string = bfromcstr(yytext); return STRING;

(-)?[0-9]+(\.[0-9]+)?         yylval->number = atof(yytext); return NUMBER;
"+"                           yylval->identifier = bfromcstr(yytext); return IDENTIFIER;
"-"                           yylval->identifier = bfromcstr(yytext); return IDENTIFIER;
"*"                           yylval->identifier = bfromcstr(yytext); return IDENTIFIER;
"/"                           yylval->identifier = bfromcstr(yytext); return IDENTIFIER;
[a-zA-Z]+[a-zA-Z0-9]*         yylval->identifier = bfromcstr(yytext); return IDENTIFIER;

[ \t\n]+                      /* ignore whitespace */;
%%
