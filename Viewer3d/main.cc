#include <QApplication>

#include "view/main_window.h"

int main(int argc, char* argv[]) {
  setenv("LC_NUMERIC", "C", 1);
  QLocale::setDefault(QLocale::C);
  QApplication app(argc, argv);
  s21::ViewerModel* model = s21::ViewerModel::GetInstance();
  s21::ViewerController* controller = s21::ViewerController::GetInstance(model);
  s21::ViewerView* view = s21::ViewerView::GetInstance(controller);
  view->show();
  return app.exec();
}
