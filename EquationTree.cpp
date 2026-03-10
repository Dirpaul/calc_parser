
#include "EquationTree.h"

double Node::eval() { return 0; }
NumberNode::NumberNode(const string& s): value(stod(s)){}
double NumberNode::eval() {return value;}
UnaryNode::UnaryNode(const string& s, unique_ptr<Node>& val): op(s), value(std::move(val)){}
double UnaryNode::eval() {
	if (op == "-") return -(value->eval());
	if (op == "+") return value->eval();
	throw runtime_error("Unkown unary operator: " + string(op));
	return 0;
}
BinaryNode::BinaryNode(const string& s, unique_ptr<Node>& l, unique_ptr<Node>& r): 
	op(s),left(std::move(l)), right(std::move(r)){}
double BinaryNode::eval() {
	if (op == "+") return left->eval() + right->eval();
	if (op == "-") return left->eval() - right->eval();
	if (op == "*") return left->eval() * right->eval();
	if (op == "/") return left->eval() / right->eval();
	if (op == "%") {
		double temp = left->eval() / right->eval();
		return (temp - static_cast<int>(temp)) * right->eval();
	}
	if (op == "^") return pow(left->eval(), right->eval());
	throw runtime_error("Unknow binary operator: " + string(op));
}
FuncNode::FuncNode(double(*f)(vector<double>), vector<unique_ptr<Node>>& v) : fu(f), arg_list(std::move(v)) {}
double FuncNode::eval() {
	vector<double> vect;
	for (int i = 0; i < arg_list.size(); ++i) {
		vect.push_back(arg_list[i]->eval());
	}
	return fu(vect);
}
