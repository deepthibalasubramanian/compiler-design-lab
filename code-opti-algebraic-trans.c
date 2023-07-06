#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <ctype.h>

#define MAX_CODE_LINES 100
#define MAX_CODE_LENGTH 100

// Structure to represent a line of three-address code
typedef struct {
    char res[MAX_CODE_LENGTH];
    char op[MAX_CODE_LENGTH];
    char arg1[MAX_CODE_LENGTH];
    char arg2[MAX_CODE_LENGTH];
} CodeLine;

// Function to check if a character is an operator
bool isOperator(char c) {
    return (c == '+' || c == '-' || c == '*' || c == '/');
}

// Function to check if a character is an opening bracket
bool isOpeningBracket(char c) {
    return (c == '(' || c == '[' || c == '{');
}

// Function to check if a character is a closing bracket
bool isClosingBracket(char c) {
    return (c == ')' || c == ']' || c == '}');
}

// Function to get the precedence of an operator
int getPrecedence(char op) {
    if (op == '+' || op == '-')
        return 1;
    else if (op == '*' || op == '/')
        return 2;
    else
        return 0;
}

// Function to perform constant folding optimization on the given expression
void optimizeExpression(char* expr) {
    int len = strlen(expr);
    char* result = (char*)malloc(len * sizeof(char));
    char* stack = (char*)malloc(len * sizeof(char));
    int resultIndex = 0;
    int stackIndex = 0;

    for (int i = 0; i < len; i++) {
        if (isOperator(expr[i])) {
            while (stackIndex > 0 && isOperator(stack[stackIndex - 1]) &&
                   getPrecedence(stack[stackIndex - 1]) >= getPrecedence(expr[i])) {
                result[resultIndex++] = stack[stackIndex - 1];
                stackIndex--;
            }
            stack[stackIndex++] = expr[i];
        } else if (isOpeningBracket(expr[i])) {
            stack[stackIndex++] = expr[i];
        } else if (isClosingBracket(expr[i])) {
            while (stackIndex > 0 && !isOpeningBracket(stack[stackIndex - 1])) {
                result[resultIndex++] = stack[stackIndex - 1];
                stackIndex--;
            }
            stackIndex--;  // Discard the opening bracket from the stack
        } else {
            result[resultIndex++] = expr[i];
        }
    }

    while (stackIndex > 0) {
        result[resultIndex++] = stack[stackIndex - 1];
        stackIndex--;
    }

    result[resultIndex] = '\0';

    strcpy(expr, result);

    free(result);
    free(stack);
}

// Function to perform constant folding optimization on the given line of code
void optimizeCodeLine(CodeLine* line) {
    optimizeExpression(line->arg1);
    optimizeExpression(line->arg2);

    int arg1, arg2;
    bool foldable = true;

    // Check if the arguments are constants and can be folded
    if (isdigit(line->arg1[0])) {
        arg1 = atoi(line->arg1);
    } else {
        foldable = false;
    }

    if (isdigit(line->arg2[0])) {
        arg2 = atoi(line->arg2);
    } else {
        foldable = false;
    }

    // Perform the folding if possible
    if (foldable) {
        int result = 0;
        if (strcmp(line->op, "+") == 0) {
            result = arg1 + arg2;
        } else if (strcmp(line->op, "-") == 0) {
            result = arg1 - arg2;
        } else if (strcmp(line->op, "*") == 0) {
            result = arg1 * arg2;
        } else if (strcmp(line->op, "/") == 0) {
            result = arg1 / arg2;
        } else if (strcmp(line->op, "%") == 0) {
            result = arg1 % arg2;
        } else {
            foldable = false;
        }

        if (foldable) {
            sprintf(line->op, "=");
            sprintf(line->arg1, "%d", result);
            sprintf(line->arg2, " ");
        }
    }
}

// Function to perform algebraic transformation optimization on the given line of code
void optimizeAlgebraicTransformation(CodeLine* line) {
    // Apply algebraic transformations and simplifications

    // Check for multiplication by 0 or 1
    if (strcmp(line->op, "*") == 0) {
        if (strcmp(line->arg1, "0") == 0 || strcmp(line->arg2, "0") == 0) {
            sprintf(line->op, "=");
            sprintf(line->arg1, "0");
            sprintf(line->arg2, " ");
        } else if (strcmp(line->arg1, "1") == 0) {
            sprintf(line->op, "=");
            strcpy(line->arg1, line->arg2);
            sprintf(line->arg2, " ");
        } else if (strcmp(line->arg2, "1") == 0) {
            sprintf(line->op, "=");
            strcpy(line->arg2, line->arg1);
            sprintf(line->arg1, " ");
        }
    }

    // Check for addition or subtraction with 0
    if (strcmp(line->op, "+") == 0 || strcmp(line->op, "-") == 0) {
        if (strcmp(line->arg1, "0") == 0) {
            sprintf(line->op, "=");
            strcpy(line->arg1, line->arg2);
            sprintf(line->arg2, " ");
        } else if (strcmp(line->arg2, "0") == 0) {
            sprintf(line->op, "=");
            sprintf(line->arg2, " ");
        }
    }

    // Check for multiplication by 2
    if (strcmp(line->op, "*") == 0 && strcmp(line->arg2, "2") == 0) {
        sprintf(line->op, "+");
        strcpy(line->arg2, line->arg1);
    }
}

// Function to display the given code line
void displayCodeLine(CodeLine* line) {
    printf("%s %s %s %s\n", line->res, line->op, line->arg1, line->arg2);
}

int main() {
    CodeLine codeLines[MAX_CODE_LINES];
    int lineCount = 0;

    // Read the code lines from input
    printf("Enter the three-address code (enter 'end' to finish):\n");
    char input[MAX_CODE_LENGTH];
    while (true) {
        fgets(input, MAX_CODE_LENGTH, stdin);
        input[strcspn(input, "\n")] = '\0';  // Remove trailing newline

        if (strcmp(input, "end") == 0) {
            break;
        }

        sscanf(input, "%s = %s %s %s",
               codeLines[lineCount].res,
               codeLines[lineCount].arg1,
               codeLines[lineCount].op,
               codeLines[lineCount].arg2);

        lineCount++;
    }

    // Perform constant folding optimization on each code line
    for (int i = 0; i < lineCount; i++) {
        printf("Optimizing line %d: ", i + 1);
        displayCodeLine(&codeLines[i]);
        optimizeCodeLine(&codeLines[i]);
        optimizeAlgebraicTransformation(&codeLines[i]);
    }

    // Display the optimized code lines
    printf("Optimized Code:\n");
    for (int i = 0; i < lineCount; i++) {
        printf("Optimized line %d: ", i + 1);
        displayCodeLine(&codeLines[i]);
    }

    return 0;
}
