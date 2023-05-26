#include "controller.h"
namespace s21 {
double Controller::Calculate(std::string& str, double x) {
  return this->model_.s21_smart_calc(str, x);
}
int Controller::Validate(std::string& str) {
  return this->model_.validator(str);
}
}  // namespace s21