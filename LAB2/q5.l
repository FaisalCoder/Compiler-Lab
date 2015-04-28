%option noyywrap
%{
char  reg[100] ;
char  fname[100] ;

char substring (char*a , char *b)
{
    int l1 = 0,l2 = 0,i=0;
    while( a[i] != '\0' )
    {
        l1++;
        i++;
    }

    i =0;
    while( b[i] != '\0' )
    {
        l2++;
        i++;
    }

    int k=0,lcheck=0;
    i=0;

    while( i < l1 )
    {
      if ( b[k] == a[i] ) 
      {
         lcheck++;k++;
     
         if ( lcheck == l2 ) break;
      }
  
      else
      {
        lcheck= 0;
        k= 0;
      }

      i++;
     }

     if ( lcheck == l2 ) return 'y';
     return 'n';

}

%}

digit     [0-9]
letter    [A-Za-z]

%%
({letter}|{digit})*    { if (substring( yytext , reg) == 'y') fprintf(yyout,"%d %s",yylineno,yytext); }  
.|"\n"                 {}


%%
int main()
{
         printf("Enter regular expression : ");
         scanf("%s",reg);
         printf("Enter input file name : ");
         scanf("%s",fname);
       //  printf("%s and %s",reg,fname);
         yyin = fopen(fname,"r");
         yyout = fopen("q5output_bad.txt","w");
         yylex();
         fclose(yyin);
         fclose(yyout);
}

