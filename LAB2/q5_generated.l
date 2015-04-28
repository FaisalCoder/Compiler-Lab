%{ 
 #include <stdio.h> 
 #include <stdlib.h> 
 #include <string.h> 
 #include <stdarg.h> 
 #include <stdbool.h> 
%} 
regularexpression (abc)*
%% 
\n {yylineno++;} 
{regularexpression} { fprintf(yyout,"%d : %s \n",yylineno,yytext);} 
 . {} 
%% 
int main() 
{ yyin = fopen("q5_input.txt","r"); 
 yyout = fopen("q5output.txt", "w"); 
 yylex(); 
 fclose(yyin); 
 fclose(yyout); 
 }