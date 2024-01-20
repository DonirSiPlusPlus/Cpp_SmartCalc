#include "s21_calculator.h"

#include <ctype.h>

#include <type_traits>

template <class... Ts>
struct overloaded : Ts... {
  using Ts::operator()...;
};

template <class... Ts>
overloaded(Ts...) -> overloaded<Ts...>;

/* Вычисление */
void s21::Calculator::Calculate(std::string expression, long double x) {
  this->expression_ = expression;
  validation();
  ParsToTokens();
  ToPolishNotation();
  answer_ = TryCalc(x);
}

/* Вычисление точек вектора */
void s21::Calculator::GraphCalculate(std::string expression) {
  if (!expression.empty()) {
    clear();
    this->expression_ = expression;
    validation();
    ParsToTokens();
    ToPolishNotation();
  }
  std::vector<long double> x_values, y_values;
  double step{20. / 10000}, X_point{-10};
  copy_output_ = output_;
  copy_result_ = result_;
  for (size_t i{0}; i < 10000; ++i) {
    x_values.push_back(X_point);
    long double Y_point = TryCalc(x_values.back());

    if (std::isnan(Y_point) || Y_point == INFINITY || Y_point == -INFINITY ||
        Y_point >= 10) {
      y_values.push_back(std::numeric_limits<long double>::quiet_NaN());
    } else {
      y_values.push_back(Y_point);
    }

    output_ = copy_output_;
    result_ = copy_result_;
    X_point += step;
  }
  answer_graph_ = std::make_pair(x_values, y_values);
}

/* Создает список токенов */
void s21::Calculator::CreateTokenMap(
    std::map<std::string, s21::Token> &token_map) {
  using std::initializer_list;
  using std::pair;
  using std::string;
  using namespace s21;
  initializer_list<pair<const string, Token>> list = {
      {" ", Token("space", kDefault, kNone, kNumber, nullptr)},
      {"x", Token("x", kDefault, kNone, kNumber, nullptr)},
      {"(", Token("(", kDefault, kNone, kOpenBracket, nullptr)},
      {")", Token(")", kDefault, kNone, kCloseBracket, nullptr)},
      {"+", Token("+", kLow, kLeft, kBinaryOperator, std::plus<double>())},
      {"-", Token("-", kLow, kLeft, kBinaryOperator, std::minus<double>())},
      {"*",
       Token("*", kMedium, kLeft, kBinaryOperator, std::multiplies<double>())},
      {"/",
       Token("/", kMedium, kLeft, kBinaryOperator, std::divides<double>())},
      {"^", Token("^", kHigh, kRight, kBinaryOperator, powl)},
      {"mod", Token("mod", kMedium, kLeft, kBinaryOperator, fmodl)},
      {"cos", Token("cos", kFunction, kRight, kUnaryFunction, cosl)},
      {"sin", Token("sin", kFunction, kRight, kUnaryFunction, sinl)},
      {"tan", Token("tan", kFunction, kRight, kUnaryFunction, tanl)},
      {"acos", Token("acos", kFunction, kRight, kUnaryFunction, acosl)},
      {"asin", Token("asin", kFunction, kRight, kUnaryFunction, asinl)},
      {"atan", Token("atan", kFunction, kRight, kUnaryFunction, atanl)},
      {"sqrt", Token("sqrt", kFunction, kRight, kUnaryFunction, sqrtl)},
      {"ln", Token("ln", kFunction, kRight, kUnaryFunction, logl)},
      {"log", Token("log", kFunction, kRight, kUnaryFunction, log10l)},
  };
  token_map.insert(list);
}

/* Разбивает выражение на токены */
void s21::Calculator::ParsToTokens() {
  for (size_t i{0}; expression_[i] && i < expression_.size();) {
    if (isalpha(expression_[i])) {
      ReadWord(i);
    } else if (isdigit(expression_[i])) {
      ReadNumb(i);
    } else {
      ReadSymbol(i);
    }
  }
}

/* Превращает слово в токен */
void s21::Calculator::ReadWord(size_t &index) {
  std::string symbs{"acdgosnqrltmi"};
  size_t start_i{index};
  while (expression_[index] && index < expression_.size() &&
         symbs.find(expression_[index]) != std::string::npos) {
    ++index;
    if (expression_[index] == 'd') {
      ++index;
      break;
    }
  }
  expression_[index] == 'x' && start_i == index ? ++index : index;
  PushToTokens(expression_.substr(start_i, index - start_i));
  if (expression_[index - 1] == 'x') {
    if (expression_[index] == '(' || isdigit(expression_[index]) ||
        (isalpha(expression_[index]) && expression_[index] != 'm') ||
        expression_[index] == 'x') {
      PushToTokens("*");
    }
  }
}

/* Превращает число в токен */
void s21::Calculator::ReadNumb(size_t &index) {
  size_t start_i = index;
  char c_numb[100] = "";
  long double numb = std::stold(expression_.substr(index));
  std::sprintf(c_numb, "%.15Lf", numb);
  if (expression_[index] == '-' || expression_[index] == '+') ++index;

  while (expression_[index] &&
         (isdigit(expression_[index]) || expression_[index] == '.')) {
    ++index;
  }
  if (expression_[index] == 'e') {
    ++index;
    expression_[index] == '-' || expression_[index] == '+' ? ++index : index;
    while (expression_[index] && isdigit(expression_[index])) {
      ++index;
    }
  }
  Token t_numb;
  t_numb.MakeNumber(expression_.substr(start_i, index - start_i), numb);
  input_.push(t_numb);
  if (expression_[index] == '(' ||
      (isalpha(expression_[index]) && expression_[index] != 'm') ||
      expression_[index] == 'x') {
    PushToTokens("*");
  }
}

