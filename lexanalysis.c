#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define MAX_TOKENS 100
#define MAX_IDENTIFIERS 100
#define MAX_KEYWORDS 35

int isKeyword(char buffer[]) {
    char keywords[MAX_KEYWORDS][15] = {
        "auto", "break", "case", "char", "const", "continue", "default",
        "do", "double", "else", "enum", "extern", "float", "for", "goto",
        "if", "int", "long", "register", "return", "short", "signed",
        "sizeof", "static", "struct", "switch", "typedef", "union",
        "unsigned", "void", "volatile", "while", "printf", "scanf"
    };

    int i, flag = 0;

    for (i = 0; i < MAX_KEYWORDS; ++i) {
        if (strcmp(keywords[i], buffer) == 0) {
            flag = 1;
            break;
        }
    }

    return flag;
}

int isConstant(char lexeme[]) {
    int i, flag = 1;

    if (!isdigit(lexeme[0])) {
        flag = 0;
    } else {
        for (i = 1; i < strlen(lexeme); ++i) {
            if (!isdigit(lexeme[i])) {
                flag = 0;
                break;
            }
        }
    }

    return flag;
}

void printToken(char lexeme[], char tokenType[]) {
    static int tokenNumber = 1;
    printf("%d. Lexeme: %s, Token Type: %s\n", tokenNumber++, lexeme, tokenType);
}

int main() {
    char input[1000];
    char lexeme[20];
    char separators[] = "(){};,<>";
    char operators[] = "+-*/%=&|!";
    char** tokens = (char**)malloc(MAX_TOKENS * sizeof(char*));
    char** identifiers = (char**)malloc(MAX_IDENTIFIERS * sizeof(char*));
    char** keywords = (char**)malloc(MAX_KEYWORDS * sizeof(char*));

    int i, j = 0, k = 0;

    for (i = 0; i < MAX_TOKENS; ++i) {
        tokens[i] = (char*)malloc(15 * sizeof(char));
    }

    for (i = 0; i < MAX_IDENTIFIERS; ++i) {
        identifiers[i] = (char*)malloc(15 * sizeof(char));
    }

    for (i = 0; i < MAX_KEYWORDS; ++i) {
        keywords[i] = (char*)malloc(15 * sizeof(char));
    }

    printf("Enter the input: ");
    fgets(input, sizeof(input), stdin);
    input[strcspn(input, "\n")] = '\0';  // Remove trailing newline

    for (i = 0; i < strlen(input); ++i) {
        if (isalnum(input[i]) || input[i] == '.') {
            lexeme[j++] = input[i];
        } else if (strchr(operators, input[i]) != NULL) {
            if (j > 0) {
                lexeme[j] = '\0';
                strcpy(tokens[k++], lexeme);
                if (isKeyword(lexeme)) {
                    printToken(lexeme, "Keyword");
                } else if (isConstant(lexeme)) {
                    printToken(lexeme, "Constant");
                } else {
                    printToken(lexeme, "Identifier");
                }
                j = 0;
                memset(lexeme, 0, sizeof(lexeme));
            }
            lexeme[j++] = input[i];
            lexeme[j] = '\0';
            strcpy(tokens[k++], lexeme);
            if (input[i] == '+')
                printToken(lexeme, "Arithmetic Operator: Addition");
            else if (input[i] == '-')
                printToken(lexeme, "Arithmetic Operator: Subtraction");
            else if (input[i] == '*')
                printToken(lexeme, "Arithmetic Operator: Multiplication");
            else if (input[i] == '/')
                printToken(lexeme, "Arithmetic Operator: Division");
            else if (input[i] == '%')
                printToken(lexeme, "Arithmetic Operator: Modulus");
            else if (input[i] == '<')
                printToken(lexeme, "Relational Operator: Less Than");
            else if (input[i] == '>')
                printToken(lexeme, "Relational Operator: Greater Than");
            else if (input[i] == '=')
                printToken(lexeme, "Operator: Assignment");
            else if (input[i] == '!')
                printToken(lexeme, "Logical Operator: Not");
            else if (input[i] == '&')
                printToken(lexeme, "Operator: Logical AND");
            else if (input[i] == '|')
                printToken(lexeme, "Operator: Logical OR");
            else if (input[i] == '&' && input[i+1] == '&') {
                lexeme[j++] = input[++i];
                lexeme[j] = '\0';
                strcpy(tokens[k++], lexeme);
                printToken(lexeme, "Logical Operator: AND");
                j = 0;
                memset(lexeme, 0, sizeof(lexeme));
            }
            else if (input[i] == '|' && input[i+1] == '|') {
                lexeme[j++] = input[++i];
                lexeme[j] = '\0';
                strcpy(tokens[k++], lexeme);
                printToken(lexeme, "Logical Operator: OR");
                j = 0;
                memset(lexeme, 0, sizeof(lexeme));
            }
            j = 0;
            memset(lexeme, 0, sizeof(lexeme));
        } else if (strchr(separators, input[i]) != NULL) {
            if (j > 0) {
                lexeme[j] = '\0';
                strcpy(tokens[k++], lexeme);
                if (isKeyword(lexeme)) {
                    printToken(lexeme, "Keyword");
                } else if (isConstant(lexeme)) {
                    printToken(lexeme, "Constant");
                } else {
                    printToken(lexeme, "Identifier");
                }
                j = 0;
                memset(lexeme, 0, sizeof(lexeme));
            }
            lexeme[j++] = input[i];
            lexeme[j] = '\0';
            strcpy(tokens[k++], lexeme);
            if (input[i] == '(')
                printToken(lexeme, "Left Parenthesis");
            else if (input[i] == ')')
                printToken(lexeme, "Right Parenthesis");
            else if (input[i] == '{')
                printToken(lexeme, "Left Brace");
            else if (input[i] == '}')
                printToken(lexeme, "Right Brace");
            else if (input[i] == ';')
                printToken(lexeme, "Separator: Semicolon");
            else if (input[i] == ',')
                printToken(lexeme, "Separator: Comma");
            else if (input[i] == '<')
                printToken(lexeme, "Separator: Less Than");
            else if (input[i] == '>')
                printToken(lexeme, "Separator: Greater Than");
            j = 0;
            memset(lexeme, 0, sizeof(lexeme));
        } else if (isspace(input[i])) {
            if (j > 0) {
                lexeme[j] = '\0';
                strcpy(tokens[k++], lexeme);
                if (isKeyword(lexeme)) {
                    printToken(lexeme, "Keyword");
                } else if (isConstant(lexeme)) {
                    printToken(lexeme, "Constant");
                } else {
                    printToken(lexeme, "Identifier");
                }
                j = 0;
                memset(lexeme, 0, sizeof(lexeme));
            }
        }
    }

    for (i = 0; i < MAX_TOKENS; ++i) {
        free(tokens[i]);
    }
    free(tokens);

    for (i = 0; i < MAX_IDENTIFIERS; ++i) {
        free(identifiers[i]);
    }
    free(identifiers);

    for (i = 0; i < MAX_KEYWORDS; ++i) {
        free(keywords[i]);
    }
    free(keywords);

    return 0;
}
