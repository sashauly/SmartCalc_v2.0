#include "view.h"

#include "./ui_view.h"

namespace s21 {

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), ui_(new Ui::MainWindow) {
  ui_->setupUi(this);
  eventLoop();
}

MainWindow::~MainWindow() { delete ui_; }

void MainWindow::eventLoop() {
  setlocale(LC_ALL, "");
  setWindowTitle("SmartCalc_v2.0");

  this->setFixedSize(290, 540);

  ui_->result_show->setFixedWidth(270);

  this->setupButtons();

  ui_->widget->xAxis->setLabel("x");
  ui_->widget->yAxis->setLabel("y");
}

void MainWindow::setupButtons() {
  setupDigitButtons();
  setupOperationButtons();
  setupFunctionButtons();

  connect(ui_->pushButton_x, SIGNAL(clicked()), this, SLOT(xInput()));

  connect(ui_->pushButton_clear, SIGNAL(clicked()), this, SLOT(clearInput()));
  connect(ui_->pushButton_erase, SIGNAL(clicked()), this, SLOT(clearInput()));

  connect(ui_->pushButton_open, SIGNAL(clicked()), this, SLOT(bracketInput()));
  connect(ui_->pushButton_close, SIGNAL(clicked()), this, SLOT(bracketInput()));

  connect(ui_->pushButton_dot, SIGNAL(clicked()), this, SLOT(dotInput()));
  connect(ui_->pushButton_equal, SIGNAL(clicked()), this, SLOT(equalInput()));

  connect(ui_->pushButton_graph, SIGNAL(clicked()), this, SLOT(setupGraph()));
  connect(ui_->pushButton_draw_graph, SIGNAL(clicked()), this,
          SLOT(drawGraph()));
  ui_->pushButton_graph->setCheckable(true);
  connect(ui_->pushButton_clear_graph, SIGNAL(clicked()), this,
          SLOT(clearGraph()));
}

void MainWindow::setupDigitButtons() {
  QList<QPushButton *> buttonsDigits = {
      ui_->pushButton_0, ui_->pushButton_1, ui_->pushButton_2,
      ui_->pushButton_3, ui_->pushButton_4, ui_->pushButton_5,
      ui_->pushButton_6, ui_->pushButton_7, ui_->pushButton_8,
      ui_->pushButton_9, ui_->pushButton_pi};
  for (auto &iterButtons : buttonsDigits) {
    connect(iterButtons, SIGNAL(clicked()), this, SLOT(digitInput()));
  }
}

void MainWindow::setupOperationButtons() {
  QList<QPushButton *> buttonsOperations = {
      ui_->pushButton_plus, ui_->pushButton_minus, ui_->pushButton_mult,
      ui_->pushButton_div,  ui_->pushButton_pow,
  };
  for (auto &iterOperations : buttonsOperations) {
    connect(iterOperations, SIGNAL(clicked()), this, SLOT(operationInput()));
  }
}

void MainWindow::setupFunctionButtons() {
  QList<QPushButton *> buttonsFunctions = {
      ui_->pushButton_sin,  ui_->pushButton_cos,  ui_->pushButton_tan,
      ui_->pushButton_asin, ui_->pushButton_acos, ui_->pushButton_atan,
      ui_->pushButton_sqrt, ui_->pushButton_ln,   ui_->pushButton_mod,
      ui_->pushButton_log,
  };
  for (auto &iterFunctions : buttonsFunctions) {
    connect(iterFunctions, SIGNAL(clicked()), this, SLOT(functionInput()));
  }
}

void MainWindow::xInput() {
  QPushButton *button = (QPushButton *)sender();
  clearOutput();
  QString result_label2 = (ui_->result_show->text() + button->text());
  ui_->result_show->setText(result_label2);
}

