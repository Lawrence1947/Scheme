#ifndef SCOPE_H
#define SCOPE_H

#include <string>
#include <memory>
#include <unordered_map>

#include <objects/object.h>
#include <error.h>

class Scope : public Object {
public:
  Scope() = default;

  void Cache(const std::string& name, std::shared_ptr<Object> object) {
    auto it = scope_.find(name);
    if (it != scope_.end()) {
      throw SyntaxError{ALREADY_DEFINED};
    }

    scope_.emplace(name, object);
  }

  void Rewrite(const std::string& name, std::shared_ptr<Object> object) {
    auto it = scope_.find(name);
    if (it == scope_.end()) {
      throw SyntaxError{NOT_YET_DEFINED};
    }

    it->second = object;
  }

  std::shared_ptr<Object> GetObject(const std::string& name) {
    auto it = scope_.find(name);
    if (it != scope_.end()) {
      return it->second;
    }
    return nullptr;
  }

  std::string ToString() const override { throw RuntimeError{}; }

  std::shared_ptr<Object> Apply([[maybe_unused]] const std::vector<std::shared_ptr<Object>> arguments, 
                                [[maybe_unused]] std::shared_ptr<Scope> scope) const { throw RuntimeError{NO_OVERRIDE_SCOPE}; }

private:
  std::unordered_map<std::string, std::shared_ptr<Object>> scope_;
};

#endif