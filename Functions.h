#pragma once
#include <map>
#include <vector>
#include <string>
#include <functional>
#include <stdexcept>

#include "main.h"

using namespace std;

class Functions {
public:
	Functions();
	void add_function(const string&, double(*)(vector<double>), int);
	pair<double(*)(vector<double>), int> get(const string&)const ;
	const map<string, pair<double(*)(vector<double>), int>>& get_map()const;
	bool is_fu(const string&)const;
private:
	map<string, pair<double(*)(vector<double>),int>> func_list;
};

