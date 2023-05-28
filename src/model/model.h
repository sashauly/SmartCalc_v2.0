#ifndef SRC_MODEL_MODEL_H_
#define SRC_MODEL_MODEL_H_

#include <algorithm>
#include <cmath>
#include <cstring>
#include <iostream>
#include <sstream>
#include <stack>
#include <string>

namespace s21 {

class Model {
 public:
  Model() {}
  ~Model() {}
  double Calculator(std::string& str, double x = 0.0);
  int Validator(std::string& str);

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

  void funcParser(std::string& func, int* i, lexeme_enum* type);
  int getPriority(int type);
  lexeme_enum typeOperation(char ch);
  int binaryOperations(int oper, double* c);
  int funcOperations(int oper, double* c);
  int Calculations();
  void Parser(std::string& str, double x);
  bool isOperation(char ch);
};

}  // namespace s21

#endif  // SRC_MODEL_MODEL_H_