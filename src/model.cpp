#include "model.h"
#include "const.h"
#include <fstream>
#include <iostream>
#include <sstream>

float convertValue(const float faction, const int val) {
  return (faction + 1.0) / 2.0 * (float)val;
}

Model::Model(const std::string filename) {
  std::ifstream file(filename);
  if (!file) {
    std::cerr << "open file failed!" << std::endl;
  }

  // 读一行
  std::string line;
  while (std::getline(file, line)) {
    std::stringstream ss(line);
    std::string tag;
    ss >> tag;

    // 分tag处理
    if (tag == "v") {
      float x, y, z;
      ss >> x >> y >> z;

      x = convertValue(x, imageWidth);
      y = convertValue(y, imageHeight);
      vertices.push_back(vec3f(x, y, z));
    } else if (tag == "f") {
      std::string v1, v2, v3;
      ss >> v1 >> v2 >> v3;
      f_vertex_index.push_back(
          vec3i(getVertexIndex(v1), getVertexIndex(v2), getVertexIndex(v3)));
    }
  }
}

int Model::getVertexIndex(std::string vertex_info) {
  // 拿到face里的vertex idx
  size_t slash_idx = vertex_info.find('/');
  std::string ret;
  if (slash_idx == std::string::npos) {
    ret = vertex_info;
  } else {
    ret = vertex_info.substr(0, slash_idx);
  }
  return std::stoi(ret) - 1;
}