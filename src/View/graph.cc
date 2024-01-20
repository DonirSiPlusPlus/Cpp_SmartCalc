#include "graph.h"

#include "ui_graph.h"

Graph::Graph(QWidget *parent) : QWidget(parent), ui(new Ui::Graph) {
  ui->setupUi(this);

  ui->widget->xAxis->setRange(-10, 10);
  ui->widget->yAxis->setRange(-10, 10);
}

Graph::~Graph() { delete ui; }

/* Устанавливает точки у */
void Graph::SetXVector(std::vector<long double> x_values) {
  x_ = QVector<double>(x_values.begin(), x_values.end());
}

/* Устанавливает точки х */
void Graph::SetYVector(std::vector<long double> y_values) {
  y_ = QVector<double>(y_values.begin(), y_values.end());
}

/* Вставка строки с выражением */
void Graph::SetFunction(QString expression) {
  ui->function->setText(expression);
}

/* Построение графика */
void Graph::DrawGraph(size_t find_status1, size_t find_status2) {
  ui->widget->addGraph();
  if (find_status1 != std::string::npos || find_status2 != std::string::npos) {
    ui->widget->graph(0)->setScatterStyle(
        QCPScatterStyle(QCPScatterStyle::ssDot, Qt::blue, Qt::white, 5));
    ui->widget->graph(0)->setLineStyle(QCPGraph::lsNone);
  }
  ui->widget->graph(0)->addData(x_, y_);
  ui->widget->replot();
  x_.clear();
  y_.clear();
}
