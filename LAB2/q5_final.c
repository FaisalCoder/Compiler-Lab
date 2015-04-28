#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdarg.h>
#include <stdbool.h>

int main(){

FILE *f = fopen("q5_generated.l", "w");

if (f == NULL)
{
   printf("Error opening file!\n");
}

char* regularexpression= malloc(100);
char* fileName= malloc(100);

printf("Please Enter Regular Expression .\n");
scanf("%s", regularexpression);
printf("Please Enter input file name. \n");
scanf("%s", fileName);

char* mainString;

mainString = malloc(10000);
mainString[0]='\0';

char* definitions="%{ \n #include <stdio.h> \n #include <stdlib.h> \n #include <string.h> \n #include <stdarg.h> \n #include <stdbool.h> \n%} \nregularexpression ";

strcat(mainString,definitions);                         //Concatenating to the main string to be copied
strcat(mainString,regularexpression);

char* rules="\n%% \n\\n {yylineno++;} \n{regularexpression} { fprintf(yyout,\"%d : %s \\n\",yylineno,yytext);} \n . {} \n%% \n";

strcat(mainString,rules);

char* cCode="int main() \n{ yyin = fopen(\"";
strcat(mainString,cCode);
strcat(mainString,fileName);      

char* cCodeBody="\",\"r\"); \n yyout = fopen(\"q5output.txt\", \"w\"); \n yylex(); \n fclose(yyin); \n fclose(yyout); \n }";

strcat(mainString,cCodeBody);
fprintf(f,"%s", mainString);                  //finally writing to file
fclose(f);

system("lex q5_generated.l");

system("cc -c -o q5_generated.o lex.yy.c");
system("cc -o q5test q5_generated.o -ll");
//system("gcc -o q5test lex.yy.c");
system("./q5test");

 

}
