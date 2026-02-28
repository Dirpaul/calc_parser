#pragma once

#include <memory>
#include "EquationTree.h"
#include "Token.h"
#include "EquationLexer.h"

using namespace std;

class parser {
	friend ostream& operator<<(ostream& os, const parser& p) {
		for (Token t : p.el.get_lexems()) {
			cout << t.value;
		}
		cout << " = ";
		os << setprecision(9) << p.root.get()->eval();
		return os;
	}
private:
	EquationLexer el;
	const Functions* fu;
	void make_tree();
	//size_t position;
	unique_ptr<Node> root;
	bool next();
	unique_ptr<Node> expr();
	unique_ptr<Node> term();
	unique_ptr<Node> power();
	unique_ptr<Node> primary();
	unique_ptr<Node> function();
	vector<Token>::const_iterator current, end;
	void throwing(const string&, const string* = nullptr)const;
public:
	parser(const EquationLexer&, const Functions* = nullptr);
	parser(pair<EquationLexer, const Functions*>);
};
/*
expr   → term (('+'|'-') term)*
term   → power (('*'|'/') power)*
power  → factor ('^' power)?
factor → number | '(' expr ')' | '-' factor | func '(' expr ')'
*/
