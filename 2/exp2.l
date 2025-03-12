%{
#include <stdio.h>
#include <string.h>
%}

int yywrap() { return 1; }

%%

"int"|"if"|"else"|"while"|"return"|"for"|"break"|"continue" {
    printf("KEYWORD: %s\n", yytext);
}

[a-zA-Z_][a-zA-Z0-9_]*  { printf("IDENTIFIER: %s\n", yytext); }
[0-9]+                  { printf("CONSTANT: %s\n", yytext); }
[+\-*/=<>&|]            { printf("OPERATOR: %s\n", yytext); }
.                       { printf("UNKNOWN: %s\n", yytext); }

%%

int main(int argc, char* argv[]) {
    if (argc < 2) {
        printf("Usage: %s <input file>\n", argv[0]);
        return 1;
    }

    FILE *file = fopen(argv[1], "r");
    if (!file) {
        perror("Error opening file");
        return 1;
    }

    yyin = file;
    yylex();
    fclose(file);
    return 0;
}
