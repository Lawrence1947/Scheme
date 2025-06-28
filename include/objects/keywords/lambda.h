#ifndef LAMBDA_H
#define LAMBDA_H

#include <memory>

#include <scheme.h>
#include <objects/types/symbol.h>
#include <objects/types/number.h>
#include <objects/specials/scope.h>
#include <objects/specials/null.h>

class LambdaEval : public Object {
public:
  explicit LambdaEval(std::vector<std::string> variables, std::shared_ptr<Object> function_body) 
                      : variables_(variables), function_body_(function_body) {};

  std::string ToString() const override {
    std::string result = "Lambda ( ";
    for (const auto& var : variables_) {
      result += var;
      result += " ";
    }
    result += ") ";
    result += function_body_->ToString();
    return result;
  }

  std::shared_ptr<Object> Apply(const std::vector<std::shared_ptr<Object>> arguments, 
                                [[maybe_unused]] std::shared_ptr<Scope> scope, const Scheme *scheme) const override {
    if (arguments.size() < variables_.size()) {
      throw SyntaxError{NOT_ENOUGH_ARGUMENTS};
    }
    if (arguments.size() > variables_.size()) {
      throw SyntaxError{TOO_MANY_ARGUMENTS};
    }
    std::shared_ptr<Scope> local_scope = std::make_shared<Scope>();
    for (size_t i = 0; i < variables_.size(); ++i) {
      std::shared_ptr<Object> object = scheme->EvaluateObject(arguments[i], scope);
      if (!Is<Number>(object) && !Is<Bool>(object)) {
        throw RuntimeError{LAMBDA_EVAL};
      }
      local_scope->Cache(variables_[i], object);
    }
    return scheme->EvaluateObject(function_body_, local_scope);
  }

private:
  std::vector<std::string> variables_;
  std::shared_ptr<Object> function_body_;
};

class Lambda : public Symbol {
public:
  Lambda() : Symbol("lambda") {}

  std::shared_ptr<Object> Apply(const std::vector<std::shared_ptr<Object>> arguments, 
                                [[maybe_unused]] std::shared_ptr<Scope> scope, [[maybe_unused]] const Scheme *scheme) const override {
    if (arguments.size() < 2) {
      throw SyntaxError{NOT_ENOUGH_ARGUMENTS};
    }
    if (arguments.size() > 2) {
      throw SyntaxError{TOO_MANY_ARGUMENTS};
    }

    std::vector<std::string> variables;
    std::shared_ptr<Object> variables_list = arguments.front();
    if (Is<Cell>(variables_list)) {
      std::shared_ptr<Cell> cell = std::static_pointer_cast<Cell>(variables_list);
      while (cell) {
        if (!Is<Cell>(cell)) {
          throw SyntaxError{LAMBDA_SYNTAX};
        }
        std::shared_ptr<Cell> variable_cell = std::static_pointer_cast<Cell>(cell);
        if (!Is<Symbol>(variable_cell->GetFirst())) {
          throw SyntaxError{LAMBDA_SYNTAX};
        }
        variables.push_back(std::static_pointer_cast<Symbol>(cell->GetFirst())->GetName());
        cell = std::static_pointer_cast<Cell>(variable_cell->GetSecond());
      }
    } else if (Is<Symbol>(variables_list)) {
      variables.push_back(std::static_pointer_cast<Symbol>(variables_list)->GetName());
    } else {
      throw SyntaxError{LAMBDA_SYNTAX};
    }

    return std::make_shared<LambdaEval>(std::move(variables), arguments.back() /*function body*/);
  }
};


#endif