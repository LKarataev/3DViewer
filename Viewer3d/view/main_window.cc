#include "main_window.h"

using s21::ViewerView;
ViewerView *ViewerView::instance_ = nullptr;

ViewerView::ViewerView(ViewerController *controller, QWidget *parent)
    : QWidget(parent), controller_(controller) {
  SetDesignToMainWindow();
  LoadConfirgurations();
  AddWidgetsToMainWindow();
  QMetaObject::connectSlotsByName(this);
  model_render_->update();
}

void ViewerView::SetDesignToMainWindow() {
  setWindowTitle("3D Viewer");
  setFixedSize(1200, 800);

  setLayout(main_layout_);
  main_layout_->setSpacing(0);
  main_layout_->setContentsMargins(0, 0, 0, 0);
  main_layout_->setColumnMinimumWidth(0, 800);
  main_layout_->setAlignment(Qt::AlignTop);
  main_layout_->addLayout(second_layout_, 0, 1);
  main_layout_->addLayout(fourth_layout_, 0, 0);

  second_layout_->setAlignment(Qt::AlignCenter);
  second_layout_->setSpacing(15);
  second_layout_->setContentsMargins(10, 10, 10, 10);
  second_layout_->addLayout(third_layout_, 23, 0, 1, 3);

  fourth_layout_->setAlignment(Qt::AlignBottom);
  fourth_layout_->setSpacing(0);
  fourth_layout_->setContentsMargins(10, 10, 10, 10);
  fourth_layout_->setColumnMinimumWidth(0, 550);

  line_edit_scale_->setValidator(new QDoubleValidator(0, 12, 2, nullptr));

  check_box_jpeg_->setTristate(false);
  check_box_jpeg_->setChecked(true);
  check_box_bmp_->setTristate(false);

  button_group_screenshot_type_->setExclusive(true);
  button_group_screenshot_type_->addButton(check_box_jpeg_);
  button_group_screenshot_type_->addButton(check_box_bmp_);
}

void ViewerView::LoadConfirgurations() {
  QString path = QCoreApplication::applicationDirPath() + "/config.cfg";
  controller_->LoadConfigurationFile(path.toStdString());
  slider_line_width_->setValue(controller_->GetLineWidth());
  slider_vertex_width_->setValue(controller_->GetVertexWidth());
  line_edit_scale_->setText(QString::number(1 - controller_->GetScale()));
  line_edit_line_width_->setText(QString::number(controller_->GetLineWidth()));
  line_edit_vertex_width_->setText(
      QString::number(controller_->GetVertexWidth()));
  combo_box_line_type_->setCurrentIndex(controller_->GetIsLineDotted());
  combo_box_projection_type_->setCurrentIndex(
      controller_->GetIsProjectionCentral());
  combo_box_vertex_type_->setCurrentIndex(controller_->GetIsVertexRound());
}

