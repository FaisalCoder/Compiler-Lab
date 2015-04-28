%{
#include<stdio.h>
int yylex();
int yyerror(char*);
%}

%token A
%token B
%token C

%%
E	: { printf("E -> aE\n"); } A E
	| { printf("E -> F\n"); } F
	;
F	: { printf("F -> bF\n"); } B F
	| { printf("F -> G\n"); } G
	;
G	: { printf("G -> cG\n"); } C G
	| 
	;
%%

int main(){
  yyparse();
 return 0;
}
int yyerror(char* s){
  printf("Error!\n");

}

