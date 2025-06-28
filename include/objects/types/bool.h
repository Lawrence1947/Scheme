#ifndef BOOL_H
#define BOOL_H

#include <objects/object.h>
#include <error.h>

class Bool : public Object {
public:
  explicit Bool(bool flag) : flag_(flag) {}

  bool GetFlag() const { return flag_; }

  std::string ToString() const override { return (flag_ ? "#t" : "#f"); }
  std::shared_ptr<Object> Apply([[maybe_unused]] const std::vector<std::shared_ptr<Object>> arguments, 
                                [[maybe_unused]] std::shared_ptr<Scope> scope) const { throw RuntimeError{NO_OVERRIDE_BOOL}; }

private:
  bool flag_;
};

#endif