#include <bits/stdc++.h>
#include "ClassDefs.h"
using namespace std;

Program::Program(class Vars* vars, class Statements* statements)
{
	this->vars = vars;
	this->statements = statements;
}

Vars::Vars(class Vars* vars)
{
	this->var_list = vars->var_list;
}

Vars::Vars()
{

}

void Vars::pushes_back(class Vars* vars)
{
	var_list = vars->var_list;
	(this->var_list).insert((this->var_list).end(), var_list.begin(), var_list.end());
}

void Vars::pushes_back(class Var* var)
{
	(this->var_list).push_back(var);
}

Var::Var(string name)
{
	this->name = name;
	enum VarType vtype = normalVar;
	this->vtype = vtype;	
}

Var::Var(enum VarType type, string name)
{
	this->vtype = type;
	this->name = name;
}

Var::Var(enum VarType type, string name, class Expr* expr)
{
	this->vtype = type;
	this->name = name;
	this->length = expr->getVal();
}

Var::Var(enum VarType type, string name, int val)
{
	this->vtype = type;
	this->name = name;
	this->length = val;
}

bool Var::isArray()
{
	if(this->vtype == 2)
		return 1;
	return 0;
}

Statements::Statements()
{

}

void Statements::pushes_back(class Statement* statement)
{
	(this->statement_list).push_back(statement);
}

void Statements::setStmtList(vector<class Statement*> statement_list)
{
	this->statement_list = statement_list;
}

vector<class Statement*> Statements::getStmtList()
{
	return this->statement_list;
}

Assignment::Assignment(class LHS* lhs, string Op, class Expr* expr)
{
	this->lhs = lhs;
	this->Op = Op;
	this->expr = expr;	
}

LHS::LHS(string name)
{
	this->name = name;
	enum VarType vtype = normalVar;
	this->vtype = vtype;	
}

LHS::LHS(string name, Expr* expr)
{
	this->name = name;
	this->index = expr->getVal();
	enum VarType vtype = arrayVar;
	this->vtype = vtype;
}

IfStatement::IfStatement(BoolExpr* bool_expr, Statements* block)
{
	this->cond = bool_expr;
	this->ifBlock = block;
}

IfElseStatement::IfElseStatement(BoolExpr* bool_expr, Statements* block1, Statements* block2)
{
	this->cond = bool_expr;
	this->ifBlock = block1;
	this->elseBlock = block2;
}

ForStatement::ForStatement(LHS* lhs, Expr* start, Expr* end, Statements* block)
{
	this->var = lhs;
	this->start = start;
	this->end = end;
	this->step = new NormalExpr(1);
	this->forBlock = block;
}

ForStatement::ForStatement(LHS* lhs, Expr* start, Expr* end, Expr* step, Statements* block)
{
	this->var = lhs;
	this->start = start;
	this->end = end;
	this->step = step;
	this->forBlock = block;
}

WhileStatement::WhileStatement(BoolExpr* bool_expr, Statements* block)
{
	this->cond = bool_expr;
	this->whileBlock = block;
}

GoToStatement::GoToStatement(string label)
{
	this->label = label;
	this->cond = new BoolExpr(1);
}

GoToStatement::GoToStatement(string label, BoolExpr* expr)
{
	this->label = label;
	this->cond = expr;
}

PrintStatement::PrintStatement(string text)
{
	this->text = text;
}

PrintStatement::PrintStatement(string text, class Vars* vars)
{
	this->text = text;
	this->vars = vars;
}

PrintLnStatement::PrintLnStatement(string text)
{
	this->text = text;
}

ReadStatement::ReadStatement(class Var* var)
{
	this->var = var;
}

NormalExpr::NormalExpr(int value)
{
	this->setVal(value);
	enum ExprType type = normal;
	this->etype = type;
}

NormalExpr::NormalExpr(LHS* lhs)
{
	this->setVal(lhs->value);
	enum ExprType type = normal;
	this->etype = type;
}

int Expr::getVal()
{
	return this->value;
}

void Expr::setVal(int value)
{
	this->value = value;
}

BinaryExpr::BinaryExpr(class Expr* first, string Op, class Expr* second)
{
	this->first = first;
	this->Op = Op;
	this->second = second;
	if(this->Op == "ADD") {
		this->setVal(this->first->getVal() + this->second->getVal());
	} else if(this->Op == "SUB") {
		this->setVal(this->first->getVal() - this->second->getVal());
	} else if(this->Op == "MUL") {
		this->setVal(this->first->getVal() * this->second->getVal());
	} else if(this->Op == "DIV") {
		this->setVal(this->first->getVal() / this->second->getVal());
	} 
	enum ExprType type = binary;
	this->etype = type;
}

UnaryExpr::UnaryExpr(string Op, class Expr* second)
{
	this->Op = Op;
	this->second = second;

	if(this->Op == "SUB") {
		this->setVal(this->second->getVal() * (-1));
	}

	enum ExprType type = unary;
	this->etype = type;	
}

BoolExpr::BoolExpr(bool val)
{
	this->val = val;
	enum ExprType type = boolean;
	this->etype = type;		
}

BoolExpr::BoolExpr(class Expr* left, string Op, class Expr* right)
{
	this->first = left;
	this->second = right;
	this->Op = Op;

	if(Op == "GT") {
		if(left->getVal() > right->getVal()) 
			this->val = 1;
		else
			this->val = 0;
	} else if(Op == "LT") {
		if(left->getVal() < right->getVal()) 
			this->val = 1;
		else
			this->val = 0;
	} else if(Op == "GEQ") {
		if(left->getVal() >= right->getVal()) 
			this->val = 1;
		else
			this->val = 0;
	} else if(Op == "LEQ") {
		if(left->getVal() <= right->getVal()) 
			this->val = 1;
		else
			this->val = 0;
	} if(Op == "EQUAL") {
		if(left->getVal() == right->getVal()) 
			this->val = 1;
		else
			this->val = 0;
	} else if(Op == "NOT_EQUAL") {
		if(left->getVal() != right->getVal()) 
			this->val = 1;
		else
			this->val = 0;
	}

	enum ExprType type = boolean;
	this->etype = type;		
}

Block::Block(class Statements* sts)
{
	this->setStmtList(sts->getStmtList());
}

LabeledStatement::LabeledStatement(string label)
{
	this->label = label;
}