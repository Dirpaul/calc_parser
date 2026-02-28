#pragma once
//#include "main.h"
#include <iostream>
#include <string>
#include <iomanip>
#include <vector>

using namespace std;

#include "Token.h"

class EquationLexer {
	friend ostream& operator<<(ostream& os, const EquationLexer& l) {
		for (int i = 0; i < l.lexems.size(); ++i) {
			os << l.lexems[i].value << " ";
		}
		return os;
	}
	//friend EquationLexer normalizer(const EquationLexer&);
private:
	string expr_str;
	vector<Token> lexems;
	void add_lexem(string& temp, token_type);
	void processing(const string&);
	bool check_pos(size_t)const;
	void throwing(const string&,char = 0, const string* = nullptr)const;
public:
	EquationLexer(istream&);
	EquationLexer(const string&);
	EquationLexer(const string&, vector<Token> l);
	EquationLexer(const EquationLexer&);
	EquationLexer(EquationLexer&&)noexcept;
	void show_lexems()const;
	const vector<Token>& get_lexems()const;
	string get_expr()const;
	bool get_token(size_t, Token&)const;//bool size_t, Token&
	size_t lexem_size()const;
	EquationLexer& operator=(const EquationLexer&);
	EquationLexer& operator=(EquationLexer&&) noexcept;
	vector<Token>::const_iterator begin()const{ return lexems.begin(); }
	vector<Token>::const_iterator end()const { return lexems.end(); }
};

extern bool exit_istream_flag;
