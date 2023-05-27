#include "controller.h"
namespace s21 {
double Controller::Calculate(std::string& str, double x) {
  return this->model_.Calculator(str, x);
}
int Controller::Validate(std::string& str) {
  return this->model_.Validator(str);
}
}  // namespace s21
