#ifndef SRC_MODEL_MODEL_H_
#define SRC_MODEL_MODEL_H_

#include <algorithm>
#include <cmath>
#include <cstring>
#include <iostream>
#include <sstream>
#include <stack>
#include <string>

#define PI acos(-1)

namespace s21 {

class Model {
 public:
  Model() {}
  ~Model() {}
  double s21_smart_calc(std::string& str, double x);
  int validator(std::string& str);

 private:
  typedef enum {
    NONE = 0,
    NUM,
    SUM,
    SUB,
    MULT,
    DIV,
    MOD,
    COS,
    SIN,
    TAN,
    ACOS,
    ASIN,
    ATAN,
    LN,
    LOG,
    SQRT,
    POW,
    OPEN,
    CLOSED
  } lexeme_enum;

  typedef struct Lexeme {
    double value_;
    lexeme_enum type_;
  } Lexeme;
  std::stack<Lexeme> numbers_;
  std::stack<Lexeme> operations_;

  void func_parser(std::string& func, int* i, lexeme_enum* type);
  int get_priority(int type);
  lexeme_enum type_operation(char ch);
  int binary_operations(int oper, double* c);
  int func_operations(int oper, double* c);
  int calculations();
  void parser(std::string& str, double x);
  bool is_operation(char ch);
};

}  // namespace s21

#endif  // SRC_MODEL_MODEL_H_