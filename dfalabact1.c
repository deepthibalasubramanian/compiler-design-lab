#include<stdio.h>
#include<stdlib.h>
#include<string.h>
int main(){
    int n,s,f,i,j,k,c,l,u,t;;
    char dfa[10][10],node[10],in[10],final[10],string1[15];
    printf("Enter number of nodes: ");
    scanf("%d",&n);
    printf("Enter number of states: ");
    scanf("%d",&s);
    printf("Enter number of final states: ");
    scanf("%d",&f);
    char z=scanf("%c",&z);
    for(int i=0;i<n;i++){
        printf("\nEnter value of node %d: ",i);
        printf("%c",node[i]=getchar());
        scanf("%c",&z);
    }

    for(int i=0;i<s;i++){
        printf("\nEnter the state %d: ",i);
        printf("%c",in[i]=getchar());
        scanf("%c",&z);
    }
    
    for(int i=0;i<f;i++){
        printf("\nEnter final state %d: ",i);
        printf("%c",final[i]=getchar());
        scanf("%c",&z);
    }
    
    for(int i=0;i<n;i++){
        dfa[i+1][0]=node[i];
    }
    for(int i=0;i<s;i++){
        dfa[0][i+1]=in[i];
    }
    
    dfa[0][0]='D';
    
    for(i=0;i<n;i++){
        for(j=0;j<s;j++){
            printf("\nD(%c,%c)=",dfa[i+1][0],dfa[0][j+1]);
            printf("%c",dfa[i+1][j+1]=getchar());
            scanf("%c",&z);
        }
    }
    
    printf("Transition Table: \n");
    for(i=0;i<n;i++){
        for(j=0;j<s;j++){
            printf("\t%c",dfa[i][j]);
        }
        printf("\n");
    }
    
    printf("Enter the string to be checked: ");
    scanf("%s",string1);
    c=dfa[1][0];
    l=strlen(string1);
    for(i=0;i<n;i++){
        printf("(%c,%c)->",c,string1[i]);
        for(j=0;j<n;j++){
            if(c==dfa[j+1][0]){
                u=j+1;
                break;
            }
        }
        for(j=0;j<s;j++){
            if(string1[i]==dfa[0][j+1]){
                t=j++;
                break;
            }
        }
        
        c=dfa[u][t];
    }
    printf("%c",c);
    
    for(i=0;i<f;i++){
        if(final[i]==c){
            k++;
            break;
        }
    }
    
    if(k==0)
        printf("\n%s is not accepted",string1);
    else
        printf("\n%s is accepted",string1);
 
}
