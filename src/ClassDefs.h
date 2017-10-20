#include <bits/stdc++.h>
using namespace std;

enum ExprType { boolean = 1, normal = 2 }
enum StatementType { assignment = 1, forStmt = 2, ifStmt = 3, ifElseStmt = 4, whileStmt = 5, goToStmt = 6, labeled =  7 }

/* --------- Main Program -------- */

class Program:public AstNode {
	private:
		class Vars* vars;
		class Statements* statements;
	public:
		Program(class varDecl*, class statDecl*);
}


/* --------- Variables --------- */
class Vars:public AstNode {
	private:
		vector<class Var*> var_list;
		int count;
	public:
		varDecls();
		void push_back(class Var*);		
}

class Var:public AstNode {
	private:
		string type; /* Array or Int */
		string name; /* Name of the var */
		unsigned int length; /* If it is array, then length of array */
	public:
		Var(string, string, unsigned int);
		Var(string, string);
		bool isArray();		
}
 
/* --------- Statements ------------ */
class Statements:public AstNode {
	private:
		vector<class Statement*> statements;
		int count;
	public:
		Statements();
		void push_back(class Statement*);
}

class Statement:public AstNode {
	private:
		StatementType stype; /* Assignment, For, While, GoTo, If, If Else */
	public:
		Statement(StatementType);
}

/* ------------ LHS -----------*/
class LHS:public Var {
	private:
		int index; /* If LHS is array, then index of array */
	public:
		LHS(string, string, index);
		LHS(string);
}

/* ----- Assignment Statement ------ */

class Assignment:public Statement {
	private:
		class LHS* lhs; /* LHS of assignment statement */
		class Expr* expr; /* RHS of assignment statement */
		string Op; /* = (At Present), (In future, += , -=) */
	public:
		Assignment(class LHS*, string, class Expr*)
}

/* ------ Block -------- */

class Block:public Statements {
	public:
		Block();	
}

/* ----- For Statement -------- */

class ForStatement:public Statement {
	private:
		LHS* var;  /* var which is being looped */
		class Expr* start;  /* Initial Value */
		class Expr* end;    /* Final Value */
		class Expr* step;   /* Step Value */
		class Block* forBlock; /* For Block */
	public:
		ForStatement(LHS*, Expr*, Expr*, Expr*, Block*)
}

/*-------- While Statement -------- */

class WhileStatement:public Statement {
	private:
		class BoolExpr* cond; /* Condition */
		class Block* whileBlock;
	public:
		WhileStatement(BoolExpr*, Block*);
}

/* -------- If Statement ----------- */

class IfStatement:public Statement {
	private:
		class BoolExpr* cond;  /* condition */
		class Block* ifBlock;      /* If Block */
	public:
		IfStatement(BoolExpr*, Block*);
}

/* -------- If Else Statement ---------- */

class IfElseStatement:public IfStatement {
	private:
		class Block* elseBlock;
	public:
		IfElseStatement(BoolExpr*, Block*, Block*);
}

/* ---------- GoTo Statement ------------ */

class GoToStatement:public Statement {
	private:
		class LabeledStatement* lbdStmt;
		class BoolExpr* cond; /* If Conditional Goto */
	public:
		GoToStatement(LabeledStatement*, BoolExpr*);
		GoToStatement(LabeledStatement*);
}

/* ------ Labeled Statement ------------ */
class LabeledStatement:public Statement {
	private:
		class Label* label;
	public:
		LabeledStatement(Label*);
}

class Label:public Var {

}

/* ------- Expressions ---------- */

class Expr:public AstNode {
	private:
		ExprType etype; /* Boolean or not */
		string expr;    /* Expression as String */
		int value;      /* evaluated value */

	public:
		Expr(string, ExprType);
}

class BooleanExpr:public Expr {
	private:
		bool val; /* True or False (after Evaluation)*/
	public:
		BooleanExpr();
}