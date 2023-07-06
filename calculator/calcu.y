%{
#include <stdio.h> 
#include <stdlib.h> 
#include "lex.yy.c" 
int yywrap();
int yylex();
int yyerror(char *msg); 
int flag = 0;
%}
%token N
%left '+' '-' '*' '/' '%' '(' ')'
%%
S: E { printf("Answer is : %d\n", $$); return 0; }
;
E: E'+'E {$$=$1+$3;}
| E'-'E {$$=$1-$3;}
| E'*'E {$$=$1*$3;}
| E'/'E {$$=$1/$3;}
| E'%'E {$$=$1%$3;}
| '(' E ')' {$$=$2;}
| N {$$=$1;}
;
%%
int yyerror(char *msg)
{
printf("invalid arithmetic expression\n"); flag = 1;
exit(0);
}
int main()
{
printf("enter the arithmetic operation\n"); yyparse();
if(flag==0){
printf("Valid arithmetic operation\n");
}
}
