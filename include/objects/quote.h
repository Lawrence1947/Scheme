#ifndef QUOTE_H
#define QUOTE_H

#include <objects/symbol.h>


class Quote : public Symbol {
public:
  Quote() : Symbol("'") {}
};


#endif