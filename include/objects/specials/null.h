#ifndef NULL_H
#define NULL_H

#include <objects/types/symbol.h>

class Null : public Symbol {
public:
  Null() : Symbol("") {}
};

#endif