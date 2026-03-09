#include "Functions.h"

Functions::Functions(){}
void Functions::add_function(const string& str, double(*fu)(vector<double>), int size) {
	func_list.insert({ str, { fu, size } });
}
pair<double(*)(vector<double>), int> Functions::get(const string& s)const{
	return func_list.at(s);
}
const map<string, pair<double(*)(vector<double>),int>>& Functions::get_map()const{
	return func_list;
}
bool Functions::is_fu(const string& s) const{
	for (const pair<string, pair<double(*)(vector<double>), int>>& p : func_list) {
		if (s == p.first)  return true;;
	}
	return false;
}
