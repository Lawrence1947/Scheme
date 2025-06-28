#ifndef SYMBOL_H
#define SYMBOL_H

#include <string>

#include <objects/object.h>
#include <error.h>

class Scheme;

class Symbol : public Object {
public:
  explicit Symbol(const std::string& name) : name_(std::move(name)) {}

  std::string GetName() const { return name_; }

  std::string ToString() const override { return GetName(); }
  std::shared_ptr<Object> Apply([[maybe_unused]] const std::vector<std::shared_ptr<Object>> arguments, 
                                [[maybe_unused]] std::shared_ptr<Scope> scope, [[maybe_unused]] const Scheme *scheme) const 
                                  { throw RuntimeError{NO_OVERRIDE_SYMBOL}; }

private:
  std::string name_;
};

#endif