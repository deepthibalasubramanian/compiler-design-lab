%{
#include <stdio.h>
#include <string.h>
%}

%option noyywrap

%{
// Function to validate identifiers
int isValidIdentifier(char* identifier) {
    // Check if the identifier starts with a letter or underscore
    if (!((identifier[0] >= 'a' && identifier[0] <= 'z') ||
          (identifier[0] >= 'A' && identifier[0] <= 'Z') ||
          identifier[0] == '_')) {
        return 0; // Invalid identifier
    }

    // Check if the remaining characters are alphanumeric or underscore
    for (int i = 1; i < strlen(identifier); i++) {
        if (!((identifier[i] >= 'a' && identifier[i] <= 'z') ||
              (identifier[i] >= 'A' && identifier[i] <= 'Z') ||
              (identifier[i] >= '0' && identifier[i] <= '9') ||
              identifier[i] == '_')) {
            return 0; // Invalid identifier
        }
    }

    return 1; // Valid identifier
}
%}

%%

[0-9]+              { printf("INTEGER LITERAL: %s\n", yytext); }
[0-9]+\.[0-9]+     { printf("FLOATING POINT LITERAL: %s\n", yytext); }
[a-zA-Z_][a-zA-Z0-9_]* {
                      if (isValidIdentifier(yytext)) {
                          printf("VALID IDENTIFIER: %s\n", yytext);
                      } else {
                          printf("INVALID IDENTIFIER: %s\n", yytext);
                      }
                    }
\+\+                { printf("INCREMENT OPERATOR: %s\n", yytext); }
--                  { printf("DECREMENT OPERATOR: %s\n", yytext); }
[+\-*/%]            { printf("ARITHMETIC OPERATOR: %s\n", yytext); }
[><=!]=?            { printf("RELATIONAL OPERATOR: %s\n", yytext); }
&&|\\|!             { printf("LOGICAL OPERATOR: %s\n", yytext); }
\?                  { printf("TERNARY OPERATOR: %s\n", yytext); }
\(                  { printf("LEFT PARENTHESIS\n"); }
\)                  { printf("RIGHT PARENTHESIS\n"); }
\{                  { printf("LEFT CURLY BRACE\n"); }
\}                  { printf("RIGHT CURLY BRACE\n"); }
\[                  { printf("LEFT SQUARE BRACKET\n"); }
\]                  { printf("RIGHT SQUARE BRACKET\n"); }
,                   { printf("COMMA\n"); }
;                   { printf("SEMICOLON\n"); }
:                   { printf("COLON\n"); }
\.                  { printf("DOT\n"); }
"([^\"\\]|\\.)*"    { printf("STRING LITERAL: %s\n", yytext); }
[ \t\n]             ; // Ignore whitespace and newlines

%%

int main()
{
    yylex();
    return 0;
}
