%{
#include "parser.tab.h"
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
								printf("(NUMBER)%s ", yytext);
								return NUM; 
							}							
{alpha}{alphaNumeric}* 		{ 
								printf("(ID)%s ", yytext);
								return ID; 
							}
{alpha}{alphaNumeric}*[:]	{									
								printf("(LABEL)%s ", yytext);
								return LABEL;
							}														
\"{string}*\" 				{ 
								printf("(STRING)%s ", yytext);
								return STRING; 
							}
"\""						{
								printf("\"");
								return ICOMMA;
							}
"+"							{
								printf("+");
								return ADD;
							}
"-"							{
								printf("-");
								return SUB;
							}
"*"							{								
								printf("*");
								return MUL;
							}
"/"							{								
								printf("/");
								return DIV;
							}							
"<"							{									
								printf("<");
								return LT;
							}
">"							{
								printf(">");
								return GT;
							}
"="							{								
								printf("=");
								return EQ;
							}
"=="						{									
								printf("==");
								return EQUAL;
							}
"!="						{									
								printf("!=");
								return NOT_EQUAL;
							}							
"<="						{								
								printf("<=");
								return LEQ;
							}
">="						{
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
