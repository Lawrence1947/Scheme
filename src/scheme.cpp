#include <scheme.h>

#include <iostream>
#include <sstream>

#include <tokenizer.h>
#include <parser.h>
#include <error.h>

#include <objects/object.h>

#include <objects/specials/quote.h>
#include <objects/specials/null.h>

#include <objects/types/cell.h>
#include <objects/types/number.h>
#include <objects/types/bool.h>

#include <objects/types/function.h>
#include <objects/operations/addition.h>
#include <objects/operations/subtraction.h>
#include <objects/operations/multiplication.h>
#include <objects/operations/division.h>
#include <objects/operations/greater.h>
#include <objects/operations/less.h>
#include <objects/operations/equal.h>

#include <objects/keywords/bool_predicate.h>
#include <objects/keywords/number_predicate.h>
#include <objects/keywords/and.h>
#include <objects/keywords/or.h>
#include <objects/keywords/not.h>
#include <objects/keywords/define.h>
#include <objects/keywords/set.h>
#include <objects/keywords/if.h>


Scheme::Scheme() : scope_(std::make_shared<Scope>()) {
  InitializeBaseOperations();
  InitializeBaseLiterals();
  InitializeKeywords();
  InitializeControlCommands();
}

void Scheme::InitializeBaseOperations() {
  syntax_list.emplace("+", std::make_shared<Addition>());
  syntax_list.emplace("-", std::make_shared<Subtraction>());
  syntax_list.emplace("*", std::make_shared<Multiplication>());
  syntax_list.emplace("/", std::make_shared<Division>());
  syntax_list.emplace(">", std::make_shared<Greater>());
  syntax_list.emplace("<", std::make_shared<Less>());
  syntax_list.emplace("=", std::make_shared<Equal>());
}

void Scheme::InitializeBaseLiterals() {
  syntax_list.emplace("#t", std::make_shared<Bool>(true));
  syntax_list.emplace("#f", std::make_shared<Bool>(false));
}

void Scheme::InitializeKeywords() {
  syntax_list.emplace("boolean?", std::make_shared<BoolPredicate>());
  syntax_list.emplace("number?", std::make_shared<NumberPredicate>());
  syntax_list.emplace("and", std::make_shared<And>());
  syntax_list.emplace("or", std::make_shared<Or>());
  syntax_list.emplace("not", std::make_shared<Not>());

  syntax_list.emplace("if", std::make_shared<If>());

  syntax_list.emplace("define", std::make_shared<Define>());
  syntax_list.emplace("set!", std::make_shared<Set>());
}

void Scheme::InitializeControlCommands() {

}



void Scheme::REPL(std::istream& in) const {
  std::string expression;
  std::cout << "Scheme 1.0.0\n";
  std::cout << "This program is free software, and you are welcome to redistribute it.\n\n";

  while (in) {
    std::cout << ">>> ";
    std::getline(in, expression);
    if (expression.empty()) {
      continue;
    }
    try {
      std::cout << Evaluate(expression);
    } catch (const std::runtime_error& ex) {
      std::cout << ex.what();
    }
  }
}

std::string Scheme::Evaluate(const std::string& expression) const {
  std::istringstream in(expression);
  Tokenizer tokenizer(&in);

  std::string result;
  while (!tokenizer.IsEnd()) {
    std::shared_ptr<Object> list = Parse(&tokenizer);
    if (!list) { throw SyntaxError(); }
    if (Is<Quote>(list)) {
      FlushIfQuote(result, &tokenizer);
    } else {
      std::shared_ptr<Object> result_object = EvaluateList(list);
      if (Is<Null>(result_object)) continue;
      result += (result_object ? result_object->ToString() : "()");
    }
    result += "\n";
  }

  return result;
}

std::shared_ptr<Object> Scheme::EvaluateList(std::shared_ptr<Object> list) const {
  if (!Is<Cell>(list)) {
    return EvaluatePureObject(list);
  }

  std::vector<std::shared_ptr<Object>> arguments;
  std::shared_ptr<Cell> cell = std::static_pointer_cast<Cell>(list);
  std::shared_ptr<Object> function = EvaluateObject(cell->GetFirst());
  if (Is<If>(function)) {
    return EvaluateIf(cell);
  }
  while (cell->GetSecond()) {
    if (!Is<Cell>(cell->GetSecond())) {
      throw SyntaxError{};
    }
    std::shared_ptr<Cell> next_cell = std::static_pointer_cast<Cell>(cell->GetSecond());
    arguments.push_back(EvaluateObject(next_cell->GetFirst()));
    cell = next_cell;
  }

  return function->Apply(arguments, scope_);
}

std::shared_ptr<Object> Scheme::EvaluateObject(std::shared_ptr<Object> object) const {
  if (!object) {
    return nullptr;
  }
  if (Is<Number>(object)) {
    return object;
  }
  if (Is<Symbol>(object)) {
    return GetEvaluatedSymbol(std::static_pointer_cast<Symbol>(object));
  }
  if (Is<Cell>(object)) {
    return EvaluateList(object);
  }
  throw RuntimeError{EVAL_OBJECT};
  return nullptr;
}

std::shared_ptr<Object> Scheme::EvaluateIf(std::shared_ptr<Cell> if_list) const {
  std::vector<std::shared_ptr<Object>> arguments;
  std::shared_ptr<Object> if_function = EvaluateObject(if_list->GetFirst());
  if (!Is<Cell>(if_list->GetSecond())) {
    throw SyntaxError{IF_SYNTAX};
  }
  std::shared_ptr<Cell> cell = std::static_pointer_cast<Cell>(if_list->GetSecond());
  arguments.push_back(EvaluateObject(cell->GetFirst()));
  while (cell->GetSecond()) {
    if (!Is<Cell>(cell->GetSecond())) {
      throw SyntaxError{IF_SYNTAX};
    }
    std::shared_ptr<Cell> next_cell = std::static_pointer_cast<Cell>(cell->GetSecond());
    arguments.push_back(next_cell->GetFirst());
    cell = next_cell;
  }
  return EvaluateObject(if_function->Apply(arguments, scope_));
}

std::shared_ptr<Object> Scheme::EvaluatePureObject(std::shared_ptr<Object> object) const {
  if (Is<Symbol>(object)) {
    std::string name = std::static_pointer_cast<Symbol>(object)->GetName();
    std::shared_ptr<Object> dereference = scope_->GetObject(name);
    if (dereference) {
      return dereference;
    }
    throw NameError{name};
  }
  return object;
}

std::shared_ptr<Object> Scheme::GetEvaluatedSymbol(std::shared_ptr<Symbol> symbol) const {
  auto it = syntax_list.find(symbol->GetName());
  if (it != syntax_list.end()) {
    return it->second;
  }

  return symbol;
}


void Scheme::FlushIfQuote(std::string& result_str, Tokenizer* tokenizer) const {
  std::shared_ptr<Object> next_list = Parse(tokenizer);
  if (next_list) {
    result_str += next_list->ToString();
  } else {
    result_str += "()";
  }
}


