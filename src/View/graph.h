#ifndef GRAPH_H
#define GRAPH_H

#include <qcustomplot.h>

#include <QWidget>

namespace Ui {
class Graph;
}

class Graph : public QWidget {
  Q_OBJECT

 public:
  explicit Graph(QWidget *parent = nullptr);
  ~Graph();

  void SetFunction(QString expression);
  void SetXVector(std::vector<long double> x_values);
  void SetYVector(std::vector<long double> y_values);
  void DrawGraph(size_t find_status1, size_t find_status2);

 private:
  Ui::Graph *ui;
  QVector<double> x_;
  QVector<double> y_;
};

#endif  // GRAPH_H
