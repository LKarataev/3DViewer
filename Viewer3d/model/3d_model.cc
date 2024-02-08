#include "3d_model.h"

using s21::ViewerModel;

ViewerModel *ViewerModel::instance_ = nullptr;

void ViewerModel::AllocateMemoryForVertices() {
  if (model_.count_of_vertices > 0) {
    model_.vertices = new double[3 * model_.count_of_vertices];
    model_.basic_vertices = new double[3 * model_.count_of_vertices];
  }
  model_.polygons = new Polygon[model_.count_of_facets + 1];
}

unsigned int ViewerModel::CountVerticesInFacet(const std::string &src) {
  unsigned int result = 0;
  std::string::const_iterator buffer = src.begin();

  while (buffer != src.end() && (*buffer == 'f' || *buffer == ' ')) {
    ++buffer;
  }

  while (buffer != src.end() && *buffer != '\n') {
    if (isdigit(*buffer)) ++result;
    while (isdigit(*buffer) || *buffer == '/') ++buffer;
    if (*buffer == ' ') {
      ++buffer;
    } else {
      break;
    }
  }

  return result;
}

void ViewerModel::GetVerticesFromFacet(const std::string &src,
                                       unsigned int *vertices) {
  unsigned int i = 0;
  size_t start_pos = src.find_first_not_of("f ");
  std::string buffer = src.substr(start_pos);
  while (buffer.length() > 0) {
    if (buffer[0] == '\n') {
      break;
    }
    if (isdigit(buffer[0])) {
      size_t end_pos = buffer.find_first_not_of("1234567890/");
      if (end_pos == std::string::npos) {
        end_pos = buffer.length();
      }
      std::string num_str = buffer.substr(0, end_pos);
      vertices[i * 2] = stoi(num_str) - 1;
      i++;
      buffer = buffer.substr(end_pos);
    } else {
      buffer = buffer.substr(1);
    }
  }
}

void ViewerModel::Parse3DModel(const std::string &file_name) {
  if (movements_.is_model_loaded == true) {
    FreeMemoryModel();
  } else {
    movements_.is_model_loaded = true;
  }
  ReadObjFile(file_name);
  CalculateMaxValues();
  UpdateVertices();
}

void ViewerModel::SetModelSettings() {
  movements_.frustum = movements_.max_side * (movements_.scale + 1) / 100.0;
  movements_.left =
      movements_.max_left - movements_.max_side * (0.05 + movements_.scale);
  movements_.right =
      movements_.max_left + movements_.max_side * (1.05 + movements_.scale);
  movements_.bottom =
      movements_.max_bottom - movements_.max_side * (0.05 + movements_.scale);
  movements_.top =
      movements_.max_bottom + movements_.max_side * (1.05 + movements_.scale);
  movements_.far =
      movements_.max_far + fabs(movements_.max_far - movements_.max_near);
  movements_.near =
      movements_.max_near - fabs(movements_.max_far - movements_.max_near);
}

void ViewerModel::FreeMemoryModel() {
  delete[] model_.basic_vertices;
  model_.basic_vertices = nullptr;
  delete[] model_.vertices;
  model_.vertices = nullptr;
  for (unsigned int i = 1; i <= model_.count_of_facets; i++) {
    delete[] model_.polygons[i].vertices;
    model_.polygons[i].vertices = nullptr;
  }
  delete[] model_.polygons;
  model_.polygons = nullptr;
}

void ViewerModel::CalculateMaxValues() {
  movements_.max_left = model_.basic_vertices[0];
  movements_.max_right = model_.basic_vertices[0];
  movements_.max_bottom = model_.basic_vertices[1];
  movements_.max_top = model_.basic_vertices[1];
  movements_.max_near = model_.basic_vertices[2];
  movements_.max_far = model_.basic_vertices[2];
  for (unsigned int i = 0; i < model_.count_of_vertices; i++) {
    double x = model_.basic_vertices[3 * i];
    double y = model_.basic_vertices[3 * i + 1];
    double z = model_.basic_vertices[3 * i + 2];

    movements_.max_left = std::min(movements_.max_left, x);
    movements_.max_right = std::max(movements_.max_right, x);
    movements_.max_bottom = std::min(movements_.max_bottom, y);
    movements_.max_top = std::max(movements_.max_top, y);
    movements_.max_near = std::min(movements_.max_near, z);
    movements_.max_far = std::max(movements_.max_far, z);
  }
  movements_.max_side =
      std::max(fabs(movements_.max_right - movements_.max_left),
               fabs(movements_.max_top - movements_.max_bottom));
  movements_.heap_height = movements_.max_side * (2.0 * std::tan(M_PI / 6.0));
}

