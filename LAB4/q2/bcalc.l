%{
#include<stdio.h>
#include<stdlib.h>
#include"y.tab.h"
extern int yylval;
%}

%option noyywrap

num [0-9]+

%%
{num}      { yylval = atoi(yytext); return NUMBER ; }
"("        { return OBRAC ; }
")"        { return CBRAC ;}
"!"        { return NOT ; }
"||"       { return OR; }
"&&"       { return AND ;}
">"        { return GT ;}
"<"        { return LT ;}
">="       { return GEQ ;}
"<="       { return LEQ ;}
"=="       { return EQ; }
"!="       { return NEQ;}
.|\n       ;
%%
