#ifndef OBJECT_H
#define OBJECT_H

#include <memory>


class Object : public std::enable_shared_from_this<Object> {
public:
  virtual ~Object() = default;
};

template <class T>
bool Is(const std::shared_ptr<Object>& obj) {
  return std::dynamic_pointer_cast<T>(obj) != nullptr;
}

#endif