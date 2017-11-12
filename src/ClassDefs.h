#include <bits/stdc++.h>
using namespace std;

enum VarType {normalVar = 1, arrayVar = 2};
enum ExprType { boolean = 1, normal = 2, binary = 3, unary = 4};
enum StatementType { assignment = 1, forStmt = 2, ifStmt = 3, ifElseStmt = 4, whileStmt = 5, goToStmt = 6, labeled =  7 };


union Node{
	int number;
	char *value;
	class Program* program;
	class Vars* vars;
	class Var* var;
	class Expr* expr;
	class BinaryExpr *binary_expr;
	class Statements* statements;
	class Statement* statement;
	class Assignment* assignment;
	class LHS* lhs; 
	class LHSs* lhss;
	class BoolExpr* bool_expr;
	class Block* block;

	Node(){
		number = 0;
		value = NULL;
		program = NULL;
		vars = NULL;
		var = NULL;
		expr = NULL;
		binary_expr = NULL;
		statements = NULL;
		statement = NULL;
		assignment = NULL;
		lhs = NULL;
		lhss = NULL;
		bool_expr = NULL;
		block = NULL;
	}
};

typedef union Node YYSTYPE;

#define YYSTYPE_IS_DECLARED 1

/*---------- Classes -------------- */
class AstNode;
class Program;
class Vars;
class Var;
class Statements;
class LHS;
class LHSs;
class Block;

class Statement;
class Assignment;
class ForStatement;
class WhileStatement;
class IfStatement;
class IfElseStatement;
class GoToStatement;
class LabeledStatement;
class PrintStatement;
class PrintLnStatement;
class ReadStatement;

class Label;
class Expr;
class BoolExpr;
class BinaryExpr;
class UnaryExpr;
class NormalExpr;




class AstNode {
	
};

void print_vars();

/* --------- Variables --------- */
class Vars:public AstNode {
	private:		
		int count;
	public:
		vector<class Var*> var_list;
		Vars();
		Vars(class Vars*);
		void pushes_back(class Var*);
		void pushes_back(class Vars*);
		void traverse();
		int interpret();
};

class Var:public AstNode {
	private:		
	public:
		string name; /* Name of the var */
		unsigned int length; /* If it is array, then length of array */	
		enum VarType vtype; /* Array or Int */
		Var(enum VarType, string, class Expr*);
		Var(enum VarType, string, int);
		Var(enum VarType, string);
		Var(string);
		bool isArray();	
		void traverse();
		int interpret();	
};
 
/* --------- Statements ------------ */
class Statement:public AstNode {
	private:
		
	public:
		StatementType stype; /* Assignment, For, While, GoTo, If, If Else */		
		virtual void traverse(){};
		virtual int interpret(){};
};

class Statements:public AstNode {
	private:
		vector<class Statement*> statement_list;
		int count;
	public:
		Statements();
		void pushes_back(class Statement*);
		vector<class Statement*> getStmtList();
		void setStmtList(vector<class Statement*>);
		void traverse();
		int interpret();
};

/* --------- Main Program -------- */

class Program:public AstNode {
	private:
	public:
		class Vars* vars;
		class Statements* statements;
		Program(class Vars*, class Statements*);
		void traverse();
		int interpret();
};

/* ------------ LHS -----------*/
class LHS:public AstNode {
	private:
	public:
		string name; /* Name of the var */
		unsigned int length; /* If it is array, then length of array */	
		enum VarType vtype; /* Array or Int */		
		int int_index; /* If LHS is array, then index of array */
		string string_index; /* If LHS is array,then index of array */
		Expr* expr_index;  /* If LHS is array, then index of array */
		int value; /*value stored in LHS */
		LHS(string, string);
		LHS(string, int);
		LHS(string);
		LHS(string, Expr*);
		void traverse();
		int interpret();
};

class LHSs:public AstNode {
	public:
		vector<class LHS*> lhs_list;
		LHSs();		
		void pushes_back(class LHS*);		
		void traverse();
		int interpret();
};

/* ----- Assignment Statement ------ */

class Assignment:public Statement {
	private:
	public:
		class LHS* lhs; /* LHS of assignment statement */
		class Expr* expr; /* RHS of assignment statement */
		string Op; /* = (At Present), (In future, += , -=) */
		Assignment(class LHS*, string, class Expr*);
		void traverse();
		int interpret();
};

