#ifndef SRC_S21_CREDIT_CALC_H_  //  SRC_S21_CREDIT_CALC_H_
#define SRC_S21_CREDIT_CALC_H_  //  SRC_S21_CREDIT_CALC_H_

#include <cmath>
#include <string>

namespace s21 {

class Credit_Calc {
 public:
  Credit_Calc() {}
  ~Credit_Calc() {}

  void Calculate() { payment_type_ ? CalcAnnuitet() : CalcDiffer(); }
  void SetSumOfCredit(double sum) { sum_of_credit_ = sum; }
  void SetCreditTerm(int term) { credit_term_ = term; }
  void SetTermType(int time_choose) {
    !time_choose ? credit_term_ *= 12 : credit_term_;
  }
  void SetProcentRate(double rate) { this->rate_ = rate / 1200; }
  void SetPaymenType(bool annuitet) { payment_type_ = annuitet; }
  void clear();

  std::string GetMonthlyPay();
  std::string GetOverpay();
  std::string GetTotalPay();

 private:
  double monthly_payment_;
  double overpayment_;
  double total_payout_{0};
  double first_pay_;
  double last_pay_;

  double sum_of_credit_{0};
  int credit_term_{1};
  double rate_{0.01};
  bool payment_type_{1};

  void CalcAnnuitet();
  void CalcDiffer();
};

}  // namespace s21

#endif  //  SRC_S21_CREDIT_CALC_H_
