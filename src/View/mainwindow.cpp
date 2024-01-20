#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::MainWindow) {
  ui->setupUi(this);

  connect(ui->button_0, SIGNAL(clicked()), this, SLOT(PrintDigit()));
  connect(ui->button_1, SIGNAL(clicked()), this, SLOT(PrintDigit()));
  connect(ui->button_2, SIGNAL(clicked()), this, SLOT(PrintDigit()));
  connect(ui->button_3, SIGNAL(clicked()), this, SLOT(PrintDigit()));
  connect(ui->button_4, SIGNAL(clicked()), this, SLOT(PrintDigit()));
  connect(ui->button_5, SIGNAL(clicked()), this, SLOT(PrintDigit()));
  connect(ui->button_6, SIGNAL(clicked()), this, SLOT(PrintDigit()));
  connect(ui->button_7, SIGNAL(clicked()), this, SLOT(PrintDigit()));
  connect(ui->button_8, SIGNAL(clicked()), this, SLOT(PrintDigit()));
  connect(ui->button_9, SIGNAL(clicked()), this, SLOT(PrintDigit()));
  connect(ui->plus, SIGNAL(clicked()), this, SLOT(PrintDigit()));
  connect(ui->minus, SIGNAL(clicked()), this, SLOT(PrintDigit()));
  connect(ui->multiple, SIGNAL(clicked()), this, SLOT(PrintDigit()));
  connect(ui->div, SIGNAL(clicked()), this, SLOT(PrintDigit()));
  connect(ui->mod, SIGNAL(clicked()), this, SLOT(PrintDigit()));
  connect(ui->open_bracket, SIGNAL(clicked()), this, SLOT(PrintDigit()));
  connect(ui->close_bracket, SIGNAL(clicked()), this, SLOT(PrintDigit()));
  connect(ui->x, SIGNAL(clicked()), this, SLOT(PrintDigit()));
  connect(ui->point, SIGNAL(clicked()), this, SLOT(PrintDigit()));
  connect(ui->powered, SIGNAL(clicked()), this, SLOT(PrintDigit()));
  connect(ui->exp, SIGNAL(clicked()), this, SLOT(PrintDigit()));
  connect(ui->cos, SIGNAL(clicked()), this, SLOT(PrintFunc()));
  connect(ui->sin, SIGNAL(clicked()), this, SLOT(PrintFunc()));
  connect(ui->tan, SIGNAL(clicked()), this, SLOT(PrintFunc()));
  connect(ui->acos, SIGNAL(clicked()), this, SLOT(PrintFunc()));
  connect(ui->asin, SIGNAL(clicked()), this, SLOT(PrintFunc()));
  connect(ui->atan, SIGNAL(clicked()), this, SLOT(PrintFunc()));
  connect(ui->sqrt, SIGNAL(clicked()), this, SLOT(PrintFunc()));
  connect(ui->log, SIGNAL(clicked()), this, SLOT(PrintFunc()));
  connect(ui->ln, SIGNAL(clicked()), this, SLOT(PrintFunc()));
  connect(ui->equal, &QPushButton::clicked, this,
          &MainWindow::on_equal_clicked);
  connect(ui->graph, &QPushButton::clicked, this,
          &MainWindow::on_graph_clicked);
}

MainWindow::~MainWindow() { delete ui; }

/* Вывод одиночного символа */
void MainWindow::PrintDigit() {
  if (ui->result->text().size() >= 255) {
    return;
  }
  CheckResultString();

  QPushButton *button{(QPushButton *)sender()};
  std::string res{ui->result->text().toStdString()};

  if (!ValidInput(res, button->text().toStdString())) {
    return;
  }

  res += button->text().toStdString();
  ui->result->setText(QString::fromStdString(res));
}

/* Вывод функции */
void MainWindow::PrintFunc() {
  if (ui->result->text().size() >= 255) {
    return;
  }
  CheckResultString();

  QPushButton *button{(QPushButton *)sender()};
  QString res{ui->result->text()};

  if (res.toStdString().back() == 'e') {
    return;
  }

  res += button->text() + '(';
  ui->result->setText(res);
}

/* стирает сообщение об ошибке */
void MainWindow::CheckResultString() {
  if (was_throw_) {
    was_throw_ = false;
    ui->result->clear();
  } else if (ui->result->text().toStdString() == "INF" ||
             ui->result->text().toStdString() == "-INF" ||
             ui->result->text().toStdString() == "nan") {
    ui->result->clear();
  }
}

/* Очистка строки */
void MainWindow::on_delete_all_clicked() { ui->result->clear(); }

/* Подсчет выражения */
void MainWindow::on_equal_clicked() {
  try {
    controller_.CalculateExression(ui->result->text(), ui->x_value->value());
    ui->result->setText(controller_.GetAnswer());
  } catch (const std::exception &e) {
    was_throw_ = true;
    ui->result->setText(e.what());
  }
}

/* Стирает символ */
void MainWindow::on_delete_token_clicked() {
  std::string res{ui->result->text().toStdString()};
  res.pop_back();
  ui->result->setText(QString::fromStdString(res));
}

/* Вызов окна с графиком */
void MainWindow::on_graph_clicked() {
  if (graph) {
    delete graph;
  }
  graph = new Graph;
  try {
    QString res{ui->result->text()};
    graph->SetFunction(res);
    if (res.isEmpty()) {
      graph->show();
      return;
    }
    controller_.GraphCalculate(res);
    graph->SetXVector(controller_.GetXVector());
    graph->SetYVector(controller_.GetYVector());
    graph->DrawGraph(res.toStdString().find("tan"),
                     res.toStdString().find("mod"));
    graph->show();
  } catch (const std::exception &e) {
    was_throw_ = true;
    ui->result->setText(e.what());
  }
}

/* Вызов окна с кредитным калькулятором */
void MainWindow::on_credit_calc_clicked() {
  if (credit_) {
    delete credit_;
  }
  credit_ = new credit;
  credit_->show();
}

/* Валидация ввода */
bool MainWindow::ValidInput(std::string result, std::string new_symb) {
  char last_symb = result.back();
  std::string opers_left{"^/*d(-+"};
  std::string opers_right{"^/*m)"};

  if (!result.size()) {
    if (opers_right.find(new_symb.front()) != opers_right.npos ||
        new_symb == "." || new_symb == "e") {
      return false;
    }
  } else if (isdigit(new_symb.back()) && result.back() == '0') {
    if (result.size() == 1) {
      return false;
    } else {
      auto i = result.end() - 1;
      while (*i == '0') {
        --i;
      }
      if (opers_left.find(*i) != opers_left.npos) {
        return false;
      }
    }
  } else if (new_symb == ".") {
    std::string tokens{"^/*.+-x()de"};
    if (tokens.find(last_symb) != tokens.npos) {
      return false;
    }

    size_t i{result.size() - 1};
    while (std::isdigit(result[i])) {
      --i;
    }

    if (result[i] == '.') {
      return false;
    }
  } else if (new_symb == "e" && !isdigit(last_symb)) {
    return false;
  } else if (opers_left.find(last_symb) != opers_left.npos) {
    if (opers_right.find(new_symb.front()) != opers_right.npos) {
      return false;
    } else if (last_symb != '(' && (new_symb == "+" || new_symb == "-")) {
      return false;
    }
  } else if (last_symb == 'e') {
    if (new_symb == "-" || new_symb == "+") {
      return true;
    }
    if (!isdigit(new_symb.front())) {
      return false;
    }
  }

  return true;
}
