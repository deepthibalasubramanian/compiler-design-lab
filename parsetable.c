#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_PRODUCTIONS 100
#define MAX_LENGTH 100

typedef struct {
    char lhs[MAX_LENGTH];
    char rhs[MAX_LENGTH];
} Production;

void splitProduction(char input[], char lhs[], char rhs[]) {
    char *arrow = strchr(input, '-');
    if (arrow != NULL && *(arrow + 1) == '>') {
        *arrow = '\0';
        strcpy(lhs, input);
        strcpy(rhs, arrow + 2);
    } else {
        strcpy(lhs, "");
        strcpy(rhs, "");
    }
}

void acceptProductions(Production productions[], int n);

int isTerminal(char symbol) {
    return !(symbol >= 'A' && symbol <= 'Z');
}

void findFirstSet(char nonTerminal, Production productions[], int n, char firstSet[]) {
    for (int i = 0; i < n; i++) {
        if (productions[i].lhs[0] == nonTerminal) {
            if (isTerminal(productions[i].rhs[0])) {
                // First set contains the terminal symbol
                firstSet[strlen(firstSet)] = productions[i].rhs[0];
                firstSet[strlen(firstSet)] = '\0';
            } else {
                // Recursively find FIRST set for non-terminal symbol
                findFirstSet(productions[i].rhs[0], productions, n, firstSet);
            }
        }
    }
}

void calculateFirstSets(Production productions[], int n, char firstSets[][MAX_LENGTH]) {
    for (int i = 0; i < n; i++) {
        char nonTerminal = productions[i].lhs[0];
        char firstSet[MAX_LENGTH] = "";

        findFirstSet(nonTerminal, productions, n, firstSet);

        // Copy the FIRST set to the result array
        strcpy(firstSets[nonTerminal - 'A'], firstSet);
    }
}

void displayFirstSets(char firstSets[][MAX_LENGTH]) {
    printf("\nFIRST Sets:\n");
    
    for (int i = 0; i < 26; i++) {
        if (strlen(firstSets[i]) > 0) {
            printf("FIRST(%c) = {%s}\n", 'A' + i, firstSets[i]);
        }
    }
}

int main() {
    int n;
    printf("Enter the number of grammar productions: ");
    scanf("%d", &n);

    if (n <= 0 || n > MAX_PRODUCTIONS) {
        printf("Invalid number of productions. Exiting.\n");
        return 1;
    }

    Production productions[MAX_PRODUCTIONS];
    char firstSets[26][MAX_LENGTH];
    for (int i = 0; i < 26; i++) {
        strcpy(firstSets[i], "");
    }

    acceptProductions(productions, n);
    calculateFirstSets(productions, n, firstSets);
    displayFirstSets(firstSets);

    return 0;
}

void acceptProductions(Production productions[], int n) {
    printf("Enter the grammar productions:\n");
    
    for (int i = 0; i < n; i++) {
        char input[MAX_LENGTH];
        printf("Production %d: ", i + 1);
        scanf("%s", input);
        
        splitProduction(input, productions[i].lhs, productions[i].rhs);
    }
}
