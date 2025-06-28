#ifndef CELL_H
#define CELL_H

#include <string>

#include <objects/object.h>
#include <error.h>

class Cell : public Object {
public:
  explicit Cell(std::shared_ptr<Object> first, std::shared_ptr<Object> second) : first_(std::move(first)), second_(std::move(second)) {}

  std::shared_ptr<Object> GetFirst() const { return first_; }
  std::shared_ptr<Object> GetSecond() const { return second_; }

  std::shared_ptr<Object> Apply([[maybe_unused]] const std::vector<std::shared_ptr<Object>> arguments, 
                                [[maybe_unused]] std::shared_ptr<Scope> scope) const { throw RuntimeError{NO_OVERRIDE_CELL}; }

  std::string ToString() const override {
    std::string result = "(";
    if (first_) {
      result += first_->ToString();
    } else {
      result += "()";
    }
    result += UnwindObject(second_);
    return result;
  }

private:
  std::shared_ptr<Object> first_;
  std::shared_ptr<Object> second_;

  std::string UnwindObject(std::shared_ptr<Object> object) const {
    if (!object) {
      return ")";
    }

    std::string result;
    if (Is<Cell>(object)) {
      result += " ";
      std::shared_ptr<Object> first = std::dynamic_pointer_cast<Cell>(object)->GetFirst();
      if (first) {
        result += first->ToString();
      } else {
        result += "()";
      }
      result += UnwindObject(std::dynamic_pointer_cast<Cell>(object)->GetSecond());
      return result;
    } 

    result += " . ";
    result += object->ToString();
    result += ")";
    return result;
  }
};

#endif