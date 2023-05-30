#ifndef VIEW_H
#define VIEW_H

#include <qmath.h>
#include <stdlib.h>

#include <QMainWindow>
#include <QPushButton>
#include <QVector>
#include <cctype>

#include "../../controller/controller.h"
#include "qcustomplot.h"

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

namespace s21 {

class MainWindow : public QMainWindow {
  Q_OBJECT

 public:
  MainWindow(QWidget *parent = nullptr);
  ~MainWindow();

 private:
  Ui::MainWindow *ui_;
  QVector<double> x_, y_;
  Controller controller_;

  QList<QPushButton *> buttonsDigits;
  QList<QPushButton *> buttonsOperations;
  QList<QPushButton *> buttonsFunctions;

  void eventLoop();

  bool isNumber(QChar ch);
  bool isLetter(QChar ch);
  bool isOperation(QChar ch);

 private slots:
  void setupButtons();
  void setupDigitButtons();
  void setupOperationButtons();
  void setupFunctionButtons();

  void digitInput();
  void xInput();
  void bracketInput();
  void operationInput();
  void functionInput();
  void clearInput();
  void clearOutput();
  void dotInput();
  void equalInput();

  void setupGraph();
  void drawGraph();
  void clearGraph();
};
}  // namespace s21
#endif  // VIEW_H