void MainWindow::digitInput() {
  QPushButton *button = (QPushButton *)sender();
  clearOutput();
  if (ui_->x_value->hasFocus()) {
    QString result_label1 = (ui_->x_value->text() + button->text());
    ui_->x_value->setText(result_label1);
  } else if (ui_->x_min->hasFocus()) {
    int result_label1 = (ui_->x_min->text() + button->text()).toInt();
    ui_->x_min->setValue(result_label1);
  } else if (ui_->x_max->hasFocus()) {
    int result_label1 = (ui_->x_max->text() + button->text()).toInt();
    ui_->x_max->setValue(result_label1);
  } else if (ui_->y_max->hasFocus()) {
    int result_label1 = (ui_->y_max->text() + button->text()).toInt();
    ui_->y_max->setValue(result_label1);
  } else if (ui_->y_min->hasFocus()) {
    int result_label1 = (ui_->y_min->text() + button->text()).toInt();
    ui_->y_min->setValue(result_label1);
  } else {
    QString result_label2 = (ui_->result_show->text() + button->text());
    ui_->result_show->setText(result_label2);
  }
}

void MainWindow::bracketInput() {
  QPushButton *button = (QPushButton *)sender();
  clearOutput();

  QString str = ui_->result_show->text();
  ui_->result_show->setText(str + button->text());
}

void MainWindow::operationInput() {
  QPushButton *button = (QPushButton *)sender();
  clearOutput();

  QString str = ui_->result_show->text();
  int len = str.isNull() ? 0 : str.length();
  if (len != 0) {
    if ((isNumber(str[len - 1])) || str[len - 1] == ')' ||
        str[len - 1] == 'x' || str[len - 1] == QString::fromStdString("π")) {
      ui_->result_show->setText(str + button->text());
    }
    if (str[len - 1] == '(') {
      if (button == ui_->pushButton_plus || button == ui_->pushButton_minus) {
        ui_->result_show->setText(str + button->text());
      }
    }
  } else {
    if (button == ui_->pushButton_plus || button == ui_->pushButton_minus) {
      ui_->result_show->setText(str + button->text());
    }
  }
}

void MainWindow::functionInput() {
  QPushButton *button = (QPushButton *)sender();
  clearOutput();
  QString result_label = ui_->result_show->text();

  if (button == ui_->pushButton_sin) {
    ui_->result_show->setText(result_label + "sin(");
  } else if (button == ui_->pushButton_cos) {
    ui_->result_show->setText(result_label + "cos(");
  } else if (button == ui_->pushButton_tan) {
    ui_->result_show->setText(result_label + "tan(");
  } else if (button == ui_->pushButton_asin) {
    ui_->result_show->setText(result_label + "asin(");
  } else if (button == ui_->pushButton_acos) {
    ui_->result_show->setText(result_label + "acos(");
  } else if (button == ui_->pushButton_atan) {
    ui_->result_show->setText(result_label + "atan(");
  } else if (button == ui_->pushButton_sqrt) {
    ui_->result_show->setText(result_label + "sqrt(");
  } else if (button == ui_->pushButton_mod) {
    ui_->result_show->setText(result_label + "%");
  } else if (button == ui_->pushButton_ln) {
    ui_->result_show->setText(result_label + "ln(");
  } else if (button == ui_->pushButton_log) {
    ui_->result_show->setText(result_label + "log(");
  }
}

void MainWindow::clearInput() {
  QPushButton *button = (QPushButton *)sender();
  if (button == ui_->pushButton_clear) {
    ui_->result_show->setText("");
  } else {
    QString result_label = ui_->result_show->text();
    result_label.resize(result_label.size() - 1);
    ui_->result_show->setText(result_label);
  }
}

void MainWindow::clearOutput() {
  QString result = ui_->result_show->text();
  if (result == "Format Error" || result == "Enter an expression") {
    ui_->result_show->setText("");
  }
}

void MainWindow::dotInput() {
  int count = 0;
  QString str = ui_->result_show->text();
  int len = str.isNull() ? 0 : str.length();
  for (int i = 0; i < len; i++) {
    if (str[i] == '.') {
      count = 1;
    } else if (!isNumber(str[i])) {
      count = 0;
    }
  }
  if (len != 0) {
    if (count == 0 && (isNumber(str[len - 1]))) {
      if (ui_->x_value->hasFocus()) {
        ui_->x_value->setText(ui_->x_value->text() + ".");
      } else {
        ui_->result_show->setText(ui_->result_show->text() + ".");
      }
    }
  }
}

