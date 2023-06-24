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

int isTerminal(char symbol) {
    return !(symbol >= 'A' && symbol <= 'Z');
}

void findFirstSet(char nonTerminal, Production productions[], int n, char firstSet[]) {
    for (int i = 0; i < n; i++) {
        if (productions[i].lhs[0] == nonTerminal) {
            if (isTerminal(productions[i].rhs[0])) {
                // First set contains the terminal symbol
                if (strchr(firstSet, productions[i].rhs[0]) == NULL) {
                    strncat(firstSet, &productions[i].rhs[0], 1);
                }
            } else {
                // Recursively find FIRST set for non-terminal symbol
                findFirstSet(productions[i].rhs[0], productions, n, firstSet);
                // Add symbols from the first set of the non-terminal
                char tempFirstSet[MAX_LENGTH] = "";
                findFirstSet(productions[i].rhs[0], productions, n, tempFirstSet);
                for (int j = 0; j < strlen(tempFirstSet); j++) {
                    if (tempFirstSet[j] != 'e') {
                        if (strchr(firstSet, tempFirstSet[j]) == NULL) {
                            strncat(firstSet, &tempFirstSet[j], 1);
                        }
                    }
                }
            }
        }
    }
}

void findFollowSet(char nonTerminal, Production productions[], int n, char followSet[]) {
    if (nonTerminal == productions[0].lhs[0]) {
        if (strchr(followSet, '$') == NULL) {
            strcat(followSet, "$");
        }
    }
    
    for (int i = 0; i < n; i++) {
        char *pos = strchr(productions[i].rhs, nonTerminal);
        while (pos != NULL) {
            if (*(pos + 1) == '\0') {
                // Last symbol in production
                if (nonTerminal != productions[i].lhs[0]) {
                    findFollowSet(productions[i].lhs[0], productions, n, followSet);
                    strcat(followSet, followSet);
                }
            } else if (isTerminal(*(pos + 1))) {
                // Terminal symbol after non-terminal
                if (strchr(followSet, *(pos + 1)) == NULL) {
                    strncat(followSet, (pos + 1), 1);
                }
            } else {
                // Non-terminal symbol after non-terminal
                char firstSet[MAX_LENGTH] = "";
                findFirstSet(*(pos + 1), productions, n, firstSet);

                int epsilonFound = 0;
                for (int j = 0; j < strlen(firstSet); j++) {
                    if (firstSet[j] == 'e') {
                        epsilonFound = 1;
                    } else {
                        if (strchr(followSet, firstSet[j]) == NULL) {
                            strncat(followSet, &firstSet[j], 1);
                        }
                    }
                }

                if (epsilonFound) {
                    findFollowSet(productions[i].lhs[0], productions, n, followSet);
                    strcat(followSet, followSet);
                }
            }

            pos = strchr(pos + 1, nonTerminal);
        }
    }
}

void calculateFirstSets(Production productions[], int n, char firstSets[][MAX_LENGTH]) {
    for (int i = 0; i < 26; i++) {
        char nonTerminal = 'A' + i;
        char firstSet[MAX_LENGTH] = "";

        findFirstSet(nonTerminal, productions, n, firstSet);

        // Remove duplicate symbols from firstSet
        char uniqueSymbols[MAX_LENGTH] = "";
        for (int j = 0; j < strlen(firstSet); j++) {
            if (strchr(uniqueSymbols, firstSet[j]) == NULL) {
                strncat(uniqueSymbols, &firstSet[j], 1);
            }
        }

        // Copy the unique symbols to the result array
        strcpy(firstSets[i], uniqueSymbols);
    }
}

void calculateFollowSets(Production productions[], int n, char followSets[][MAX_LENGTH]) {
    for (int i = 0; i < 26; i++) {
        char nonTerminal = 'A' + i;
        char followSet[MAX_LENGTH] = "";

        findFollowSet(nonTerminal, productions, n, followSet);

        // Remove duplicate symbols from followSet
        char uniqueSymbols[MAX_LENGTH] = "";
        for (int j = 0; j < strlen(followSet); j++) {
            if (strchr(uniqueSymbols, followSet[j]) == NULL) {
                strncat(uniqueSymbols, &followSet[j], 1);
            }
        }

        // Copy the unique symbols to the result array
        strcpy(followSets[i], uniqueSymbols);
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

void displayFollowSets(char followSets[][MAX_LENGTH]) {
    printf("\nFOLLOW Sets:\n");
    
    for (int i = 0; i < 26; i++) {
        if (strlen(followSets[i]) > 0) {
            printf("FOLLOW(%c) = {%s}\n", 'A' + i, followSets[i]);
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
    char followSets[26][MAX_LENGTH];

    for (int i = 0; i < 26; i++) {
        strcpy(firstSets[i], "");
        strcpy(followSets[i], "");
    }

    printf("Enter the grammar productions:\n");
    for (int i = 0; i < n; i++) {
        char input[MAX_LENGTH];
        scanf("%s", input);
        splitProduction(input, productions[i].lhs, productions[i].rhs);
    }

    calculateFirstSets(productions, n, firstSets);
    calculateFollowSets(productions, n, followSets);

    displayFirstSets(firstSets);
    displayFollowSets(followSets);

    return 0;
}
