#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

// Constants for token types
#define KEYWORD 1
#define IDENTIFIER 2
#define LITERAL 3
#define OPERATOR 4
#define SEPARATOR 5
#define PREPROCESSOR 6 
#define HEADER 7

// Structure to hold token information
typedef struct {
    int serialNumber;
    char lexeme[50];
    int type;
} Token;

// Function to classify tokens
int classifyToken(char* token) {
    // Check for preprocessor directive
    if (strcmp(token, "#include") == 0 || strcmp(token, "#define") == 0)
        return PREPROCESSOR;

    // Check for headers
    if (token[0] == '<' && token[strlen(token) - 1] == '>')
        return HEADER;

    // Check for keywords
    char* keywords[] = {
        "auto", "break", "case", "char", "const", "continue", "default", "do",
        "double", "else", "enum", "extern", "float", "for", "goto", "if",
        "int", "long", "register", "return", "short", "signed", "sizeof", "static",
        "struct", "switch", "typedef", "union", "unsigned", "void", "volatile", "while"
    };
    int numKeywords = sizeof(keywords) / sizeof(keywords[0]);
    for (int i = 0; i < numKeywords; i++) {
        if (strcmp(token, keywords[i]) == 0)
            return KEYWORD;
    }

    // Check for separators
    char separators[] = { ',', ';', '.', ':', '?', '\'', '\"', '(', ')', '[', ']', '{', '}' };
    int numSeparators = sizeof(separators) / sizeof(separators[0]);
    for (int i = 0; i < numSeparators; i++) {
        if (token[0] == separators[i]) {
            return SEPARATOR;
        }
    }

    // Check for relational operators
    char* relationalOps[] = { ">", "<", ">=", "<=", "!=", "==" };
    int numRelationalOps = sizeof(relationalOps) / sizeof(relationalOps[0]);
    for (int i = 0; i < numRelationalOps; i++) {
        if (strcmp(token, relationalOps[i]) == 0)
            return OPERATOR;
    }

    // Check for arithmetic operators
    char arithmeticOps[] = { '+', '-', '*', '/', '%' };
    int numArithmeticOps = sizeof(arithmeticOps) / sizeof(arithmeticOps[0]);
    for (int i = 0; i < numArithmeticOps; i++) {
        if (token[0] == arithmeticOps[i])
            return OPERATOR;
    }

    // Check for logical operators
    char* logicalOps[] = { "||", "&&", "!" };
    int numLogicalOps = sizeof(logicalOps) / sizeof(logicalOps[0]);
    for (int i = 0; i < numLogicalOps; i++) {
        if (strcmp(token, logicalOps[i]) == 0)
            return OPERATOR;
    }

    // Check for unary operators
    char* unaryOps[] = { "|", "&" };
    int numUnaryOps = sizeof(unaryOps) / sizeof(unaryOps[0]);
    for (int i = 0; i < numUnaryOps; i++) {
        if (strcmp(token, unaryOps[i]) == 0)
            return OPERATOR;
    }

    // Check for ternary operator
    if (strcmp(token, "?:") == 0)
        return OPERATOR;

    // Check for literal constants
    int isLiteral = 1;
    for (int i = 0; i < strlen(token); i++) {
        if (!isdigit(token[i])) {
            isLiteral = 0;
            break;
        }
    }
    if (isLiteral)
        return LITERAL;

    // Default classification is identifier
    return IDENTIFIER;
}


    
// Function to get the type of operator
char* getOperatorType(char* token) {
    // Check for arithmetic operators
    char arithmeticOps[] = { '+', '-', '*', '/', '%' };
    int numArithmeticOps = sizeof(arithmeticOps) / sizeof(arithmeticOps[0]);
    for (int i = 0; i < numArithmeticOps; i++) {
        if (token[0] == arithmeticOps[i]){
            if (token[1] == '=')
                return "Assignment";
            else if (token[0] == '+' && token[1] == '+')
                return "Increment";
            else if (token[0] == '-' && token[1] == '-')
                return "Decrement";
            else if (token[1] == NULL)
                return "Arithmetic";
        }
    }

    // Check for logical operators
    char* logicalOps[] = { "!", "||", "&&" };
    int numLogicalOps = sizeof(logicalOps) / sizeof(logicalOps[0]);
    for (int i = 0; i < numLogicalOps; i++) {
        if (strcmp(token, logicalOps[i]) == 0)
            return "Logical";
    }

    // Check for unary operators
    char* unaryOps[] = { "|", "&" };
    int numUnaryOps = sizeof(unaryOps) / sizeof(unaryOps[0]);
    for (int i = 0; i < numUnaryOps; i++) {
        if (strcmp(token, unaryOps[i]) == 0)
            return "Unary";
    }

    // Check for ternary operator
    if (strcmp(token, "?:") == 0)
        return "Ternary";

    // Check for relational operators
    char* relationalOps[] = { ">", "<", ">=", "<=", "!=", "==" };
    int numRelationalOps = sizeof(relationalOps) / sizeof(relationalOps[0]);
    for (int i = 0; i < numRelationalOps; i++) {
        if (strcmp(token, relationalOps[i]) == 0)
            return "Relational";
    }

    // Check for assignment operators
    char* assignmentOps[] = { "=", "+=", "-=", "*=", "/=", "%=" };
    int numAssignmentOps = sizeof(assignmentOps) / sizeof(assignmentOps[0]);
    for (int i = 0; i < numAssignmentOps; i++) {
        if (strcmp(token, assignmentOps[i]) == 0)
            return "Assignment";
    }

    return "Unknown";
}