void ViewerView::AddWidgetsToMainWindow() {
  main_layout_->addWidget(model_render_, 0, 0, 1, 1);
  fourth_layout_->addWidget(label_full_path_to_obj_, 0, 0, 1, 1);
  fourth_layout_->addWidget(label_count_of_vertices_, 0, 1, 1, 1);
  fourth_layout_->addWidget(label_count_of_facets_, 0, 2, 1, 1);

  second_layout_->addWidget(button_open_file_, 0, 0, 1, 3);
  second_layout_->addWidget(button_color_background_, 17, 0, 1, 3);
  second_layout_->addWidget(button_color_line_, 18, 0, 1, 3);
  second_layout_->addWidget(button_color_vertex_, 19, 0, 1, 3);
  second_layout_->addWidget(label_scale_, 1, 0, 1, 1);
  second_layout_->addWidget(label_move_, 2, 0, 1, 1);
  second_layout_->addWidget(label_move_x_, 3, 0, 1, 1);
  second_layout_->addWidget(label_move_y_, 4, 0, 1, 1);
  second_layout_->addWidget(label_move_z_, 5, 0, 1, 1);
  second_layout_->addWidget(label_rotate_, 6, 0, 1, 1);
  second_layout_->addWidget(label_rotate_x_, 7, 0, 1, 1);
  second_layout_->addWidget(label_rotate_y_, 8, 0, 1, 1);
  second_layout_->addWidget(label_rotate_z_, 9, 0, 1, 1);
  second_layout_->addWidget(label_line_width_, 10, 0, 1, 1);
  second_layout_->addWidget(label_vertex_width_, 11, 0, 1, 1);
  second_layout_->addWidget(slider_scale_, 1, 1, 1, 1);
  second_layout_->addWidget(slider_move_x_, 3, 1, 1, 1);
  second_layout_->addWidget(slider_move_y_, 4, 1, 1, 1);
  second_layout_->addWidget(slider_move_z_, 5, 1, 1, 1);
  second_layout_->addWidget(slider_rotate_x_, 7, 1, 1, 1);
  second_layout_->addWidget(slider_rotate_y_, 8, 1, 1, 1);
  second_layout_->addWidget(slider_rotate_z_, 9, 1, 1, 1);
  second_layout_->addWidget(slider_line_width_, 10, 1, 1, 1);
  second_layout_->addWidget(slider_vertex_width_, 11, 1, 1, 1);
  second_layout_->addWidget(line_edit_scale_, 1, 2, 1, 1);
  second_layout_->addWidget(line_edit_move_x_, 3, 2, 1, 1);
  second_layout_->addWidget(line_edit_move_y_, 4, 2, 1, 1);
  second_layout_->addWidget(line_edit_move_z_, 5, 2, 1, 1);
  second_layout_->addWidget(line_edit_rotate_x_, 7, 2, 1, 1);
  second_layout_->addWidget(line_edit_rotate_y_, 8, 2, 1, 1);
  second_layout_->addWidget(line_edit_rotate_z_, 9, 2, 1, 1);
  second_layout_->addWidget(line_edit_line_width_, 10, 2, 1, 1);
  second_layout_->addWidget(line_edit_vertex_width_, 11, 2, 1, 1);
  second_layout_->addWidget(combo_box_line_type_, 20, 0, 1, 3);
  second_layout_->addWidget(combo_box_projection_type_, 21, 0, 1, 3);
  second_layout_->addWidget(combo_box_vertex_type_, 22, 0, 1, 3);

  third_layout_->addWidget(check_box_jpeg_, 1, 0, 1, 1);
  third_layout_->addWidget(check_box_bmp_, 1, 1, 1, 1);
  third_layout_->addWidget(button_make_screenshot_, 1, 2, 1, 1);
  third_layout_->addWidget(button_make_gif_, 2, 0, 1, 3);
}

void ViewerView::on_slider_move_x_valueChanged(int) {
  controller_->SetXShift((double)slider_move_x_->value());
  line_edit_move_x_->setText(QString::number(slider_move_x_->value()));
  UpdateView();
}

void ViewerView::on_slider_move_y_valueChanged(int) {
  controller_->SetYShift((double)slider_move_y_->value());
  line_edit_move_y_->setText(QString::number(slider_move_y_->value()));
  UpdateView();
}

void ViewerView::on_slider_move_z_valueChanged(int) {
  controller_->SetZShift((double)slider_move_z_->value());
  line_edit_move_z_->setText(QString::number(slider_move_z_->value()));
  UpdateView();
}

void ViewerView::on_slider_rotate_x_valueChanged(int) {
  controller_->SetXAngle((double)slider_rotate_x_->value());
  line_edit_rotate_x_->setText(QString::number(slider_rotate_x_->value()));
  UpdateView();
}

void ViewerView::on_slider_rotate_y_valueChanged(int) {
  controller_->SetYAngle((double)slider_rotate_y_->value());
  line_edit_rotate_y_->setText(QString::number(slider_rotate_y_->value()));
  UpdateView();
}

void ViewerView::on_slider_rotate_z_valueChanged(int) {
  controller_->SetZAngle((double)slider_rotate_z_->value());
  line_edit_rotate_z_->setText(QString::number(slider_rotate_z_->value()));
  UpdateView();
}

