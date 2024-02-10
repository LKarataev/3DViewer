#include "rendering.h"

using s21::Viewer3DModelRender;

Viewer3DModelRender::Viewer3DModelRender(s21::ViewerController *controller)
    : controller_(controller) {
  setFixedWidth(800);
  setFixedHeight(800);
}

Viewer3DModelRender::~Viewer3DModelRender() {}

void Viewer3DModelRender::initializeGL() {
  glEnable(GL_DEPTH_TEST);
  glDepthFunc(GL_LEQUAL);
  glDisable(GL_CULL_FACE);
  glCullFace(GL_BACK);
}

void Viewer3DModelRender::paintGL() {
  glClearColor(controller_->GetColorBackgroundRed(),
               controller_->GetColorBackgroundGreen(),
               controller_->GetColorBackgroundBlue(), 1.0f);
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  if (controller_->GetIsModelLoaded() == true) DrawModel();
}

void Viewer3DModelRender::DrawModel() {
  controller_->UpdateVertices();
  double frustum = controller_->GetFrustum();

  if (controller_->GetIsProjectionCentral()) {
    glOrtho(-frustum, frustum, -frustum, frustum, -1000000, 1000000);
    glFrustum(-frustum, frustum, -frustum, frustum,
              controller_->GetHeapHeight(), controller_->GetFar());
    glTranslated(0, 0, -controller_->GetHeapHeight() * 2);
  } else {
    glOrtho(controller_->GetLeft(), controller_->GetRight(),
            controller_->GetBottom(), controller_->GetTop(),
            controller_->GetNear(), controller_->GetFar());
  }
  glMatrixMode(GL_MODELVIEW);
  glLoadIdentity();

  glEnableClientState(GL_VERTEX_ARRAY);
  glVertexPointer(3, GL_DOUBLE, 0,
                  static_cast<GLdouble *>(controller_->GetVertices()));
  if (controller_->GetLineWidth()) DrawLines();
  if (controller_->GetVertexWidth()) DrawVertex();
  glDisableClientState(GL_VERTEX_ARRAY);
}

void Viewer3DModelRender::DrawLines() {
  glColor3d(controller_->GetColorLineRed(), controller_->GetColorLineGreen(),
            controller_->GetColorLineBlue());
  glLineWidth(controller_->GetLineWidth());
  if (controller_->GetIsLineDotted()) {
    glEnable(GL_LINE_STIPPLE);
    glLineStipple(2, 0xAAAA);
  } else {
    glDisable(GL_LINE_STIPPLE);
  }
  for (unsigned int i = 1; i <= controller_->GetCountOfFacets(); i++) {
    glDrawElements(GL_LINES, controller_->GetNumbersOfVerticesInFacet(i) * 2,
                   GL_UNSIGNED_INT, controller_->GetConcretePolygonVertices(i));
  }
}

void Viewer3DModelRender::DrawVertex() {
  glColor3d(controller_->GetColorVertexRed(),
            controller_->GetColorVertexGreen(),
            controller_->GetColorVertexBlue());
  glPointSize(controller_->GetVertexWidth());
  if (controller_->GetIsVertexRound()) {
    glEnable(GL_POINT_SMOOTH);
  } else {
    glDisable(GL_POINT_SMOOTH);
  }
  glDrawArrays(GL_POINTS, 0, controller_->GetCountOfVertices());
}
