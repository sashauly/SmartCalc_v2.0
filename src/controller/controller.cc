#include "controller.h"
namespace s21 {
double Controller::calculate(std::string& str, double x) {
  return this->model_.calculator(str, x);
}
int Controller::validate(std::string& str) {
  return this->model_.validator(str);
}
}  // namespace s21
