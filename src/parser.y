%{
  #include <stdio.h>
  #include <stdlib.h>
  FILE *yyin;
  int yylex (void);
  void yyerror (char const *s);
%}

%token DECLBLOCK
%token CODEBLOCK
%token NUMBER
%token IDENTIFIER
%token STRING
%token ETOK
%token IF
%token ELSE
%token FOR
%token WHILE
%token GOTO
%token INT
%token LABEL
%token PRINT
%token PRINTLN
%token READ
%token EQ
%token LEQ
%token GEQ
%token TRUE
%token FALSE
%left '+'
%left '*'
%left '='
%left '>'
%left '<'

%%

program:			decl_block code_block

decl_block	   :  	DECLBLOCK '{' declaration_list '}'			   

code_block	   :  	CODEBLOCK '{' statement_list '}'			   

declaration_list :  INT declarations

declarations   : 	IDENTIFIER ';'
			   | 	IDENTIFIER '[' expr ']' ';'
			   |    IDENTIFIER ';' declaration_list
			   | 	IDENTIFIER '[' expr ']' ';' declaration_list
			   | 	IDENTIFIER ',' declarations
			   | 	IDENTIFIER '[' expr ']' ',' declarations

var 		   :	IDENTIFIER
			   |	IDENTIFIER '[' expr ']'			   

var_num 	   : 	var 
			   | 	NUMBER

statement_list : 	statement	   
			   | 	for_block			   
			   | 	while_block			   
			   | 	if_else_block			   
			   | 	goto_block
			   |	statement statement_list
			   | 	for_block statement_list
			   | 	while_block statement_list
			   | 	if_else_block statement_list
			   | 	goto_block statement_list
			   | 	LABEL statement_list

statement 	   : 	var '=' expr ';'		  	   
		  	   | 	print ';'
		  	   | 	println ';'
		  	   | 	read';'
print 		   : 	PRINT STRING extra_values
			   | 	PRINT STRING
			   |	PRINT extra_values

extra_values   : 	',' var extra_values 
			   | 	',' var
			   | 	',' STRING extra_values 
			   | 	',' STRING 

println 	   : 	PRINTLN STRING

read 		   : 	READ var			   

for_block 	   : 	FOR IDENTIFIER '=' var_num ',' var_num '{' statement_list '}'
	      	   | 	FOR IDENTIFIER '=' var_num ',' var_num ',' var_num '{' statement_list '}'

while_block    : 	WHILE bool_expr '{' statement_list '}'

if_else_block  : 	IF bool_expr '{' statement_list '}'
			   |	IF bool_expr '{' statement_list '}' ELSE '{' statement_list '}'

goto_block 	   : 	GOTO IDENTIFIER ';'
		   	   | 	GOTO IDENTIFIER IF bool_expr ';'

expr		   : 	expr '+' expr 
			   |	expr '-' expr
			   |	expr '*' expr
			   |    expr '/' expr			  
			   | 	var_num			   

bool_expr 	   : 	var_num boolOp var_num 
		  	   | 	TRUE
		  	   | 	FALSE

boolOp 		   : 	'<' 
	   		   | 	'>' 
	   		   | 	EQ 
	   		   | 	LEQ
	   		   | 	GEQ

%%

void yyerror (char const *s)
{
       fprintf (stderr, "%s\n", s);
}

int main(int argc, char *argv[])
{
	if (argc == 1 ) {
		fprintf(stderr, "Correct usage: bcc filename\n");
		exit(1);
	}

	if (argc > 2) {
		fprintf(stderr, "Passing more arguments than necessary.\n");
		fprintf(stderr, "Correct usage: bcc filename\n");
	}

	yyin = fopen(argv[1], "r");

	yyparse();
}