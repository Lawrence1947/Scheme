#ifndef TOKENIZER_H
#define TOKENIZER_H

#include <variant>
#include <string>
#include <memory>
#include <istream>

enum class BracketToken { OPEN, CLOSE };
struct SymbolToken { std::string name; };
struct ConstantToken { int value; };
struct QuoteToken {};
struct DotToken {};
struct NullToken {};

using Token = std::variant<BracketToken,
                          ConstantToken,
                          SymbolToken,
                          QuoteToken,
                          DotToken,

                          //Empty token
                          NullToken>;


class Tokenizer {
public:
  Tokenizer(std::istream* in) : in_(in) { Next(); }

  Token GetToken() const { return token_; }

  bool IsEnd() { return is_end_; }
  void Next();

  void DebugPrint();

private:
  std::istream* in_ = nullptr;
  Token token_ = NullToken{};
  bool is_end_ = false;

  void SkipSpaces();

  void TokenizeNumberOrName(int symbol);
  void TokenizeNumber(bool is_negative);
  void TokenizeName();
};


#endif