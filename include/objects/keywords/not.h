#ifndef NOT_H
#define NOT_H

#include <scheme.h>
#include <objects/types/symbol.h>
#include <objects/types/bool.h>

class Not : public Symbol {
public:
  Not() : Symbol("not") {}

  std::shared_ptr<Object> Apply(const std::vector<std::shared_ptr<Object>> arguments, 
                                std::shared_ptr<Scope> scope, const Scheme *scheme) const override {
    if (arguments.size() < 1) {
      throw SyntaxError{NOT_ENOUGH_ARGUMENTS};
    }
    if (arguments.size() > 1) {
      throw SyntaxError{TOO_MANY_ARGUMENTS};
    }
    std::shared_ptr<Object> object = scheme->EvaluateObject(arguments.front(), scope);
    if (Is<Symbol>(object)) {
      object = scope->GetObject(std::static_pointer_cast<Symbol>(object)->GetName());
    }
    if (Is<Bool>(object)) {
      return std::make_shared<Bool>(!std::static_pointer_cast<Bool>(object)->GetFlag());
    }
    return std::make_shared<Bool>(false);
  }
};

#endif