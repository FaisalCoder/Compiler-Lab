%option noyywrap

%{
int LT = 1, LE = 2, EQ = 3, NE = 4, GT = 5, GE = 6, IF = 7, THEN = 8, ELSE = 9, ID = 10, NUMBER = 11, RELOP = 12;
double numbers[100];
char *identifiers[100][100];
int identifiersCount = 0;
int numbersCount = 0;
int yylval;
%}

delim [ \t\n]
ws {delim}+
letter [A-Za-z]
digit [0-9]
id {letter}({letter}|{digit})*
number {digit}+(\.{digit}+)?(E[+-]?{digit}+)?

%%

{ws} { }
if { return (IF); }
then { return (THEN); }
else { return (ELSE); }
{number} { yylval = installNum(); return ( NUMBER); }
{id} { yylval = installID(); return ( ID); }
"<" { yylval = LT; return(RELOP); }
"<=" { yylval = LE; return(RELOP); }
"=" { yylval = EQ; return(RELOP); }
"<>" { yylval = NE; return(RELOP); }
">" { yylval = GT; return(RELOP); }
">=" { yylval = GE; return(RELOP); }
%%

printTokenDescription(int token) {
    if (token == LT) {
        printf("LT");
    } else if (token == LE) {
        printf("LE");
    } else if (token == EQ) {
        printf("EQ");
    } else if (token == NE) {
        printf("NE");
    } else if (token == GT) {
        printf("GT");
    } else if (token == GE) {
        printf("GE");
    } else if (token == IF) {
        printf("IF");
    } else if (token == THEN) {
        printf("THEN");
    } else if (token == ELSE) {
        printf("ELSE");
    } else if (token == ID) {
        printf("ID");
    } else if (token == NUMBER) {
        printf("NUMBER");
    } else if (token == RELOP) {
        printf("RELOP");
    }
}

int installID() {
strcat(yytext,"\0");
    int i;
    for (i = 0; i < identifiersCount; i++) {
        if (strcmp(identifiers[i], yytext) == 0) {
            return i;
        }
    }
    if (identifiersCount == 100) {
        printf("Maximum identifiers limit reached");
    } else {
       strcpy(identifiers[identifiersCount] ,yytext);

        identifiersCount++;
        return identifiersCount - 1;
    }
}

int installNum() {
    double num = atof(yytext);
    int i;
    for (i = 0; i < numbersCount; i++) {
        if (numbers[i] == num) {
            return i;
        }
    }
    if (numbersCount == 100) {
        printf("Maximum numbers limit reached");
    } else {
        numbers[numbersCount] = num;
        numbersCount++;
        return (numbersCount - 1);
    }
}

int main() {
    yyin = fopen("q1input.txt", "r");
    for (;;) {
        int token = yylex();
        if (token == 0) {
            return;
        }
        printTokenDescription(token);
        if (token == RELOP) {
            printf(" : ");
            printTokenDescription(yylval);
        } else if (token == ID) {
            printf(" : [%d] %s", yylval, identifiers[yylval]);
        } else if (token == NUMBER) {
            printf(" : [%d] %e", yylval, numbers[yylval]);
        }
        printf("\n");
    }

}


