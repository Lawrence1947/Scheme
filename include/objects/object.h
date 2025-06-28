#ifndef OBJECT_H
#define OBJECT_H

#include <memory>
#include <string>
#include <vector>

class Scope;

class Object : public std::enable_shared_from_this<Object> {
public:
  virtual ~Object() = default;
  virtual std::string ToString() const = 0;
  virtual std::shared_ptr<Object> Apply(const std::vector<std::shared_ptr<Object>> arguments, std::shared_ptr<Scope> scope) const = 0;
};

template <class T>
bool Is(const std::shared_ptr<Object>& obj) {
  return std::dynamic_pointer_cast<T>(obj) != nullptr;
}

#endif 