#ifndef SRC_VIEWER3D_VIEW_MAIN_WINDOW_H_
#define SRC_VIEWER3D_VIEW_MAIN_WINDOW_H_

#include <QButtonGroup>
#include <QCheckBox>
#include <QColorDialog>
#include <QCoreApplication>
#include <QDir>
#include <QFileDialog>
#include <QGridLayout>
#include <QLabel>

#include "../controller/controller.h"
#include "custom_elements.h"
#include "gif_lib.h"
#include "qgifimage.h"
#include "rendering.h"

namespace s21 {
class ViewerView : public QWidget {
  Q_OBJECT

 public:
  static ViewerView *GetInstance(s21::ViewerController *controller) {
    if (!instance_) instance_ = new ViewerView(controller, nullptr);
    return instance_;
  }

 protected:
  void closeEvent(QCloseEvent *event);

 private:
  s21::ViewerController *controller_;
  static ViewerView *instance_;
  Viewer3DModelRender *model_render_ = new Viewer3DModelRender(controller_);

  QGridLayout *main_layout_ = new QGridLayout();
  QGridLayout *second_layout_ = new QGridLayout();
  QGridLayout *third_layout_ = new QGridLayout();
  QGridLayout *fourth_layout_ = new QGridLayout();

  CustomPushButton *button_open_file_ =
      new CustomPushButton("Открыть", "button_open_file");
  CustomPushButton *button_color_background_ =
      new CustomPushButton("Цвет фона", "button_color_background");
  CustomPushButton *button_color_line_ =
      new CustomPushButton("Цвет линий", "button_color_line");
  CustomPushButton *button_color_vertex_ =
      new CustomPushButton("Цвет вершин", "button_color_vertex");
  CustomPushButton *button_make_screenshot_ =
      new CustomPushButton("Скриншот", "button_make_screenshot");
  CustomPushButton *button_make_gif_ =
      new CustomPushButton("GIF", "button_make_gif");

  QLabel *label_scale_ = new QLabel("Scale");
  QLabel *label_move_ = new QLabel("Move:");
  QLabel *label_move_x_ = new QLabel("X");
  QLabel *label_move_y_ = new QLabel("Y");
  QLabel *label_move_z_ = new QLabel("Z");
  QLabel *label_rotate_ = new QLabel("Rotate:");
  QLabel *label_rotate_x_ = new QLabel("X");
  QLabel *label_rotate_y_ = new QLabel("Y");
  QLabel *label_rotate_z_ = new QLabel("Z");
  QLabel *label_line_width_ = new QLabel("Line");
  QLabel *label_vertex_width_ = new QLabel("Vertex");
  QLabel *label_full_path_to_obj_ = new QLabel("");
  QLabel *label_count_of_vertices_ = new QLabel("");
  QLabel *label_count_of_facets_ = new QLabel("");

  CustomSlider *slider_scale_ = new CustomSlider(500, 1, 775, "slider_scale");
  CustomSlider *slider_move_x_ =
      new CustomSlider(0, -180, 180, "slider_move_x");
  CustomSlider *slider_move_y_ =
      new CustomSlider(0, -180, 180, "slider_move_y");
  CustomSlider *slider_move_z_ =
      new CustomSlider(0, -180, 180, "slider_move_z");
  CustomSlider *slider_rotate_x_ =
      new CustomSlider(0, -180, 180, "slider_rotate_x");
  CustomSlider *slider_rotate_y_ =
      new CustomSlider(0, -180, 180, "slider_rotate_y");
  CustomSlider *slider_rotate_z_ =
      new CustomSlider(0, -180, 180, "slider_rotate_z");
  CustomSlider *slider_line_width_ =
      new CustomSlider(1, 0, 7, "slider_line_width");
  CustomSlider *slider_vertex_width_ =
      new CustomSlider(1, 0, 11, "slider_vertex_width");

  CustomLineEdit *line_edit_scale_ =
      new CustomLineEdit(0, 2, "line_edit_scale");
  CustomLineEdit *line_edit_move_x_ =
      new CustomLineEdit(-360, 360, "line_edit_move_x");
  CustomLineEdit *line_edit_move_y_ =
      new CustomLineEdit(-360, 360, "line_edit_move_y");
  CustomLineEdit *line_edit_move_z_ =
      new CustomLineEdit(-360, 360, "line_edit_move_z");
  CustomLineEdit *line_edit_rotate_x_ =
      new CustomLineEdit(-360, 360, "line_edit_rotate_x");
  CustomLineEdit *line_edit_rotate_y_ =
      new CustomLineEdit(-360, 360, "line_edit_rotate_y");
  CustomLineEdit *line_edit_rotate_z_ =
      new CustomLineEdit(-360, 360, "line_edit_rotate_z");
  CustomLineEdit *line_edit_line_width_ =
      new CustomLineEdit(0, 11, "line_edit_line_width");
  CustomLineEdit *line_edit_vertex_width_ =
      new CustomLineEdit(0, 11, "line_edit_vertex_width");

  CustomComboBox *combo_box_line_type_ =
      new CustomComboBox("Сплошная", "Пунктирная", "combo_box_line_type");
  CustomComboBox *combo_box_projection_type_ =
      new CustomComboBox("Параллельная проекция", "Центральная проекция",
                         "combo_box_projection_type");
  CustomComboBox *combo_box_vertex_type_ = new CustomComboBox(
      "Квадратные вершины", "Круглые вершины", "combo_box_vertex_type");

  QButtonGroup *button_group_screenshot_type_ = new QButtonGroup();

  QCheckBox *check_box_jpeg_ = new QCheckBox("JPEG");
  QCheckBox *check_box_bmp_ = new QCheckBox("BMP");

  explicit ViewerView(s21::ViewerController *controller,
                      QWidget *parent = nullptr);

  void UpdateView();
  void StartRecord();
  void SaveFrameForGif();
  void StopRecord();
  void LoadConfirgurations();
  void SetDesignToMainWindow();
  void AddWidgetsToMainWindow();

 private slots:
  void on_slider_scale_sliderMoved(int);
  void on_slider_move_x_valueChanged(int);
  void on_slider_move_y_valueChanged(int);
  void on_slider_move_z_valueChanged(int);
  void on_slider_rotate_x_valueChanged(int);
  void on_slider_rotate_y_valueChanged(int);
  void on_slider_rotate_z_valueChanged(int);
  void on_slider_line_width_valueChanged(int);
  void on_slider_vertex_width_valueChanged(int);
  void on_line_edit_scale_textEdited();
  void on_line_edit_move_x_textEdited();
  void on_line_edit_move_y_textEdited();
  void on_line_edit_move_z_textEdited();
  void on_line_edit_rotate_x_textEdited();
  void on_line_edit_rotate_y_textEdited();
  void on_line_edit_rotate_z_textEdited();
  void on_line_edit_line_width_textEdited();
  void on_line_edit_vertex_width_textEdited();
  void on_button_open_file_clicked();
  void on_button_make_screenshot_clicked();
  void on_button_make_gif_clicked();
  void on_button_color_background_clicked();
  void on_button_color_line_clicked();
  void on_button_color_vertex_clicked();
  void on_combo_box_line_type_currentIndexChanged(int);
  void on_combo_box_projection_type_currentIndexChanged(int);
  void on_combo_box_vertex_type_currentIndexChanged(int);
};

}  // namespace s21

#endif  // SRC_VIEWER3D_VIEW_MAIN_WINDOW_H_
