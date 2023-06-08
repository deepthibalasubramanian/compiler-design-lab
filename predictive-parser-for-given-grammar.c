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
	//creating an array to hold the input grammar
	char arr[][100];
	strcpy(arr[0],"E->TD");
	strcpy(arr[1],"D->+TD");
	strcpy(arr[2],"D->e");
	strcpy(arr[3],"T->FS");
	strcpy(arr[4],"S->*FS");
	strcpy(arr[5],"F->(E)");
	strcpy(arr[6],"F->id");
	//input grammar is accepted and stored in the array
	
	//creating arrays to hold first and follow values of given non terminals in the grammar
	char first[][100];
	char follow[][100];
	
	//find the first of every non terminal in the grammar
	for ( int i = 0 ; i < 7 ; i++ ) {
		char test[100] = arr[0];
		for ( int j = 3 ; j != '\0' ; j++ ) {
			if (test[j].isalpha()){
				if(test[j].islower()){
					first[i]=test[j];
			}
			else if (test[j].
		
	
}
