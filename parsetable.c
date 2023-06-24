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

void acceptProductions(Production productions[], int n) {
    printf("Enter the grammar productions:\n");
    
    for (int i = 0; i < n; i++) {
        char input[MAX_LENGTH];
        printf("Production %d: ", i + 1);
        scanf("%s", input);
        
        splitProduction(input, productions[i].lhs, productions[i].rhs);
    }
}

void displayProductions(Production productions[], int n) {
    printf("\nGrammar Productions:\n");
    
    for (int i = 0; i < n; i++) {
        printf("%s -> %s\n", productions[i].lhs, productions[i].rhs);
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
    acceptProductions(productions, n);
    displayProductions(productions, n);

    return 0;
}
