%option noyywrap
%option yylineno
%{
char * anagram ;
char anagramChecker(char * a,char* b)
{
   int array1[26]={0};
   int array2[26]={0};
   int i=0,l1=0,l2=0;

   while( a[i] != '\0')
   {l1++;i++;}

   i=0;
   while( b[i] != '\0')
   {l2++;i++;}

   if ( l1 != l2 ) return 'n';

   i=0;
   while( i < l1 )
   {
      int current = a[i]-'a';
      array1[current]++;
      i++;
   }

   i=0;
   while( i < l2 )
   {
      int current = b[i]-'a';
      array2[current]++;
      i++;
   }

   int no=0;i=0;
   while( i < 26 ) 
   {
       if ( array1[i] != array2[i] )
       {
          no = 1;
       }
      i++;
   }

   if ( no == 1 ) return 'n';
   return 'y';
}

%}

%%
[a-z]*    { if ( anagramChecker(yytext, anagram) == 'y') fprintf(yyout,"%d : %s\n",yylineno,yytext); }   
.|\n      {}

%%
int main()
{
         anagram = "faisal";
         yyin = fopen("q7input.txt","r");
         yyout = fopen("q7output.txt","w");
         yylex();
         fclose(yyin);
         fclose(yyout);
}

