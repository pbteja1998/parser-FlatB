%{
  #include <stdio.h>
  #include <stdlib.h>
  FILE *yyin;
  int yylex (void);
  void yyerror (char const *s);
%}
/*	-------------  Tokens ----------------------*/
%start Program

%token DLB CDB
%token IF ELSE FOR WHILE GOTO
%token ICOMMA COMMA SC
%token TRUE FALSE INT
%token PRINT PRINTLN READ
%token ID STRING LABEL
%token NUM
%token ADD SUB MUL DIV
%token LT GT LEQ GEQ EQ
%token EQUAL NOT_EQUAL
%token OB CB OSB CSB
%token ETOK

/* --------------- Left Precedence ---------------*/
%left EQUAL NOT_EQUAL
%left LT GT LEQ GEQ
%left ADD SUB MUL DIV

%%

Program			: Decl_Block Code_Block

Decl_Block		: DLB OB Decl_List CB

Decl_List		: INT Vars SC
				| Decl_List INT Vars SC

Vars 			: Var
				| Vars COMMA Var

Var 			: ID
				| ID OSB Expr CSB

Code_Block		: CDB OB Stat_List CB

Stat_List		: Stat_List Statement
				| Statement

Statement		: Assignment
				| LABEL Statement
				| IF Boolean_Expr Block
				| IF Boolean_Expr Block ELSE Block
				| FOR ID EQ Expr COMMA Expr Block
				| FOR ID EQ Expr COMMA Expr COMMA Expr Block
				| WHILE Boolean_Expr Block
				| GOTO ID SC
				| GOTO ID IF Boolean_Expr SC
				| PRINT STRING SC
				| PRINT STRING COMMA Vars SC
				| PRINTLN STRING SC
				| READ Var SC

Assignment		: Var EQ Expr SC

Expr 			: Var
				| Expr ADD Expr
				| Expr SUB Expr
				| Expr MUL Expr
				| Expr DIV Expr
				| SUB Expr
				| Boolean_Expr
				| NUM

Boolean_Expr	: TRUE
				| FALSE
				| Expr GT Expr
				| Expr LT Expr
				| Expr LEQ Expr
				| Expr GEQ Expr
				| Expr EQUAL Expr
				| Expr NOT_EQUAL Expr

Block 			: OB Stat_List CB

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