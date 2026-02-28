#include "parser.h"
#include "Functions.h"

parser::parser(const EquationLexer& e,const Functions* f)try : el(e),fu(f),
root(nullptr), current(el.begin()), end(el.end()) { 
	make_tree();
	if (current != end) throwing("make_tree() the expression is not fully pars");
}catch (runtime_error& re) { throw; }
parser::parser(pair<EquationLexer, const Functions*> p)try :parser(p.first, p.second) {
}catch (runtime_error& re) { throw; }
void parser::throwing(const string& s, const string* expr) const{
	throw runtime_error("[" + el.get_expr() + "]" + "\nParser: " + s + (expr ? " [" + *expr + "]" : ""));
}
bool parser::next() {
	if (current == end) return false;
	++current;
	return current != end;
}
void parser::make_tree() { root = expr();}
unique_ptr<Node> parser::expr() {// (-2 + 4) * 5^2
	unique_ptr<Node> left = term(), right;
	while (current != end) {
		if (current->kind == close || current->kind == comm) return left;
		//if (current->kind == comm) return left;
		if (current->kind == oper && (current->value == "+" || current->value == "-")) {
			Token tmp_curr = *current;
			next();
			right = term();
			left = make_unique<BinaryNode>(tmp_curr.value, left, right);
		}
		else throwing("expr() wrong, expected + or - but not '" + current->value + string("'"));
	}
	return left;
}
unique_ptr<Node> parser::term() {
	unique_ptr<Node> left = power(), right;
	while(current != end && current->kind == oper && (current->value == "*" || current->value == "%" ||
		current->value == "/")){ 
		Token tmp_curr = *current;
		next();
		unique_ptr<Node> right = power();
		left = make_unique<BinaryNode>(tmp_curr.value, left, right);
	}
	return left;
}
unique_ptr<Node> parser::power() {
	unique_ptr<Node> left = primary(),right;
	if (current != end && current->kind == oper && current->value == "^") {
		Token tmp_curr = *current;
		next();
		right = power();
		return make_unique<BinaryNode>(tmp_curr.value, left, right);
	}
	return left;
}
unique_ptr<Node> parser::primary() {
	if (current != end) {
		unique_ptr<Node> temp;
		if (current->kind == num) {
			temp = make_unique<NumberNode>(current->value);
			next();
			return temp;
		}
		else if (current->kind == oper && (current->value == "-" || current->value == "+")) {
			const Token& tmp_curr = *current;
			next();
			unique_ptr<Node> value = primary();
			temp = make_unique<UnaryNode>(tmp_curr.value, value);
			return temp;
		}
		else if (current->kind == open) {
			next();//eat '('
			temp = expr();
			if (current == end || (current != end && current->kind != close)) throwing("primary(), expected close");
			next(); //eat ')'
			return temp;
		}
		else if (current->kind == word) {
			if (fu && fu->is_fu(current->value)) return function();
			else throwing("primary(), word is not recognized", &current->value);
			if(current == end)  throwing("primary(), unexpecting end of an expression");
			throwing("primary(), wrong use of function or variable", &current->value);
		}
		else  throwing("primary() wrong, unexpected", &current->value);
	}
	else throwing("primary(), unexpecting end of an expression");
}
unique_ptr<Node> parser::function() {
	pair<double (*)(const vector<double>), int> fu_pair = fu->get(current->value);
	vector<unique_ptr<Node>> args;
	next(); //eat word
	if (current != end && current->kind == open) {
		next();//eat '('
		while (current != end && current->kind != close) {
			args.push_back(expr());
			if (current != end && current->kind == comm) next();
		};
		if (current != end && current->kind == close) {
			next();
			if (args.size() == fu_pair.second) return make_unique<FuncNode>(fu_pair.first, args);
			throwing("primary(), wrong arg count fo function");
		}
	}
	throwing("primary(), expected '(' after function name");
}









