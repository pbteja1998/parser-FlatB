%{
#include "ClassDefs.h"
#include <bits/stdc++.h>

  extern "C" int yylex();
  extern "C" int yyparse();
  extern "C" FILE *yyin;
  extern union Node yylval;
  void yyerror(const char *s);
  class Program* start;
%}
/*	-------------  Tokens ----------------------*/
%start Program

%token DLB CDB
%token IF ELSE FOR WHILE GOTO
%token ICOMMA COMMA SC
%token TRUE FALSE INT
%token PRINT PRINTLN READ
%token <value> ID STRING LABEL
%token <number> NUM
%token <value> ADD SUB MUL DIV MOD
%token <value> LT GT LEQ GEQ EQ
%token <value> EQUAL NOT_EQUAL
%token OB CB OSB CSB
%token ETOK

/* --------------- Left Precedence ---------------*/
%left EQUAL NOT_EQUAL
%left LT GT LEQ GEQ
%left ADD SUB MOD
%left MUL DIV

/* ------------- Non-Terminal Types	------------- */
%type <program> Program
%type <declarations> Decl_List
%type <declaration> Declaration
%type <declarations> Decl_Block
%type <statements> Code_Block
%type <vars> Vars
%type <var> Var
%type <expr> Expr
%type <binary_expr> BinaryExpr
%type <statements> Stat_List
%type <statement> Statement
%type <assignment> Assignment
%type <lhs> Lhs
%type <lhss> Lhss
%type <bool_expr> Boolean_Expr

%%

Program			: Decl_Block Code_Block {
	$$ = new Program($1, $2);
	start = $$;
}
				;

Decl_Block		: DLB OB Decl_List CB { $$ = $3; }
				;

Decl_List		: { $$ = new Declarations(); }
				| Decl_List Declaration { $$->pushes_back($2); }
				;

Declaration		: INT Vars SC { $$ = new Declaration($2); }
				;

Vars 			: Var {$$ = new Vars(); $$->pushes_back($1);}
				| Vars COMMA Var {$$->pushes_back($3);}
				;


Var 			: ID { $$ = new Var($1); }
				| ID OSB NUM CSB {
	enum VarType type;
	type = arrayVar;
	$$ = new Var(type, $1, $3);
}
				| ID OSB Expr CSB {
	enum VarType type;
	type = arrayVar;
	$$ = new Var(type, $1, $3);
}
				;


Code_Block		: CDB OB Stat_List CB { $$ = $3; }
				;

Stat_List		: { $$ = new Statements(); }
				| Stat_List Statement { $$->pushes_back($2); }
				;


Statement		: Assignment { $$ = $1; }
				| LABEL Stat_List { $$ = new LabeledStatement($1, $2); }
				| IF Boolean_Expr OB Stat_List CB { $$ = new IfStatement($2, $4); }
				| IF Boolean_Expr OB Stat_List CB ELSE OB Stat_List CB { $$ = new IfElseStatement($2, $4, $8); }
				| FOR Lhs EQ Expr COMMA Expr OB Stat_List CB { $$ = new ForStatement($2, $4, $6, $8); }
				| FOR Lhs EQ Expr COMMA Expr COMMA Expr OB Stat_List CB { $$ = new ForStatement($2, $4, $6, $8, $10); }
				| WHILE Boolean_Expr OB Stat_List CB { $$ = new WhileStatement($2, $4); }
				| GOTO ID SC { $$ = new GoToStatement($2); }
				| GOTO ID IF Boolean_Expr SC { $$ = new GoToStatement($2, $4);  }
				| PRINT Lhs SC{ $$ = new PrintStatement($2); }
				| PRINT STRING SC { $$ = new PrintStatement($2); }
				| PRINT STRING COMMA Lhss SC { $$ = new PrintStatement($2, $4); }				
				| PRINTLN STRING SC { $$ = new PrintLnStatement($2); }
				| READ Lhs SC { $$ = new ReadStatement($2); }
				;


Assignment		: Lhs EQ Expr SC { $$ = new Assignment($1, $2, $3); }
				;

Lhs				: ID { $$ = new LHS($1); }
				| ID OSB Expr CSB {$$ = new LHS($1, $3);}			
				;

Lhss 			: Lhs {$$ = new LHSs(); $$->pushes_back($1);}
				| Lhss COMMA Lhs {$$->pushes_back($3);}
				;

Expr 			: Lhs 	{ $$ = new NormalExpr($1); }
				| BinaryExpr { $$ = $1; }				
				| SUB Expr { $$ = new UnaryExpr($1, $2); }
				| Boolean_Expr { $$ = $1; }
				| NUM { $$ = new NormalExpr($1); }
				;

BinaryExpr      : Expr ADD Expr { $$ = new BinaryExpr($1, $2, $3); }
				| Expr SUB Expr { $$ = new BinaryExpr($1, $2, $3); }
				| Expr MUL Expr { $$ = new BinaryExpr($1, $2, $3); }
				| Expr DIV Expr { $$ = new BinaryExpr($1, $2, $3); }
				| Expr MOD Expr { $$ = new BinaryExpr($1, $2, $3); }


Boolean_Expr	: TRUE	{ $$ = new BoolExpr(1); }
				| FALSE { $$ = new BoolExpr(0); }
				| Expr GT Expr {$$ = new BoolExpr($1, $2, $3);}
				| Expr LT Expr {$$ = new BoolExpr($1, $2, $3); }
				| Expr LEQ Expr {$$ = new BoolExpr($1, $2, $3);}
				| Expr GEQ Expr {$$ = new BoolExpr($1, $2, $3);}
				| Expr EQUAL Expr {$$ = new BoolExpr($1, $2, $3);}
				| Expr NOT_EQUAL Expr {$$ = new BoolExpr($1, $2, $3);}
				;
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

	cout << "--------Traversals-------------" << endl;
	start->traverse();
	cout << "--------Interpreter------------" << endl;
	start->interpret();	
	//cout << "--------All Vars---------------" << endl;
	//print_vars();
}