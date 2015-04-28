%{
#include<stdio.h>
int yyerror(char*);
int yylex();
%}

%token NUMBER
%token NOT
%token OR
%token AND
%token OBRAC
%token CBRAC
%token GT
%token LT
%token EQ
%token NEQ
%token GEQ
%token LEQ

%%

Start : BoolExpr         			{ if($$) printf("True\n"); else printf("False\n"); }

BoolExpr : Boolterm                             	
	 | BoolExpr OR Boolterm          		{ $$ = $1 || $3 ; }
         ;

Boolterm : Boolatom                                    	
	 | Boolterm AND Boolatom     			{ $$ = $1 && $3 ;}
	 ;

Boolatom : Bliteral					
	 | NOT Bliteral 				{ if($2 > 0) $$ = 1; else $$ = 0; }
	 ;

Bliteral : Expr                                   	{ if($1 > 0) $$ = 1; else $$ = 0;}
	 | OBRAC BoolExpr CBRAC        			{ $$ = $2 ; }
	 | Expr GT Expr 				{ if($1 > $3) $$ = 1; else $$ = 0; }
	 | Expr LT Expr					{ if($1 < $3) $$ = 1; else $$ = 0; }
 	 | Expr EQ Expr                     		{ if($1 == $3) $$ = 1; else $$ = 0; }
	 | Expr NEQ Expr         			{ if($1 != $3) $$ = 1; else $$ = 0; }
	 | Expr GEQ Expr                    		{ if($1 >= $3) $$ = 1; else $$ = 0; }
	 | Expr LEQ Expr          			{ if($1 <= $3) $$ = 1; else $$ = 0; }
	 ;

Expr : NUMBER 
	;
%%
int main(){
  yyparse();
  return 0;
}

int yyerror(char* s){
  printf("Error: %s",s);
  return 1;
}
