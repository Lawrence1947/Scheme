#ifndef OR_H
#define OR_H

#include <scheme.h>
#include <objects/types/symbol.h>
#include <objects/types/bool.h>

class Or : public Symbol {
public:
  Or() : Symbol("or") {}

  std::shared_ptr<Object> Apply(const std::vector<std::shared_ptr<Object>> arguments, 
                                std::shared_ptr<Scope> scope, const Scheme *scheme) const override {
    for (std::shared_ptr<Object> object : arguments) {
      object = scheme->EvaluateObject(object, scope);
      if (Is<Symbol>(object)) {
        object = scope->GetObject(std::static_pointer_cast<Symbol>(object)->GetName());
      }
      if (!Is<Bool>(object)) {
        throw SyntaxError{INVALID_TYPE};
      }
      if (std::static_pointer_cast<Bool>(object)->GetFlag()) {
        return std::make_shared<Bool>(true);
      }
    }
    return std::make_shared<Bool>(false);
  }
};

#endif