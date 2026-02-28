#include "Token.h"

ostream& operator<<(ostream& os, const Token& t) {
	os << t.value;
	switch (t.kind) {
	case 0: return os << ":NONE";
	case 1: return os << ":num";
	case 2: return os << "power";
	case 3: return os << ":op";
	case 4: return os << ":word";
	case 5: return os << ":open";
	case 6:	return os << ":close";
	default: return os << ":UNDEF";
	}
}

