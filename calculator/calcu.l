%{
#include "y.tab.h" 
#include <stdio.h> 
#include <stdlib.h>
%}
%%
[0-9]+ {yylval=atoi(yytext); return N;} 
[\n] {return 0;}
. {return yytext[0];}
%%
int yywrap()
{
return 1;
}
