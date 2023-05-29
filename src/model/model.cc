#include "model.h"

namespace s21 {

bool Model::isOperation(char ch) {
  return ((ch) == '+' || (ch) == '-' || (ch) == '*' || (ch) == '/' ||
          (ch) == '^') ||
         (ch) == '%';
}

//  Проверка ошибок во входной строке
int Model::validator(std::string& str) {
  int error = 1;
  int open_brackets = 0;
  int closed_brackets = 0;
  int count_dot = 0;
  int str_size = (int)str.size();

  for (int i = 0; i < str_size; i++) {
    if (isdigit(str[i])) {
      for (; isdigit(str[i]) || str[i] == '.'; i++) {
        if (str[i] == ',') str[i] = '.';
        if (str[i] == '.') count_dot++;
      }
      if (count_dot > 1) {
        error = 0;
        break;
      }
      count_dot = 0;
    }
    if (isOperation(str[i])) {
      if (isOperation(str[i + 1]) || (str[i + 1] == '.') ||
          (str[i + 1] == ',') || i == str_size - 1 ||
          (i == 0 && str[i] != '+' && str[i] != '-')) {
        error = 0;
        break;
      }
    }
    if (str[i] == '(') {
      open_brackets++;
      if (str[i + 1] == ')') {
        error = 0;
        break;
      }
    }
    if (str[i] == ')') {
      closed_brackets++;
      if (str[i + 1] == '(' || isOperation(str[i - 1])) {
        error = 0;
        break;
      }
    }
  }
  if (open_brackets != closed_brackets) error = 0;
  if (str[0] == '.' || str[0] == ',') error = 0;

  return error;
}
//  Возвращает тип функции, полученный путем парсинга строки
void Model::funcParser(std::string& func, int* i, lexeme_enum* type = 0) {
  char tmp_str[256] = {};

  for (int j = 0; std::isalpha(func[*i]); *i += 1, j++) {
    tmp_str[j] = func[*i];
  }

  if (!strcmp(tmp_str, "cos")) {
    *type = COS;
  } else if (!strcmp(tmp_str, "sin")) {
    *type = SIN;
  } else if (!strcmp(tmp_str, "tan")) {
    *type = TAN;
  } else if (!strcmp(tmp_str, "acos")) {
    *type = ACOS;
  } else if (!strcmp(tmp_str, "asin")) {
    *type = ASIN;
  } else if (!strcmp(tmp_str, "atan")) {
    *type = ATAN;
  } else if (!strcmp(tmp_str, "sqrt")) {
    *type = SQRT;
  } else if (!strcmp(tmp_str, "ln")) {
    *type = LN;
  } else if (!strcmp(tmp_str, "log")) {
    *type = LOG;
  }
}
//  Возвращает приоритет операции или функции
int Model::getPriority(int type) {
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
Model::lexeme_enum Model::typeOperation(char ch) {
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
    case '%':
      type = MOD;
      break;
  }
  return type;
}

//  Вычисление бинарных операций
void Model::binaryOperations(int oper, double* c) {
  double a = 0, b = 0;
  *c = 0;
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
      *c = b / a;
      break;
    case MOD:
      *c = fmod(b, a);
      break;
  }
}
//  Вычисление функций
void Model::funcOperations(int oper, double* c) {
  double a = 0, b = 0;
  *c = 0;
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
}
//  Вычисление в зависимости от оператора в стеке
void Model::calculations() {
  double c = 0;
  int oper = operations_.top().type_;
  if (oper >= SUM && oper <= MOD) {
    binaryOperations(oper, &c);
  } else if (oper >= COS && oper <= POW) {
    funcOperations(oper, &c);
  }
  operations_.pop();
  numbers_.push({c, NUM});
}

//  Основной парсер строки
void Model::Parser(std::string& str, double x) {
  str.erase(remove(str.begin(), str.end(), ' '), str.end());

  for (int i = 0; i < (int)str.length(); i++) {
    if ((str[i] == '-' && i == 0) ||
        (i > 0 && str[i] == '-' && str[i - 1] == '(')) {
      numbers_.push({0, NUM});
      operations_.push({0, SUB});
      continue;
    } else if ((str[i] == '+' && i == 0) ||
               (i > 0 && str[i] == '+' && str[i - 1] == '(')) {
      numbers_.push({0, NUM});
      operations_.push({0, SUM});
      continue;
    } else if (isdigit(str[i])) {
      double number = 0.0;
      number = atof(&str[i]);
      std::ostringstream stream;
      stream << number;
      std::string value__str = stream.str();
      numbers_.push({number, NUM});
      i += value__str.length() - 1;
      continue;
    } else if (str[i] == 'p') {
      numbers_.push({std::acos(-1), NUM});
      i++;
      continue;
    } else if (str[i] == 'x') {
      numbers_.push({x, NUM});
      continue;
    } else if (isalpha(str[i])) {
      lexeme_enum func_type = NONE;
      funcParser(str, &i, &func_type);
      operations_.push({0, func_type});
      i--;
      continue;
    } else if (isOperation(str[i])) {
      lexeme_enum type = typeOperation(str[i]);
      if (operations_.empty()) {
        operations_.push({0, type});
        continue;
      }
      if (getPriority(type) > getPriority(operations_.top().type_)) {
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
double Model::calculator(std::string& str, double x) {
  double result = 0;

  Parser(str, x);
  while (!operations_.empty()) {
    calculations();
  }
  result = numbers_.top().value_;
  return result;
}

}  // namespace s21
