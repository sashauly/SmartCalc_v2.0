#include "model.h"

namespace s21 {

bool Model::is_number(char ch) { return ((ch) >= '0' && (ch) <= '9'); }
bool Model::is_letter(char ch) {
  return ((ch) >= 'a' && (ch) <= 'z') || ((ch) >= 'A' && (ch) <= 'Z');
}
bool Model::is_operation(char ch) {
  return ((ch) == '+' || (ch) == '-' || (ch) == '*' || (ch) == '/' ||
          (ch) == '^');
}

//  Проверка ошибок во входной строке
int Model::validator(std::string& str) {
  int error = 0;
  int i = 0;
  int open_sk = 0;
  int close_sk = 0;
  for (; str[i] != '\0' && str[i] != '\n' && error == 0; i++) {
    if (str[i] == '(') open_sk++;
    if (str[i] == ')') close_sk++;
    if ((str[i] == '(' && str[i + 1] == ')') ||
        (str[i] == ')' && str[i + 1] == '(') || (str[0] == ')') ||
        (is_operation(str[i]) && is_operation(str[i + 1]))) {
      error = 1;
      break;
    }
  }
  if (is_operation(str[i - 1])) error = 1;
  if ((open_sk != close_sk) || (str[i - 1]) == '(') error = 1;
  return error;
}
//  Возвращает тип функции, полученный путем парсинга строки
int Model::func_parser(std::string& dst, std::string& src, int* i,
                       lexeme_enum* type) {
  *type = NONE;
  int error = 0;
  int j = 0;

  while (is_letter(src[*i])) {
    dst[j] = src[*i];
    *i = *i + 1;
    j++;
  }
  *i = *i - 1;

  char dst_arr[dst.length() + 1];

  strcpy(dst_arr, dst.c_str());

  // std::string func_array[10] = {"cos",  "sin",  "tan", "acos", "asin",
  //                               "atan", "sqrt", "ln",  "log",  "mod"};

  if (!strcmp(dst_arr, "cos")) {
    *type = COS;
  } else if (!strcmp(dst_arr, "sin")) {
    *type = SIN;
  } else if (!strcmp(dst_arr, "tan")) {
    *type = TAN;
  } else if (!strcmp(dst_arr, "acos")) {
    *type = ACOS;
  } else if (!strcmp(dst_arr, "asin")) {
    *type = ASIN;
  } else if (!strcmp(dst_arr, "atan")) {
    *type = ATAN;
  } else if (!strcmp(dst_arr, "sqrt")) {
    *type = SQRT;
  } else if (!strcmp(dst_arr, "ln")) {
    *type = LN;
  } else if (!strcmp(dst_arr, "log")) {
    *type = LOG;
  } else if (!strcmp(dst_arr, "mod")) {
    *type = MOD;
  } else {
    error = 1;
  }
  return error;
}
//  Возвращает приоритет операции или функции
int Model::get_priority(int type) {
  int priority = 0;
  if (type == SUM || type == SUB)
    priority = 1;
  else if (type >= MULT && type <= MOD)
    priority = 2;
  else if (type == POW || type == SQRT)
    priority = 3;
  else if (type >= COS && type <= LOG)
    priority = 4;
  return priority;
}
//  Возвращает тип операции
lexeme_enum Model::type_operation(char ch) {
  lexeme_enum type = NONE;
  if ((ch) == '+') {
    type = SUM;
  } else if ((ch) == '-') {
    type = SUB;
  } else if ((ch) == '*') {
    type = MULT;
  } else if ((ch) == '/') {
    type = DIV;
  } else if ((ch) == '^') {
    type = POW;
  }
  return type;
}

//  Вычисление бинарных операций
int Model::binary_operations(int oper, double* c) {
  double a = 0, b = 0;
  *c = 0;
  int error = 0;
  a = numbers_.top().value;
  numbers_.pop();
  b = numbers_.top().value;
  numbers_.pop();
  switch (oper) {
    case SUM:
      *c = a + b;
      break;
    case SUB:
      *c = b - a;
      break;
    case MULT:
      *c = a * b;
      break;
    case DIV:
      if (a != 0) {
        *c = b / a;
      } else {
        error = 1;
      }
      break;
    case MOD:
      *c = fmod(b, a);
      break;
  }
  return error;
}
//  Вычисление функций
int Model::func_operations(int oper, double* c) {
  double a = 0, b = 0;
  *c = 0;
  int error = 0;
  a = numbers_.top().value;
  numbers_.pop();
  if (oper == COS) {
    *c = cos(a);
  } else if (oper == SIN) {
    *c = sin(a);
  } else if (oper == TAN) {
    *c = tan(a);
  } else if (oper == ACOS) {
    *c = acos(a);
  } else if (oper == ASIN) {
    *c = asin(a);
  } else if (oper == ATAN) {
    *c = atan(a);
  } else if (oper == LN) {
    *c = log(a);
  } else if (oper == LOG) {
    *c = log10(a);
  } else if (oper == SQRT) {
    *c = sqrt(a);
  } else if (oper == POW) {
    b = numbers_.top().value;
    numbers_.pop();
    *c = pow(b, a);
  }
  return error;
}

//  Вычисление в зависимости от оператора в стеке
int Model::calculations() {
  double c = 0;
  int error = 0;
  int oper = operations_.top().type;
  if (oper >= SUM && oper <= MOD) {
    error = binary_operations(oper, &c);
  } else if (oper >= COS && oper <= POW) {
    error = func_operations(oper, &c);
  }
  operations_.pop();
  if (error == 0) {
    numbers_.push({c, NUM});
  }
  return error;
}

//  Основной парсер строки
int Model::parser(std::string& str, double x) {
  int error = 0;
  int i = 0;
  while (i < (int)str.length()) {
    std::string tmp = {0};
    // Унарный минус
    if ((str[i] == '-' && i == 0) ||
        (i > 0 && str[i] == '-' && str[i - 1] == '(')) {
      numbers_.push({0, NUM});
      operations_.push({0, SUB});
      continue;
      // Унарный плюс
    } else if ((str[i] == '+' && i == 0) ||
               (i > 0 && str[i] == '+' && str[i - 1] == '(')) {
      numbers_.push({0, NUM});
      operations_.push({0, SUM});
      continue;
      // Число
    } else if (is_number(str[i])) {
      double number = 0.0;
      number = atof(&str[i]);
      std::ostringstream stream;
      stream << number;
      std::string value_str = stream.str();
      numbers_.push({number, NUM});
      i += value_str.length();
      continue;
      // Число PI
    } else if (str[i] == 'p') {
      numbers_.push({PI, NUM});
      i++;
      continue;
      // x
    } else if (str[i] == 'x') {
      numbers_.push({x, NUM});
      continue;
      // Функция
    } else if (is_letter(str[i])) {
      lexeme_enum func_type = NONE;
      error = func_parser(tmp, str, &i, &func_type);
      if (error == 0) {
        operations_.push({0, func_type});
        continue;
      } else {
        break;
      }
      // Операнд
    } else if (is_operation(str[i])) {
      lexeme_enum type = type_operation(str[i]);
      if (operations_.empty()) {
        operations_.push({0, type});
        continue;
      } else {
        if (get_priority(type) > get_priority(operations_.top().type)) {
          operations_.push({0, type});
          continue;
        } else {
          error = calculations();
          if (error == 0) {
            i--;
            continue;
          } else {
            break;
          }
        }
      }
      // Открывающая скобка
    } else if (str[i] == '(') {
      operations_.push({0, OPEN});
      continue;
      // Закрывающая скобка
    } else if (str[i] == ')') {
      while (operations_.top().type != OPEN) {
        error = calculations();
        if (error != 0) {
          break;
        }
      }
      operations_.pop();
      continue;
    } else {
      error = 1;
      break;
    }
  }
  return error;
}

//  Основная функция SMART_CALC
double Model::s21_smart_calc(std::string& str, double x) {
  double result = 0;
  int error = 0;

  // Удаления пробелов из строки
  // str.erase(remove(str.begin(), str.end(), ' '), str.end());

  error = parser(str, x);
  if (error == 0) {
    while (!operations_.empty()) {
      error = calculations();
      if (error != 0) {
        while (!operations_.empty()) {
          operations_.pop();
        }
        break;
      }
    }
    if (error == 0) {
      result = numbers_.top().value;
    }
    while (!numbers_.empty()) {
      numbers_.pop();
    }
  } else {
    while (!operations_.empty()) {
      operations_.pop();
    }
    while (!numbers_.empty()) {
      numbers_.pop();
    }
  }
  return !(error) ? result : error;
}

}  // namespace s21
int main() {
  s21::Model a;
  std::string str = "2+2";
  double res;
  if (a.validator(str)) {
    res = a.s21_smart_calc(str, 0.0);
  }
  std::cout << res;
  return 0;
}