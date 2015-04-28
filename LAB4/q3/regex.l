%{
#include<stdio.h>
#include<stdlib.h>
#include"y.tab.h"
extern int yylval;
%}

%option noyywrap

%%

"a"             { return A; }
"b"             { return B; }
"c"		{ return C; }
.|\n            ;
%%