char* getSeparatorType(char* token) {
    char separators[] = { ',', ';', '.', ':', '!', '?', '\'', '\"', '(', ')', '[', ']', '{', '}' };
    int numSeparators = sizeof(separators) / sizeof(separators[0]);

    for (int i = 0; i < numSeparators; i++) {
        if (token[0] == separators[i]) {
            if (i < 7) {
                return "Punctuation";
            } else if (i==8){
                return "Left Parenthesis";
            } else if (i==9){
                return "Right Parenthesis";
            } else if (i==10){
                return "Left Angle Brace";
            } else if (i==11){
                return "Right Angle Brace";
            } else if (i==12){
                return "Left Curly Brace";
            } else if (i==13){
                return "Right Curly Brace";
            }
        }
    }

    return "Unknown";
}

int main() {
    char input[500];
    printf("Enter the input: ");
    fgets(input, sizeof(input), stdin);

    // Tokenize input
    char* token = strtok(input, " \n\t");
    int tokenCount = 0;
    Token tokens[100];

    // Classify tokens and store in the array
    while (token != NULL) {
        Token t;
        t.serialNumber = tokenCount + 1;
        strcpy(t.lexeme, token);
        t.type = classifyToken(token);
        tokens[tokenCount] = t;
        tokenCount++;

        token = strtok(NULL, " \n\t");
    }

    // Print the tokens with their classification
    printf("\n--- Token Classification ---\n");
    printf("Serial No.\tLexeme\t\tToken Type\n");
    printf("--------------------------------\n");
    for (int i = 0; i < tokenCount; i++) {
        Token t = tokens[i];
        printf("%d\t\t%s\t\t", t.serialNumber, t.lexeme);
        switch (t.type) {
            case KEYWORD:
                printf("Keyword\n");
                break;
            case PREPROCESSOR:
                printf("Preprocessor Directive\n");
                break;
            case HEADER:
                printf("Header\n");
                break;
            case IDENTIFIER:
                printf("Identifier\n");
                break;
            case LITERAL:
                printf("Literal\n");
                break;
            case OPERATOR:
                printf("Operator - %s\n", getOperatorType(t.lexeme));
                break;
            case SEPARATOR:
                printf("Separator (%s)\n", getSeparatorType(t.lexeme));
                break;
            default:
                printf("Unknown\n");
                break;
        }
    }

    return 0;
}
