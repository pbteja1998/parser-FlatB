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

map<string, class Statements*> labeled_blocks;

int tabs_needed = 0;
const int tab_width = 4;

void printTabs(){
  for(int i = 0; i < tabs_needed; i++){
    for(int j = 0; j < tab_width; j++)
    cout << " ";
  }
}

Program::Program(class Declarations* declarations, class Statements* statements)
{
	this->declarations = declarations;
	this->statements = statements;
}

Declarations::Declarations()
{

}

void Declarations::pushes_back(class Declaration* declaration)
{
	this->declaration_list.push_back(declaration);
}

Declaration::Declaration(class Vars* vars)
{
	this->vars = vars;
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
	normal_vars[name] = 0;
}

Var::Var(enum VarType type, string name)
{
	this->vtype = type;
	this->name = name;
	if(type == normalVar)
		normal_vars[name] = 0;		
}

Var::Var(enum VarType type, string name, class Expr* expr)
{
	this->vtype = type;
	this->name = name;
	this->length = expr->getVal();

	if(type == arrayVar){
		array_defs[name] = this->length;
		for(int i = 0; i < this->length; i++)
			array_vars[name].push_back(0);
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
			array_vars[name].push_back(0);
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
	this->isGoTo = 0;
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
	// cout << "HERE" << endl;
	this->name = name;
	this->int_index = int_index;
	enum VarType vtype = arrayVar;
	this->vtype = vtype;

	if(array_vars.find(name) != array_vars.end()){
		this->value = array_vars[name][int_index];
	}

	// cout << "HEREENDED" << endl;
}

LHS::LHS(string name, Expr* expr_index)
{
	this->name = name;
	this->expr_index = expr_index;
	enum VarType vtype = arrayVar;
	this->vtype = vtype;
}

void LHSs::pushes_back(class LHS *lhs)
{	
	this->lhs_list.push_back(lhs);
}

IfStatement::IfStatement(BoolExpr* bool_expr, Statements* block)
{
	this->isGoTo = 0;
	this->cond = bool_expr;
	this->ifBlock = block;
}

IfElseStatement::IfElseStatement(BoolExpr* bool_expr, Statements* block1, Statements* block2)
{
	this->isGoTo = 0;
	this->cond = bool_expr;
	this->ifBlock = block1;
	this->elseBlock = block2;
}

ForStatement::ForStatement(LHS* lhs, Expr* start, Expr* end, Statements* block)
{
	this->isGoTo = 0;
	this->isStep = 0;
	this->var = lhs;
	this->start = start;
	this->end = end;
	this->step = new NormalExpr(1);
	this->forBlock = block;	
}

ForStatement::ForStatement(LHS* lhs, Expr* start, Expr* end, Expr* step, Statements* block)
{
	this->isGoTo = 0;
	this->isStep = 1;
	this->var = lhs;
	this->start = start;
	this->end = end;
	this->step = step;
	this->forBlock = block;
}

WhileStatement::WhileStatement(BoolExpr* bool_expr, Statements* block)
{
	this->isGoTo = 0;
	this->cond = bool_expr;
	this->whileBlock = block;
}

GoToStatement::GoToStatement(string label)
{
	this->isGoTo = 1;
	this->label = label;
	this->cond = new BoolExpr(1);
}

GoToStatement::GoToStatement(string label, BoolExpr* expr)
{
	this->isGoTo = 1;
	this->label = label;
	this->cond = expr;
}

PrintStatement::PrintStatement(string text)
{
	this->isGoTo = 0;
	this->assigned = 1;
	this->text = text;
}

PrintStatement::PrintStatement(string text, class LHSs* lhss)
{
	this->isGoTo = 0;
	this->assigned = 1;
	this->text = text;
	this->lhss = lhss;
}

PrintStatement::PrintStatement(class LHS* var)
{
	this->isGoTo = 0;
	this->assigned = 0;
	this->var = var;
}

PrintLnStatement::PrintLnStatement(string text)
{
	this->isGoTo = 0;
	this->text = text;
}

ReadStatement::ReadStatement(class LHS* var)
{
	this->isGoTo = 0;
	this->var = var;
}

NormalExpr::NormalExpr(int value)
{
	this->value_assigned = 1;
	this->setVal(value);
	enum ExprType type = normal;
	this->etype = type;

	// cout << "asdas " << this->value << endl;
}

NormalExpr::NormalExpr(LHS* lhs)
{
	this->value_assigned = 2;
	this->lhs = lhs;
	// cout << endl;
	// cout << lhs->name << "[" << lhs->int_index << "]" << " = " << lhs->value << endl;
	// cout << endl;
	this->setVal(lhs->interpret());
	enum ExprType type = normal;
	this->etype = type;

	this->expr = lhs->name;
	
	if(lhs->vtype == arrayVar){
		if(lhs->int_index)
			this->value = array_vars[lhs->name][lhs->int_index];
		else if(lhs->string_index != "")
			this->value = array_vars[lhs->name][normal_vars[lhs->string_index]];		
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
	// if(this->Op == "+") {		
	// 	this->setVal(this->first->getVal() + this->second->getVal());
	// } else if(this->Op == "-") {
	// 	this->setVal(this->first->getVal() - this->second->getVal());
	// } else if(this->Op == "*") {
	// 	this->setVal(this->first->getVal() * this->second->getVal());
	// } else if(this->Op == "/") {
	// 	this->setVal(this->first->getVal() / this->second->getVal());
	// } else if(this->Op == "%%") {
	// 	// cout << "here" << endl;
	// 	cout << this->first->getVal() << " %% " << this->second->getVal() << " = " << this->first->getVal() % this->second->getVal() << endl;
	// 	this->setVal(this->first->getVal() % this->second->getVal());
	// } 
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
	this->assigned = 1;
	this->val = val;
	enum ExprType type = boolean;
	this->etype = type;		
}

BoolExpr::BoolExpr(class Expr* left, string Op, class Expr* right)
{
	// cout << "OP " << Op << endl; 
	this->assigned = 0;
	this->first = left;
	this->second = right;
	this->Op = Op;

	if(Op == ">") {
		if(left->getVal() > right->getVal()) 
			this->val = 1;
		else
			this->val = 0;
	} else if(Op == "<") {
		if(left->getVal() < right->getVal()) 
			this->val = 1;
		else
			this->val = 0;
	} else if(Op == ">=") {
		if(left->getVal() >= right->getVal()) 
			this->val = 1;
		else
			this->val = 0;
	} else if(Op == "<=") {
		if(left->getVal() <= right->getVal()) 
			this->val = 1;
		else
			this->val = 0;
	} if(Op == "==") {
		if(left->getVal() == right->getVal()) 
			this->val = 1;
		else
			this->val = 0;
	} else if(Op == "!=") {
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

LabeledStatement::LabeledStatement(string label, class Statements* statements)
{
	this->isGoTo = 0;
	this->label = label;
	this->statements = statements;
	labeled_blocks[this->label] = this->statements;
}

/* ---------------- Program --------------- */

void Program::traverse()
{	
	printTabs();
	cout << "<program>" << endl;
	tabs_needed++;
	this->declarations->traverse();
	this->statements->traverse();
	tabs_needed--;
	printTabs();
	cout << "</program>" << endl;
}

int Program::interpret()
{
	this->declarations->interpret();
	this->statements->interpret();

	return 0;
}

/* ---------------- Declarations --------------- */

void Declarations::traverse()
{
	printTabs();
	cout << "<declarations count=" << this->declaration_list.size() << ">" << endl;
	tabs_needed++;

	for(int i = 0; i < this->declaration_list.size(); i++) {
		this->declaration_list[i]->traverse();
	}
	tabs_needed--;
	printTabs();
	cout << "</declarations>" << endl;
}

int Declarations::interpret()
{
	vector<class Declaration*> declaration_list = this->declaration_list;
	for(int i = 0; i < declaration_list.size(); i++) {
		declaration_list[i]->interpret();
	}	
}

/* ---------------- Declaration --------------- */

void Declaration::traverse()
{
	printTabs();
	cout << "<declaration>" << endl;
	tabs_needed++;

	this->vars->traverse();
	
	tabs_needed--;
	printTabs();
	cout << "</declaration>" << endl;
}

int Declaration::interpret()
{
	this->vars->interpret();
}

/* ---------------- Vars --------------- */

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

int Vars::interpret()
{
	vector<class Var*> var_list = this->var_list;
	
	for(int i = 0; i < var_list.size(); i++) {
		var_list[i]->interpret();
	}

	return 0;
}

/* ---------------- Var --------------- */

void Var::traverse()
{
	printTabs();
	if(this->isArray()) {
		cout << "<var type=\"int_array\" name=\"" << this->name << "\" size=\"" << this->length << "\" />" << endl;
	} else {
		cout << "<var type=\"int\" name=\"" << this->name << "\"/>" << endl;
	}
}

int Var::interpret()
{
	if(this->vtype == normalVar) {
		normal_vars[this->name] = 0;
	} else {
		vector<int> arr(this->length, 0);
		array_vars[this->name] = arr;
	}

	return 0;
}

/* ---------------- Statements --------------- */

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

int Statements::interpret()
{
	vector<class Statement*> statement_list = this->statement_list;
	
	for(int i = 0; i < statement_list.size(); i++) {
		statement_list[i]->interpret();
		if(statement_list[i]->isGoTo) {
			class GoToStatement *stmnt = dynamic_cast<GoToStatement*> (statement_list[i]);
			if(stmnt->cond->interpret())
				break;
		}			
	}

	return 0;
}

/* ---------------- Assignment --------------- */

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

int Assignment::interpret()
{	
	if(this->lhs->vtype == normalVar) {
		normal_vars[this->lhs->name] = this->expr->interpret();
	} else {
		if(this->lhs->int_index){			
			array_vars[this->lhs->name][this->lhs->int_index] = this->expr->interpret();
			// cout << "here1" << endl;
		}			
		else if(this->lhs->string_index != ""){
			int index = normal_vars[this->lhs->string_index];			
			array_vars[this->lhs->name][index] = this->expr->interpret();	
			// cout << "here2" << endl;
			// cout << normal_vars[this->expr->expr] << endl;
			// cout << this->expr->interpret() << endl;
		} else {
			array_vars[this->lhs->name][this->lhs->expr_index->interpret()] = this->expr->interpret();
			// cout << "here3" << endl;
		}			
		
	}

	return 0;
}

/* ---------------- LHS --------------- */

void LHS::traverse()
{
	printTabs();
	if(this->vtype == normalVar)
		cout << "<LHS type=\"int\" name=\"" << this->name << "\" />" << endl;
	else{
		// if(this->int_index)
		// 	cout << "<LHS type=\"array_int\" name=\"" << this->name << "\" index=\"" << this->int_index << "\" />" << endl;
		// else if(this->string_index != "")
		// 	cout << "<LHS type=\"array_int\" name=\"" << this->name << "\" index=\"" << this->string_index << "\" />" << endl;
		// else
			cout << "<LHS type=\"array_int\" name=\"" << this->name << "\" index=\"" << this-expr_index->interpret() << "\" />" << endl;
	}		
}

int LHS::interpret()
{	
	if(this->vtype == normalVar) {
		return normal_vars[this->name];
	} else {
		string name = this->name;;
		int index;
		// if(this->int_index)	
		// 	index = this->int_index;
		// else if(this->string_index != ""){
		// 	index = normal_vars[this->string_index];
		// 	cout << "index = " << index << endl;
		// }			
		// else
		index = this->expr_index->interpret();
		// cout << name << "[" << index << "] = " << array_vars[name][index] << endl;
		return array_vars[name][index];
	}
}

/* ---------------- NormalExpr --------------- */

void NormalExpr::traverse()
{
	printTabs();
	cout << "<normal_expr name=\"" << this->expr << "\" value=\"" << this->interpret() << "\" />" << endl;	
}

int NormalExpr::interpret()
{
	if(this->value_assigned == 1)
		return this->value;

	if(this->value_assigned == 2)
		this->value = this->lhs->interpret();

	else if(this->expr != "")
		this->value = normal_vars[this->expr];

	// cout << "HERE" << endl;
	// cout << this->expr << endl;
	// cout << this->value << endl;
	// cout << "HERE_END" << endl;
	return this->value;
}

/* ---------------- BinaryExpr --------------- */

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

int BinaryExpr::interpret()
{
	if(this->Op == "+") 
		return this->first->interpret() + this->second->interpret();
	if(this->Op == "-") 
		return this->first->interpret() - this->second->interpret();
	if(this->Op == "*") 
		return this->first->interpret() * this->second->interpret();
	if(this->Op == "/") 
		return this->first->interpret() / this->second->interpret();
	if(this->Op == "%") 
		return this->first->interpret() % this->second->interpret();
}

/* ---------------- BoolExpr --------------- */

void BoolExpr::traverse()
{
	if(this->assigned){
		printTabs();
		cout << "<boolean_expr value=\"" << this->val << "\" >" << endl;		

		printTabs();
		cout << "</boolean_expr>" << endl;
		return;
	}		

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

int BoolExpr::interpret()
{
	if(this->assigned)
		return this->val;

	if(this->Op == ">") {
		// cout << this->first->interpret() << ">" << this->second->interpret() << endl;
		if(this->first->interpret() > this->second->interpret())
			return 1;			
		return 0;
	}

	if(this->Op == ">=") {
		if(this->first->interpret() >= this->second->interpret())
			return 1;
		return 0;
	}

	if(this->Op == "<") {
		if(this->first->interpret() < this->second->interpret())
			return 1;
		return 0;
	}

	if(this->Op == "<=") {
		if(this->first->interpret() <= this->second->interpret())
			return 1;
		return 0;
	}

	if(this->Op == "==") {
		if(this->first->interpret() == this->second->interpret())
			return 1;
		return 0;
	}

	if(this->Op == "!=") {
		if(this->first->interpret() != this->second->interpret())
			return 1;
		return 0;
	}
}

/* ---------------- UnaryExpr --------------- */

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

int UnaryExpr::interpret()
{
	if(this->Op == "-")
		return -1 * this->second->interpret();
}

/* ---------------- LabeledStatement --------------- */

void LabeledStatement::traverse()
{
	printTabs();
	cout << "<labeled_stmnt label=\"" << this->label << "\">" << endl;
	tabs_needed++;		
		this->statements->traverse();
	tabs_needed--;
	printTabs();
	cout << "</labeled_stmnt>" << endl;
}

int LabeledStatement::interpret()
{
	// labeled_blocks[this->label] = this->statements;
	this->statements->interpret();
	return 0;
}

/* ---------------- IfStatement --------------- */

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

int IfStatement::interpret()
{
	if(this->cond->interpret()) {
		this->ifBlock->interpret();
	}

	return 0;
}

/* ---------------- IfElseStatement --------------- */

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

int IfElseStatement::interpret()
{
	if(this->cond->interpret()) {
		this->ifBlock->interpret();
	} else {
		this->elseBlock->interpret();
	}
}

/* ---------------- ForStatement --------------- */

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

int ForStatement::interpret()
{
	int step = 1;

	if(this->isStep)
		step = this->step->interpret();
	
	int initial_val = this->start->interpret();
	int final_val = this->end->interpret();

	if(this->var->vtype == normalVar) {
		for(normal_vars[this->var->name] = initial_val; normal_vars[this->var->name] <= final_val; normal_vars[this->var->name] += step)
			this->forBlock->interpret();
		
	} else {
		string name = this->var->name;;
		int index;
		if(this->var->int_index)	
			index = this->var->int_index;
		else if(this->var->string_index != "")
			index = normal_vars[this->var->string_index];			
		else
			index = this->var->expr_index->interpret();
			
		for(array_vars[name][index] = initial_val; array_vars[name][index] <= final_val; array_vars[name][index] += step)
			this->forBlock->interpret();				
	}

	return 0;
}

/* ---------------- WhileStatement --------------- */

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

int WhileStatement::interpret()
{
	while(this->cond->interpret())
		this->whileBlock->interpret();
	
	return 0;
}

/* ---------------- GoToStatement --------------- */

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

int GoToStatement::interpret()
{
	if(this->cond->interpret()) {
		string label = this->label + ":";
		// cout << "Label  " << label << endl;
		labeled_blocks[label]->interpret();
	}
}

/* ---------------- PrintStatement --------------- */

void PrintStatement::traverse()
{
	printTabs();
	cout << "<print_stmnt>" << endl;
	if(this->assigned){
		tabs_needed++;
		cout << this->text << endl;
		if(this->lhss)		
		for(int i = 0; i < this->lhss->lhs_list.size(); i++) {
			this->lhss->lhs_list[i]->traverse();
		}
		tabs_needed--;
	}
	else
		this->var->traverse();
	printTabs();
	cout << "</print_stmnt>" << endl;
}

int PrintStatement::interpret()
{	
	if(this->assigned){
		cout << this->text.substr(1,this->text.size()-2);
		if(this->lhss)
		for(int i = 0; i < this->lhss->lhs_list.size(); i++) {
			cout << this->lhss->lhs_list[i]->interpret() << endl;
		}
		else 
		cout << endl;
	}
	else
		cout << this->var->interpret() << endl;
	return 0;
}

/* ---------------- PrintLnStatement --------------- */

void PrintLnStatement::traverse()
{
	printTabs();
	cout << "<println_stmnt>" << endl;
	printTabs();
	cout << "</println_stmnt>" << endl;
}

int PrintLnStatement::interpret()
{
	cout << this->text.substr(1,this->text.size()-2) << endl;
	return 0;
}

/* ---------------- ReadStatement --------------- */

void ReadStatement::traverse()
{
	printTabs();
	cout << "<read_stmnt>" << endl;
	tabs_needed++;
	this->var->traverse();
	tabs_needed--;
	printTabs();
	cout << "</read_stmnt>" << endl;
}

int ReadStatement::interpret()
{
	if(this->var->vtype == normalVar)
		cin >> normal_vars[this->var->name];
	else
		cin >> array_vars[this->var->name][this->var->expr_index->interpret()];
	
	return 0;
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

LHSs::LHSs()
{

}