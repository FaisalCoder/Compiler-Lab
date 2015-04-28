%{
#include<stdio.h>
int yyerror(char*);
int yylex();
%}

%token DIGIT
%token PLUS
%token STAR
%token OPEN_PAREN 
%token CLOSE_PAREN

%%
S	: E						{ printf("%d\n",$$);}
	;

E	: E PLUS T 					{ $$ = $1 + $3 ; }
	| T
	;

T	: T STAR F 					{ $$ = $1 * $3 ; }
	| F
	;

F	: OPEN_PAREN E CLOSE_PAREN        		{ $$ = $2 ; }
	| DIGIT						{ $$ = yylval; }
	;
 
%%
int main(){
  yyparse();
  return 0;
}

int yyerror(char* s){
  printf("Error: %s\n",s);
  return 1;
}
