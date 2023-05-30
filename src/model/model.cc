#include "model.h"

namespace s21 {

bool Model::IsOperation(char ch) {
  return ((ch) == '+' || (ch) == '-' || (ch) == '*' || (ch) == '/' ||
          (ch) == '^') ||
         (ch) == '%';
}
int Model::Validator(std::string& str) {
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
    if (IsOperation(str[i])) {
      if (IsOperation(str[i + 1]) || (str[i + 1] == '.') ||
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
      if (str[i + 1] == '(' || IsOperation(str[i - 1])) {
        error = 0;
        break;
      }
    }
  }
  if (open_brackets != closed_brackets) error = 0;
  if (str[0] == '.' || str[0] == ',') error = 0;

  return error;
}
void Model::FuncParser(std::string& func, int* i, LexemeEnum* type = 0) {
  char tmp_str[256] = {};

  for (int j = 0; std::isalpha(func[*i]); *i += 1, j++) {
    tmp_str[j] = func[*i];
  }

  if (!strcmp(tmp_str, "cos")) {
    *type = kCos;
  } else if (!strcmp(tmp_str, "sin")) {
    *type = kSin;
  } else if (!strcmp(tmp_str, "tan")) {
    *type = kTan;
  } else if (!strcmp(tmp_str, "acos")) {
    *type = kAcos;
  } else if (!strcmp(tmp_str, "asin")) {
    *type = kAsin;
  } else if (!strcmp(tmp_str, "atan")) {
    *type = kAtan;
  } else if (!strcmp(tmp_str, "sqrt")) {
    *type = kSqrt;
  } else if (!strcmp(tmp_str, "ln")) {
    *type = kLn;
  } else if (!strcmp(tmp_str, "log")) {
    *type = kLog;
  }
}
int Model::GetPriority(int type) {
  int priority = 0;
  if (type == kSum || type == kSub)
    priority = 1;
  else if (type >= kMult && type <= kMod)
    priority = 2;
  else if (type == kPow || type == kSqrt)
    priority = 3;
  else if (type >= kCos && type <= kLog)
    priority = 4;
  return priority;
}
Model::LexemeEnum Model::TypeOperation(char ch) {
  LexemeEnum type = kNone;
  switch (ch) {
    case '+':
      type = kSum;
      break;
    case '-':
      type = kSub;
      break;
    case '*':
      type = kMult;
      break;
    case '/':
      type = kDiv;
      break;
    case '^':
      type = kPow;
      break;
    case '%':
      type = kMod;
      break;
  }
  return type;
}
void Model::BinaryOperations(int oper, double* c) {
  double a = 0, b = 0;
  *c = 0;
  a = numbers_.top().value_;
  numbers_.pop();
  b = numbers_.top().value_;
  numbers_.pop();
  switch (oper) {
    case kSum:
      *c = a + b;
      break;
    case kSub:
      *c = b - a;
      break;
    case kMult:
      *c = a * b;
      break;
    case kDiv:
      *c = b / a;
      break;
    case kMod:
      *c = std::fmod(b, a);
      break;
  }
}
void Model::FuncOperations(int oper, double* c) {
  double a = 0, b = 0;
  *c = 0;
  a = numbers_.top().value_;
  numbers_.pop();
  switch (oper) {
    case kCos:
      *c = std::cos(a);
      break;
    case kSin:
      *c = std::sin(a);
      break;
    case kTan:
      *c = std::tan(a);
      break;
    case kAcos:
      *c = std::acos(a);
      break;
    case kAsin:
      *c = std::asin(a);
      break;
    case kAtan:
      *c = std::atan(a);
      break;
    case kLn:
      *c = std::log(a);
      break;
    case kLog:
      *c = std::log10(a);
      break;
    case kSqrt:
      *c = sqrt(a);
      break;
    case kPow:
      b = numbers_.top().value_;
      numbers_.pop();
      *c = std::pow(b, a);
      break;
  }
}
void Model::Calculations() {
  double c = 0;
  int oper = operations_.top().type_;
  if (oper >= kSum && oper <= kMod) {
    BinaryOperations(oper, &c);
  } else if (oper >= kCos && oper <= kPow) {
    FuncOperations(oper, &c);
  }
  operations_.pop();
  numbers_.push({c, kNum});
}
void Model::Parser(std::string& str, double x) {
  str.erase(remove(str.begin(), str.end(), ' '), str.end());

  for (int i = 0; i < (int)str.length(); i++) {
    if ((str[i] == '-' && i == 0) ||
        (i > 0 && str[i] == '-' && str[i - 1] == '(')) {
      numbers_.push({0, kNum});
      operations_.push({0, kSub});
      continue;
    } else if ((str[i] == '+' && i == 0) ||
               (i > 0 && str[i] == '+' && str[i - 1] == '(')) {
      numbers_.push({0, kNum});
      operations_.push({0, kSum});
      continue;
    } else if (isdigit(str[i])) {
      double number = 0.0;
      number = atof(&str[i]);
      std::ostringstream stream;
      stream << number;
      std::string value__str = stream.str();
      numbers_.push({number, kNum});
      i += value__str.length() - 1;
      continue;
    } else if (str[i] == 'p') {
      numbers_.push({std::acos(-1), kNum});
      i++;
      continue;
    } else if (str[i] == 'x') {
      numbers_.push({x, kNum});
      continue;
    } else if (isalpha(str[i])) {
      LexemeEnum func_type = kNone;
      FuncParser(str, &i, &func_type);
      operations_.push({0, func_type});
      i--;
      continue;
    } else if (IsOperation(str[i])) {
      LexemeEnum type = TypeOperation(str[i]);
      if (operations_.empty()) {
        operations_.push({0, type});
        continue;
      }
      if (GetPriority(type) > GetPriority(operations_.top().type_)) {
        operations_.push({0, type});
        continue;
      } else {
        if (type == kPow) {
          operations_.push({0, type});
          continue;
        }
        Calculations();
        i--;
        continue;
      }
    } else if (str[i] == '(') {
      operations_.push({0, kOpen});
      continue;
    } else if (str[i] == ')') {
      while (operations_.top().type_ != kOpen) {
        Calculations();
      }
      operations_.pop();
      continue;
    }
  }
}
double Model::Calculator(std::string& str, double x) {
  double result = 0;
  Parser(str, x);
  while (!operations_.empty()) {
    Calculations();
  }
  result = numbers_.top().value_;
  return result;
}

}  // namespace s21