/* Превращает символ в токен */
void s21::Calculator::ReadSymbol(size_t &index) {
  if (expression_[index] == '-' || expression_[index] == '+') {
    if (!index || expression_[index - 1] == '(') {
      Token unar_sign;
      if (expression_[index] == '-') {
        unar_sign.MakeUnaryNegation();
        input_.push(unar_sign);
      }
    } else {
      PushToTokens(expression_.substr(index, 1));
    }
  } else {
    PushToTokens(expression_.substr(index, 1));
  }
  ++index;
  if (expression_[index - 1] == ')') {
    if (expression_[index] == '(' || isdigit(expression_[index]) ||
        (isalpha(expression_[index]) && expression_[index] != 'm') ||
        expression_[index] == 'x') {
      PushToTokens("*");
    }
  }
}

/* Добавляет токен в очередь токенов */
void s21::Calculator::PushToTokens(std::string token) {
  auto token_map_it = token_map_.find(token);
  if (token_map_it == token_map_.end()) {
    throw std::logic_error("Incorrect symbol: " + token);
  }

  input_.push(token_map_it->second);
}

/* Валидация выражения */
void s21::Calculator::validation() {
  auto iter = expression_.begin();
  auto iter_end = expression_.end();

  if (expression_.empty() || !expression_.size()) throw std::logic_error("");

  int brackets{0};
  std::string first_symb{"/*.^)m"};
  if (first_symb.find(*iter) != std::string::npos)
    throw std::logic_error("Incorrect first symbol");

  std::string ops{"-+*/^(d"};
  while (iter != iter_end) {
    (*iter == ')') ? --brackets : brackets;
    if (brackets < 0) {
      throw std::logic_error("Incorrect bracket");
    }
    if (*iter == '(') {
      (iter + 1 == iter_end) ? throw std::logic_error("Incorrect bracket")
                             : ++brackets;
    }
    if (ops.find(*iter) != std::string::npos &&
        std::string("*/^)").find(*(iter + 1)) != std::string::npos) {
      throw std::logic_error("Incorrect operators");
    }
    ++iter;
    int points{0};
    while (iter != iter_end && (isdigit(*iter) || *iter == '.')) {
      (*iter++ == '.') ? ++points : points;
    }
    if (points > 1) {
      throw std::logic_error("Incorrect numb");
    }
  }
  if (ops.find(*(expression_.end() - 1)) != ops.npos ||
      (expression_.back() != 'x' && isalpha(expression_.back()))) {
    throw std::logic_error("Incorrect last symbol");
  }
  while (brackets--) {
    expression_ += ')';
  }
}

/* Алгоритм Дейкстры */
void s21::Calculator::ToPolishNotation() {
  for (; !input_.empty(); input_.pop()) {
    Token i = input_.front();
    switch (i.GetType()) {
      case Type::kUnaryPrefixOperator:
        stack_.push(i);
        break;
      case Type::kNumber:
        output_.push(i);
        break;
      case Type::kUnaryFunction:
      case Type::kOpenBracket:
        stack_.push(i);
        break;
      case Type::kBinaryOperator: {
        while (!stack_.empty() &&
               (stack_.top().GetPrecedence() > i.GetPrecedence() ||
                (stack_.top().GetPrecedence() == i.GetPrecedence() &&
                 i.GetAssociativity() == Associativity::kLeft))) {
          output_.push(stack_.top());
          stack_.pop();
        }
        stack_.push(i);
        break;
      }
      case Type::kCloseBracket: {
        while (true) {
          if (stack_.empty()) {
            throw std::logic_error("Incorrect brackets");
          } else if (stack_.top().GetType() == Type::kOpenBracket) {
            stack_.pop();
            break;
          } else {
            output_.push(stack_.top());
            stack_.pop();
          }
        }
        if (!stack_.empty() && stack_.top().GetType() == Type::kUnaryFunction) {
          output_.push(stack_.top());
          stack_.pop();
        }
        break;
      }
      default:
        break;
    }
  }
  while (!stack_.empty()) {
    output_.push(stack_.top());
    stack_.pop();
  }
}

/* Вычисление выражения */
long double s21::Calculator::TryCalc(long double x_value) {
  while (!output_.empty()) {
    std::visit(overloaded{[&](double numb) { result_.push_back(numb); },
                          [&](s21::Token::unary_function function) {
                            long double arg{function(result_.back())};
                            result_.pop_back();
                            result_.push_back(arg);
                          },
                          [&](s21::Token::binary_function function) {
                            long double arg2{result_.back()};
                            result_.pop_back();
                            long double arg1{result_.back()};
                            result_.pop_back();
                            result_.push_back(function(arg1, arg2));
                          },
                          [&](auto) { result_.push_back(x_value); }},
               output_.front().GetFunction());
    output_.pop();
  }
  return result_.back();
}

/* Возвращает ответ в виде double */
long double s21::Calculator::GetAnswer() { return answer_; }

/* Возвращает ответ в строчном виде */
std::string s21::Calculator::GetAnswerString() {
  if (answer_ != answer_) return "nan";

  if (answer_ == INFINITY) return "INF";

  if (answer_ == -INFINITY) return "-INF";

  answer_string = std::to_string(answer_);

  for (size_t i = answer_string.size() - 1; answer_string[i] == '0'; --i) {
    answer_string.pop_back();
  }

  if (answer_string.back() == '.') answer_string.pop_back();

  return answer_string;
}

/* Возвращает вектора для графа */
s21::Calculator::XYGraph s21::Calculator::GetGraph() { return answer_graph_; }

void s21::Calculator::clear() {
  result_.clear();
  expression_.clear();

  while (!input_.empty()) input_.pop();

  while (!output_.empty()) output_.pop();

  while (!stack_.empty()) stack_.pop();
}
