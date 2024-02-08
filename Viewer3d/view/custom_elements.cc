#include "custom_elements.h"

s21::CustomSlider::CustomSlider(int value, int min, int max,
                                QString object_name) {
  setOrientation(Qt::Horizontal);
  setMinimum(min);
  setMaximum(max);
  setValue(value);
  setSingleStep(1);
  setFixedWidth(270);
  setObjectName(object_name);
}

s21::CustomLineEdit::CustomLineEdit(int min, int max, QString object_name) {
  setText("0");
  setFixedWidth(40);
  setValidator(new QIntValidator(min, max, nullptr));
  setObjectName(object_name);
}

s21::CustomPushButton::CustomPushButton(QString text, QString object_name) {
  setText(text);
  setObjectName(object_name);
}

s21::CustomComboBox::CustomComboBox(QString first_item, QString second_item,
                                    QString object_name) {
  addItem(first_item, Qt::Horizontal);
  addItem(second_item, Qt::Horizontal);
  setObjectName(object_name);
}
