%option noyywrap
%%
"double"/" " {printf("%s","float");}
"int"/" " {printf("%s","short");}
%%
int main()
{
    yylex();
    return 0;
}
