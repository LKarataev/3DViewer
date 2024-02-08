#ifndef SRC_VIEWER3D_MODEL_3D_MODEL_H_
#define SRC_VIEWER3D_MODEL_3D_MODEL_H_

#include <cmath>
#include <cstdio>
#include <fstream>
#include <sstream>

namespace s21 {

class ViewerModel {
 public:
  static ViewerModel* GetInstance() {
    if (!instance_) {
      instance_ = new ViewerModel();
    }
    return instance_;
  }

  void GetVerticesFromFacet(const std::string& src, unsigned int* vertices);
  void Parse3DModel(const std::string& file_name);
  void FreeMemoryModel();
  void UpdateVertices();

  void SetXAngle(double value) { movements_.x_angle = value; }
  void SetYAngle(double value) { movements_.y_angle = value; }
  void SetZAngle(double value) { movements_.z_angle = value; }
  void SetXShift(double value) { movements_.x_shift = value; }
  void SetYShift(double value) { movements_.y_shift = value; }
  void SetZShift(double value) { movements_.z_shift = value; }
  void SetRecordStatus(bool value) { record_status_ = value; }
  void SetCountOfFrames(unsigned int value) { count_of_frames_ = value; }
  void SetScale(double value) { movements_.scale = value; }

  double GetFrustum() const { return movements_.frustum; }
  double GetMaxSide() const { return movements_.max_side; }
  double GetHeapHeight() const { return movements_.heap_height; }
  double GetLeft() const { return movements_.left; }
  double GetRight() const { return movements_.right; }
  double GetTop() const { return movements_.top; }
  double GetBottom() const { return movements_.bottom; }
  double GetFar() const { return movements_.far; }
  double GetNear() const { return movements_.near; }
  bool GetRecordStatus() const { return record_status_; }
  unsigned int GetCountOfFrames() const { return count_of_frames_; }
  double GetScale() const { return movements_.scale; }
  bool GetIsModelLoaded() const { return movements_.is_model_loaded; }
  unsigned int GetCountOfFacets() const { return model_.count_of_facets; }
  unsigned int GetNumbersOfVerticesInFacet(unsigned int i) const {
    return model_.polygons[i].numbers_of_vertices_in_facet;
  }
  unsigned int* GetConcretePolygonVertices(unsigned int i) const {
    return model_.polygons[i].vertices;
  }
  unsigned int GetCountOfVertices() const { return model_.count_of_vertices; }
  double* GetVertices() const { return model_.vertices; }

 private:
  class Polygon {
   public:
    unsigned int* vertices = nullptr;
    unsigned int numbers_of_vertices_in_facet = 0;
  };

  class WireframeModel {
   public:
    unsigned int count_of_vertices = 0;
    unsigned int count_of_facets = 0;
    Polygon* polygons = nullptr;
    double* vertices = nullptr;
    double* basic_vertices = nullptr;
  };

  class TransformData {
   public:
    double x_angle = 0;
    double y_angle = 0;
    double z_angle = 0;
    double x_shift = 0;
    double y_shift = 0;
    double z_shift = 0;
    bool is_model_loaded = 0;
    double max_side = 0;
    double max_left = 0;
    double max_right = 0;
    double max_bottom = 0;
    double max_top = 0;
    double max_near = 0;
    double max_far = 0;
    double left = 0;
    double right = 0;
    double top = 0;
    double bottom = 0;
    double far = 0;
    double near = 0;
    double scale = 0;
    double frustum = 0;
    double heap_height = 0;
  };

  WireframeModel model_;
  TransformData movements_;
  bool record_status_ = false;
  unsigned int count_of_frames_ = 0;
  std::string current_path_;
  std::ifstream file_;
  static ViewerModel* instance_;

  ViewerModel() {}

  void AllocateMemoryForVertices();
  unsigned int CountVerticesInFacet(const std::string& src);
  void SetModelSettings();
  void CalculateMaxValues();
  void ReadObjFile(const std::string& file_name);
  void CountVerticesAndFacetsFromFile();
  void GetDataFromFileToModel();
};

}  // namespace s21

#endif  // SRC_VIEWER3D_MODEL_3D_MODEL_H_
