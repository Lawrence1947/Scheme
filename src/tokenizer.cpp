#include <tokenizer.h>

#include <iostream>
#include <cctype>
#include <cstring>


void Tokenizer::SkipSpaces() {
  while (std::isspace(in_->peek())) in_->get();
}

void Tokenizer::TokenizeNumber(bool is_negative) {
  std::string number_str;
  if (is_negative) {
    in_->get();
    number_str += '-';
  }

  while (std::isdigit(in_->peek())) {
    number_str += static_cast<char>(in_->get());
  }

  token_ = ConstantToken{atoi(number_str.c_str())};
}

void Tokenizer::TokenizeName() {
  std::string name_str;
  while (std::isalpha(in_->peek()) || strchr("-+!$%&*/:<=>?^_~", in_->peek())) {
    name_str += static_cast<char>(in_->get());
  }

  token_ = SymbolToken{name_str};
}

void Tokenizer::TokenizeNumberOrName(int symbol) {
  if (symbol == '-') {
    in_->get();
    if (std::isdigit(in_->peek())) {
      in_->unget();
      TokenizeNumber(true /*is_negative*/);
    } else {
      in_->unget();
      TokenizeName();
    }
  } else if (std::isdigit(symbol)) {
    TokenizeNumber(false /*is_negative*/);
  } else {
    TokenizeName();
  }
}

void Tokenizer::Next() {
  if (is_end_) return;
  if (!in_ || in_->eof() || in_->peek() == EOF) {
    token_ = NullToken{};
    is_end_ = true;
  }

  SkipSpaces();

  int symbol = in_->peek();
  if (symbol == EOF) {
    token_ = NullToken{};
    is_end_ = true;
  }

  if (symbol == '(') {
    in_->get();
    token_ = BracketToken::OPEN;
  } else if (symbol == ')') {
    in_->get();
    token_ = BracketToken::CLOSE;
  } else if (symbol == '.') {
    in_->get();
    token_ = DotToken{};
  } else if (symbol == '\'') {
    in_->get();
    token_ = QuoteToken{};
  } else {
    TokenizeNumberOrName(symbol);
  }
}


void Tokenizer::DebugPrint() {
  while (!IsEnd()) {
    Token token = GetToken();
    Next();

    if (auto* number = std::get_if<ConstantToken>(&token)) {
      std::cout << number->value << "\n";
    } else if (auto* identifier = std::get_if<SymbolToken>(&token)) {
      std::cout << identifier->name << "\n";
    } else if (auto* bracket = std::get_if<BracketToken>(&token)) {
      if (*bracket == BracketToken::OPEN) {
        std::cout << "(\n";
      } else {
        std::cout << ")\n";
      }
    } else if (std::get_if<QuoteToken>(&token)) {
      std::cout << "\'\n";
    } else if (std::get_if<DotToken>(&token)) {
      std::cout << ".\n";
    }
  }
}