#include "mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::MainWindow) {
  ui->setupUi(this);
  setFixedSize(750, 425);
  ui->label->setAlignment(Qt::AlignVCenter | Qt::AlignRight);
  ui->lineEdit->setPlaceholderText("Введите значение для x");
  connect_button();
}

MainWindow::~MainWindow() { delete ui; }

void MainWindow::connect_button() {
  connect(ui->pushButton, SIGNAL(clicked()), this, SLOT(pushButton_click()));
  connect(ui->pushButton_2, SIGNAL(clicked()), this, SLOT(pushButton_click()));
  connect(ui->pushButton_3, SIGNAL(clicked()), this, SLOT(pushButton_click()));
  connect(ui->pushButton_4, SIGNAL(clicked()), this, SLOT(pushButton_click()));
  connect(ui->pushButton_5, SIGNAL(clicked()), this, SLOT(pushButton_click()));
  connect(ui->pushButton_6, SIGNAL(clicked()), this, SLOT(pushButton_click()));
  connect(ui->pushButton_7, SIGNAL(clicked()), this, SLOT(pushButton_click()));
  connect(ui->pushButton_8, SIGNAL(clicked()), this, SLOT(pushButton_click()));
  connect(ui->pushButton_9, SIGNAL(clicked()), this, SLOT(pushButton_click()));
  connect(ui->pushButton_10, SIGNAL(clicked()), this, SLOT(pushButton_click()));
  connect(ui->pushButton_11, SIGNAL(clicked()), this, SLOT(pushButton_click()));
  connect(ui->pushButton_13, SIGNAL(clicked()), this, SLOT(pushButton_click()));
  connect(ui->pushButton_14, SIGNAL(clicked()), this, SLOT(pushButton_click()));
  connect(ui->pushButton_15, SIGNAL(clicked()), this, SLOT(pushButton_click()));
  connect(ui->pushButton_16, SIGNAL(clicked()), this, SLOT(pushButton_click()));
  connect(ui->pushButton_18, SIGNAL(clicked()), this, SLOT(pushButton_click()));
  connect(ui->pushButton_19, SIGNAL(clicked()), this, SLOT(pushButton_click()));
  connect(ui->pushButton_20, SIGNAL(clicked()), this, SLOT(pushButton_click()));
  connect(ui->pushButton_21, SIGNAL(clicked()), this, SLOT(pushButton_click()));
  connect(ui->pushButton_22, SIGNAL(clicked()), this, SLOT(pushButton_click()));
  connect(ui->pushButton_23, SIGNAL(clicked()), this, SLOT(pushButton_click()));
  connect(ui->pushButton_24, SIGNAL(clicked()), this, SLOT(pushButton_click()));
  connect(ui->pushButton_25, SIGNAL(clicked()), this, SLOT(pushButton_click()));
  connect(ui->pushButton_26, SIGNAL(clicked()), this, SLOT(pushButton_click()));
  connect(ui->pushButton_27, SIGNAL(clicked()), this, SLOT(pushButton_click()));
  connect(ui->pushButton_28, SIGNAL(clicked()), this, SLOT(pushButton_click()));
  connect(ui->pushButton_29, SIGNAL(clicked()), this, SLOT(pushButton_click()));
  connect(ui->pushButton_30, SIGNAL(clicked()), this, SLOT(pushButton_click()));
  connect(ui->pushButton_32, SIGNAL(clicked()), this, SLOT(pushButton_click()));
  connect(ui->pushButton_17, SIGNAL(clicked()), this, SLOT(delete_str()));
  connect(ui->pushButton_31, SIGNAL(clicked()), this, SLOT(clear_str()));
  connect(ui->pushButton_12, SIGNAL(clicked()), this, SLOT(strPush()));
  connect(ui->pushButton_34, SIGNAL(clicked()), this,
          SLOT(on_pushButton_34_clicked()));
}

void MainWindow::clear_str() {
  QString str = ui->label->text();
  str.chop(1);
  str.clear();
  str = "0";
  ui->label->setText(str);
}

void MainWindow::strPush() {
  double num = 0.0;
  int res = 0;
  char x[256] = {0};
  int len_label = ui->label->text().size();
  int len_edit = ui->lineEdit->text().size();
  if (len_label > 255 || len_edit > 255)
    ui->label->setText("Many elements");
  else {
    char *str = new char(len_label);
    QByteArray arr = ui->label->text().toUtf8();
    strlcpy(str, arr, len_label + 1);
    QByteArray arr_1 = ui->lineEdit->text().toUtf8();
    strlcpy(x, arr_1, len_edit + 1);
    ui->lineEdit->clear();
    res = result_calc(str, &num, x);
    if (!res)
      ui->label->setText(QString::number(num, 'g', 8));
    else if (res == 1)
      ui->label->setText("Incorrect data");
    else if (res == 2)
      ui->label->setText("System error");
    delete str;
  }
}

void MainWindow::pushButton_click() {
  QPushButton *button = (QPushButton *)sender();
  QString num = ui->label->text();
  if ((num == "0" && button->text() != ".") || num == "Incorrect data" ||
      num == "System error" || num == "Many elements")
    num = button->text();
  else
    num += button->text();
  if (button->text() == "cos") num += '(';
  if (button->text() == "sin") num += '(';
  if (button->text() == "tan") num += '(';
  if (button->text() == "acos") num += '(';
  if (button->text() == "asin") num += '(';
  if (button->text() == "atan") num += '(';
  if (button->text() == "sqrt") num += '(';
  if (button->text() == "ln") num += '(';
  if (button->text() == "log") num += '(';
  ui->label->setText(num);
}

void MainWindow::delete_str() {
  QString str = ui->label->text();
  QString trg = str.right(3);
  QString trgThree = str.right(4);
  QString trgFour = str.right(5);
  QString trgInc = str.right(14);
  QString trgElem = str.right(13);
  QString trgErr = str.right(12);

  if (trgFour == "acos(" || trgFour == "asin(" || trgFour == "atan(" ||
      trgFour == "sqrt(")
    str.remove(str.size() - 5, 5);
  else if (trgThree == "cos(" || trgThree == "sin(" || trgThree == "tan(" ||
           trgThree == "log(")
    str.remove(str.size() - 4, 4);
  else if (trg == "mod" || trg == "ln(")
    str.remove(str.size() - 3, 3);
  else if (trgInc == "Incorrect data")
    str.remove(str.size() - 14, 14);
  else if (trgElem == "Many elements")
    str.remove(str.size() - 13, 13);
  else if (trgErr == "System error")
    str.remove(str.size() - 12, 12);
  else
    str.remove(str.size() - 1, 1);
  if (str == "") str += "0";
  ui->label->setText(str);
}

void MainWindow::on_pushButton_33_clicked() {
  uiGraph = new GraphForm(nullptr, ui->label->text());
  uiGraph->show();
  connect(uiGraph, &GraphForm::firstEmit, this, &MainWindow::show);
  this->close();
}

void MainWindow::on_pushButton_34_clicked() { ui->lineEdit->clear(); }
