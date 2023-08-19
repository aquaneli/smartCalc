#ifndef GRAPHFORM_H
#define GRAPHFORM_H

#include <qcustomplot.h>

#include <QWidget>

#include "ui_graphform.h"

namespace Ui {
class GraphForm;
}

class GraphForm : public QWidget {
  Q_OBJECT

 public:
  explicit GraphForm(QWidget *parent = nullptr, QString str = "");
  ~GraphForm();

 private:
  Ui::GraphForm *ui;
  QVector<double> x, y;
  QString strQ;

 signals:
  void firstEmit();

 private slots:
  void on_pushButton_clicked();
  void on_pushButton_2_clicked();
};

#endif  // GRAPHFORM_H
