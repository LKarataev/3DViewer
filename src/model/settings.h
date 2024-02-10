#ifndef SRC_VIEWER3D_MODEL_SETTINGS_H_
#define SRC_VIEWER3D_MODEL_SETTINGS_H_

#include <cstdio>
#include <fstream>
#include <string>

namespace s21 {

class ViewerSettings {
 private:
  unsigned int line_width_ = 1;
  unsigned int vertex_width_ = 1;
  bool is_line_dotted_ = false;
  bool is_projection_central_ = false;
  bool is_vertex_round_ = false;
  float color_background_red_ = 255.0f;
  float color_background_green_ = 255.0f;
  float color_background_blue_ = 255.0f;
  float color_line_red_ = 0.0f;
  float color_line_green_ = 0.0f;
  float color_line_blue_ = 0.0f;
  float color_vertex_red_ = 255.0f;
  float color_vertex_green_ = 0.0f;
  float color_vertex_blue_ = 0.0f;

 public:
  ViewerSettings() = default;

  unsigned int GetLineWidth() const { return line_width_; }
  unsigned int GetVertexWidth() const { return vertex_width_; }
  bool GetIsLineDotted() const { return is_line_dotted_; }
  bool GetIsProjectionCentral() const { return is_projection_central_; }
  bool GetIsVertexRound() const { return is_vertex_round_; }
  float GetColorBackgroundRed() const { return color_background_red_; }
  float GetColorBackgroundGreen() const { return color_background_green_; }
  float GetColorBackgroundBlue() const { return color_background_blue_; }
  float GetColorLineRed() const { return color_line_red_; }
  float GetColorLineGreen() const { return color_line_green_; }
  float GetColorLineBlue() const { return color_line_blue_; }
  float GetColorVertexRed() const { return color_vertex_red_; }
  float GetColorVertexGreen() const { return color_vertex_green_; }
  float GetColorVertexBlue() const { return color_vertex_blue_; }

  void SetLineWidth(unsigned int value) { line_width_ = value; }
  void SetVertexWidth(unsigned int value) { vertex_width_ = value; }
  void SetIsLineDotted(bool value) { is_line_dotted_ = value; }
  void SetIsProjectionCentral(bool value) { is_projection_central_ = value; }
  void SetIsVertexRound(bool value) { is_vertex_round_ = value; }
  void SetColorBackgroundRed(float value) { color_background_red_ = value; }
  void SetColorBackgroundGreen(float value) { color_background_green_ = value; }
  void SetColorBackgroundBlue(float value) { color_background_blue_ = value; }
  void SetColorLineRed(float value) { color_line_red_ = value; }
  void SetColorLineGreen(float value) { color_line_green_ = value; }
  void SetColorLineBlue(float value) { color_line_blue_ = value; }
  void SetColorVertexRed(float value) { color_vertex_red_ = value; }
  void SetColorVertexGreen(float value) { color_vertex_green_ = value; }
  void SetColorVertexBlue(float value) { color_vertex_blue_ = value; }

  void LoadConfigurationFile(const std::string &path);
  void SaveConfigurationFile(const std::string &path);
};

}  // namespace s21

#endif  // SRC_VIEWER3D_MODEL_SETTINGS_H_
