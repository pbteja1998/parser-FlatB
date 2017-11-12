%{
#include <bits/stdc++.h>
#include "ClassDefs.h"
#include "parser.tab.h"
#define YY_DECL extern "C" int yylex()
	extern union Node yylval;
	using namespace std;
%}
digit [0-9]
alpha [a-zA-Z]
alphaNumeric [0-9a-zA-Z]
delimiter [ \t]+
string (\\n|\\t|\\'|\\\\|\\\"|[^\\"'])
%%
"declblock"					{															
								printf("declblock ");
								return DLB;	
							}
"codeblock"					{								
								printf("codeblock ");
								return CDB;	
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
{digit}+ 					{ 
								yylval.number = atoi(yytext);
								printf("(NUMBER)%s ", yytext);
								return NUM; 
							}							
{alpha}{alphaNumeric}* 		{ 
								yylval.value = strdup(yytext);
								printf("(ID)%s ", yytext);
								return ID; 
							}
{alpha}{alphaNumeric}*[" "]*[:]	{			
								yylval.value = strdup(yytext);						
								printf("(LABEL)%s ", yytext);
								return LABEL;
							}														
\"{string}*\" 				{ 
								yylval.value = strdup(yytext);
								printf("(STRING)%s ", yytext);
								return STRING; 
							}
"\""						{
								printf("\"");
								return ICOMMA;
							}
"%"							{
								yylval.value = strdup(yytext);
								printf("%%");
								return MOD;
							}
"+"							{
								yylval.value = strdup(yytext);
								printf("+");
								return ADD;
							}
"-"							{
								yylval.value = strdup(yytext);
								printf("-");
								return SUB;
							}
"*"							{								
								yylval.value = strdup(yytext);
								printf("*");
								return MUL;
							}
"/"							{								
								yylval.value = strdup(yytext);
								printf("/");
								return DIV;
							}							
"<"							{								
								yylval.value = strdup(yytext);	
								printf("<");
								return LT;
							}
">"							{
								yylval.value = strdup(yytext);
								printf(">");
								return GT;
							}
"="							{								
								yylval.value = strdup(yytext);
								printf("=");
								return EQ;
							}
"=="						{								
								yylval.value = strdup(yytext);	
								printf("==");
								return EQUAL;
							}
"!="						{								
								yylval.value = strdup(yytext);	
								printf("!=");
								return NOT_EQUAL;
							}							
"<="						{								
								yylval.value = strdup(yytext);
								printf("<=");
								return LEQ;
							}
">="						{
								yylval.value = strdup(yytext);
								printf(">=");
								return GEQ;
							}
"{"							{			
								printf("{");					
								return OB;
							}
"}"							{			
								printf("}");													
								return CB;
							}
"["							{			
								printf("[");				
								return OSB;
							}
"]"							{			
								printf("]");													
								return CSB;
							}
","							{			
								printf(",");													
								return COMMA;	
							}
";"							{			
								printf(";");													
								return SC;	
							}
{delimiter}					{								
								/*Do nothing*/;
							}
"\n" 						{ 
								printf("\n");
							}							
.							{								
								printf("ETOK ");
								return ETOK;
							}
%%
