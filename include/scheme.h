#ifndef SCHEME_H
#define SCHEME_H

#include <sstream>

class Scheme {
public:
  Scheme() = default;

  void REPL(std::istream& in);

private:

  std::string Evaluate(const std::string& expression);
};







#endif