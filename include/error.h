#ifndef ERROR_H
#define ERROR_H

#include <stdexcept>

// Syntax errors
#define UNFINISHED_EXPRESSION "Control flow reaches the end of unfinished expression.\n"
#define NOT_ENOUGH_ARGUMENTS "Too few arguments to call function.\n"
#define TOO_MANY_ARGUMENTS "Too many arguments to call function.\n"
#define INVALID_TYPE "Invalid type of arguments to call function.\n"
#define ALREADY_DEFINED "Object has already defined.\n"
#define NOT_YET_DEFINED "Object is not defined.\n"
#define IF_SYNTAX "Invalid if-statement syntax.\n"

// Runtime errors
#define FPE "Floating point exception.\n"
#define EVAL_OBJECT "Couldn't evaluate specific object.\n"
#define NO_OVERRIDE_SYMBOL "Symbol apply function shouldn't be called.\n"
#define NO_OVERRIDE_NUMBER "Number apply function shouldn't be called.\n"
#define NO_OVERRIDE_SCOPE "Scope apply function shouldn't be called.\n"
#define NO_OVERRIDE_BOOL "Bool apply function shouldn't be called.\n"
#define NO_OVERRIDE_CELL "Cell apply function shouldn't be called.\n"

class SyntaxError : public std::runtime_error {
public:
  SyntaxError() : std::runtime_error{"Unkonw syntax error.\n"} {}
  SyntaxError(const std::string& name) : std::runtime_error{name} {}
};

class RuntimeError : public std::runtime_error {
public:
  RuntimeError() : std::runtime_error{"Unkown runtime error.\n"} {}
  RuntimeError(const std::string& name) : std::runtime_error{name} {}
};

class NameError : public std::runtime_error {
public:
  explicit NameError(const std::string& name) : std::runtime_error{"Name not found: " + name + "\n"} {}
};


#endif