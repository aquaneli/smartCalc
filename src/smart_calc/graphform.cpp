#include "graphform.h"

#include "mainwindow.h"

GraphForm::GraphForm(QWidget *parent, QString str)
    : QWidget(parent), ui(new Ui::GraphForm) {
  ui->setupUi(this);
  setFixedSize(830, 650);
  this->setWindowTitle("My Window");
  ui->widget->xAxis->setLabel("X");
  ui->widget->yAxis->setLabel("Y");
  ui->widget->setInteractions(QCP::iRangeDrag | QCP::iRangeZoom);
  strQ = str;
}

GraphForm::~GraphForm() { delete ui; }

void GraphForm::on_pushButton_clicked() {
  this->close();
  emit firstEmit();
}

void GraphForm::on_pushButton_2_clicked() {
  QPen pen;
  pen.setColor(QColor(208, 68, 71));
  ui->widget->clearGraphs();
  int result = 0;
  double h, step, maxX, minX;
  int len = strQ.size();
  char *str_char = new char(len + 1);
  QByteArray arrX = strQ.toUtf8();
  strlcpy(str_char, arrX, len + 1);
  double res = 0;
  maxX = ui->doubleSpinBox->text().toDouble();
  minX = ui->doubleSpinBox_2->text().toDouble();
  h = 0.001;
  double minY = 0;
  double maxY = 0;
  for (step = minX; step <= maxX && !result; step += h) {
    QString strX = QString::number(step, 'f', 3);
    QByteArray arrX2 = strX.toUtf8();
    char *pntX = arrX2.data();
    if ((result = result_calc(str_char, &res, pntX)) == 0) {
      if (res > maxY) maxY = res;
      if (res < minY) minY = res;
      x.push_back(step);
      y.push_back(res);
    }
  }
  delete str_char;
  ui->widget->addGraph();
  ui->widget->graph(0)->setLineStyle(QCPGraph::lsLine);
  pen.setColor(QColor(208, 68, 71));
  ui->widget->graph(0)->setPen(pen);
  ui->widget->graph(0)->addData(x, y);
  ui->widget->xAxis->setRange(minX, maxX);
  ui->widget->yAxis->setRange(minY, maxY);
  ui->widget->replot();
  x.clear();
  y.clear();
}
