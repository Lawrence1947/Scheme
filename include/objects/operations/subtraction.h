#ifndef SUBTRACTION_H
#define SUBTRACTION_H

#include <objects/types/function.h>

class Subtraction : public Function {
public:
  Subtraction() : Function("-") {}

  std::shared_ptr<Object> Apply(const std::vector<std::shared_ptr<Object>> arguments, std::shared_ptr<Scope> scope) const override {
    if (arguments.size() < 2) { 
      throw SyntaxError{NOT_ENOUGH_ARGUMENTS};
    }

    std::shared_ptr<Object> object = arguments.front();
    if (Is<Symbol>(object)) {
      object = scope->GetObject(std::static_pointer_cast<Symbol>(object)->GetName());
    }
    if (!Is<Number>(object)) {
      throw SyntaxError{INVALID_TYPE}; 
    }

    int64_t sub = std::static_pointer_cast<Number>(arguments.front())->GetValue();
    for (size_t i = 1; i < arguments.size(); ++i) {
      object = arguments[i];
      if (Is<Symbol>(object)) {
        object = scope->GetObject(std::static_pointer_cast<Symbol>(object)->GetName());
      }
      if (!Is<Number>(object)) { 
        throw SyntaxError{INVALID_TYPE};
      }
      sub -= std::static_pointer_cast<Number>(object)->GetValue();
    }
    return std::make_shared<Number>(sub);
  }
};

#endif
