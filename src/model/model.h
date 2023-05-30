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
    kNone = 0,
    kNum,
    kSum,
    kSub,
    kMult,
    kDiv,
    kMod,
    kCos,
    kSin,
    kTan,
    kAcos,
    kAsin,
    kAtan,
    kLn,
    kLog,
    kSqrt,
    kPow,
    kOpen,
    kClosed
  } LexemeEnum;

  typedef struct Lexeme {
    double value_;
    LexemeEnum type_;
  } Lexeme;

  std::stack<Lexeme> numbers_;
  std::stack<Lexeme> operations_;

  void FuncParser(std::string& func, int* i, LexemeEnum* type);
  int GetPriority(int type);
  LexemeEnum TypeOperation(char ch);
  void BinaryOperations(int oper, double* c);
  void FuncOperations(int oper, double* c);
  void Calculations();
  void Parser(std::string& str, double x);
  bool IsOperation(char ch);
};
}  // namespace s21

#endif  // SRC_MODEL_MODEL_H_