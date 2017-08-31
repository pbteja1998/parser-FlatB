%{
#include "parser.tab.h"
%}

%%
"declblock"					{
								
								printf("declblock ");
								return DECLBLOCK;	
							}
"codeblock"					{
								
								printf("codeblock ");
								return CODEBLOCK;	
							}						
"if"						{
								
								printf("if ");
								return IF;
							}
"else"						{
								
								printf("else ");
								return ELSE;
							}
"true"						{	
								
								printf("true ");
								return TRUE;
							}
"false"						{
								
								printf("false ");
								return FALSE;
							}							
"for"						{
								
								printf("for ");
								return FOR;
							}
"while"						{	
								
								printf("while ");
								return WHILE;
							}
"goto"						{
								
								printf("goto ");
								return GOTO;
							}
"int"						{
								
								printf("\tint ");
								return INT;
							}
"print"						{	
								
								printf("print ");
								return PRINT;
							}
"println"					{
								
								printf("println ");
								return PRINTLN;
							}
"read"						{
								
								printf("read ");
								return READ;
							}
[0-9][0-9]*  				{
								
								printf("(NUMBER)%s ", yytext);
								return NUMBER;
							}
[a-zA-Z][a-zA-Z0-9]*		{
								
								printf("(IDENTIFIER)%s ", yytext);
								return IDENTIFIER;
							}
["][a-zA-Z0-9:,\ ]*["]		{	
								
								printf("(STRING)%s ", yytext);
								return STRING;
							}
[a-zA-Z][a-zA-Z0-9]*[\ ]*[:]		{	
								
								printf("(LABEL)%s ", yytext);
								return LABEL;
							}
"\""						{
								
								printf("\" ");
								return '"';
							}
"+"							{
								
								printf("+ ");
								return '+';
							}
"-"							{
								
								printf("- ");
								return '-';
							}
"*"							{
								
								printf("* ");
								return '*';
							}
"<"							{	
								
								printf("< ");
								return '<';
							}
">"							{
								
								printf("> ");
								return '>';
							}
"="							{
								
								printf("= ");
								return '=';
							}
"=="						{	
								
								printf("== ");
								return EQ;
							}
"<="						{
								
								printf("<= ");
								return LEQ;
							}
">="						{
								
								printf(">= ");
								return GEQ;
							}
"{"							{
								
								printf("{\n");
								return '{';
							}
"}"							{
								
								printf("\n}\n");
								return '}';
							}
"["							{
								
								printf("[ ");
								return '[';
							}
"]"							{
								
								printf("] ");
								return ']';
							}
","							{
								
								printf(", ");
								return ',';	
							}
";"							{
								
								printf(";");
								return ';';	
							}
[\t  ][\t  ]*				{								
								/*Do nothing*/;
							}
.							{
								
								printf("ETOK ");
								return ETOK;
							}