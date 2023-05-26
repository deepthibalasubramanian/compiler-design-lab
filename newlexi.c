#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define MAX_TOKENS 100
#define MAX_LENGTH 100

typedef struct {
    int serialNumber;
    char lexeme[MAX_LENGTH];
    char type[MAX_LENGTH];
} Token;

int isKeyword(char* lexeme) {
    char keywords[][10] = {
        "auto", "break", "case", "char", "const", "continue", "default",
        "do", "double", "else", "enum", "extern", "float", "for", "goto",
        "if", "int", "long", "register", "return", "short", "signed", "sizeof",
        "static", "struct", "switch", "typedef", "union", "unsigned", "void",
        "volatile", "while"
    };

    int numKeywords = sizeof(keywords) / sizeof(keywords[0]);

    for (int i = 0; i < numKeywords; i++) {
        if (strcmp(lexeme, keywords[i]) == 0)
            return 1; // It's a keyword
    }

    return 0; // It's not a keyword
}

int isSeparator(char c) {
    char separators[] = {',', ';', ':', '.', '!', '?', '"', '\'', '`'};

    int numSeparators = sizeof(separators) / sizeof(separators[0]);

    for (int i = 0; i < numSeparators; i++) {
        if (c == separators[i])
            return 1; // It's a separator
    }

    return 0; // It's not a separator
}

int isOperator(char c) {
    char operators[] = {'+', '-', '*', '/', '%', '>', '<', '=', '&', '|'};
    int numOperators = sizeof(operators) / sizeof(operators[0]);

    for (int i = 0; i < numOperators; i++) {
        if (c == operators[i])
            return 1; // It's an operator
    }

    return 0; // It's not an operator
}

void printTokens(Token tokens[], int numTokens) {
    printf("Serial No.\tLexeme\t\tType\n");
    printf("-----------------------------------------\n");

    for (int i = 0; i < numTokens; i++) {
        printf("%d\t\t%s\t\t%s\n", tokens[i].serialNumber,
               tokens[i].lexeme, tokens[i].type);
    }
}

int main() {
    char input[MAX_LENGTH];
    printf("Enter the input: ");
    fgets(input, sizeof(input), stdin);

    int numTokens = 0;
    Token tokens[MAX_TOKENS];

    char* token = strtok(input, " \t\n");

    while (token != NULL && numTokens < MAX_TOKENS) {
        strcpy(tokens[numTokens].lexeme, token);

        if (strcmp(token, "#include") == 0 || strcmp(token, "#define") == 0) {
            strcpy(tokens[numTokens].type, "Preprocessor Directive");
        } else if (token[0] == '<' && token[strlen(token) - 1] == '>') {
            strcpy(tokens[numTokens].type, "Header");
        } else if (isKeyword(token)) {
            strcpy(tokens[numTokens].type, "Keyword");
        } else if (isSeparator(token[0])) {
            strcpy(tokens[numTokens].type, "Separator");
        } else if (token[0] == '(' || token[0] == ')' || token[0] == '[' ||
                   token[0] == ']' || token[0] == '{' || token[0] == '}') {
            strcpy(tokens[numTokens].type, "Bracket");
        } else if (isOperator(token[0])) {
            strcpy(tokens[numTokens].type, "Operator");
        } else {
            // Assume it's an identifier or literal constant
            int isLiteral = 1;
            int len = strlen(token);

            for (int i = 0; i < len; i++) {
                if (!isdigit(token[i]) && !isalpha(token[i]) &&
                    token[i] != '.' && token[i] != '\'' && token[i] != '\"') {
                    isLiteral = 0;
                    break;
                }
            }

            if (isLiteral) {
                strcpy(tokens[numTokens].type, "Literal Constant");
            } else {
                strcpy(tokens[numTokens].type, "Identifier");
            }
        }

        tokens[numTokens].serialNumber = numTokens + 1;

        numTokens++;
        token = strtok(NULL, " \t\n");
    }

    printTokens(tokens, numTokens);

    return 0;
}
