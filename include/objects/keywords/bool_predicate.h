#ifndef BOOL_PREDICATE_H
#define BOOL_PREDICATE_H

#include <scheme.h>
#include <objects/types/symbol.h>
#include <objects/types/bool.h>

class BoolPredicate : public Symbol {
public:
  BoolPredicate() : Symbol("boolean?") {}

  std::shared_ptr<Object> Apply(const std::vector<std::shared_ptr<Object>> arguments, 
                                std::shared_ptr<Scope> scope, const Scheme *scheme) const override {
    if (arguments.size() < 1) {
      throw SyntaxError{NOT_ENOUGH_ARGUMENTS};
    }
    if (arguments.size() > 1) {
      throw SyntaxError{TOO_MANY_ARGUMENTS};
    }
    if (Is<Bool>(scheme->EvaluateObject(arguments.front(), scope))) {
      return std::make_shared<Bool>(true);
    }
    return std::make_shared<Bool>(false);
  }
};

#endif