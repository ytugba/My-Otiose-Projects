%{
    #include <stdio.h>
    #include "y.tab.h"
    #define YY_DECL int yylex()
    void yyerror(char *);
%}

%%

[a-z]       {
                yylval = *yytext - 'a';
                return VARIABLE;
            }

[0-9]+      {
                yylval = atoi(yytext);
                return INTEGER;
            }

"\n"    {return NEWLINE;}

"~"     {return TILDE;}

"sith"	{return SITH;}
"jedi" 	{return JEDI;}
"yell" {return YELL;}
"quit"	{return QUIT;}

"+"		{return ADD;}
"-"		{return SUB;}
"*"		{return MULT;}
"/"		{return DIV;}
"%"		{return REM;}

"="		{return EQ;}

"{"		{return L_BRA;}
"}"		{return R_BRA;}
"("		{return L_PAR;}
")"		{return R_PAR;}

"<"		{return SMALLER;}
">"		{return GREATER;}
"<="	{return LESS_EQ;}
">="	{return GREATER_EQ;}

"&&"    {return AND_OP;}
"||"	{return OR_OP;}

"=="	{return EQ_OP;}
"!="	{return NOT_OP;}

[ \t]	;

%%

int yywrap(void) 
{
    return 1;
}