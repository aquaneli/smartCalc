#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QDebug>
#include <QLabel>
#include <QMainWindow>
#include <QPropertyAnimation>
#include <QWidget>

#include "graphform.h"
#include "qcustomplot.h"
#include "ui_mainwindow.h"

extern "C" {
#include "../s21_smart_calc.h"
}

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow {
  Q_OBJECT
 public:
  MainWindow(QWidget *parent = nullptr);
  ~MainWindow();

 private:
  Ui::MainWindow *ui;
  GraphForm *uiGraph;

 private slots:
  void pushButton_click();
  void delete_str();
  void connect_button();
  void strPush();
  void clear_str();
  void on_pushButton_33_clicked();
  void on_pushButton_34_clicked();
};

#endif  // MAINWINDOW_H
