%{
#include "parser.tab.h"
%}

%%
[0-9][0-9]*  				{return NUMBER;}
[a-zA-Z][a-zA-Z0-9]*		{return IDENTIFIER;}
"if"						{return IF;}
"else"						{return ELSE;}
"for"						{return FOR;}
"while"						{return WHILE;}
"goto"						{return GOTO;}
"int"						{return INT;}
"print"						{return PRINT;}
"println"					{return PRINTLN;}
"read"						{return READ;}
[a-zA-Z][a-zA-Z0-9]*[:]		{return LABEL;}
"+"							{return '+';}
"-"							{return '-';}
"*"							{return '*';}
"<"							{return '<';}
">"							{return '>';}
"="							{return '=';}
"=="						{return EQ;}
"<="						{return LEQ;}
">="						{return GEQ;}
"{"							{return '{';}
"}"							{return '}';}
[\t \n][\t \n]*				{/*Do nothing*/;}
.							{return ETOK;}
