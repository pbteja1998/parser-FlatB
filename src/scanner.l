%{
#include "parser.tab.h"
%}

%%
"declblock"					{
								printf("Token type: declblock\n");
								return DECLBLOCK;	
							}
"codeblock"					{
								printf("Token type: codeblock\n");
								return CODEBLOCK;	
							}						
"if"						{
								printf("Token type: If\n");
								return IF;
							}
"else"						{
								printf("Token type: Else\n");
								return ELSE;
							}
"true"						{	
								printf("Token type: True\n");
								return TRUE;
							}
"false"						{
								printf("Token type: False\n");
								return FALSE;
							}							
"for"						{
								printf("Token type: For\n");
								return FOR;
							}
"while"						{	
								printf("Token type: While\n");
								return WHILE;
							}
"goto"						{
								printf("Token type: Goto\n");
								return GOTO;
							}
"int"						{
								printf("Token type: Int\n");
								return INT;
							}
"print"						{	
								printf("Token type: print\n");
								return PRINT;
							}
"println"					{
								printf("Token type: Println\n");
								return PRINTLN;
							}
"read"						{
								printf("Token type: read\n");
								return READ;
							}
[0-9][0-9]*  				{
								printf("Token type: Number Lexeme/Token Value: %s\n", yytext);
								return NUMBER;
							}
[a-zA-Z][a-zA-Z0-9]*		{
								printf("Token type: IDENTIFIER Lexeme/Token Value: %s\n", yytext);
								return IDENTIFIER;
							}
["][a-zA-Z0-9:,\ ]*["]		{	
								printf("Token type: STRING Lexeme/Token Value: %s\n", yytext);
								return STRING;
							}
[a-zA-Z][a-zA-Z0-9]*[\ ]*[:]		{	
								printf("Token type: LABEL Lexeme/Token Value: %s\n", yytext);
								return LABEL;
							}
"\""						{
								printf("Token type: \" Lexeme/Token Value: %s\n", yytext);
								return '"';
							}
"+"							{
								printf("Token type: + Lexeme/Token Value: %s\n", yytext);
								return '+';
							}
"-"							{
								printf("Token type: - Lexeme/Token Value: %s\n", yytext);
								return '-';
							}
"*"							{
								printf("Token type: * Lexeme/Token Value: %s\n", yytext);
								return '*';
							}
"<"							{	
								printf("Token type: < Lexeme/Token Value: %s\n", yytext);
								return '<';
							}
">"							{
								printf("Token type: > Lexeme/Token Value: %s\n", yytext);
								return '>';
							}
"="							{
								printf("Token type: = Lexeme/Token Value: %s\n", yytext);
								return '=';
							}
"=="						{	
								printf("Token type: == Lexeme/Token Value: %s\n", yytext);
								return EQ;
							}
"<="						{
								printf("Token type: <= Lexeme/Token Value: %s\n", yytext);
								return LEQ;
							}
">="						{
								printf("Token type: >= Lexeme/Token Value: %s\n", yytext);
								return GEQ;
							}
"{"							{
								printf("Token type: { Lexeme/Token Value: %s\n", yytext);
								return '{';
							}
"}"							{
								printf("Token type: } Lexeme/Token Value: %s\n", yytext);
								return '}';
							}
"["							{
								printf("Token type: [ Lexeme/Token Value: %s\n", yytext);
								return '[';
							}
"]"							{
								printf("Token type: ] Lexeme/Token Value: %s\n", yytext);
								return ']';
							}
","							{
								printf("Token type: , Lexeme/Token Value: %s\n", yytext);
								return ',';	
							}
";"							{
								printf("Token type: ; Lexeme/Token Value: %s\n", yytext);
								return ';';	
							}
[\t \n][\t \n]*				{
								printf("Token type: space or tab Lexeme/Token Value: %s\n", yytext);
								/*Do nothing*/;
							}
.							{
								printf("Token type: ETOK Lexeme/Token Value: %s\n", yytext);
								return ETOK;
							}
