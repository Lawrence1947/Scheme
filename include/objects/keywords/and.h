#ifndef AND_H
#define AND_H

#include <objects/types/symbol.h>
#include <objects/types/bool.h>

class And : public Symbol {
public:
  And() : Symbol("and") {}

  std::shared_ptr<Object> Apply(const std::vector<std::shared_ptr<Object>> arguments, std::shared_ptr<Scope> scope) const override {
    for (std::shared_ptr<Object> object : arguments) {
      if (Is<Symbol>(object)) {
        object = scope->GetObject(std::static_pointer_cast<Symbol>(object)->GetName());
      }
      if (!Is<Bool>(object)) {
        throw SyntaxError{INVALID_TYPE};
      }
      if (!std::static_pointer_cast<Bool>(object)->GetFlag()) {
        return std::make_shared<Bool>(false);
      }
    }
    return std::make_shared<Bool>(true);
  }
};

#endif