#include "credit.h"

#include "ui_credit.h"

credit::credit(QWidget *parent) : QWidget(parent), ui(new Ui::credit) {
  ui->setupUi(this);
}

credit::~credit() { delete ui; }

/* Нажатие на кнопку "вычислить" */
void credit::on_button_calc_clicked() {
  controller_.clear();
  ui->monthly_pay->clear();
  ui->overpay->clear();
  ui->total->clear();

  controller_.SetSumOfCredit(ui->sum_cred->value());
  controller_.SetCreditTerm(ui->time_cred->value());
  controller_.SetProcentRate(ui->stavka->value());
  controller_.SetTermType(ui->time_choose->currentIndex());
  controller_.SetPaymenType(ui->annuitet->isChecked());
  controller_.CalculateCredit();

  ui->monthly_pay->setText("Ежемесячный платеж: " +
                           QString::fromStdString(controller_.GetMonthlyPay()));
  ui->overpay->setText("Переплата: " +
                       QString::fromStdString(controller_.GetOverpay()));
  ui->total->setText("Общая выплата: " +
                     QString::fromStdString(controller_.GetTotalPay()));
}

/* Перекраска кнопки дифферецированного платежа */
void credit::on_differ_pay_toggled(bool checked) {
  checked ? ui->differ_pay->setStyleSheet(
                "background-color: rgb(5, 5, 5); color: rgb(177, 142, 74);")
          : ui->differ_pay->setStyleSheet("background-color: rgb(5, 5, 5);");
}

/* Перекраска кнопки аннуитетного платежа */
void credit::on_annuitet_toggled(bool checked) {
  checked ? ui->annuitet->setStyleSheet(
                "background-color: rgb(5, 5, 5); color: rgb(177, 142, 74);")
          : ui->annuitet->setStyleSheet("background-color: rgb(5, 5, 5);");
}

/* Затенение кнопки вычисления при нажатии */
void credit::on_button_calc_pressed() {
  ui->button_calc->setStyleSheet(
      "background-color: rgb(101, 85, 54); border-radius: 10px;");
}

/* Осветление кнопки вычисления при отжатии */
void credit::on_button_calc_released() {
  ui->button_calc->setStyleSheet(
      "background-color: rgb(177, 142, 74); border-radius: 10px;");
}
