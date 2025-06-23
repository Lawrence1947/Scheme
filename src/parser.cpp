#include <parser.h>

#include <sstream>
#include <iostream>

#include <tokenizer.h>
#include <objects/object.h>
#include <objects/number.h>
#include <objects/symbol.h>
#include <objects/cell.h>
#include <objects/quote.h>
#include <objects/dot.h>
#include <error.h>

bool NextTokenIsNotOpenCell(Tokenizer* tokenizer);
std::shared_ptr<Object> ParseList(Tokenizer* tokenizer);

std::shared_ptr<Object> Parse(Tokenizer* tokenizer) {
  if (tokenizer->IsEnd()) { throw SyntaxError{}; }

  Token curr_token = tokenizer->GetToken();
  tokenizer->Next();

  if (auto* number = std::get_if<ConstantToken>(&curr_token)) {
    return std::make_shared<Number>(number->value);
  } 
  
  if (auto* identifier = std::get_if<SymbolToken>(&curr_token)) {
    return std::make_shared<Symbol>(identifier->name);
  } 
  
  if (auto* bracket = std::get_if<BracketToken>(&curr_token)) {
    if (*bracket == BracketToken::OPEN) {
      if (tokenizer->IsEnd()) { throw SyntaxError{}; }
      return ParseList(tokenizer);
    }
    return nullptr;
  } 
  
  if (std::get_if<QuoteToken>(&curr_token)) {
    return std::make_shared<Quote>();
  } 
  
  if (std::get_if<DotToken>(&curr_token)) {
    return std::make_shared<Dot>();
  }

  throw SyntaxError{};
  return nullptr;
}

std::shared_ptr<Object> ParseList(Tokenizer* tokenizer) {
  bool no_cell = NextTokenIsNotOpenCell(tokenizer);
  std::shared_ptr<Object> first = Parse(tokenizer);
  if (!first && no_cell) {
    return nullptr;
  }

  if (Is<Dot>(first)) {
    std::shared_ptr<Object> second = Parse(tokenizer);
    std::shared_ptr<Object> not_close_bracket = Parse(tokenizer);
    if (not_close_bracket) { throw SyntaxError{}; }
    return second;
  }

  return std::make_shared<Cell>(first, ParseList(tokenizer));
}

bool NextTokenIsNotOpenCell(Tokenizer* tokenizer) {
  Token token = tokenizer->GetToken();
  if (auto* bracket = std::get_if<BracketToken>(&token)) {
    if (*bracket == BracketToken::OPEN) {
      return false;
    }
  }
  return true;
}

// We have to copy string here in order to have correct shifting
void DebugPrintParsedList(std::shared_ptr<Object> list, std::string shift) {
  shift += "--";

  if (list == nullptr) {
    std::cout << shift << " " << "nullptr\n";
  }

  if (Is<Number>(list)) {
    std::cout << shift << " " << std::dynamic_pointer_cast<Number>(list)->GetValue() << "\n";
  }

  if (Is<Symbol>(list)) {
    std::cout << shift << " " << std::dynamic_pointer_cast<Symbol>(list)->GetName() << "\n";
  }

  if (Is<Cell>(list)) {
    std::shared_ptr<Cell> cell = std::dynamic_pointer_cast<Cell>(list);
    std::cout << shift << " " << "cell\n";
    DebugPrintParsedList(cell->GetFirst(), shift);
    DebugPrintParsedList(cell->GetSecond(), shift);
  }
}