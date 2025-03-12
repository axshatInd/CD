%{
    #include <stdio.h>
    int vowel_count = 0, consonant_count = 0, digit_count = 0;
    %}
    
    %%
    
    [aeiouAEIOU]    { vowel_count++; }
    [a-zA-Z]        { consonant_count++; }
    [0-9]          { digit_count++; }
    /* Ignore other characters */
    
    %%
    
    int main() {
        printf("Enter text (Ctrl+D to end input):\n");
        yylex();
        printf("Vowels: %d\n", vowel_count);
        printf("Consonants: %d\n", consonant_count);
        printf("Digits: %d\n", digit_count);
        return 0;
    }
    
    int yywrap() { return 1; }
    