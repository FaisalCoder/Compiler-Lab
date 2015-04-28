%option noyywrap
%%
"double"/" " {printf("%s","float");}
"int"/" " {printf("%s","short");}
%%
int main()
{
    yyin = fopen("q4_input.txt","r");
    yylex();
    return 0;
}
