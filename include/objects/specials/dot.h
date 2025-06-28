#ifndef DOT_H
#define DOT_H

#include <objects/types/symbol.h>

class Dot : public Symbol {
public:
  Dot() : Symbol(".") {}
};

#endif