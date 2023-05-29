#include "view.h"

#include "./ui_view.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::MainWindow) {
  ui->setupUi(this);
  eventLoop();
}

MainWindow::~MainWindow() { delete ui; }

void MainWindow::eventLoop() {
  setlocale(LC_ALL, "");
  setWindowTitle("SmartCalc_v2.0");

  this->setFixedSize(290, 540);

  ui->result_show->setFixedWidth(270);

  this->setupButtons();

  ui->widget->xAxis->setLabel("x");
  ui->widget->yAxis->setLabel("y");
}

void MainWindow::setupButtons() {
  setupDigitButtons();
  setupOperationButtons();
  setupFunctionButtons();

  connect(ui->pushButton_x, SIGNAL(clicked()), this, SLOT(xInput()));

  connect(ui->pushButton_clear, SIGNAL(clicked()), this, SLOT(clearInput()));
  connect(ui->pushButton_erase, SIGNAL(clicked()), this, SLOT(clearInput()));

  connect(ui->pushButton_open, SIGNAL(clicked()), this, SLOT(bracketInput()));
  connect(ui->pushButton_close, SIGNAL(clicked()), this, SLOT(bracketInput()));

  connect(ui->pushButton_dot, SIGNAL(clicked()), this, SLOT(dotInput()));
  connect(ui->pushButton_equal, SIGNAL(clicked()), this, SLOT(equalInput()));

  connect(ui->pushButton_graph, SIGNAL(clicked()), this, SLOT(setupGraph()));
  connect(ui->pushButton_draw_graph, SIGNAL(clicked()), this,
          SLOT(drawGraph()));
  ui->pushButton_graph->setCheckable(true);
  connect(ui->pushButton_clear_graph, SIGNAL(clicked()), this,
          SLOT(clearGraph()));
}

void MainWindow::setupDigitButtons() {
  this->buttonsDigits = {ui->pushButton_0, ui->pushButton_1, ui->pushButton_2,
                         ui->pushButton_3, ui->pushButton_4, ui->pushButton_5,
                         ui->pushButton_6, ui->pushButton_7, ui->pushButton_8,
                         ui->pushButton_9, ui->pushButton_pi};
  for (auto &iterButtons : this->buttonsDigits) {
    connect(iterButtons, SIGNAL(clicked()), this, SLOT(digitInput()));
  }
}

void MainWindow::setupOperationButtons() {
  this->buttonsOperations = {
      ui->pushButton_plus, ui->pushButton_minus, ui->pushButton_mult,
      ui->pushButton_div,  ui->pushButton_pow,
  };
  for (auto &iterOperations : this->buttonsOperations) {
    connect(iterOperations, SIGNAL(clicked()), this, SLOT(operationInput()));
  }
}

void MainWindow::setupFunctionButtons() {
  this->buttonsFunctions = {
      ui->pushButton_sin,  ui->pushButton_cos,  ui->pushButton_tan,
      ui->pushButton_asin, ui->pushButton_acos, ui->pushButton_atan,
      ui->pushButton_sqrt, ui->pushButton_ln,   ui->pushButton_mod,
      ui->pushButton_log,
  };
  for (auto &iterFunctions : this->buttonsFunctions) {
    connect(iterFunctions, SIGNAL(clicked()), this, SLOT(functionInput()));
  }
}

void MainWindow::xInput() {
  QPushButton *button = (QPushButton *)sender();
  clearOutput();
  QString result_label2 = (ui->result_show->text() + button->text());
  ui->result_show->setText(result_label2);
}

void MainWindow::digitInput() {
  QPushButton *button = (QPushButton *)sender();
  clearOutput();
  if (ui->x_value->hasFocus()) {
    QString result_label1 = (ui->x_value->text() + button->text());
    ui->x_value->setText(result_label1);
  } else if (ui->x_min->hasFocus()) {
    int result_label1 = (ui->x_min->text() + button->text()).toInt();
    ui->x_min->setValue(result_label1);
  } else if (ui->x_max->hasFocus()) {
    int result_label1 = (ui->x_max->text() + button->text()).toInt();
    ui->x_max->setValue(result_label1);
  } else if (ui->y_max->hasFocus()) {
    int result_label1 = (ui->y_max->text() + button->text()).toInt();
    ui->y_max->setValue(result_label1);
  } else if (ui->y_min->hasFocus()) {
    int result_label1 = (ui->y_min->text() + button->text()).toInt();
    ui->y_min->setValue(result_label1);
  } else {
    QString result_label2 = (ui->result_show->text() + button->text());
    ui->result_show->setText(result_label2);
  }
}

void MainWindow::bracketInput() {
  QPushButton *button = (QPushButton *)sender();
  clearOutput();

  QString str = ui->result_show->text();
  ui->result_show->setText(str + button->text());
}

void MainWindow::operationInput() {
  QPushButton *button = (QPushButton *)sender();
  clearOutput();

  QString str = ui->result_show->text();
  int len = str.isNull() ? 0 : str.length();
  if (len != 0) {
    if ((isNumber(str[len - 1])) || str[len - 1] == ')' ||
        str[len - 1] == 'x' || str[len - 1] == QString::fromStdString("π")) {
      ui->result_show->setText(str + button->text());
    }
    if (str[len - 1] == '(') {
      if (button == ui->pushButton_plus || button == ui->pushButton_minus) {
        ui->result_show->setText(str + button->text());
      }
    }
  } else {
    if (button == ui->pushButton_plus || button == ui->pushButton_minus) {
      ui->result_show->setText(str + button->text());
    }
  }
}

