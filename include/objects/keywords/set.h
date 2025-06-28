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
    std::shared_ptr<Object> object = scheme->EvaluateObject(arguments.front(), scope);
    if (!Is<Symbol>(object)) {
      throw SyntaxError{INVALID_TYPE};
    }
    
    std::shared_ptr<Object> value = scheme->EvaluateObject(arguments.back(), scope);
    scope->Rewrite(std::static_pointer_cast<Symbol>(object)->GetName(), scheme->EvaluatePureObject(value, scope));
    return std::make_shared<Null>();
  }
};

#endif