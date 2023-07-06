%{ 
#include "y.tab.h" 
#include <stdio.h> 
#include <stdlib.h> 
%} 
alpha [A-Za-z] 
digit [0-9] 
%% 
{alpha}+({alpha}|{digit})* {return ID;} 
{digit}+ {yylval=atoi(yytext); return ID;} 
[\n] {return 0;} 
. {return yytext[0];} 
%% 
int yywrap() 
{ 
return 1;
}
