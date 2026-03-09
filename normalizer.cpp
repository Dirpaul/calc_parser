#include "normalizer.h"
#include "Functions.h"

//normalizer correct expression for mathematical representation
// 8(32+3)5cos(3) -> 8*(32+3)* 5 * cos(3)
// but not check correct of expression

pair<EquationLexer, const Functions*> normalizer(const EquationLexer& l, const Functions* map) {
	const vector<Token>& lexems = l.get_lexems();
	vector<Token> newl; //new lexems
	size_t size = l.lexem_size();
	if (size < 2) return { EquationLexer(l.get_expr(), lexems), map };
	--size;
	token_type curr;
	string curr_name;
	token_type next;
	Token mul{ oper, "*" };
	for (size_t i = 0; i < size; ++i) {
		curr = lexems[i].kind;
		curr_name = lexems[i].value;
		newl.push_back(lexems[i]);
		next = lexems[i + 1].kind;
		if (curr == num) {
			if (next == open || next == word) newl.push_back(mul);
		}
		else if (curr == close) {
			if (next == open || next == num || next == word) newl.push_back(mul);
		}
		else if (map && curr == word && !map->is_fu(curr_name)) {
			if (next == num || next == word || (next == open)) newl.push_back(mul);
		}
	}
	newl.push_back(lexems[size]);
	return {EquationLexer(l.get_expr(), newl), map};
}
