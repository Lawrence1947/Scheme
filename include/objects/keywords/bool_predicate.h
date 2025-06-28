#ifndef BOOL_PREDICATE_H
#define BOOL_PREDICATE_H

#include <objects/types/symbol.h>
#include <objects/types/bool.h>

class BoolPredicate : public Symbol {
public:
  BoolPredicate() : Symbol("boolean?") {}

  std::shared_ptr<Object> Apply(const std::vector<std::shared_ptr<Object>> arguments, [[maybe_unused]] std::shared_ptr<Scope> scope) const override {
    if (arguments.size() < 1) {
      throw SyntaxError{NOT_ENOUGH_ARGUMENTS};
    }
    if (arguments.size() > 1) {
      throw SyntaxError{TOO_MANY_ARGUMENTS};
    }
    if (Is<Bool>(arguments.front())) {
      return std::make_shared<Bool>(true);
    }
    return std::make_shared<Bool>(false);
  }
};

#endif