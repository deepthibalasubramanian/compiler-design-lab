#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAX_PROD 10
#define MAX_SYMBOL 10
#define MAX_ROW 6
#define MAX_COL 10
#define MAX_INPUT 10

char prod[MAX_PROD][MAX_SYMBOL];
char table[MAX_ROW][MAX_COL][MAX_SYMBOL];
int size[MAX_ROW][MAX_COL];
int n;
char s[MAX_INPUT], stack[MAX_INPUT];
char nonTerminals[MAX_ROW][MAX_SYMBOL];
char terminals[MAX_COL][MAX_SYMBOL];

void display(int i, int j) {
    int k;
    for (k = 0; k <= i; k++)
        printf("%c", stack[k]);
    printf(" \t\t ");
    for (k = j; k <= n; k++)
        printf("%c", s[k]);
    printf("\n");
}

void initializeParseTable() {
    int i, j;
    for (i = 0; i < MAX_ROW; i++) {
        for (j = 0; j < MAX_COL; j++) {
            strcpy(table[i][j], "");
            size[i][j] = 0;
        }
    }
}

void getParseTable(int nonTerminalsLength, int terminalsLength) {
    int i, j;
    char entry[MAX_SYMBOL];
    printf("Enter the parse table entries:\n");
    for (i = 0; i < nonTerminalsLength; i++) {
        for (j = 0; j < terminalsLength; j++) {
            printf("Entry [%s, %s]: ", nonTerminals[i], terminals[j]);
            scanf("%s", entry);
            if (strcmp(entry, "NULL") == 0) {
                continue;
            } else {
                strcpy(table[i][j], entry);
            }
            size[i][j] = strlen(table[i][j]);
        }
    }
}

void displayParseTable() {
    int i, j;
    printf("Parse table:\n");
    printf("\t");
    for (i = 0; i < MAX_COL; i++) {
        printf("%s\t", terminals[i]);
    }
    printf("\n");
    for (i = 0; i < MAX_ROW; i++) {
        printf("%s\t", nonTerminals[i]);
        for (j = 0; j < MAX_COL; j++) {
            printf("%s\t", table[i][j]);
        }
        printf("\n");
    }
}

int main() {
    int i, j, k, row, col;
    printf("Enter the number of productions: ");
    scanf("%d", &n);

    printf("Enter the grammar:\n");
    for (i = 0; i < n; i++) {
        printf("Production %d: ", i + 1);
        scanf("%s", prod[i]);
    }

    printf("Enter the non-terminals (comma-separated): ");
    char nonTerminalInput[100];
    scanf("%s", nonTerminalInput);
    char* token = strtok(nonTerminalInput, ",");
    i = 0;
    int ntcount = 0;
    while (token != NULL && i < MAX_ROW) {
        strcpy(nonTerminals[i], token);
        ntcount++;
        i++;
        token = strtok(NULL, ",");
    }

    printf("Enter the terminals (comma-separated): ");
    char terminalInput[100];
    scanf("%s", terminalInput);
    token = strtok(terminalInput, ",");
    i = 0;
    int tercount = 0;
    while (token != NULL && i < MAX_COL) {
        strcpy(terminals[i], token);
        tercount++;
        i++;
        token = strtok(NULL, ",");
    }

    initializeParseTable();
    getParseTable(ntcount, tercount);
    displayParseTable();

    printf("Enter the string: ");
    scanf("%s", s);
    strcat(s, "$");
    n = strlen(s);
    stack[0] = '$';
    stack[1] = nonTerminals[0][0];
    i = 1;
    j = 0;
    printf("\nStack operations:\n");
    while (1) {
        if (stack[i] == s[j]) {
            i--;
            j++;
            if (stack[i] == '$' && s[j] == '$') {
                printf("SUCCESS, String parsed and accepted.\n");
                break;
            } else if (stack[i] == '$' && s[j] != '$') {
                printf("Error\n");
                break;
            }
            display(i, j);
        } else {
            for (row = 0; row < MAX_ROW; row++) {
                if (stack[i] == nonTerminals[row][0])
                    break;
            }
            for (col = 0; col < MAX_COL; col++) {
                if (s[j] == terminals[col][0])
                    break;
            }
            if (row == MAX_ROW || col == MAX_COL) {
                printf("\nError\n");
                break;
            }
            if (table[row][col][0] == '\0') {
                printf("\nError\n");
                break;
            } else if (strcmp(table[row][col], "e") == 0) {
                i--;
                display(i, j);
            } else {
                for (k = size[row][col] - 1; k >= 0; k--) {
                    stack[i] = table[row][col][k];
                    i++;
                }
                i--;
                display(i, j);
            }
        }
    }
    return 0;
}
