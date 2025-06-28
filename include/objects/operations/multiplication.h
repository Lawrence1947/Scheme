#ifndef MULTIPLICATION_H
#define MULTIPLICATION_H

#include <objects/types/function.h>

class Multiplication : public Function {
public:
  Multiplication() : Function("*") {}

  std::shared_ptr<Object> Apply(const std::vector<std::shared_ptr<Object>> arguments, std::shared_ptr<Scope> scope) const override {
    if (arguments.size() < 2) {
      throw SyntaxError{NOT_ENOUGH_ARGUMENTS};
    }

    int64_t mul = 1;
    for (std::shared_ptr<Object> object : arguments) {
      if (Is<Symbol>(object)) {
        object = scope->GetObject(std::static_pointer_cast<Symbol>(object)->GetName());
      }
      if (!Is<Number>(object)) {
        throw SyntaxError{INVALID_TYPE};
      }
      mul *= std::static_pointer_cast<Number>(object)->GetValue();
    }
    return std::make_shared<Number>(mul);
  }
};

#endif
