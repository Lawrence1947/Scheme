#ifndef SYMBOL_H
#define SYMBOL_H

#include <string>

#include <objects/object.h>


class Symbol : public Object {
public:
  explicit Symbol(const std::string& name) : name_(std::move(name)) {}

  const std::string& GetName() const { return name_; }

private:
  std::string name_;
};


#endif