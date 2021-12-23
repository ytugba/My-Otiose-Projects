%token INTEGER VARIABLE NEWLINE
%token JEDI SITH YELL QUIT
%token ADD SUB MULT DIV REM
%token EQ
%token L_BRA R_BRA L_PAR R_PAR
%token SMALLER GREATER LESS_EQ GREATER_EQ
%token AND_OP OR_OP EQ_OP NOT_OP
%token TILDE

%left L_PAR R_PAR
%left L_BRA R_BRA
%left MULT DIV REM
%left ADD SUB
%left SMALLER GREATER LESS_EQ GREATER_EQ
%left EQ_OP NOT_OP
%left AND_OP OR_OP
%right EQ

%{
    void yyerror(char *);
    int yylex(void);
    int sym[26];
	#include <stdio.h>
	#include "lex.yy.c"
%}

%%

program:
        program  statement TILDE NEWLINE
        | program NEWLINE
        |
        ;

statement:
    expr                     { printf("%d\n", $1); }

    | VARIABLE EQ expr       { sym[$1] = $3; }

    | QUIT { printf("\nOK\n"); exit(1); }

    | JEDI L_PAR expr R_PAR NEWLINE
    	L_BRA expr R_BRA NEWLINE
      SITH NEWLINE
      	L_BRA expr R_BRA 
      		{ 
      			if($3==0) { printf("\nWelcome to the dark side. We have cookies.\n"); printf("%d\n", $11); }
      			else if ($3 ==1) { printf("\nMay the force be with you.\n");  printf("%d\n", $6); }
      		}

    | YELL L_PAR expr R_PAR NEWLINE
    	 L_BRA expr R_BRA 
    		{ 
    			if($3 == 1) { int i; printf("\nYell nine times for Mortal Man doomed to die!\n"); for( i= 0; i<9; i++) {printf("%d ", $7); } printf("\n"); } 
    			else if ($3 ==0) printf("\nYou Shall Not Pass!\n");
   			}
	;

expr: 
    INTEGER			
    | VARIABLE					{ $$ = sym[$1]; }
    | expr ADD expr          	{ $$ = $1 + $3; }
    | expr SUB expr           	{ $$ = $1 - $3; }
    | expr MULT expr          	{ $$ = $1 * $3; }
    | expr DIV expr         	{ if ( $3 == 0 ) { printf("%d Cannot divide by zero!\n", $1); exit(1); } else $$ = $1 / $3; }
    | expr REM expr        		{ $$ = $1 % $3; }
    | expr SMALLER expr         { $$ = $1 < $3; }
    | expr GREATER expr         { $$ = $1 > $3; }
    | expr LESS_EQ expr         { $$ = $1 <= $3; }
    | expr GREATER_EQ expr      { $$ = $1 >= $3; }
    | expr AND_OP expr          { $$ = $1 && $3; }
    | expr OR_OP expr        	{ $$ = $1 || $3; }
    | expr EQ_OP expr           { $$ = $1 == $3; }
    | expr NOT_OP expr         	{ $$ = $1 != $3; }  
    | L_PAR expr R_PAR          { $$ = $2; }
    ;
%%

void yyerror(char *s) 
{
    fprintf(stderr, "Syntax Error!\n");
}

int main(int argc, char *argv[]) 
{
    yyin = fopen(argv[1], "r");
        	
        	yyparse();
	
	fclose(yyin);
    
    return 0;
}