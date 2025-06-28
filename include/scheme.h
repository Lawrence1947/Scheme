#ifndef SCHEME_H
#define SCHEME_H

#include <sstream>
#include <memory>
#include <string>
#include <map>

#include <tokenizer.h>
#include <objects/object.h>
#include <objects/types/symbol.h>
#include <objects/types/function.h>
#include <objects/types/cell.h>
#include <objects/specials/scope.h>

class Scheme {
public:
  Scheme();

  void REPL(std::istream& in) const;

private:
  void InitializeBaseOperations();
  void InitializeBaseLiterals();
  void InitializeKeywords();
  void InitializeControlCommands();

  void FlushIfQuote(std::string& result_str, Tokenizer* tokenizer) const;

  std::shared_ptr<Scope> GetScope() { return scope_; }

  std::string Evaluate(const std::string& expression) const;
  std::shared_ptr<Object> EvaluateList(std::shared_ptr<Object> list) const;
  std::shared_ptr<Object> EvaluateObject(std::shared_ptr<Object> object) const;

  std::shared_ptr<Object> EvaluateIf(std::shared_ptr<Cell> if_list) const;
  std::shared_ptr<Object> EvaluatePureObject(std::shared_ptr<Object> object) const;
  std::shared_ptr<Object> GetEvaluatedSymbol(std::shared_ptr<Symbol> symbol) const;

private:
  std::map<std::string, std::shared_ptr<Object>> syntax_list;
  std::shared_ptr<Scope> scope_;
};







#endif