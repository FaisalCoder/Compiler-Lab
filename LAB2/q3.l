%option noyywrap
%%
[ \t\n]+   {fprintf(yyout," ");}
:          {fprintf(yyout,",");}
,          {fprintf(yyout,"@");}
;          {fprintf(yyout,":");}
.          {fprintf(yyout,"%s",yytext);}
%%
int main()
{
         yyin = fopen("q3input.txt","r");
         yyout = fopen("q3output.txt","w");
         yylex();
         fclose(yyin);
         fclose(yyout);
}
