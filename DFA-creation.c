#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main() {
    int n, s, f, i, j, c, l, u, t;
    char dfa[10][10], node[10], in[10], final[10], string1[15], choice;

    do {
        printf("Enter number of nodes: ");
        scanf("%d", &n);
        printf("Enter number of states: ");
        scanf("%d", &s);
        printf("Enter number of final states: ");
        scanf("%d", &f);
        char z;
        scanf("%c", &z);

        for (int i = 0; i < n; i++) {
            printf("Enter value of node %d: ", i);
            scanf(" %c", &node[i]);
            scanf("%c", &z);
        }

        for (int i = 0; i < s; i++) {
            printf("Enter the state %d: ", i);
            scanf(" %c", &in[i]);
            scanf("%c", &z);
        }

        for (int i = 0; i < f; i++) {
            printf("Enter final state %d: ", i);
            scanf(" %c", &final[i]);
            scanf("%c", &z);
        }

        for (int i = 0; i < n; i++) {
            dfa[i + 1][0] = node[i];
        }
        for (int i = 0; i < s; i++) {
            dfa[0][i + 1] = in[i];
        }

        dfa[0][0] = 'D';

        for (i = 0; i < n; i++) {
            for (j = 0; j < s; j++) {
                printf("D(%c,%c)=", dfa[i + 1][0], dfa[0][j + 1]);
                scanf(" %c", &dfa[i + 1][j + 1]);
                scanf("%c", &z);
            }
        }

        printf("\nTransition Table: \n");
        for (i = 0; i <= n; i++) {
            for (j = 0; j <= s; j++) {
                printf("\t%c", dfa[i][j]);
            }
            printf("\n");
        }

        do {
            printf("Enter the string to be checked: ");
            scanf("%s", string1);
            c = dfa[1][0];
            l = strlen(string1);
            int k = 0; // Reset k to zero for each new string

            for (i = 0; i < l; i++) {
                printf("(%c,%c)->", c, string1[i]);
                for (j = 0; j < n; j++) {
                    if (c == dfa[j + 1][0]) {
                        u = j + 1;
                        break;
                    }
                }

                if (j == n) {
                    printf("\nInvalid input: Character not found in transition table.\n");
                    printf("String is rejected.\n");
                    break;
                }

                for (j = 0; j < s; j++) {
                    if (string1[i] == dfa[0][j + 1]) {
                        t = j + 1;
                        break;
                    }
                }

                if (j == s) {
                    printf("\nInvalid input: Character not found in transition table.\n");
                    printf("String is rejected.\n");
                    break;
                }

                c = dfa[u][t];
            }

            if (i == l) {
                printf("%c", c);

                for (i = 0; i < f; i++) {
                    if (final[i] == c) {
                        k++;
                        break;
                    }
                }

                if (k == 0)
                    printf("\n%s is not accepted", string1);
                else
                    printf("\n%s is accepted", string1);
            }

            printf("\nDo you want to check another string? (y/n): ");
            scanf(" %c", &choice);
        } while (choice == 'y' || choice == 'Y');

        printf("\nDo you want to continue with another set of nodes, states, and final states? (y/n): ");
        scanf(" %c", &choice);
    } while (choice == 'y' || choice == 'Y');

    return 0;
}
