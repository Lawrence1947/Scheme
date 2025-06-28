#ifndef IF_H
#define IF_H

#include <objects/types/symbol.h>
#include <objects/types/bool.h>
#include <objects/specials/scope.h>

class If : public Symbol {
public:
  If() : Symbol("if") {}

  std::shared_ptr<Object> Apply(const std::vector<std::shared_ptr<Object>> arguments, [[maybe_unused]] std::shared_ptr<Scope> scope) const override {
    if (arguments.size() < 3) {
      throw SyntaxError{NOT_ENOUGH_ARGUMENTS};
    }
    if (arguments.size() > 3) {
      throw SyntaxError{TOO_MANY_ARGUMENTS};
    }
    std::shared_ptr<Object> object = arguments.front();
    if (!Is<Bool>(object)) {
      throw SyntaxError{INVALID_TYPE};
    }
    return (std::static_pointer_cast<Bool>(object)->GetFlag() ? arguments[1] : arguments[2]);
  }
};

#endif