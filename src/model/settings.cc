#include "settings.h"

using s21::ViewerSettings;

void ViewerSettings::LoadConfigurationFile(const std::string &path) {
  std::ifstream file(path, std::ios::binary);
  if (file.is_open()) {
    file.read(reinterpret_cast<char *>(this), sizeof(ViewerSettings));
    file.close();
  }
}

void ViewerSettings::SaveConfigurationFile(const std::string &path) {
  std::ofstream file(path, std::ios::binary | std::ios::trunc);
  if (file.is_open()) {
    file.write(reinterpret_cast<char *>(this), sizeof(ViewerSettings));
    file.close();
  }
}
