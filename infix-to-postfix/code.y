%{ 
#include <stdio.h> 
#include <stdlib.h> 
#include "lex.yy.c" 
int yywrap(); 
int yylex(); 
int yyerror(char *msg); 
int flag = 0; 
char st[100]; 
int top=0; 
void A1() 
{ 
st[top++]=yytext[0]; 
} 
void A2() 
{ 
printf("%c", st[--top]); 
}
void A3() 
{ 
printf("%c", yytext[0]); 
} 
%} 
%token ID 
%left '+' '-' '*' '/' '%' '(' ')' UMINUS 
%% 
S: E 
E: E'+'{A1();}T{A2();} | E'-'{A1();}T{A2();} | T ; 
T: T'*'{A1();}F{A2();} | T'/'{A1();}F{A2();} | F ; 
F: '('E{A2();}')'| '-'{A1();}F{A2();} | ID{A3();} ;
%% 
int yyerror(char *msg) 
{ 
printf("invalid arithmetic expression\n"); 
flag = 1; 
exit(0); } 

int main() 
{ 
printf("enter the arithmetic operation\n"); 
yyparse(); 
printf("\n");
 } 
 
