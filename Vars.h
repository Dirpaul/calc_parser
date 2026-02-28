#pragma once
#include <utility>
#include <iostream>
#include <string>
#include <map>

using namespace std;

class variables {
public:
	variables(initializer_list<pair<string,double>>);
	void add_var(pair<string, double>);
	double operator[](const string&)const;
private:
	map<string, double> vars;
};
