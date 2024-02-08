macx: {
QT += core gui openglwidgets
}

unix:!macx {
QT += core gui opengl widgets
}
CONFIG += c++17 sdk_no_version_check

macx:ICON = ../src/Viewer3d/Viewer3d.icns

SOURCES += \
../src/Viewer3d/controller/controller.cc \
../src/Viewer3d/main.cc \
../src/Viewer3d/model/3d_model.cc \
../src/Viewer3d/view/custom_elements.cc \
../src/Viewer3d/view/main_window.cc \
../src/Viewer3d/view/rendering.cc \
../src/Viewer3d/model/settings.cc

HEADERS += \
../src/Viewer3d/model/3d_model.h \
../src/Viewer3d/view/custom_elements.h \
../src/Viewer3d/view/main_window.h \
../src/Viewer3d/view/rendering.h \
../src/Viewer3d/model/settings.h \
../src/Viewer3d/controller/controller.h

include(../src/Viewer3d/QtGifImage/src/gifimage/qtgifimage.pri)
