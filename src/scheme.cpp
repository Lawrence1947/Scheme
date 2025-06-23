#include <scheme.h>

#include <iostream>
#include <sstream>

#include <tokenizer.h>
#include <objects/object.h>
#include <parser.h>


void Scheme::REPL(std::istream& in) {
  std::string expression;
  std::cout << "Scheme 1.0.0\n";
  std::cout << "This program is free software, and you are welcome to redistribute it.\n\n";

  while (in) {
    std::cout << ">>> ";
    std::getline(in, expression);
    if (expression.empty()) {
      continue;
    }

    try {
      std::cout << Evaluate(expression);
    } catch (const std::runtime_error& ex) {
      std::cout << ex.what();
    }

    std::cout << "\n";
  }
}

std::string Scheme::Evaluate(const std::string& expression) {
  std::istringstream in(expression);
  Tokenizer tokenizer(&in);

  std::shared_ptr<Object> list = Parse(&tokenizer);
  if (Is<Object>(list)) {
    std::cout << "Object\n";
  } else {
    std::cout << "Not an Object\n"; 
  }

  DebugPrintParsedList(list);
  std::cout << tokenizer.IsEnd() << "\n";

  return {};
}



