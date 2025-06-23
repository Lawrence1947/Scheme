#ifndef PARSER_H
#define PARSER_H

#include <objects/object.h>
#include <tokenizer.h>

std::shared_ptr<Object> Parse(Tokenizer* tokenizer);
void DebugPrintParsedList(std::shared_ptr<Object> list, std::string shift = {});

#endif