#ifndef SRC_VIEWER3D_VIEW_CUSTOM_ELEMENTS_H_
#define SRC_VIEWER3D_VIEW_CUSTOM_ELEMENTS_H_

#include <QComboBox>
#include <QLineEdit>
#include <QPushButton>
#include <QSlider>
#include <QValidator>

namespace s21 {

class CustomSlider : public QSlider {
 public:
  explicit CustomSlider(int value, int min, int max, QString object_name);
};

class CustomLineEdit : public QLineEdit {
 public:
  explicit CustomLineEdit(int min, int max, QString object_name);
};

class CustomPushButton : public QPushButton {
 public:
  explicit CustomPushButton(QString text, QString object_name);
};

class CustomComboBox : public QComboBox {
 public:
  explicit CustomComboBox(QString first_item, QString second_item,
                          QString object_name);
};

}  // namespace s21

#endif  // SRC_VIEWER3D_VIEW_CUSTOM_ELEMENTS_H_
