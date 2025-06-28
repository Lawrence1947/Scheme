#ifndef LAMBDA_H
#define LAMBDA_H

#include <objects/types/symbol.h>
#include <objects/types/number.h>
#include <objects/specials/scope.h>
#include <objects/specials/null.h>

class Lambda : public Symbol {
public:
  Lambda() : Symbol("lambda") {}

  std::shared_ptr<Object> Apply(const std::vector<std::shared_ptr<Object>> arguments, std::shared_ptr<Scope> scope) const override {
    if (arguments.size() < 2) {
      throw SyntaxError{NOT_ENOUGH_ARGUMENTS};
    }
    if (arguments.size() > 2) {
      throw SyntaxError{TOO_MANY_ARGUMENTS};
    }
    if (!Is<Symbol>(arguments.front())) {
      throw SyntaxError{INVALID_TYPE};
    }
    
    scope->Cache(std::static_pointer_cast<Symbol>(arguments.front())->GetName(), arguments.back());
    return std::make_shared<Null>();
  }
};

#endif