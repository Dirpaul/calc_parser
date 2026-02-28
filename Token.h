#pragma once
//#include "main.h"
#include <iostream>
#include <string>

using namespace std;

enum token_type { none, num, power, oper, word, open, close, comm };

struct Token {
	token_type kind = none;
	string value;
	size_t pos;
	size_t length;
};

ostream& operator<<(ostream& os, const Token& t);
