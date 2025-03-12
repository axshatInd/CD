%{
#include <stdio.h>
#include <stdlib.h>

void yyerror(const char *);
int yylex();
%}

%token NUMBER
%left '+' '-'
%left '*' '/'
%left '(' ')'

%%

calculation:
    calculation expression '\n' { printf("Result: %d\n", $2); }
    | /* empty */
    ;

expression:
    expression '+' expression { $$ = $1 + $3; }
    | expression '-' expression { $$ = $1 - $3; }
    | expression '*' expression { $$ = $1 * $3; }
    | expression '/' expression 
        { 
            if ($3 == 0) 
                yyerror("Error: Division by zero!");
            else 
                $$ = $1 / $3; 
        }
    | '(' expression ')' { $$ = $2; }
    | NUMBER { $$ = $1; }
    ;

%%

void yyerror(const char *s) {
    fprintf(stderr, "%s\n", s);
}

int main() {
    printf("Enter an expression:\n");
    yyparse();
    return 0;
}
