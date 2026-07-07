#pragma once
#include "vecmath.h"
#include <string>
#include <vector>

// 用来加载、管理模型
class Model {
public:
  Model() = default;
  Model(const std::string filename);

  std::string file_name;
  std::vector<vec3f> vertices;
  std::vector<vec3i> f_vertex_index;
  int getVertexIndex(std::string vertex_info);
};