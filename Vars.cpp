#include "Vars.h"

variables::variables(initializer_list<pair<string, double>> il):vars(il.begin(), il.end()) {}
void variables::add_var(pair<string, double> p) {vars.insert(p);}

double variables::operator[](const string& s)const {return vars.at(s);}