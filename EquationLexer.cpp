#include "EquationLexer.h"
#include <iterator>
#include <string>
#include <utility>
#include <algorithm>

void EquationLexer::throwing(const string& s, char arg, const string* num) const {
	throw runtime_error("lexem: " + s + (arg?" \t\"" + string(1,arg) + "\"[" + to_string(arg)+ "]":"") + (num?"\"" + *num + "\"" : ""));
}
void EquationLexer::add_lexem(string& temp, token_type type){
	if (count(temp.begin(), temp.end(), '.') > 1) throwing("wrong number",0, &temp);
	if (!temp.empty()) lexems.push_back(Token{ type ,temp});
	temp = {};
}
void EquationLexer::processing(const string& str){
	string temp{};
	//char prev{ ' ' };// n - number, o - operator, f - function, ' ' - empty init state
	token_type prev{ none };
	size_t sz = str.size();
	for (int i = 0; i < str.size(); ++i) {
		unsigned char ch = str[i];
		//if (ch > 127 || ch < 0) {// isascii(ch) unsigned or signed char
		if(!isascii(ch)){ //do not working with | or more 
			throwing("wrong char(ascii)", ch);
		}
		if (isspace(ch)) {
			add_lexem(temp, prev);
			continue;
		}
		if (isdigit(ch) || ch == '.') {
			if (prev != num) add_lexem(temp, prev);
			temp += ch;
			prev = num;
		}
		else if (isalpha(ch) || ch == '_') {//need make digit in functions name
			if (prev != word) add_lexem(temp,prev);
			temp += ch;
			prev = word;
		}
		else if (ch == '+' || ch == '-' || ch == '*' || ch == '/' || ch == '%' || ch == '^') {
			add_lexem(temp,prev);
			temp += ch;
			prev = oper;
		}
		else if (ch == '(') {
			add_lexem(temp,prev);
			temp = ch;
			prev = open;
		}
		else if (ch == ')') {
			add_lexem(temp,prev);
			temp = ch;
			prev = close;
		}
		else if (ch == ',') {
			add_lexem(temp, prev);
			temp = ch;
			prev = comm;
		}
		else throwing("wrong char(notdef)", ch);
		if (i == (sz - 1)) add_lexem(temp,prev);
	}
}
EquationLexer::EquationLexer(const string& str)try :expr_str(str){
	if (str.empty()) throwing("empty expression");
	processing(str);
}catch (runtime_error re) {
	cout << re.what() << endl;
	throw;
}
bool exit_istream_flag = 0;
EquationLexer::EquationLexer(istream& istr)try{
	while (getline(istr, expr_str) && expr_str != "quit") {
		processing(expr_str);
		//show_lexems();
	}
	if (expr_str == "quit") exit_istream_flag = true;
	if (!istr) {
		istr.ignore();
		istr.clear();
	}
}catch(runtime_error re){
	cout << re.what() << endl;
}
EquationLexer::EquationLexer(const string& s, vector<Token> l):expr_str(s), lexems(l) {}
EquationLexer::EquationLexer(const EquationLexer& other):expr_str(other.expr_str), lexems(other.lexems) {}
EquationLexer::EquationLexer(EquationLexer&& other)noexcept:expr_str(std::move(other.expr_str)), 
													lexems(std::move(other.lexems)) {
	other.expr_str = "";
	other.lexems.clear();
}
EquationLexer& EquationLexer::operator=(const EquationLexer& other){
	lexems = other.lexems;
	return *this;
}
EquationLexer& EquationLexer::operator=(EquationLexer&& other)noexcept{
	lexems = std::move(other.lexems);
	return *this;
}
void EquationLexer::show_lexems()const {
	for (Token a : lexems)	cout << "[" << a << "]";
	cout << endl;
}
const vector<Token>& EquationLexer::get_lexems()const {return lexems;}
bool EquationLexer::check_pos(size_t current)const {
	return current < lexems.size();
}
string EquationLexer::get_expr()const { return expr_str; }
//const Token& EquationLexer::get_token(size_t pos)const{
bool EquationLexer::get_token(size_t pos, Token& out)const{
	if (check_pos(pos)) {
		out = lexems[pos];
		return true;
	}
	return false;
}

size_t EquationLexer::lexem_size()const {
	return lexems.size();
}

