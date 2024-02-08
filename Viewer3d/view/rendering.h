#ifndef SRC_VIEWER3D_VIEW_RENDERING_H_
#define SRC_VIEWER3D_VIEW_RENDERING_H_
#define GL_SILENCE_DEPRECATION
#if defined(__APPLE__)
#include <OpenGL/gl.h>
#else
#include <GL/gl.h>
#endif
#include <QOpenGLWidget>

#include "../controller/controller.h"

namespace s21 {

class Viewer3DModelRender : public QOpenGLWidget {
 private:
  ViewerController* controller_;

  void DrawModel();
  void DrawLines();
  void DrawVertex();

 protected:
  void initializeGL() override;
  void paintGL() override;

 public:
  explicit Viewer3DModelRender(ViewerController* controller);
  ~Viewer3DModelRender();
};

}  // namespace s21

#endif  // SRC_VIEWER3D_VIEW_RENDERING_H_
