%option noyywrap
%{
int count = 0;
%}
%%
"//".*               {count++;}
"/*"(.*(\n)?)*"*/"   {count++;}
.|\n                 {fprintf(yyout,"%s",yytext);}

%%
int main()
{
    yyout = fopen("q6output.txt","w");
    yylex();
    printf("Total Comments in C++ program : %d\n",count);
    return 0;
}
