#include "main.h"
#include "parser.h"
#include "Functions.h"
#include "normalizer.h"
#include "EquationLexer.h"
#include "tests.h"
#include "Vars.h"

Functions fu_map;
Functions lst;
void fill_fu_list() {
lst.add_function("sum", [](const vector<double> v) { return v[0] + v[1]; }, 2);
	lst.add_function("minus", [](const vector<double> v) { return v[0] - v[1]; }, 2);
	lst.add_function("div", [](const vector<double> v) { return v[0] / v[1]; }, 2);
	lst.add_function("mul", [](const vector<double> v) { return v[0] * v[1]; }, 2);
	lst.add_function("triple_sum", [](const vector<double> v) {
		return v[0] + v[1] + v[2]; }, 3);
}
void tests() {
	fill_fu_list();
	//ex1();
	//ex2();// need fix
	//functions_check();
	//ex3();
	//ex4();
	//ex5();
	ex6();
}

void ex1() {
	try {
		EquationLexer el{ "723..123 + 234 * sin(234) - (234 * 123) + 23 - abc234" };
		el.show_lexems();
	}
	catch (runtime_error re) {
		//cout << re.what() << endl;
	}
	while (true) {
		try {
			EquationLexer el1{ cin };
			el1.show_lexems();
			if (exit_istream_flag) break;
		}
		catch (runtime_error re) {
			//cout << re.what() << endl;
		}
	}
}
void ex2(){
	vector<string> vs{
		"()623.123) + (123 - 23) * 231 * (711.21 / 21)",
		"(623.23 + 32)(324(3232)*32) + 32/213 - 12% 12",
		"(((12312.)+23*32)/32",
		"123+(32-324)*324/23"
	};
	for (const string& s : vs) {
		try {
			//EquationLexer l1{ s };
			cout << "212#####(" << s << ")**************" << endl;
			//l1.show_lexems();
			parser p1({ s });//parser p1(l1); //add move
			
		}
		catch (runtime_error re) {}
	}
	while (true) {
		try {
			//EquationLexer l2{ cin };
			//l2.show_lexems();
			parser p2(cin);
			if (exit_istream_flag) break;
		}
		catch (runtime_error re) {
	functions_check();
		}
	}
}

void functions_check() {//functions check
	
	NumberNode n1("12.0");
	NumberNode n2("2.0");
	vector<Node*> vectNode{ &n1, &n2 };
	vector<double> vectDbl;
	vectDbl.push_back(vectNode[0]->eval());
	vectDbl.push_back(vectNode[1]->eval());
	cout << lst.get("sum").first(vectDbl) << endl;
	cout << lst.get("minus").first(vectDbl) << endl;
	cout << lst.get("div").first(vectDbl) << endl;
	cout << lst.get("mul").first(vectDbl) << endl;
	//vector<Node*> triple{ new NumberNode("10.0"), new NumberNode("5.0"), new NumberNode("2") };
	//cout << lst.get("triple_sum")(vector<Node*>{new NumberNode("10.0"), 
		//new NumberNode("5.0"), new NumberNode("2")}) << endl;
}
double cos(vector<double> v) {
	return cos(v[0]);
}
double sin(vector<double> v) {
	return sin(v[0]);
}
void ex3(){
	Functions fu_map;
	fu_map.add_function("cos", cos, 1);
	//cout << "show fu_map" << " size=" << fu_map.get_map().size() << endl;
	for (pair<string, pair<double(*)(const vector<double>), int>> p : fu_map.get_map()) cout << p.first << endl;
	
	for (int i = 0; i < ::vs1[0].size(); ++i) {
		try {
			//cout << "#" << i << " " << vs[i] << "\n";
			EquationLexer l{ ::vs1[0][i]};
			/*if (i == 9) {
				cout << "SOME" << endl;
			}*/
			//l = std::move(normalizer(l));
			pair<EquationLexer, const Functions*> pr = normalizer(l, &fu_map);
			cout << parser{normalizer(l, &fu_map)} << endl;;
			//cout << parser{normalizer(l, &fu_map)} << endl;;
			//cout << normalizer(vs[i], &fu_map) << endl;
		}
		catch (runtime_error re) {
			//cout << re.what() << endl;
		}
	}
	
}
void ex4() {
	fu_map.add_function("cos", cos, 1);
	//cout << "show fu_map" << " size=" << fu_map.get_map().size() << endl;
	for (pair<string, pair<double(*)(const vector<double>), int>> p : fu_map.get_map()) cout << p.first << endl;
	vector<string>& vs = ::vs1[0];
	for (int i = 0; i < vs.size(); ++i) {
		try {
			//cout << "#" << i << " " << vs[i] << "\n";
			EquationLexer l{ vs[i] };
			/*if (i == 9) {
				cout << "SOME" << endl;
			}*/
			//l = std::move(normalizer(l));
			pair<EquationLexer, const Functions*> p = normalizer(l, &fu_map);
			cout << parser{p} << endl;;
			//cout << parser{ normalizer(l, &fu_map) } << endl;;
			//cout << normalizer(vs[i], fu_map) << endl;
		}
		catch (runtime_error re) {
			//cout << re.what() << endl;
		}
	}
}

void ex5() {
	fu_map.add_function("cos", cos, 1);
	fu_map.add_function("sin", sin, 1);
	//pair<double(*)(vector<double>), int> p = lst.get("mul");
	//fu_map.add_function("mul", p.first, p.second);
	for (pair < string, pair<double(*)(vector<double>), int>> p : lst.get_map()) {
		fu_map.add_function(p.first, p.second.first, p.second.second);
	}
	string enter;
	int cnt = 0;
	while (cin >> enter && enter != "quit" ) {
		cout << "\r\r\r\r\r\r\r\r\r\r\r\r\r\r\r";
		if (cnt > 6) cnt = 0;
		vector<string>& vs = ::vs1[cnt++];
		for (int i = 0; i < vs.size(); ++i) {
			try {
				EquationLexer l{ vs[i] };
				//pair<EquationLexer, const Functions*> pr = normalizer(l, &fu_map);
				//parser p{pr };
				if (i == 6) {
					//cout << "SOME" << endl;
				}
				parser p(normalizer(l, &fu_map));
				cout << p << endl;
			}
			catch (runtime_error& re) {
				cout << re.what() << endl;
			}
		}
	}
}
void ex6() {
	string s;
	Functions fu;
	fu.add_function("cos", [](vector<double> v) {return cos(v[0]); }, 1);
	fu.add_function("sin", [](vector<double> v) {return sin(v[0]); }, 1);
	fu.add_function("tg", [](vector<double> v) {return tan(v[0]); }, 1);
	fu.add_function("triple_sum", [](vector<double> v) {return v[0]+v[1]+v[2]; }, 3);
	fu.add_function("sum", [](vector<double> v) {return v[0]+v[1]; }, 2);
	fu.add_function("atan2", [](vector<double> v){
		return atan2(v[0], v[1]);
		}, 2);
	//fu.add_function("acos", [](vector<double> v) {return v[0]+v[1]; }, 2);
	//fu.add_function("acos2", [](vector<double> v) {return v[0]+v[1]; }, 2);
	while (getline(cin,s) && s != "quit") {
		try {
			EquationLexer l{ s };
			//EquationLexer l{ "2+ 2"};
			l.show_lexems();
			cout << parser{ normalizer(l,&fu)};
		}
		catch (runtime_error& re) {
			cout << re.what() << endl;
		}
		cout << endl;
	}
	
}




