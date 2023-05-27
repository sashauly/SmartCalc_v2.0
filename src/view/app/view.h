#ifndef VIEW_H
#define VIEW_H

#include <qmath.h>
#include <stdlib.h>

#include <QMainWindow>
#include <QPushButton>
#include <QVector>
#include <cctype>

#include "../../controller/controller.h"

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
  QVector<double> x, y;
  s21::Controller controller;

  QList<QPushButton *> buttonsDigits;
  QList<QPushButton *> buttonsOperations;
  QList<QPushButton *> buttonsFunctions;

  bool isNumber(QChar ch);
  bool isLetter(QChar ch);
  bool isOperation(QChar ch);

 private slots:
  void setupButtons();
  void setupDigitButtons();
  void setupOperationButtons();
  void setupFunctionButtons();

  void digitInput();
  void bracketInput();
  void operationInput();
  void functionInput();
  void clearInput();

  void on_pushButton_dot_clicked();
  void on_pushButton_pi_clicked();
  void on_pushButton_equal_clicked();
  void graph();
  void make_graph();
  void on_pushButton_clear_graph_clicked();
};
#endif  // VIEW_H
