#ifndef FUNCTION_H
#define FUNCTION_H

#include <objects/types/symbol.h>

class Function : public Symbol {
public:
  Function(const std::string& name) : Symbol(name) {}
};

#endif