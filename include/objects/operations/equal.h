#ifndef EQUAL_H
#define EQUAL_H

#include <array>

#include <objects/types/function.h>
#include <objects/types/number.h>
#include <objects/types/bool.h>

class Equal : public Function {
public:
  Equal() : Function("=") {}

  std::shared_ptr<Object> Apply(const std::vector<std::shared_ptr<Object>> arguments, std::shared_ptr<Scope> scope) const override {
    if (arguments.size() < 2) {
      throw SyntaxError{NOT_ENOUGH_ARGUMENTS};
    }

    if (arguments.size() > 2) {
      throw SyntaxError{TOO_MANY_ARGUMENTS};
    }

    std::array<std::shared_ptr<Object>, 2> params;
    for (size_t i = 0; i < 2; ++i) {
      params[i] = arguments[i];
      if (Is<Symbol>(params[i])) {
        params[i] = scope->GetObject(std::static_pointer_cast<Symbol>(params[i])->GetName());
      }
      if (!Is<Number>(params[i])) {
        throw SyntaxError{INVALID_TYPE};
      }
    }

    return std::make_shared<Bool>(std::static_pointer_cast<Number>(params.front())->GetValue() 
                                  == std::static_pointer_cast<Number>(params.back())->GetValue());
  }
};

#endif