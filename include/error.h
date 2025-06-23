#ifndef ERROR_H
#define ERROR_H

#include <stdexcept>

class SyntaxError : public std::runtime_error {
public:
  SyntaxError() : std::runtime_error{"Syntax error.\n"} {}
};

class RuntimeError : public std::runtime_error {
public:
  RuntimeError() : std::runtime_error{"Unkown runtime error.\n"} {}
};

class NameError : public std::runtime_error {
public:
  explicit NameError(const std::string& name) : std::runtime_error{"Name not found: " + name} {}
};


#endif