void ViewerView::on_slider_line_width_valueChanged(int) {
  controller_->SetLineWidth((double)slider_line_width_->value());
  line_edit_line_width_->setText(QString::number(slider_line_width_->value()));
  UpdateView();
}

void ViewerView::on_slider_vertex_width_valueChanged(int) {
  controller_->SetVertexWidth((double)slider_vertex_width_->value());
  line_edit_vertex_width_->setText(
      QString::number(slider_vertex_width_->value()));
  UpdateView();
}

void ViewerView::on_slider_scale_sliderMoved(int) {
  double value = slider_scale_->value() / 500.0;
  if (value <= 1) {
    controller_->SetScale((1 - value) / value);
    line_edit_scale_->setText(QString::number(value, 'f', 2));
  } else {
    controller_->SetScale(1 - value);
    line_edit_scale_->setText(QString::number(20 * value - 19, 'f', 2));
  }
  UpdateView();
}

void ViewerView::on_line_edit_scale_textEdited() {
  double value = line_edit_scale_->displayText().toDouble();
  if (value <= 1) {
    controller_->SetScale((1 - (value + 19) / 20) / (value + 19) / 20);
    slider_scale_->setValue(value * 500);
  } else {
    controller_->SetScale(1 - (value + 19) / 20);
    slider_scale_->setValue((value + 19) * 25);
  }
  UpdateView();
}

void ViewerView::on_line_edit_move_x_textEdited() {
  slider_move_x_->setValue(line_edit_move_x_->displayText().toInt());
}

void ViewerView::on_line_edit_move_y_textEdited() {
  slider_move_y_->setValue(line_edit_move_y_->displayText().toInt());
}

void ViewerView::on_line_edit_move_z_textEdited() {
  slider_move_z_->setValue(line_edit_move_z_->displayText().toInt());
}

void ViewerView::on_line_edit_rotate_x_textEdited() {
  slider_rotate_x_->setValue(line_edit_rotate_x_->displayText().toInt());
}

void ViewerView::on_line_edit_rotate_y_textEdited() {
  slider_rotate_y_->setValue(line_edit_rotate_y_->displayText().toInt());
}

void ViewerView::on_line_edit_rotate_z_textEdited() {
  slider_rotate_z_->setValue(line_edit_rotate_z_->displayText().toInt());
}

void ViewerView::on_line_edit_line_width_textEdited() {
  slider_line_width_->setValue(line_edit_line_width_->displayText().toInt());
}

void ViewerView::on_line_edit_vertex_width_textEdited() {
  slider_vertex_width_->setValue(
      line_edit_vertex_width_->displayText().toInt());
}

void ViewerView::on_button_open_file_clicked() {
  QString filter = "OBJ Files (*.obj)";
  QString filename = QFileDialog::getOpenFileName(this, "Select a file",
                                                  QDir::homePath(), filter);
  if (filename.isEmpty() == false) {
    controller_->Parse3DModel(filename.toStdString());
    unsigned int vertices = controller_->GetCountOfVertices();
    unsigned int facets = controller_->GetCountOfFacets();
    label_full_path_to_obj_->setText("File: " + filename);
    label_count_of_vertices_->setText("Vertices: " + QString::number(vertices));
    label_count_of_facets_->setText("Facets: " + QString::number(facets));
    model_render_->update();
  }
}

void ViewerView::on_button_color_background_clicked() {
  QColor color = QColorDialog::getColor(Qt::darkCyan, this, "Background color");
  if (color.isValid()) {
    controller_->SetColorBackgroundRed(color.redF());
    controller_->SetColorBackgroundGreen(color.greenF());
    controller_->SetColorBackgroundBlue(color.blueF());
  }
  UpdateView();
}

void ViewerView::on_button_color_line_clicked() {
  QColor color = QColorDialog::getColor(Qt::white, this, "Line color");
  if (color.isValid()) {
    controller_->SetColorLineRed(color.redF());
    controller_->SetColorLineGreen(color.greenF());
    controller_->SetColorLineBlue(color.blueF());
  }
  UpdateView();
}