void MainWindow::equalInput() {
  double x = 0.0;
  double result = 0.0;
  QString str = ui_->result_show->text();

  QString pi = QString::fromStdString("π");

  if (str == "") {
    ui_->result_show->setText("Enter an expression");
  } else {
    if (str.contains(pi)) {
      str.replace(pi, QString::fromStdString("pi"));
    }
    if (str.contains('x')) {
      if (ui_->x_value->text() != "") {
        str.replace("x", ui_->x_value->text());
        x = ui_->x_value->text().toDouble();
      }
    }
    std::string stdString = str.toStdString();
    if (controller_.Validate(stdString)) {
      result = controller_.Calculate(stdString, x);
      ui_->result_show->setText(QString::number(result));
    } else {
      ui_->result_show->setText("Format Error");
    }
  }
}

void MainWindow::setupGraph() {
  QPushButton *button = (QPushButton *)sender();
  if (button->isChecked()) {
    this->setFixedWidth(890);
    ui_->result_show->setFixedWidth(870);

    button->setChecked(true);
    ui_->x_value->setEnabled(0);
    ui_->x_value->setPlaceholderText("Graph enabled");
    ui_->pushButton_equal->setEnabled(0);
    ui_->result_show->setPlaceholderText("Enter a function containing x:");

    ui_->x_max->setEnabled(true);
    ui_->x_min->setEnabled(true);
    ui_->y_max->setEnabled(true);
    ui_->y_min->setEnabled(true);
  } else {
    this->setFixedWidth(290);
    ui_->result_show->setFixedWidth(270);

    button->setChecked(false);
    ui_->x_value->setEnabled(1);
    ui_->x_value->setPlaceholderText("Enter x value:");
    ui_->pushButton_equal->setEnabled(1);
    ui_->result_show->setPlaceholderText("");

    ui_->x_max->setEnabled(false);
    ui_->x_min->setEnabled(false);
    ui_->y_max->setEnabled(false);
    ui_->y_min->setEnabled(false);

    ui_->widget->replot();
    x_.clear();
    y_.clear();
    ui_->result_show->setText("");
  }
}

void MainWindow::drawGraph() {
  QString str = ui_->result_show->text();
  if (str.contains("x") == false) {
    ui_->result_show->setText("Expression doesn't contain x");
  } else {
    double x_min_num = ui_->x_min->value();
    double x_max_num = ui_->x_max->value();
    double y_min_num = ui_->y_min->value();
    double y_max_num = ui_->y_max->value();

    double step = 0.001 * (qFabs(x_min_num) + qFabs(x_max_num));
    double Y = 0;
    double X = (double)x_min_num;
    while (X < (double)x_max_num) {
      x_.push_back(X);
      std::string stdString = str.toStdString();
      Y = controller_.Calculate(stdString, X);
      y_.push_back(Y);
      X += step;
    }
    ui_->widget->addGraph();
    ui_->widget->graph(0)->setLineStyle(QCPGraph::lsLine);
    ui_->widget->graph(0)->addData(x_, y_);
    ui_->widget->xAxis->setRange(x_min_num, x_max_num);
    ui_->widget->yAxis->setRange(y_min_num, y_max_num);
    ui_->widget->replot();
    x_.clear();
    y_.clear();
    ui_->widget->graph(0)->data()->clear();
  }
}

void MainWindow::clearGraph() {
  ui_->result_show->setText("");
  ui_->widget->replot();
  x_.clear();
  y_.clear();
}

bool MainWindow::isNumber(QChar ch) { return ((ch) >= '0' && (ch) <= '9'); }
bool MainWindow::isLetter(QChar ch) {
  return ((ch) >= 'a' && (ch) <= 'z') || ((ch) >= 'A' && (ch) <= 'Z');
}
bool MainWindow::isOperation(QChar ch) {
  return ((ch) == '+' || (ch) == '-' || (ch) == '*' || (ch) == '/' ||
          (ch) == '^');
}

}  // namespace s21