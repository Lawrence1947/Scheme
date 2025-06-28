#ifndef NUMBER_H
#define NUMBER_H

#include <scheme.h>
#include <objects/object.h>
#include <error.h>

class Number : public Object {
public:
  explicit Number(int64_t value) : value_(value) {}

  int64_t GetValue() const { return value_; }

  std::string ToString() const override { return std::to_string(value_); }
  std::shared_ptr<Object> Apply([[maybe_unused]] const std::vector<std::shared_ptr<Object>> arguments, 
                                [[maybe_unused]] std::shared_ptr<Scope> scope, [[maybe_unused]] const Scheme *scheme) const 
                                  { throw RuntimeError{NO_OVERRIDE_NUMBER}; }

private:
  int64_t value_;
};

#endif