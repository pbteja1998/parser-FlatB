#include <bits/stdc++.h>
#include "ClassDefs.h"
using namespace std;

// If a particular var exists, don't recreate it

/** Interpreter Defs **/

//var name, var value
map<string,int> normal_vars;

//arr name, arr size
map<string,int> array_defs;

//arr name, arr values
map<string, vector<int>> array_vars;

int tabs_needed = 0;
const int tab_width = 4;

void printTabs(){
  for(int i = 0; i < tabs_needed; i++){
    for(int j = 0; j < tab_width; j++)
    cout << " ";
  }
}

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
	normal_vars[name] = INT_MIN;
}

Var::Var(enum VarType type, string name)
{
	this->vtype = type;
	this->name = name;
	if(type == normalVar)
		normal_vars[name] = INT_MIN;		
}

Var::Var(enum VarType type, string name, class Expr* expr)
{
	this->vtype = type;
	this->name = name;
	this->length = expr->getVal();

	if(type == arrayVar){
		array_defs[name] = this->length;
		for(int i = 0; i < this->length; i++)
			array_vars[name].push_back(INT_MIN);
	}
}

Var::Var(enum VarType type, string name, int val)
{
	this->vtype = type;
	this->name = name;
	this->length = val;

	if(type == arrayVar){
		array_defs[name] = this->length;
		for(int i = 0; i < this->length; i++)
			array_vars[name].push_back(INT_MIN);
	}
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

	if(this->lhs->vtype == normalVar){
		normal_vars[this->lhs->name] = this->expr->value;
		this->lhs->value = this->expr->value;		
	}		

	if(this->lhs->vtype == arrayVar){
		array_vars[this->lhs->name][this->lhs->int_index] = this->expr->value;
		this->lhs->value = this->expr->value;
		// cout << endl <<this->lhs->name << "[" << this->lhs->int_index << "] = " << this->lhs->value << endl;
	}		
}

LHS::LHS(string name)
{
	this->name = name;
	enum VarType vtype = normalVar;
	this->vtype = vtype;
	if(normal_vars.find(name) != normal_vars.end()){
		this->value = normal_vars[name];
	}
}

LHS::LHS(string name, string string_index)
{
	this->name = name;
	this->string_index = string_index;
	enum VarType vtype = arrayVar;
	this->vtype = vtype;
}

LHS::LHS(string name, int int_index)
{
	this->name = name;
	this->int_index = int_index;
	enum VarType vtype = arrayVar;
	this->vtype = vtype;

	if(array_vars.find(name) != array_vars.end()){
		this->value = array_vars[name][int_index];
	}
}

LHS::LHS(string name, Expr* expr_index)
{
	this->name = name;
	this->expr_index = expr_index;
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

	/* Initialization */
	this->var->value = this->start->value;

	for(int i = start->value; i <= end->value; i++) {
		
	}
	
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

	// cout << "asdas " << this->value << endl;
}

