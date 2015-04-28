%{
#include<stdio.h>
#include"y.tab.h"
extern int yylval;
%}

%option noyywrap

digit [0-9]

%%
{digit}    { yylval = atoi(yytext); return DIGIT ; }
"("        { return OPEN_PAREN ; }
")"        { return CLOSE_PAREN ;}
"+"        { return PLUS; }
"*"        { return STAR; }
.|\n       ;
%%
