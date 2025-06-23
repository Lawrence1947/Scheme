#ifndef CELL_H
#define CELL_H

#include <objects/object.h>


class Cell : public Object {
public:
  explicit Cell(std::shared_ptr<Object> first, std::shared_ptr<Object> second) : first_(std::move(first)), second_(std::move(second)) {}

  std::shared_ptr<Object> GetFirst() const { return first_; }
  std::shared_ptr<Object> GetSecond() const { return second_; }

private:
  std::shared_ptr<Object> first_;
  std::shared_ptr<Object> second_;
};



#endif