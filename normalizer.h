#pragma once
#ifndef NORMALIZER_H
#define NORMALIZER_H
#include <utility>
#include "Functions.h"
#include "EquationLexer.h"

pair<EquationLexer, const Functions*> normalizer(const EquationLexer&, const Functions* = nullptr);

#endif
