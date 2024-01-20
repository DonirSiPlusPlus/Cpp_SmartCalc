#include "s21_credit_calc.h"

/* Вычисления для аннуитетного платежа */
void s21::Credit_Calc::CalcAnnuitet() {
  monthly_payment_ = round(sum_of_credit_ *
                           (rate_ / (1 - pow(1 + rate_, -credit_term_))) * 100);
  monthly_payment_ /= 100;
  overpayment_ = monthly_payment_ * credit_term_ - sum_of_credit_;
  total_payout_ = overpayment_ + sum_of_credit_;
}

/* Вычисления для дифференцировоного платежа */
void s21::Credit_Calc::CalcDiffer() {
  monthly_payment_ = sum_of_credit_ / credit_term_;
  first_pay_ = round((monthly_payment_ + sum_of_credit_ * rate_) * 100) / 100;
  for (int i{0}; i < credit_term_; ++i) {
    last_pay_ = round((monthly_payment_ +
                       (sum_of_credit_ - monthly_payment_ * i) * rate_) *
                      100) /
                100;
    total_payout_ += last_pay_;
  }
}

/* Возвращает ежемесячный платеж */
std::string s21::Credit_Calc::GetMonthlyPay() {
  char pay_str[255] = "";
  if (payment_type_) {
    std::sprintf(pay_str, "%.2lf", monthly_payment_);
  } else {
    std::sprintf(pay_str, "%.2lf ... %.2lf", first_pay_, last_pay_);
  }

  return std::string(pay_str);
}

/* Возвращает переплату */
std::string s21::Credit_Calc::GetOverpay() {
  char pay_str[255] = "";
  if (payment_type_) {
    std::sprintf(pay_str, "%.2lf", overpayment_);
  } else {
    std::sprintf(pay_str, "%.2lf", total_payout_ - sum_of_credit_);
  }

  return std::string(pay_str);
}

/* Возвращает общую выплату */
std::string s21::Credit_Calc::GetTotalPay() {
  char pay_str[255] = "";
  std::sprintf(pay_str, "%.2lf", total_payout_);

  return std::string(pay_str);
}

void s21::Credit_Calc::clear() {
  first_pay_ = last_pay_ = 0;
  monthly_payment_ = overpayment_ = 0;
  total_payout_ = 0;
}
