#ifndef DEFINE_H
#define DEFINE_H

#include <scheme.h>
#include <objects/types/symbol.h>
#include <objects/types/number.h>
#include <objects/specials/scope.h>
#include <objects/specials/null.h>

class Define : public Symbol {
public:
  Define() : Symbol("define") {}

  std::shared_ptr<Object> Apply(const std::vector<std::shared_ptr<Object>> arguments, 
                                std::shared_ptr<Scope> scope, const Scheme *scheme) const override {
    if (arguments.size() < 2) {
      throw SyntaxError{NOT_ENOUGH_ARGUMENTS};
    }
    if (arguments.size() > 2) {
      throw SyntaxError{TOO_MANY_ARGUMENTS};
    }
    if (!Is<Symbol>(arguments.front())) {
      throw SyntaxError{INVALID_TYPE};
    }
    std::shared_ptr<Object> value = scheme->EvaluateObject(arguments.back(), scope);
    scope->Cache(std::static_pointer_cast<Symbol>(arguments.front())->GetName(), scheme->EvaluatePureObject(value, scope));
    return std::make_shared<Null>();
  }
};

#endif