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
    char keywords[][20] = {
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

int isOperator(char* lexeme) {
    char arithmeticOperators[][3] = {"+", "-", "*", "/", "%"};
    char logicalOperators[][3] = {"||", "&&", "!"};
    char unaryOperators[][3] = {"|", "&"};
    char incrementOperator[] = "++";
    char decrementOperator[] = "--";
    char ternaryOperator[] = "?:";
    char relationalOperators[][3] = {">", "<", ">=", "<=", "!=", "=="};
    char assignmentOperators[][4] = {"=", "+=", "-=", "*=", "/=", "%="};

    int numArithmeticOperators = sizeof(arithmeticOperators) / sizeof(arithmeticOperators[0]);
    int numLogicalOperators = sizeof(logicalOperators) / sizeof(logicalOperators[0]);
    int numUnaryOperators = sizeof(unaryOperators) / sizeof(unaryOperators[0]);
    int numRelationalOperators = sizeof(relationalOperators) / sizeof(relationalOperators[0]);
    int numAssignmentOperators = sizeof(assignmentOperators) / sizeof(assignmentOperators[0]);

    for (int i = 0; i < numArithmeticOperators; i++) {
        if (strcmp(lexeme, arithmeticOperators[i]) == 0)
            return 1; // It's an arithmetic operator
    }

    for (int i = 0; i < numLogicalOperators; i++) {
        if (strcmp(lexeme, logicalOperators[i]) == 0)
            return 2; // It's a logical operator
    }

    for (int i = 0; i < numUnaryOperators; i++) {
        if (strcmp(lexeme, unaryOperators[i]) == 0)
            return 3; // It's a unary operator
    }

    if (strcmp(lexeme, incrementOperator) == 0)
        return 4; // It's an increment operator

    if (strcmp(lexeme, decrementOperator) == 0)
        return 5; // It's a decrement operator

    if (strcmp(lexeme, ternaryOperator) == 0)
        return 6; // It's a ternary operator

    for (int i = 0; i < numRelationalOperators; i++) {
        if (strcmp(lexeme, relationalOperators[i]) == 0)
            return 7; // It's a relational operator
    }

    for (int i = 0; i < numAssignmentOperators; i++) {
        if (strcmp(lexeme, assignmentOperators[i]) == 0)
            return 8; // It's an assignment operator
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
        if (strcmp(token, "#include") == 0 || strcmp(token, "#define") == 0) {
            strcpy(tokens[numTokens].lexeme, token);
            strcpy(tokens[numTokens].type, "Preprocessor Directive");
            tokens[numTokens].serialNumber = numTokens + 1;
            numTokens++;
        } else if (token[0] == '<' && token[strlen(token) - 1] == '>') {
            strcpy(tokens[numTokens].lexeme, token);
            strcpy(tokens[numTokens].type, "Header");
            tokens[numTokens].serialNumber = numTokens + 1;
            numTokens++;
        } else {
            int len = strlen(token);
            int i = 0;

            while (i < len) {
                if (isspace(token[i])) {
                    i++;
                    continue;
                } else if (isSeparator(token[i])) {
                    tokens[numTokens].lexeme[0] = token[i];
                    tokens[numTokens].lexeme[1] = '\0';
                    strcpy(tokens[numTokens].type, "Separator");
                    tokens[numTokens].serialNumber = numTokens + 1;
                    numTokens++;
                    i++;
                } else if (token[i] == '(' || token[i] == ')') {
                    tokens[numTokens].lexeme[0] = token[i];
                    tokens[numTokens].lexeme[1] = '\0';
                    strcpy(tokens[numTokens].type, "Parenthesis");
                    tokens[numTokens].serialNumber = numTokens + 1;
                    numTokens++;
                    i++;
                } else if (token[i] == '[' || token[i] == ']') {
                    tokens[numTokens].lexeme[0] = token[i];
                    tokens[numTokens].lexeme[1] = '\0';
                    strcpy(tokens[numTokens].type, "Angle Brace");
                    tokens[numTokens].serialNumber = numTokens + 1;
                    numTokens++;
                    i++;
                } else if (token[i] == '{' || token[i] == '}') {
                    tokens[numTokens].lexeme[0] = token[i];
                    tokens[numTokens].lexeme[1] = '\0';
                    strcpy(tokens[numTokens].type, "Curly Brace");
                    tokens[numTokens].serialNumber = numTokens + 1;
                    numTokens++;
                    i++;
                } else if (isOperator(token + i) != 0) {
                    int j = i;
                    while (j < len && isOperator(token + i) == isOperator(token + j))
                        j++;

                    strncpy(tokens[numTokens].lexeme, token + i, j - i);
                    tokens[numTokens].lexeme[j - i] = '\0';

                    if (isKeyword(tokens[numTokens].lexeme)) {
                        strcpy(tokens[numTokens].type, "Keyword");
                    } else if (isOperator(tokens[numTokens].lexeme) == 1) {
                        strcpy(tokens[numTokens].type, "Arithmetic Operator");
                    } else if (isOperator(tokens[numTokens].lexeme) == 2) {
                        strcpy(tokens[numTokens].type, "Logical Operator");
                    } else if (isOperator(tokens[numTokens].lexeme) == 3) {
                        strcpy(tokens[numTokens].type, "Unary Operator");
                    } else if (isOperator(tokens[numTokens].lexeme) == 4) {
                        strcpy(tokens[numTokens].type, "Increment Operator");
                    } else if (isOperator(tokens[numTokens].lexeme) == 5) {
                        strcpy(tokens[numTokens].type, "Decrement Operator");
                    } else if (isOperator(tokens[numTokens].lexeme) == 6) {
                        strcpy(tokens[numTokens].type, "Ternary Operator");
                    } else if (isOperator(tokens[numTokens].lexeme) == 7) {
                        strcpy(tokens[numTokens].type, "Relational Operator");
                    } else if (isOperator(tokens[numTokens].lexeme) == 8) {
                        strcpy(tokens[numTokens].type, "Assignment Operator");
                    } else if (isdigit(tokens[numTokens].lexeme[0]) ||
                               tokens[numTokens].lexeme[0] == '"' ||
                               tokens[numTokens].lexeme[0] == '\'') {
                        strcpy(tokens[numTokens].type, "Literal Constant");
                    } else {
                        strcpy(tokens[numTokens].type, "Identifier");
                    }

                    tokens[numTokens].serialNumber = numTokens + 1;
                    numTokens++;
                    i = j;
                } else {
                    int j = i;
                    while (j < len && !isspace(token[j]) &&
                           !isSeparator(token[j]) &&
                           token[j] != '(' && token[j] != ')' &&
                           token[j] != '[' && token[j] != ']' &&
                           token[j] != '{' && token[j] != '}' &&
                           isOperator(token + j) == 0)
                        j++;

                    strncpy(tokens[numTokens].lexeme, token + i, j - i);
                    tokens[numTokens].lexeme[j - i] = '\0';

                    if (isKeyword(tokens[numTokens].lexeme)) {
                        strcpy(tokens[numTokens].type, "Keyword");
                    } else if (isOperator(tokens[numTokens].lexeme) == 1) {
                        strcpy(tokens[numTokens].type, "Arithmetic Operator");
                    } else if (isOperator(tokens[numTokens].lexeme) == 2) {
                        strcpy(tokens[numTokens].type, "Logical Operator");
                    } else if (isOperator(tokens[numTokens].lexeme) == 3) {
                        strcpy(tokens[numTokens].type, "Unary Operator");
                    } else if (isOperator(tokens[numTokens].lexeme) == 4) {
                        strcpy(tokens[numTokens].type, "Increment Operator");
                    } else if (isOperator(tokens[numTokens].lexeme) == 5) {
                        strcpy(tokens[numTokens].type, "Decrement Operator");
                    } else if (isOperator(tokens[numTokens].lexeme) == 6) {
                        strcpy(tokens[numTokens].type, "Ternary Operator");
                    } else if (isOperator(tokens[numTokens].lexeme) == 7) {
                        strcpy(tokens[numTokens].type, "Relational Operator");
                    } else if (isOperator(tokens[numTokens].lexeme) == 8) {
                        strcpy(tokens[numTokens].type, "Assignment Operator");
                    } else if (isdigit(tokens[numTokens].lexeme[0]) ||
                               tokens[numTokens].lexeme[0] == '"' ||
                               tokens[numTokens].lexeme[0] == '\'') {
                        strcpy(tokens[numTokens].type, "Literal Constant");
                    } else {
                        strcpy(tokens[numTokens].type, "Identifier");
                    }

                    tokens[numTokens].serialNumber = numTokens + 1;
                    numTokens++;
                    i = j;
                }
            }
        }

        token = strtok(NULL, " \t\n");
    }

    printTokens(tokens, numTokens);

    return 0;
}
