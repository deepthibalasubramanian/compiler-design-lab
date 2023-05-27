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

int serialNumber = 1; // Global variable to track the serial number

void printToken(const char* tokenName, const char* tokenType) {
    printf("%d, %s, %s\n", serialNumber++, tokenName, tokenType);
}
%}

%%
"#".*              { printToken("PREPROCESSOR DIRECTIVE and HEADER", yytext); }
auto|break|case|char|const|continue|default|do|double|else|enum|extern|float|for|goto|if|inline|int|long|register|restrict|return|short|signed|sizeof|static|struct|switch|typedef|union|unsigned|void|volatile|while {
                      printToken("KEYWORD", yytext);
                    }
[0-9]+              { printToken("INTEGER LITERAL", yytext); }
[0-9]+\.[0-9]+     { printToken("FLOATING POINT LITERAL", yytext); }
[a-zA-Z_][a-zA-Z0-9_]* {
                      if (isValidIdentifier(yytext)) {
                          printToken("IDENTIFIER", yytext);
                      } else {
                          printToken("INVALID IDENTIFIER", yytext);
                      }
                    }
\+\+                { printToken("INCREMENT OPERATOR", yytext); }
--                  { printToken("DECREMENT OPERATOR", yytext); }
[+\-*/%]=           { printToken("ARITHMETIC OPERATOR", yytext); }
[+\-*/%]            { printToken("ARITHMETIC OPERATOR", yytext); }
[><]=?              { printToken("RELATIONAL OPERATOR", yytext); }
&&|\|\||!           { printToken("LOGICAL OPERATOR", yytext); }
\?                  { printToken("TERNARY OPERATOR", yytext); }
=                   { printToken("ASSIGNMENT OPERATOR", yytext); }
\(                  { printToken("LEFT PARENTHESIS", yytext); }
\)                  { printToken("RIGHT PARENTHESIS", yytext); }
\{                  { printToken("LEFT CURLY BRACE", yytext); }
\}                  { printToken("RIGHT CURLY BRACE", yytext); }
\[                  { printToken("LEFT SQUARE BRACKET", yytext); }
\]                  { printToken("RIGHT SQUARE BRACKET", yytext); }
,                   { printToken("COMMA", yytext); }
;                   { printToken("SEMICOLON", yytext); }
:                   { printToken("COLON", yytext); }
\.                  { printToken("DOT", yytext); }
"([^\"\\]|\\.)*"    { printToken("STRING LITERAL", yytext); }
[ \t\n]             ; // Ignore whitespace and newlines

%%

int main(int argc, char** argv)
{
    if (argc < 2) {
        printf("Usage: %s samplecode.txt\n", argv[0]);
        return 1;
    }

    FILE* inputFile = fopen(argv[1], "r");
    if (!inputFile) {
        printf("Error opening input file: %s\n", argv[1]);
        return 1;
    }

    yyin = inputFile;
    yylex();

    fclose(inputFile);
    return 0;
}
