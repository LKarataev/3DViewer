macx: {
QT += core gui openglwidgets
}

unix:!macx {
QT += core gui opengl widgets
}
CONFIG += c++17 sdk_no_version_check

macx:ICON = ../src/Viewer3d.icns

SOURCES += \
../src/controller/controller.cc \
../src/main.cc \
../src/model/3d_model.cc \
../src/view/custom_elements.cc \
../src/view/main_window.cc \
../src/view/rendering.cc \
../src/model/settings.cc

HEADERS += \
../src/model/3d_model.h \
../src/view/custom_elements.h \
../src/view/main_window.h \
../src/view/rendering.h \
../src/model/settings.h \
../src/controller/controller.h

include(../src/QtGifImage/src/gifimage/qtgifimage.pri)
