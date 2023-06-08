//assuming the grammar is left-recursion eliminated

/*let grammar be:
E->TE'
E'->+TE'|e                 e=EPSILON
T->FT'
T'->*FT'
F->(E)
F->id
*/

#include<stdio.h>
#include<stdlib.h>
#include<string.h>
int main(){
	printf("Enter the input grammar:");
	char arr[][100];
	strcpy(arr[0],"E->TD");
	strcpy(arr[1],"D->+TD");
	strcpy(arr[2],"D->e");
	strcpy(arr[3],"T->FS");
	strcpy(arr[4],"S->*FS");
	strcpy(arr[5],"F->(E)");
	strcpy(arr[6],"F->id");
}
