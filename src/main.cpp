#include <iostream>
#include <fstream>
#include <sstream>

#include <scheme.h>
#include <globals.h>


int main(int argc, char const *argv[])
{
  Scheme scheme;
  if (argc > 1) {
    std::ifstream file(argv[FILE_NAME_ARGUMENT]);
    if (!file) {
      std::cerr << "Cannot open file: " << argv[FILE_NAME_ARGUMENT] << "\n";
      return FILE_OPEN_ERROR;
    }
    scheme.REPL(file);
  } else {
    scheme.REPL(std::cin);
  }

  return 0;
}
