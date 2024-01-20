#ifndef SRC_TOKENS_H_  //  SRC_TOKENS_H_
#define SRC_TOKENS_H_  //  SRC_TOKENS_H_

#include <functional>
#include <iostream>
#include <map>
#include <variant>

namespace s21 {

enum Type {
  kNumber,
  kBinaryOperator,
  kUnaryPrefixOperator,
  kUnaryFunction,
  kOpenBracket,
  kCloseBracket,
  kNumTokenTypes,
};

enum Precedence {
  kDefault,
  kLow,
  kMedium,
  kHigh,
  kUnaryOperator,
  kFunction,
};

enum Associativity {
  kNone,
  kLeft,
  kRight,
};

class Token {
 public:
  using unary_function = std::function<double(double)>;
  using binary_function = std::function<double(double, double)>;
  using function_variant =
      std::variant<double, unary_function, binary_function, nullptr_t>;

  Token() = default;
  Token(const std::string &name, Precedence precedence,
        Associativity associativity, Type type, function_variant function)
      : name_{name},
        precedence_{precedence},
        associativity_(associativity),
        type_(type),
        function_(function) {}
  ~Token() = default;

  /* Accessors */
  std::string GetName() { return name_; }
  Precedence GetPrecedence() { return precedence_; }
  Associativity GetAssociativity() { return associativity_; }
  Type GetType() { return type_; }
  function_variant GetFunction() { return function_; }

  void MakeNumber(std::string name, double value) {
    Token result(name, kDefault, kNone, kNumber, value);
    *this = result;
  }

  void MakeUnaryNegation() {
    Token result("negate", kUnaryOperator, kRight, kUnaryPrefixOperator,
                 std::negate<double>());
    *this = result;
  }

 private:
  std::string name_;
  Precedence precedence_;
  Associativity associativity_;
  Type type_;
  function_variant function_;
};

}  // namespace s21

#endif  //  SRC_TOKENS_H_
