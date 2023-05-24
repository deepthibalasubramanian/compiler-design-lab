#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main() {
    int n, s, f, i, j, c, l, u, t, k = 0;
    char dfa[10][10], node[10], in[10], final[10], string1[15];

    // Input the number of nodes, states, and final states
    printf("Enter number of nodes: ");
    scanf("%d", &n);
    printf("Enter number of states: ");
    scanf("%d", &s);
    printf("Enter number of final states: ");
    scanf("%d", &f);
    char z;
    scanf("%c", &z); // Remove the newline character from the previous input

    // Input the values of nodes
    for (int i = 0; i < n; i++) {
        printf("Enter value of node %d: ", i);
        scanf(" %c", &node[i]);
        scanf("%c", &z); // Remove the newline character from the input
    }

    // Input the states
    for (int i = 0; i < s; i++) {
        printf("Enter the state %d: ", i);
        scanf(" %c", &in[i]);
        scanf("%c", &z); // Remove the newline character from the input
    }

    // Input the final states
    for (int i = 0; i < f; i++) {
        printf("Enter final state %d: ", i);
        scanf(" %c", &final[i]);
        scanf("%c", &z); // Remove the newline character from the input
    }

    // Assign nodes and states to the DFA array
    for (int i = 0; i < n; i++) {
        dfa[i + 1][0] = node[i];
    }
    for (int i = 0; i < s; i++) {
        dfa[0][i + 1] = in[i];
    }

    dfa[0][0] = 'D'; // Assign 'D' to the top-left corner of the DFA array

    // Input the transition table values for each node and state
    for (i = 0; i < n; i++) {
        for (j = 0; j < s; j++) {
            printf("D(%c,%c)=", dfa[i + 1][0], dfa[0][j + 1]);
            scanf(" %c", &dfa[i + 1][j + 1]);
            scanf("%c", &z); // Remove the newline character from the input
        }
    }

    // Display the transition table
    printf("\nTransition Table: \n");
    for (i = 0; i <= n; i++) {
        for (j = 0; j <= s; j++) {
            printf("\t%c", dfa[i][j]);
        }
        printf("\n");
    }

    // Input the string to be checked
    printf("Enter the string to be checked: ");
    scanf("%s", string1);
    c = dfa[1][0];
    l = strlen(string1);

    // Perform the string checking using the DFA
    for (i = 0; i < l; i++) {
        printf("(%c,%c)->", c, string1[i]);
        for (j = 0; j < n; j++) {
            if (c == dfa[j + 1][0]) {
                u = j + 1;
                break;
            }
        }
        for (j = 0; j < s; j++) {
            if (string1[i] == dfa[0][j + 1]) {
                t = j + 1;
                break;
            }
        }

        c = dfa[u][t];
    }
    printf("%c", c);

    // Check if the final state is reached
    for (i = 0; i < f; i++) {
        if (final[i] == c) {
            k++;
            break;
        }
    }

    // Display the result
    if (k == 0)
        printf("\n%s is not accepted", string1);
    else
        printf("\n%s is accepted", string1);

    return 0;
}
