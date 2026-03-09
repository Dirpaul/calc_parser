#pragma once
#ifndef NORMALIZER_H
#define NORMALIZER_H
#include <utility>
#include "Functions.h"
#include "EquationLexer.h"

//EquationLexer normalizer(const EquationLexer&, const Functions&);
	

pair<EquationLexer, const Functions*> normalizer(const EquationLexer&, const Functions* = nullptr);

#endif
