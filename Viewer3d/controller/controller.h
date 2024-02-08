#ifndef SRC_VIEWER3D_CONTROLLER_CONTROLLER_H_
#define SRC_VIEWER3D_CONTROLLER_CONTROLLER_H_

#include "../model/3d_model.h"
#include "../model/settings.h"

namespace s21 {

class ViewerController {
 public:
  static ViewerController *GetInstance(s21::ViewerModel *model) {
    if (!instance_) {
      instance_ = new ViewerController(model);
    }
    return instance_;
  }

  bool GetIsModelLoaded() const { return model_->GetIsModelLoaded(); }
  double GetScale() const { return model_->GetScale(); }
  bool GetRecordStatus() const { return model_->GetRecordStatus(); }
  unsigned int GetCountOfFrames() const { return model_->GetCountOfFrames(); }
  double GetFrustum() const { return model_->GetFrustum(); }
  double GetHeapHeight() const { return model_->GetHeapHeight(); }
  double GetLeft() const { return model_->GetLeft(); }
  double GetRight() const { return model_->GetRight(); }
  double GetTop() const { return model_->GetTop(); }
  double GetBottom() const { return model_->GetBottom(); }
  double GetFar() const { return model_->GetFar(); }
  double GetNear() const { return model_->GetNear(); }
  unsigned int GetCountOfFacets() const { return model_->GetCountOfFacets(); }
  unsigned int GetNumbersOfVerticesInFacet(int i) const {
    return model_->GetNumbersOfVerticesInFacet(i);
  }
  unsigned int *GetConcretePolygonVertices(int i) const {
    return model_->GetConcretePolygonVertices(i);
  }
  double *GetVertices() const { return model_->GetVertices(); }
  unsigned int GetCountOfVertices() const {
    return model_->GetCountOfVertices();
  }

  void SetXAngle(double value) { model_->SetXAngle(value); }
  void SetYAngle(double value) { model_->SetYAngle(value); }
  void SetZAngle(double value) { model_->SetZAngle(value); }
  void SetXShift(double value) { model_->SetXShift(value); }
  void SetYShift(double value) { model_->SetYShift(value); }
  void SetZShift(double value) { model_->SetZShift(value); }
  void SetScale(double value) { model_->SetScale(value); }
  void SetRecordStatus(bool value) { model_->SetRecordStatus(value); }
  void SetCountOfFrames(int value) { model_->SetCountOfFrames(value); }

  unsigned int GetLineWidth() const { return settings_->GetLineWidth(); }
  unsigned int GetVertexWidth() const { return settings_->GetVertexWidth(); }
  bool GetIsLineDotted() const { return settings_->GetIsLineDotted(); }
  bool GetIsProjectionCentral() const {
    return settings_->GetIsProjectionCentral();
  }
  bool GetIsVertexRound() const { return settings_->GetIsVertexRound(); }
  float GetColorBackgroundRed() const {
    return settings_->GetColorBackgroundRed();
  }
  float GetColorBackgroundGreen() const {
    return settings_->GetColorBackgroundGreen();
  }
  float GetColorBackgroundBlue() const {
    return settings_->GetColorBackgroundBlue();
  }
  float GetColorLineRed() const { return settings_->GetColorLineRed(); }
  float GetColorLineGreen() const { return settings_->GetColorLineGreen(); }
  float GetColorLineBlue() const { return settings_->GetColorLineBlue(); }
  float GetColorVertexRed() const { return settings_->GetColorVertexRed(); }
  float GetColorVertexGreen() const { return settings_->GetColorVertexGreen(); }
  float GetColorVertexBlue() const { return settings_->GetColorVertexBlue(); }

  void SetLineWidth(int value) { settings_->SetLineWidth(value); }
  void SetVertexWidth(int value) { settings_->SetVertexWidth(value); }
  void SetIsLineDotted(bool value) { settings_->SetIsLineDotted(value); }
  void SetIsProjectionCentral(bool value) {
    settings_->SetIsProjectionCentral(value);
  }
  void SetIsVertexRound(bool value) { settings_->SetIsVertexRound(value); }
  void SetColorBackgroundRed(float value) {
    settings_->SetColorBackgroundRed(value);
  }
  void SetColorBackgroundGreen(float value) {
    settings_->SetColorBackgroundGreen(value);
  }
  void SetColorBackgroundBlue(float value) {
    settings_->SetColorBackgroundBlue(value);
  }
  void SetColorLineRed(float value) { settings_->SetColorLineRed(value); }
  void SetColorLineGreen(float value) { settings_->SetColorLineGreen(value); }
  void SetColorLineBlue(float value) { settings_->SetColorLineBlue(value); }
  void SetColorVertexRed(float value) { settings_->SetColorVertexRed(value); }
  void SetColorVertexGreen(float value) {
    settings_->SetColorVertexGreen(value);
  }
  void SetColorVertexBlue(float value) { settings_->SetColorVertexBlue(value); }

  void SaveConfigurationFile(const std::string &path) {
    return settings_->SaveConfigurationFile(path);
  }
  void LoadConfigurationFile(const std::string &path) {
    return settings_->LoadConfigurationFile(path);
  }
  void FreeMemoryModel() { model_->FreeMemoryModel(); }
  void Parse3DModel(const std::string &file_name) {
    model_->Parse3DModel(file_name);
  }
  void UpdateVertices() { model_->UpdateVertices(); }

 private:
  ViewerModel *model_;
  ViewerSettings *settings_;
  static ViewerController *instance_;
  explicit ViewerController(ViewerModel *model) : model_(model) {
    settings_ = new ViewerSettings();
  }

  ~ViewerController() { delete settings_; }

  ViewerController(const ViewerController &) = delete;
  ViewerController &operator=(const ViewerController &) = delete;
};

}  // namespace s21

#endif  // SRC_VIEWER3D_CONTROLLER_CONTROLLER_H_
