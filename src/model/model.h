#ifndef SRC_MODEL_MODEL_H_
#define SRC_MODEL_MODEL_H_

#include <cmath>
#include <iostream>
#include <stack>
#include <string>

namespace s21 {

typedef enum {
  NUM = 1,
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

typedef struct data_t {
  double value;
  lexeme_enum type;
} data_t;

class Model {
 public:
  Model();
  ~Model();
  int s21_smart_calc(char* src, double x, double* result);

 private:
  std::stack<data_t> numbers;
  std::stack<data_t> operations;

#define PI acos(-1)

#define is_number(ch) ((ch) >= '0' && (ch) <= '9')
#define is_letter(ch) \
  ((ch) >= 'a' && (ch) <= 'z') || ((ch) >= 'A' && (ch) <= 'Z')
#define is_operation(ch) \
  ((ch) == '+' || (ch) == '-' || (ch) == '*' || (ch) == '/' || (ch) == '^')

  void remove_spaces(char* src, char* dst);
  int validator(char* str);
  int number_parser(char* dst, char* src, int* i, double* number);
  int func_parser(char* dst, char* src, int* i, int* type);
  int get_priority(int type);
  int type_operation(char ch);
  int binary_operations(struct stack** stack_n, int oper, double* c);
  int func_operations(struct stack** stack_n, int oper, double* c);
  int calculations(struct stack** stack_n, struct stack** stack_o,
                   data_t* data);
  int parser(char* str, struct stack** stack_n, struct stack** stack_o,
             data_t* data, double x);
};

}  // namespace s21

#endif  // SRC_MODEL_MODEL_H_