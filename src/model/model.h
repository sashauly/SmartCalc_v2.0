#ifndef SRC_MODEL_MODEL_H_
#define SRC_MODEL_MODEL_H_

#include <cmath>
#include <cstring>
#include <iostream>
#include <sstream>
#include <stack>
#include <string>

#define PI acos(-1)

namespace s21 {
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

class Model {
 public:
  Model() {}
  ~Model() {}
  double s21_smart_calc(std::string& str, double x);
  int validator(std::string& str);

 private:
  typedef struct data_t {
    double value;
    lexeme_enum type;
  } data_t;
  std::stack<data_t> numbers_;
  std::stack<data_t> operations_;

  int func_parser(std::string& dst, std::string& src, int* i,
                  lexeme_enum* type);
  int get_priority(int type);
  lexeme_enum type_operation(char ch);
  int binary_operations(int oper, double* c);
  int func_operations(int oper, double* c);
  int calculations();
  int parser(std::string& str, double x);
  bool is_letter(char ch);
  bool is_operation(char ch);
  bool is_number(char ch);
};

}  // namespace s21

#endif  // SRC_MODEL_MODEL_H_