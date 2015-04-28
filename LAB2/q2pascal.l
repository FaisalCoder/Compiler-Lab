%option noyywrap
%{
#include <stdio.h>
#include <string.h>
%}
letter [A-Za-z_]
digit [0-9]
id {letter}({letter}|{digit})*
%%
"if"|"class"|"div"|"do"|"to"|"file"|"begin"|"write"|"program"|"end"|"writeln"|"uses"|"var"|"integer"|"with"|"array"|"while" {printf("%10s : KEYWORD\n", yytext);}
":="|"<"|"+"|">"|"<>"|">="|"<="|"+"|"+<"|"-<"|">+"|">-"|"*"|"/"|"**"|"*<"|"/<"|"/>"|"*>" {printf("%10s : Operator\n",yytext);}
{digit}+ {printf("%10s : Integer\n",yytext);}
{digit}+"."{digit}+ {printf("%10s : Double\n",yytext);}
{id} {printf("%10s : Identifier\n",yytext);}
"{"[a-zA-Z0-9\n  \t]*"}" {printf("Comment Occurred\n");}
.|\n {}
%%
int main()
{
	freopen("pascal.txt","r",stdin);
	freopen("pascaloutput.txt","w",stdout);
	yylex();
	fclose(stdin);
	fclose(stdout);
	return 0;
}