void ViewerModel::UpdateVertices() {
  SetModelSettings();
  double x = movements_.x_angle * M_PI / 180.0;
  double y = movements_.y_angle * M_PI / 180.0;
  double z = movements_.z_angle * M_PI / 180.0;
  for (unsigned int i = 0; i < 3 * model_.count_of_vertices; i += 3) {
    double x_i = model_.basic_vertices[i];
    double y_i = model_.basic_vertices[i + 1];
    double z_i = model_.basic_vertices[i + 2];
    model_.vertices[i] =
        cos(z) * (cos(y) * x_i + sin(y) * (sin(x) * y_i + cos(x) * z_i)) -
        sin(z) * (cos(x) * y_i - sin(x) * z_i);
    model_.vertices[i + 1] =
        sin(z) * (cos(y) * x_i + sin(y) * (sin(x) * y_i + cos(x) * z_i)) +
        cos(z) * (cos(x) * y_i - sin(x) * z_i);
    model_.vertices[i + 2] =
        -sin(y) * x_i + cos(y) * (sin(x) * y_i + cos(x) * z_i);

    model_.vertices[i] += movements_.x_shift * movements_.max_side / 100;
    model_.vertices[i + 1] += movements_.y_shift * movements_.max_side / 100;
    model_.vertices[i + 2] += movements_.z_shift * movements_.max_side / 50;
  }
}

void ViewerModel::ReadObjFile(const std::string &file_name) {
  file_.open(file_name);
  if (file_.is_open()) {
    CountVerticesAndFacetsFromFile();
    AllocateMemoryForVertices();
    GetDataFromFileToModel();
    file_.close();
  }
}

void ViewerModel::CountVerticesAndFacetsFromFile() {
  model_.count_of_vertices = 0;
  model_.count_of_facets = 0;
  file_.clear();
  file_.seekg(0, std::ios::beg);
  std::string current_string;
  while (std::getline(file_, current_string)) {
    if (current_string.length() >= 2 && current_string[0] == 'v' &&
        current_string[1] == ' ')
      model_.count_of_vertices++;
    if (current_string.length() >= 2 && current_string[0] == 'f' &&
        current_string[1] == ' ')
      model_.count_of_facets++;
  }
}

void ViewerModel::GetDataFromFileToModel() {
  file_.clear();
  file_.seekg(0, std::ios::beg);
  std::string current_string;
  unsigned int k = 0, j = 0;

  while (std::getline(file_, current_string)) {
    if (current_string.size() >= 2 && current_string[0] == 'v' &&
        current_string[1] == ' ') {
      std::istringstream iss(current_string);
      double x, y, z;
      char v;
      if (iss >> v >> x >> y >> z) {
        model_.basic_vertices[k] = x;
        model_.basic_vertices[k + 1] = y;
        model_.basic_vertices[k + 2] = z;
        k += 3;
      }
    }
    if (current_string.size() >= 2 && current_string[0] == 'f' &&
        current_string[1] == ' ') {
      j++;
      model_.polygons[j].numbers_of_vertices_in_facet =
          CountVerticesInFacet(current_string);
      model_.polygons[j].vertices =
          new unsigned int[2 * model_.polygons[j].numbers_of_vertices_in_facet];
      GetVerticesFromFacet(current_string, model_.polygons[j].vertices);
      for (unsigned int i = 1;
           i < 2 * model_.polygons[j].numbers_of_vertices_in_facet - 1;
           i += 2) {
        model_.polygons[j].vertices[i] = model_.polygons[j].vertices[i + 1];
      }
      model_.polygons[j]
          .vertices[model_.polygons[j].numbers_of_vertices_in_facet * 2 - 1] =
          model_.polygons[j].vertices[0];
    }
  }
}
