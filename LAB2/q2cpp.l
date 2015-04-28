%option noyywrap

%{
#include <stdio.h>
#include <string.h>
%}
letter [A-Za-z_]
digit [0-9]
id {letter}({letter}|{digit})*
%%
"if"|"then"|"else"|"switch"|"case"|"while"|"class"|"struct" {printf("%10s : Keyword\n",yytext);}
"for"|"int"|"double"|"char"|"float"|"long"|"do" {printf("%10s : Keyword\n",yytext);}
"short"|"string"|"default"|"continue"|"break"|"return" {printf("%10s : Keyword\n",yytext);}
"<="|">="|"=="|"="|"+"|"-"|"*"|"/"|"!="|"<<"|">>"|"%"|"^"|"~"|"++"|"--"|"||"|"&&"|"&"|"|" {printf("%10s : Operator\n",yytext);}
{digit}+ {printf("%10s : Integer\n",yytext);}
{digit}+"."{digit}+ {printf("%10s : Double\n",yytext);}
{id} {printf("%10s : Identifier\n",yytext);}
.|\n {}
%%
int main()
{
	freopen("cpp.txt","r",stdin);
	freopen("cppoutput.txt","w",stdout);
	yylex();
	fclose(stdin);
	fclose(stdout);
	return 0;
}
