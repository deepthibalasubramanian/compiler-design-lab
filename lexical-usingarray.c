#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

// Function to check if a character is a separator
bool isSeparator(char ch) {
    char separators[] = " ,.;()\n\t";
    int numSeparators = strlen(separators);

    for (int i = 0; i < numSeparators; i++) {
        if (ch == separators[i]) {
            return true;
        }
    }

    return false;
}

// Function to check if a character is an operator
bool isOperator(char ch) {
    char operators[] = "+-*/=><!%^&|~";
    int numOperators = strlen(operators);

    for (int i = 0; i < numOperators; i++) {
        if (ch == operators[i]) {
            return true;
        }
    }

    return false;
}

// Function to check if a string is a keyword
bool isKeyword(char* token) {
    char keywords[][20] = {
        "auto", "break", "case", "char", "const", "continue", "default",
        "do", "double", "else", "enum", "extern", "float", "for", "goto",
        "if", "int", "long", "register", "return", "short", "signed", "sizeof",
        "static", "struct", "switch", "typedef", "union", "unsigned", "void",
        "volatile", "while"
    };
    int numKeywords = sizeof(keywords) / sizeof(keywords[0]);

    for (int i = 0; i < numKeywords; i++) {
        if (strcmp(token, keywords[i]) == 0) {
            return true;
        }
    }

    return false;
}

// Function to identify tokens in a statement
void identifyTokens(char statement[]) {
    int length = strlen(statement);
    int start = 0;
    int end = 0;
    int serialNumber = 1;

    while (end < length) {
        if (isSeparator(statement[end])) {
            if (start != end) {
                char token[100];
                strncpy(token, &statement[start], end - start);
                token[end - start] = '\0';

                if (isOperator(token[0])) {
                    printf("%d. Token: %s\tLexeme Type: Operator\n", serialNumber, token);
                } else if (isKeyword(token)) {
                    printf("%d. Token: %s\tLexeme Type: Keyword\n", serialNumber, token);
                } else {
                    printf("%d. Token: %s\tLexeme Type: Identifier\n", serialNumber, token);
                }

                serialNumber++;
            }

            if (statement[end] != ' ' && statement[end] != '\t' && statement[end] != '\n') {
                char separatorToken[2];
                strncpy(separatorToken, &statement[end], 1);
                separatorToken[1] = '\0';
                printf("%d. Token: %s\tLexeme Type: Separator\n", serialNumber, separatorToken);
                serialNumber++;
            }

            start = end + 1;
        } else if (isOperator(statement[end])) {
            if (start != end) {
                char token[100];
                strncpy(token, &statement[start], end - start);
                token[end - start] = '\0';

                if (isKeyword(token)) {
                    printf("%d. Token: %s\tLexeme Type: Keyword\n", serialNumber, token);
                } else {
                    printf("%d. Token: %s\tLexeme Type: Identifier\n", serialNumber, token);
                }

                serialNumber++;
            }

            start = end;
            end++;
            char operatorToken[2];
            strncpy(operatorToken, &statement[start], 1);
            operatorToken[1] = '\0';
            printf("%d. Token: %s\tLexeme Type: Operator\n", serialNumber, operatorToken);
            serialNumber++;
            start = end + 1;
        }

        end++;
    }

    // Check if there is a remaining token at the end of the statement
    if (start < end) {
        char token[100];
        strncpy(token, &statement[start], end - start);
        token[end - start] = '\0';

        if (isOperator(token[0])) {
            printf("%d. Token: %s\tLexeme Type: Operator\n", serialNumber, token);
        } else if (isKeyword(token)) {
            printf("%d. Token: %s\tLexeme Type: Keyword\n", serialNumber, token);
        } else {
            printf("%d. Token: %s\tLexeme Type: Identifier\n", serialNumber, token);
        }
    }
}

int main() {
    char statement[100];

    printf("Enter a statement: ");
    fgets(statement, sizeof(statement), stdin);

    identifyTokens(statement);

    return 0;
}