/* ------ Block -------- */

class Block:public Statements {
	public:
		Block(class Statements*);	
		void traverse();
		int interpret();
};

/* ----- For Statement -------- */

class ForStatement:public Statement {
	private:
	public:
		bool isStep;
		LHS* var;  /* var which is being looped */
		class Expr* start;  /* Initial Value */
		class Expr* end;    /* Final Value */
		class Expr* step;   /* Step Value */
		class Statements* forBlock; /* For Block */
		ForStatement(LHS*, Expr*, Expr*, Statements*);
		ForStatement(LHS*, Expr*, Expr*, Expr*, Statements*);
		void traverse();
		int interpret();
};

/*-------- While Statement -------- */

class WhileStatement:public Statement {
	private:
	public:
		class BoolExpr* cond; /* Condition */
		class Statements* whileBlock;
		WhileStatement(BoolExpr*, Statements*);
		void traverse();
		int interpret();
};

/* -------- If Statement ----------- */

class IfStatement:public Statement {
	private:
	public:
		class BoolExpr* cond;  /* condition */
		class Statements* ifBlock;      /* If Block */
		IfStatement(BoolExpr*, Statements*);
		void traverse();
		int interpret();
};

/* -------- If Else Statement ---------- */

class IfElseStatement:public Statement {
	private:
	public:
		class BoolExpr* cond;  /* condition */
		class Statements* ifBlock;      /* If Block */
		class Statements* elseBlock;
		IfElseStatement(BoolExpr*, Statements*, Statements*);
		void traverse();
		int interpret();
};

/* ---------- GoTo Statement ------------ */

class GoToStatement:public Statement {
	private:
	public:
		string label;
		class BoolExpr* cond; /* If Conditional Goto */
		GoToStatement(string, BoolExpr*);
		GoToStatement(string);
		void traverse();
		int interpret();
};

/* ------ Labeled Statement ------------ */
class LabeledStatement:public Statement {
	private:
	public:
		string label;
		class Statement* statement;
		LabeledStatement(string, class Statement*);
		void traverse();
		int interpret();
};

class Label:public Var {

};

/* ------- Print Statement --------- */
class PrintStatement:public Statement {
	private:
	public:
		bool assigned;
		string text;
		class LHSs* lhss;
		class LHS* var;
		PrintStatement(string);
		PrintStatement(string, class LHSs*);
		PrintStatement(class LHS*);
		void traverse();
		int interpret();
};

/* ------- PrintLn Statement --------- */
class PrintLnStatement:public Statement {
	private:
	public:
		string text;
		PrintLnStatement(string);
		void traverse();
		int interpret();
};

/* ------- Read Statement --------- */
class ReadStatement:public Statement {
	private:
	public:
		class LHS* var;
		ReadStatement(class LHS*);
		void traverse();
		int interpret();		
};

/* ------- Expressions ---------- */

class Expr:public AstNode {
	private:

	public:
		int value;      /* evaluated value */
		string expr;    /* Expression as string */
		ExprType etype; /* Boolean, normal, binary, unary */		
		int getVal();		
		void setVal(int);
		virtual void traverse(){};
		virtual int interpret(){};
};

class NormalExpr:public Expr {
	public:
		class LHS* lhs;
		NormalExpr(int);
		NormalExpr(LHS*);
		void traverse();
		int interpret();		
};

class BinaryExpr:public Expr {
	private:
		
	public:
		class Expr* first;
		string Op;
		class Expr* second;
		BinaryExpr(class Expr*, string, class Expr* );
		void traverse();
		int interpret();		
};

class BoolExpr:public Expr {
	private:
	public:
		class Expr* first;
		string Op;
		class Expr * second;
		bool val; /* True or False (after Evaluation)*/
		bool assigned; /* if BoolExpr is of type "TRUE" or "FALSE" */
		BoolExpr(class Expr*, string, class Expr*);
		BoolExpr(bool);
		void traverse();
		int interpret();		
};

class UnaryExpr:public Expr {
	private:		
	public:
		string Op;
		class Expr* second;
		UnaryExpr(string, class Expr* );
		void traverse();
		int interpret();
};