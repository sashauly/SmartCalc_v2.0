#include <QApplication>

#include "app/view.h"
#include "view/app/view.h"

using namespace s21;

int main(int argc, char *argv[]) {
  QApplication a(argc, argv);
  MainWindow w;
  w.show();
  return a.exec();
}