void ViewerView::on_button_color_vertex_clicked() {
  QColor color = QColorDialog::getColor(Qt::blue, this, "Vertex color");
  if (color.isValid()) {
    controller_->SetColorVertexRed(color.redF());
    controller_->SetColorVertexGreen(color.greenF());
    controller_->SetColorVertexBlue(color.blueF());
  }
  UpdateView();
}

void ViewerView::on_combo_box_line_type_currentIndexChanged(int) {
  if (combo_box_line_type_->currentIndex() == 0)
    controller_->SetIsLineDotted(false);
  else
    controller_->SetIsLineDotted(true);
  UpdateView();
}

void ViewerView::on_combo_box_projection_type_currentIndexChanged(int) {
  if (combo_box_projection_type_->currentIndex() == 0)
    controller_->SetIsProjectionCentral(false);
  else
    controller_->SetIsProjectionCentral(true);
  UpdateView();
}

void ViewerView::on_combo_box_vertex_type_currentIndexChanged(int) {
  if (combo_box_vertex_type_->currentIndex() == 0)
    controller_->SetIsVertexRound(false);
  else
    controller_->SetIsVertexRound(true);
  UpdateView();
}

void ViewerView::on_button_make_screenshot_clicked() {
  QString filter = "Images";
  QString save_name = QFileDialog::getSaveFileName(
      this, "Save screenshot of model", QDir::homePath(), filter);
  if (save_name.isEmpty() == false) {
    QPixmap pixmap(model_render_->size());
    model_render_->render(&pixmap);
    QImage qImage = pixmap.toImage();
    if (check_box_jpeg_->isChecked()) {
      save_name.append(".jpeg");
      qImage.save(save_name, "JPEG");
    } else {
      save_name.append(".bmp");
      qImage.save(save_name, "BMP");
    }
  }
}

void ViewerView::UpdateView() {
  model_render_->update();
  if (controller_->GetRecordStatus()) {
    if (controller_->GetCountOfFrames() < 50) {
      SaveFrameForGif();
    } else {
      StopRecord();
    }
  }
}

void ViewerView::on_button_make_gif_clicked() {
  if (controller_->GetRecordStatus() == false) {
    StartRecord();
  } else {
    StopRecord();
  }
}

void ViewerView::StartRecord() {
  QString path = QCoreApplication::applicationDirPath() + "/gif";
  if (!QDir(path).exists()) QDir().mkpath(path);
  controller_->SetRecordStatus(true);
  button_make_gif_->setText("Stop");
  SaveFrameForGif();
}

void ViewerView::StopRecord() {
  QString path = QCoreApplication::applicationDirPath() + "/gif";
  QGifImage gif(QSize(640, 480));
  gif.setDefaultDelay(100);

  for (unsigned int i = 0; i < controller_->GetCountOfFrames(); i++) {
    QString img_name = path + "/gif_frame_" + QString::number(i) + ".bmp";
    QImage img(img_name);
    img = img.scaled(640, 640, Qt::KeepAspectRatio, Qt::SmoothTransformation);
    gif.addFrame(img);
  }

  QString save_name = QFileDialog::getSaveFileName(
      this, "Save gif", QDir::homePath(), "Gif(*.gif)");
  gif.save(save_name);

  QDir(path).removeRecursively();

  controller_->SetRecordStatus(false);
  controller_->SetCountOfFrames(0);
  button_make_gif_->setText("GIF");
}

void ViewerView::SaveFrameForGif() {
  QPixmap pixmap(model_render_->size());
  model_render_->render(&pixmap);
  QImage qImage = pixmap.toImage();
  int i = controller_->GetCountOfFrames();
  QString path = QCoreApplication::applicationDirPath() + "/gif/gif_frame_";
  qImage.save(path + QString::number(i) + ".bmp", "BMP", 100);
  controller_->SetCountOfFrames(i + 1);
}

void ViewerView::closeEvent(QCloseEvent *event) {
  Q_UNUSED(event);
  QString path = QCoreApplication::applicationDirPath() + "/config.cfg";
  controller_->SaveConfigurationFile(path.toStdString());
  controller_->FreeMemoryModel();
}
