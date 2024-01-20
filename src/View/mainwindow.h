#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QWidget>

#include "controller.h"
#include "credit.h"
#include "graph.h"

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}  // namespace Ui
QT_END_NAMESPACE

class MainWindow : public QMainWindow {
  Q_OBJECT

 public:
  explicit MainWindow(QWidget *parent = nullptr);
  ~MainWindow();

 private slots:
  void PrintDigit();
  void PrintFunc();
  void CheckResultString();
  void on_delete_all_clicked();
  void on_delete_token_clicked();
  bool ValidInput(std::string result, std::string new_symb);

  void on_credit_calc_clicked();

 private:
  Ui::MainWindow *ui;
  controller controller_;
  Graph *graph{nullptr};
  credit *credit_{nullptr};

  bool was_throw_{false};

  void on_equal_clicked();
  void on_graph_clicked();

 signals:
  void signal();
};

#endif  // MAINWINDOW_H
