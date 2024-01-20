#ifndef CREDIT_H
#define CREDIT_H

#include <QWidget>

#include "controller.h"

namespace Ui {
class credit;
}

class credit : public QWidget {
  Q_OBJECT

 public:
  explicit credit(QWidget *parent = nullptr);
  ~credit();

 private slots:
  void on_button_calc_clicked();
  void on_differ_pay_toggled(bool checked);
  void on_annuitet_toggled(bool checked);
  void on_button_calc_pressed();
  void on_button_calc_released();

 private:
  Ui::credit *ui;
  controller controller_;
};

#endif  // CREDIT_H