NormalExpr::NormalExpr(LHS* lhs)
{
	// cout << endl;
	// cout << lhs->name << "[" << lhs->int_index << "]" << " = " << lhs->value << endl;
	// cout << endl;
	this->setVal(lhs->value);
	enum ExprType type = normal;
	this->etype = type;

	this->expr = lhs->name;
	
	if(lhs->vtype == arrayVar){
		if(lhs->int_index)
			this->expr = lhs->name + "[" + to_string(lhs->int_index) + "]";
		else if(lhs->string_index != "")
			this->expr = lhs->name + "[" + lhs->string_index + "]";		
	}			
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
	// cout << endl << "printing Op  " << Op << endl;
	if(this->Op == "+") {		
		this->setVal(this->first->getVal() + this->second->getVal());
	} else if(this->Op == "-") {
		this->setVal(this->first->getVal() - this->second->getVal());
	} else if(this->Op == "*") {
		this->setVal(this->first->getVal() * this->second->getVal());
	} else if(this->Op == "/") {
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

LabeledStatement::LabeledStatement(string label, class Statement* statement)
{
	this->label = label;
	this->statement = statement;	
}

/* ---------------- Traversals --------------- */

void Program::traverse()
{	
	printTabs();
	cout << "<program>" << endl;
	tabs_needed++;
	this->vars->traverse();
	this->statements->traverse();
	tabs_needed--;
	printTabs();
	cout << "</program>" << endl;
}

void Vars::traverse()
{
	vector<class Var*> var_list = this->var_list;
	printTabs();
	cout << "<vars count=" << var_list.size() << ">" << endl;

	tabs_needed++;
	for(int i = 0; i < var_list.size(); i++) {
		var_list[i]->traverse();
	}
	tabs_needed--;
	printTabs();
	cout << "</vars>" << endl;
}

void Var::traverse()
{
	printTabs();
	if(this->isArray()) {
		cout << "<var type=\"int_array\" name=\"" << this->name << "\" size=\"" << this->length << "\" />" << endl;
	} else {
		cout << "<var type=\"int\" name=\"" << this->name << "\"/>" << endl;
	}
}

void Statements::traverse()
{
	printTabs();
	vector<class Statement*> statement_list = this->statement_list;

	cout << "<statements count=" << statement_list.size() << ">" << endl;

	tabs_needed++;
	for(int i = 0; i < statement_list.size(); i++) {
		statement_list[i]->traverse();
	}
	tabs_needed--;
	printTabs();
	cout << "</statements>" << endl;
}

void Assignment::traverse()
{
	printTabs();
	cout << "<assignment Op=\"" << this->Op << "\">" << endl;
	tabs_needed++;
	this->lhs->traverse();
	this->expr->traverse();
	tabs_needed--;
	printTabs();
	cout << "</assignment>" << endl;
}

void LHS::traverse()
{
	printTabs();
	if(this->vtype == normalVar)
		cout << "<LHS type=\"int\" name=\"" << this->name << "\" />" << endl;
	else{
		if(this->int_index)
			cout << "<LHS type=\"array_int\" name=\"" << this->name << "\" index=\"" << this->int_index << "\" />" << endl;
		else if(this->string_index != "")
			cout << "<LHS type=\"array_int\" name=\"" << this->name << "\" index=\"" << this->string_index << "\" />" << endl;
	}		
}

void NormalExpr::traverse()
{
	printTabs();
	cout << "<normal_expr name=\"" << this->expr << "\" value=\"" << this->value << "\" />" << endl;	
}

void BinaryExpr::traverse()
{
	printTabs();
	cout << "<binary_expr op=\"" << this->Op << "\" >" << endl;
	tabs_needed++;
		printTabs();		
		cout << "<first>" << endl;
		tabs_needed++;
			this->first->traverse();
		tabs_needed--;
		printTabs();
		cout << "</first>" << endl;

		printTabs();		
		cout << "<second>" << endl;
		tabs_needed++;
			this->second->traverse();
		tabs_needed--;
		printTabs();
		cout << "</second>" << endl;
	tabs_needed--;
	printTabs();
	cout << "</binary_expr>" << endl;
}

void BoolExpr::traverse()
{
	printTabs();
	cout << "<boolean_expr op=\"" << this->Op << "\" >" << endl;
	tabs_needed++;
		printTabs();
		cout << "<first>" << endl;
		tabs_needed++;
			this->first->traverse();
		tabs_needed--;
		printTabs();
		cout << "</first>" << endl;

		printTabs();		
		cout << "<second>" << endl;
		tabs_needed++;
			this->second->traverse();
		tabs_needed--;
		printTabs();
		cout << "</second>" << endl;
	tabs_needed--;
	printTabs();
	cout << "</boolean_expr>" << endl;
}

void UnaryExpr::traverse()
{
	printTabs();
	cout << "<boolean_expr op=\"" << this->Op << "\" >" << endl;		
	tabs_needed++;
		printTabs();
		cout << "<second>" << endl;
		tabs_needed++;
			this->second->traverse();
		tabs_needed--;
		printTabs();
		cout << "</second>" << endl;
	tabs_needed--;
	printTabs();
	cout << "</boolean_expr>" << endl;
}

void LabeledStatement::traverse()
{
	printTabs();
	cout << "<labeled_stmnt label=\"" << this->label << "\">" << endl;
	tabs_needed++;
		this->statement->traverse();
	tabs_needed--;
	printTabs();
	cout << "</labeled_stmnt>" << endl;
}

void IfStatement::traverse()
{
	printTabs();
	cout << "<if_stmnt>" << endl;
	tabs_needed++;
		printTabs();
		cout << "<condition>" << endl;
		tabs_needed++;
			this->cond->traverse();
		tabs_needed--;
		printTabs();
		cout << "</condition>" << endl;

		printTabs();
		cout << "<block>" << endl;
		tabs_needed++;
			this->ifBlock->traverse();
		tabs_needed--;
		printTabs();
		cout << "</block>" << endl;
	tabs_needed--;
	printTabs();
	cout << "</if_stmnt>" << endl;
}

void IfElseStatement::traverse()
{
	printTabs();
	cout << "<if_else_stmnt>" << endl;
	tabs_needed++;
		printTabs();
		cout << "<condition>" << endl;
		tabs_needed++;
			this->cond->traverse();
		tabs_needed--;
		printTabs();		
		cout << "</condition>" << endl;

		printTabs();
		cout << "<if_block>" << endl;
		tabs_needed++;
			this->ifBlock->traverse();
		tabs_needed--;
		printTabs();
		cout << "</if_block>" << endl;

		printTabs();
		cout << "<else_block>" << endl;
		tabs_needed++;
			this->elseBlock->traverse();
		tabs_needed--;			
		printTabs();
		cout << "</else_block>" << endl;
	tabs_needed--;
	printTabs();
	cout << "</if_else_stmnt>" << endl;
}

void ForStatement::traverse()
{
	printTabs();
	cout << "<for_stmnt>" << endl;
	tabs_needed++;
		printTabs();
		cout << "<looping_var>" << endl;
		tabs_needed++;
			this->var->traverse();
			
			printTabs();			
			cout << "<start_value>" << endl;
			tabs_needed++;
				this->start->traverse();
			tabs_needed--;
			printTabs();
			cout << "</start_value>" << endl;

			printTabs();			
			cout << "<end_value>" << endl;
			tabs_needed++;
				this->start->traverse();
			tabs_needed--;
			printTabs();
			cout << "</end_value>" << endl;

			printTabs();
			cout << "<step_value>" << endl;
			tabs_needed++;
				this->start->traverse();
			tabs_needed--;
			printTabs();
			cout << "</step_value>" << endl;
		tabs_needed--;
		printTabs();
		cout << "</looping_var>" << endl;
		
		this->forBlock->traverse();
		
	tabs_needed--;
	printTabs();
	cout << "</for_stmnt>" << endl;
}

void WhileStatement::traverse()
{
	printTabs();
	cout << "<while_stmnt>" << endl;
	tabs_needed++;
		printTabs();		
		cout << "<condition>" << endl;
		tabs_needed++;
			this->cond->traverse();
		tabs_needed--;
		printTabs();
		cout << "</condition>" << endl;

		printTabs();
		cout << "<block>" << endl;
		tabs_needed++;
			this->whileBlock->traverse();
		tabs_needed--;
		printTabs();
		cout << "</block>" << endl;
	tabs_needed--;
	printTabs();
	cout << "</while_stmnt>" << endl;
}

void GoToStatement::traverse()
{
	printTabs();
	cout << "<goto_stmnt destination=\"" << this->label << "\">" << endl;
	tabs_needed++;
		printTabs();
		cout << "<condition>" << endl;
		tabs_needed++;
			this->cond->traverse();
		tabs_needed--;
		printTabs();
		cout << "</condition>" << endl;		
	tabs_needed--;
	printTabs();
	cout << "</goto_stmnt>" << endl;
}

void PrintStatement::traverse()
{
	printTabs();
	cout << "<print_stmnt>" << endl;

	printTabs();
	cout << "</print_stmnt>" << endl;
}

void PrintLnStatement::traverse()
{
	printTabs();
	cout << "<println_stmnt>" << endl;
	printTabs();
	cout << "</println_stmnt>" << endl;
}

void ReadStatement::traverse()
{
	printTabs();
	cout << "<read_stmnt>" << endl;
	printTabs();
	cout << "</read_stmnt>" << endl;
}

void print_vars()
{
	map<string, int> :: iterator it;

	for(it = normal_vars.begin(); it != normal_vars.end(); it++) {
		cout << it->first << " = " << it->second << endl;
	}

	map<string, vector<int>> :: iterator it1;	

	for(it1 = array_vars.begin(); it1 != array_vars.end(); it1++) {
		vector<int> x = it1->second;
		
		for(int i = 0; i < x.size(); i++) {
			cout << it1->first << "[" << i << "] = " << x[i] << endl;
		}
	}
}