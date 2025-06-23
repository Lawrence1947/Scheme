#ifndef NUMBER_H
#define NUMBER_H

#include <objects/object.h>


class Number : public Object {
public:
  explicit Number(int value) : value_(value) {}

  int GetValue() const { return value_; }

private:
  int value_;
};


#endif