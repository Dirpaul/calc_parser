#pragma once
#include "main.h"
#include "EquationLexer.h"

class Node {
public:
	virtual ~Node() = default;
	virtual double eval();
};
class NumberNode : public Node {
public:
	NumberNode(const string&);
	double eval() override;
private:
	double value;
};
class UnaryNode : public Node {
public:
	UnaryNode(const string&, unique_ptr<Node>&);
	double eval() override;
private:
	string op;
	unique_ptr<Node> value;
};
class BinaryNode : public Node {
public:
	BinaryNode(const string&, unique_ptr<Node>&, unique_ptr<Node>&);
	double eval() override;
private:
	string op;
	unique_ptr<Node> left;
	unique_ptr<Node> right;
};
class FuncNode : public Node {
public:
	FuncNode(double(*)(vector<double>), vector<unique_ptr<Node>>&);
	double eval() override;
private:
	double(*fu)(vector<double>);
	vector<unique_ptr<Node>> arg_list;
};



