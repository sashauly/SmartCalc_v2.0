#include "model.h"

namespace s21 {

bool Model::is_letter(const char ch) {
  return ((ch) >= 'a' && (ch) <= 'z') || ((ch) >= 'A' && (ch) <= 'Z');
}
bool Model::is_operation(char ch) {
  return ((ch) == '+' || (ch) == '-' || (ch) == '*' || (ch) == '/' ||
          (ch) == '^');
}

//  Проверка ошибок во входной строке
int Model::validator(std::string& str) {
  int error = 1;
  int i = 0;
  int open_sk = 0;
  int close_sk = 0;
  for (; str[i] != '\0' && str[i] != '\n' && error == 1; i++) {
    if (str[i] == '(') open_sk++;
    if (str[i] == ')') close_sk++;
    if ((str[i] == '(' && str[i + 1] == ')') ||
        (str[i] == ')' && str[i + 1] == '(') || (str[0] == ')') ||
        (is_operation(str[i]) && is_operation(str[i + 1]))) {
      error = 0;
      break;
    }
  }
  if (is_operation(str[i - 1])) error = 0;
  if ((open_sk != close_sk) || (str[i - 1]) == '(') error = 0;
  return error;
}
//  Возвращает тип функции, полученный путем парсинга строки
int Model::func_parser(std::string& func, int* i, lexeme_enum* type) {
  char dst[256] = {0};
  *type = NONE;
  int error = 0;
  int j = 0;

  while (is_letter(func[*i])) {
    dst[j] = func[*i];
    *i += 1;
    j++;
  }
  *i = *i - 1;

  if (!strcmp(dst, "cos")) {
    *type = COS;
  } else if (!strcmp(dst, "sin")) {
    *type = SIN;
  } else if (!strcmp(dst, "tan")) {
    *type = TAN;
  } else if (!strcmp(dst, "acos")) {
    *type = ACOS;
  } else if (!strcmp(dst, "asin")) {
    *type = ASIN;
  } else if (!strcmp(dst, "atan")) {
    *type = ATAN;
  } else if (!strcmp(dst, "sqrt")) {
    *type = SQRT;
  } else if (!strcmp(dst, "ln")) {
    *type = LN;
  } else if (!strcmp(dst, "log")) {
    *type = LOG;
  } else if (!strcmp(dst, "mod")) {
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
Model::lexeme_enum Model::type_operation(char ch) {
  lexeme_enum type = NONE;
  switch (ch) {
    case '+':
      type = SUM;
      break;
    case '-':
      type = SUB;
      break;
    case '*':
      type = MULT;
      break;
    case '/':
      type = DIV;
      break;
    case '^':
      type = POW;
      break;
  }
  return type;
}

//  Вычисление бинарных операций
int Model::binary_operations(int oper, double* c) {
  double a = 0, b = 0;
  *c = 0;
  int error = 0;
  a = numbers_.top().value_;
  numbers_.pop();
  b = numbers_.top().value_;
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
  a = numbers_.top().value_;
  numbers_.pop();
  switch (oper) {
    case COS:
      *c = cos(a);
      break;
    case SIN:
      *c = sin(a);
      break;
    case TAN:
      *c = tan(a);
      break;
    case ACOS:
      *c = acos(a);
      break;
    case ASIN:
      *c = asin(a);
      break;
    case ATAN:
      *c = atan(a);
      break;
    case LN:
      *c = log(a);
      break;
    case LOG:
      *c = log10(a);
      break;
    case SQRT:
      *c = sqrt(a);
      break;
    case POW:
      b = numbers_.top().value_;
      numbers_.pop();
      *c = pow(b, a);
      break;
  }
  return error;
}

//  Вычисление в зависимости от оператора в стеке
int Model::calculations() {
  double c = 0;
  int error = 0;
  int oper = operations_.top().type_;
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
void Model::parser(std::string& str, double x) {
  // Удаления пробелов из строки
  str.erase(remove(str.begin(), str.end(), ' '), str.end());

  for (int i = 0; i < (int)str.length(); i++) {
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
    } else if (isdigit(str[i])) {
      double number = 0.0;
      number = atof(&str[i]);
      std::ostringstream stream;
      stream << number;
      std::string value__str = stream.str();
      numbers_.push({number, NUM});
      i += value__str.length() - 1;
      continue;
      // Число PI
    } else if (str[i] == 'p') {
      numbers_.push({PI, NUM});
      continue;
      // x
    } else if (str[i] == 'x') {
      numbers_.push({x, NUM});
      continue;
      // Функция
    } else if (is_letter(str[i])) {
      lexeme_enum func_type = NONE;
      func_parser(str, &i, &func_type);
      operations_.push({0, func_type});
      continue;
      // Операнд
    } else if (is_operation(str[i])) {
      lexeme_enum type = type_operation(str[i]);
      if (operations_.empty()) {
        operations_.push({0, type});
        continue;
      }
      if (get_priority(type) > get_priority(operations_.top().type_)) {
        operations_.push({0, type});
        continue;
      } else {
        if (type == POW) {
          operations_.push({0, type});
          continue;
        }
        calculations();
        i--;
        continue;
      }
      // Открывающая скобка
    } else if (str[i] == '(') {
      operations_.push({0, OPEN});
      continue;
      // Закрывающая скобка
    } else if (str[i] == ')') {
      while (operations_.top().type_ != OPEN) {
        calculations();
      }
      operations_.pop();
      continue;
    }
  }
}

//  Основная функция SMART_CALC
double Model::s21_smart_calc(std::string& str, double x) {
  double result = 0;

  parser(str, x);
  while (!operations_.empty()) {
    calculations();
  }
  result = numbers_.top().value_;
  return result;
}

}  // namespace s21

// int main() {
//   s21::Model a;
//   std::string str = "2^2^3";
//   // 1+2*3^sin(0.4)^3*2+1
//   // 6.291162

//   // 1+2*3^sin(0.4)^56*2+1
//   // 6
//   double res;
//   if (a.validator(str)) {
//     res = a.s21_smart_calc(str, 0.0);
//   }
//   std::cout << res;
//   // 305045.5
//   return 0;
// }