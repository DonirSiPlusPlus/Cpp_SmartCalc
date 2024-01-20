#ifndef SRC_S21_CALCULATOR_H_  //  SRC_S21_CALCULATOR_H_
#define SRC_S21_CALCULATOR_H_  //  SRC_S21_CALCULATOR_H_

#include <cmath>
#include <limits>
#include <queue>
#include <stack>
#include <vector>

#include "tokens.h"

namespace s21 {

class Calculator {
 public:
  using XYGraph = std::pair<std::vector<long double>, std::vector<long double>>;

  Calculator() { CreateTokenMap(token_map_); }
  ~Calculator() { clear(); }

  void Calculate(std::string expression, long double x = NAN);
  void GraphCalculate(std::string expression);
  void clear();

  long double GetAnswer();
  std::string GetAnswerString();
  XYGraph GetGraph();

 private:
  std::string expression_{""};
  long double answer_{NAN};
  std::string answer_string{""};
  XYGraph answer_graph_;

  std::queue<Token> input_;
  std::stack<Token> stack_;
  std::queue<Token> output_;
  std::queue<Token> copy_output_;
  std::vector<long double> result_;
  std::vector<long double> copy_result_;

  std::map<std::string, Token> token_map_;

  /* Pars Methods */
  void validation();
  void CreateTokenMap(std::map<std::string, Token> &token_map);
  void ParsToTokens();
  void ReadWord(size_t &index);
  void ReadNumb(size_t &index);
  void ReadSymbol(size_t &index);
  void PushToTokens(std::string token);

  void ToPolishNotation();
  long double TryCalc(long double x_value = NAN);
};

}  // namespace s21

#endif  //  SRC_S21_CALCULATOR_H_