void MainWindow::functionInput() {
  QPushButton *button = (QPushButton *)sender();
  clearOutput();
  QString result_label = ui->result_show->text();

  if (button == ui->pushButton_sin) {
    ui->result_show->setText(result_label + "sin(");
  } else if (button == ui->pushButton_cos) {
    ui->result_show->setText(result_label + "cos(");
  } else if (button == ui->pushButton_tan) {
    ui->result_show->setText(result_label + "tan(");
  } else if (button == ui->pushButton_asin) {
    ui->result_show->setText(result_label + "asin(");
  } else if (button == ui->pushButton_acos) {
    ui->result_show->setText(result_label + "acos(");
  } else if (button == ui->pushButton_atan) {
    ui->result_show->setText(result_label + "atan(");
  } else if (button == ui->pushButton_sqrt) {
    ui->result_show->setText(result_label + "sqrt(");
  } else if (button == ui->pushButton_mod) {
    ui->result_show->setText(result_label + "%");
  } else if (button == ui->pushButton_ln) {
    ui->result_show->setText(result_label + "ln(");
  } else if (button == ui->pushButton_log) {
    ui->result_show->setText(result_label + "log(");
  }
}

void MainWindow::clearInput() {
  QPushButton *button = (QPushButton *)sender();
  if (button == ui->pushButton_clear) {
    ui->result_show->setText("");
  } else {
    QString result_label = ui->result_show->text();
    result_label.resize(result_label.size() - 1);
    ui->result_show->setText(result_label);
  }
}

void MainWindow::clearOutput() {
  QString result = ui->result_show->text();
  if (result == "Format Error" || result == "Enter an expression") {
    ui->result_show->setText("");
  }
}

void MainWindow::dotInput() {
  int count = 0;
  QString str = ui->result_show->text();
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
      if (ui->x_value->hasFocus()) {
        ui->x_value->setText(ui->x_value->text() + ".");
      } else {
        ui->result_show->setText(ui->result_show->text() + ".");
      }
    }
  }
}

void MainWindow::equalInput() {
  double x = 0.0;
  double result = 0.0;
  QString str = ui->result_show->text();

  QString pi = QString::fromStdString("π");
  QString div = QString::fromStdString("÷");

  if (str == "") {
    ui->result_show->setText("Enter an expression");
  } else {
    if (str.contains(pi)) {
      str.replace(pi, QString::fromStdString("pi"));
    }
    if (str.contains(div)) {
      str.replace(div, QString::fromStdString("/"));
    }
    if (str.contains('x')) {
      if (ui->x_value->text() != "") {
        str.replace("x", ui->x_value->text());
        x = ui->x_value->text().toDouble();
      }
    }
    std::string stdString = str.toStdString();
    if (controller.validate(stdString)) {
      result = controller.calculate(stdString, x);
      ui->result_show->setText(QString::number(result));
    } else {
      ui->result_show->setText("Format Error");
    }
  }
}

void MainWindow::setupGraph() {
  QPushButton *button = (QPushButton *)sender();
  if (button->isChecked()) {
    this->setFixedWidth(890);
    ui->result_show->setFixedWidth(870);

    button->setChecked(true);
    ui->x_value->setEnabled(0);
    ui->x_value->setPlaceholderText("Graph enabled");
    ui->pushButton_equal->setEnabled(0);
    ui->result_show->setPlaceholderText("Enter a function containing x:");

    ui->x_max->setEnabled(true);
    ui->x_min->setEnabled(true);
    ui->y_max->setEnabled(true);
    ui->y_min->setEnabled(true);
  } else {
    this->setFixedWidth(290);
    ui->result_show->setFixedWidth(270);

    button->setChecked(false);
    ui->x_value->setEnabled(1);
    ui->x_value->setPlaceholderText("Enter x value:");
    ui->pushButton_equal->setEnabled(1);
    ui->result_show->setPlaceholderText("");

    ui->x_max->setEnabled(false);
    ui->x_min->setEnabled(false);
    ui->y_max->setEnabled(false);
    ui->y_min->setEnabled(false);

    ui->widget->replot();
    x.clear();
    y.clear();
    ui->result_show->setText("");
  }
}

void MainWindow::drawGraph() {
  QString str = ui->result_show->text();
  if (str.contains("x") == false) {
    ui->result_show->setText("Expression doesn't contain x");
  } else {
    double x_min_num = ui->x_min->value();
    double x_max_num = ui->x_max->value();
    double y_min_num = ui->y_min->value();
    double y_max_num = ui->y_max->value();

    double step = 0.001 * (qFabs(x_min_num) + qFabs(x_max_num));
    double Y = 0;
    double X = (double)x_min_num;
    while (X < (double)x_max_num) {
      x.push_back(X);
      std::string stdString = str.toStdString();
      Y = controller.calculate(stdString, X);
      y.push_back(Y);
      X += step;
    }
    ui->widget->addGraph();
    ui->widget->graph(0)->setLineStyle(QCPGraph::lsLine);
    ui->widget->graph(0)->addData(x, y);
    ui->widget->xAxis->setRange(x_min_num, x_max_num);
    ui->widget->yAxis->setRange(y_min_num, y_max_num);
    ui->widget->replot();
    x.clear();
    y.clear();
    ui->widget->graph(0)->data()->clear();
  }
}

void MainWindow::clearGraph() {
  ui->result_show->setText("");
  ui->widget->replot();
  x.clear();
  y.clear();
}

bool MainWindow::isNumber(QChar ch) { return ((ch) >= '0' && (ch) <= '9'); }
bool MainWindow::isLetter(QChar ch) {
  return ((ch) >= 'a' && (ch) <= 'z') || ((ch) >= 'A' && (ch) <= 'Z');
}
bool MainWindow::isOperation(QChar ch) {
  return ((ch) == '+' || (ch) == '-' || (ch) == '*' || (ch) == '/' ||
          (ch) == '^');
};
