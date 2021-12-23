/* A Bison parser, made by GNU Bison 3.0.4.  */

/* Bison interface for Yacc-like parsers in C

   Copyright (C) 1984, 1989-1990, 2000-2015 Free Software Foundation, Inc.

   This program is free software: you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation, either version 3 of the License, or
   (at your option) any later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program.  If not, see <http://www.gnu.org/licenses/>.  */

/* As a special exception, you may create a larger work that contains
   part or all of the Bison parser skeleton and distribute that work
   under terms of your choice, so long as that work isn't itself a
   parser generator using the skeleton or a modified version thereof
   as a parser skeleton.  Alternatively, if you modify or redistribute
   the parser skeleton itself, you may (at your option) remove this
   special exception, which will cause the skeleton and the resulting
   Bison output files to be licensed under the GNU General Public
   License without this special exception.

   This special exception was added by the Free Software Foundation in
   version 2.2 of Bison.  */

#ifndef YY_YY_Y_TAB_H_INCLUDED
# define YY_YY_Y_TAB_H_INCLUDED
/* Debug traces.  */
#ifndef YYDEBUG
# define YYDEBUG 0
#endif
#if YYDEBUG
extern int yydebug;
#endif

/* Token type.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
  enum yytokentype
  {
    INTEGER = 258,
    VARIABLE = 259,
    NEWLINE = 260,
    JEDI = 261,
    SITH = 262,
    YELL = 263,
    QUIT = 264,
    ADD = 265,
    SUB = 266,
    MULT = 267,
    DIV = 268,
    REM = 269,
    EQ = 270,
    L_BRA = 271,
    R_BRA = 272,
    L_PAR = 273,
    R_PAR = 274,
    SMALLER = 275,
    GREATER = 276,
    LESS_EQ = 277,
    GREATER_EQ = 278,
    AND_OP = 279,
    OR_OP = 280,
    EQ_OP = 281,
    NOT_OP = 282,
    TILDE = 283
  };
#endif
/* Tokens.  */
#define INTEGER 258
#define VARIABLE 259
#define NEWLINE 260
#define JEDI 261
#define SITH 262
#define YELL 263
#define QUIT 264
#define ADD 265
#define SUB 266
#define MULT 267
#define DIV 268
#define REM 269
#define EQ 270
#define L_BRA 271
#define R_BRA 272
#define L_PAR 273
#define R_PAR 274
#define SMALLER 275
#define GREATER 276
#define LESS_EQ 277
#define GREATER_EQ 278
#define AND_OP 279
#define OR_OP 280
#define EQ_OP 281
#define NOT_OP 282
#define TILDE 283

/* Value type.  */
#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
typedef int YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define YYSTYPE_IS_DECLARED 1
#endif


extern YYSTYPE yylval;

int yyparse (void);

#endif /* !YY_YY_Y_TAB_H_INCLUDED  */
