#ifndef SRC_CONTROLLER_CONTROLLER_H_
#define SRC_CONTROLLER_CONTROLLER_H_

#include "../model/model.h"

namespace s21 {
class Controller {
 private:
  s21::Model model_;

 public:
  Controller() {}
  ~Controller() {}
  double calculate(std::string& str, double x);
  int validate(std::string& str);
};
}  // namespace s21

#endif  // SRC_CONTROLLER_CONTROLLER_H_