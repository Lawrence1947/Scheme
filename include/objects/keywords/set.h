#ifndef SET_H
#define SET_H

#include <scheme.h>
#include <objects/types/symbol.h>
#include <objects/types/number.h>
#include <objects/specials/scope.h>
#include <objects/specials/null.h>

class Set : public Symbol {
public:
  Set() : Symbol("set!") {}

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
    scope->Rewrite(std::static_pointer_cast<Symbol>(arguments.front())->GetName(), scheme->EvaluatePureObject(value, scope));
    return std::make_shared<Null>();
  }
};

#endif