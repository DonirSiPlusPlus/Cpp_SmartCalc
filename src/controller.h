#ifndef CONTROLLER_H
#define CONTROLLER_H

#include <QMainWindow>

#include "graph.h"
#include "s21_calculator.h"
#include "s21_credit_calc.h"

class controller {
 public:
  controller() {}
  ~controller() { model_.clear(); }

  void CalculateExression(QString str, double x) {
    model_.Calculate(str.toStdString(), x);
  }
  void GraphCalculate(QString str) { model_.GraphCalculate(str.toStdString()); }
  std::vector<long double> GetXVector() { return model_.GetGraph().first; }
  std::vector<long double> GetYVector() { return model_.GetGraph().second; }

  QString GetAnswer() {
    return QString::fromStdString(model_.GetAnswerString());
  }

  /* Кредитный калькулятор */
  void CalculateCredit() { credit_model_.Calculate(); }
  void SetSumOfCredit(double sum) { credit_model_.SetSumOfCredit(sum); }
  void SetCreditTerm(int term) { credit_model_.SetCreditTerm(term); }
  void SetProcentRate(double rate) { credit_model_.SetProcentRate(rate); }
  void SetTermType(int time_choose) { credit_model_.SetTermType(time_choose); }
  void SetPaymenType(bool annuitet) { credit_model_.SetPaymenType(annuitet); }
  void clear() { credit_model_.clear(); }

  std::string GetMonthlyPay() { return credit_model_.GetMonthlyPay(); }
  std::string GetOverpay() { return credit_model_.GetOverpay(); }
  std::string GetTotalPay() { return credit_model_.GetTotalPay(); }

 private:
  QString expression_;
  s21::Calculator model_;
  s21::Credit_Calc credit_model_;
};

#endif  // CONTROLLER_H
