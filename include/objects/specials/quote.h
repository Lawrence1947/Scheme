#ifndef QUOTE_H
#define QUOTE_H

#include <objects/types/symbol.h>

class Quote : public Symbol {
public:
  Quote() : Symbol("'") {}
};

#endif