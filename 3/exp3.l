%{
#include "exp3bison.tab.h" // Include Bison-generated header file
#include <stdio.h>
#include <stdlib.h>
%}

%%

[0-9]+      { yylval = atoi(yytext); return NUMBER; }
[+\-*/()]   { return yytext[0]; }
\n          { return '\n'; }
[ \t]       { /* Ignore spaces and tabs */ }
.           { printf("Invalid character: %s\n", yytext); }

%%

int yywrap() {
    return 1;
}
