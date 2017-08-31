%{
  #include <stdio.h>
  #include <stdlib.h>
  FILE *yyin;
  int yylex (void);
  void yyerror (char const *s);
%}

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
%left '+'
%left '*'
%left '='
%left '>'
%left '<'

%%

program:			decl_block code_block

decl_block:  		'{' declaration_list '}'

code_block:  		'{' statement_list '}'

declaration_list :  INT declarations

declarations   : 	IDENTIFIER ';'
			   | 	IDENTIFIER '[' NUMBER ']' ';'
			   | 	IDENTIFIER ',' declarations
			   | 	IDENTIFIER '[' NUMBER ']' ',' declarations

var 		   :	IDENTIFIER
			   |	IDENTIFIER '[' NUMBER ']'
			   |	IDENTIFIER '[' IDENTIFIER ']'

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
			   | 	LABEL ':' statement_list

statement 	   : 	var '=' expr ';'		  	   
		  	   | 	print ';'
		  	   | 	println ';'
		  	   | 	read';'

print 		   : 	PRINT STRING extra_values
			   | 	PRINT STRING
			   |	PRINT extra_values

extra_values   : 	',' IDENTIFIER extra_values 
			   | 	IDENTIFIER

println 	   : 	PRINTLN STRING

read 		   : 	READ var			   

for_block 	   : 	FOR IDENTIFIER '=' var_num ',' var_num '{' statement_list '}'
	      	   | 	FOR IDENTIFIER '=' var_num ',' var_num ',' var_num '{' statement_list '}'

while_block    : 	WHILE bool_expr '{' statement_list '}'

if_else_block  : 	IF bool_expr '{' statement_list '}'
			   |	IF bool_expr '{' statement_list '}' ELSE '{' statement_list '}'

goto_block 	   : 	GOTO LABEL 
		   	   | 	GOTO LABEL IF bool_expr

expr		   : 	expr '+' expr 
			   |	expr '*' expr 
			   | 	NUMBER
			   |	IDENTIFIER

bool_expr 	   : 	var_num boolOp var_num 
		  	   | 	"true" 
		  	   | 	"false"

boolOp 		   : 	'<' 
	   		   | 	'>' 
	   		   | 	"==" 
	   		   | 	"<=" 
	   		   | 	">="

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