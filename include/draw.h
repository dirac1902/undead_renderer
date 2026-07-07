#pragma once
#include "const.h"
#include "model.h"
#include "tgaimage.h"
#include "vecmath.h"
#include <array>
#include <iostream>

void drawLine(int x0, int y0, int x1, int y1, TGAImage &image,
              const TGAColor &color) {
  // Bresenham's line algorithm
  // 逐x方向绘制像素
  // 先处理斜率大于1的情况
  bool steep = false;
  if (std::abs(x0 - x1) < std::abs(y0 - y1)) {
    std::swap(x0, y0);
    std::swap(x1, y1);
    steep = true;
  }
  if (x0 > x1) {
    std::swap(x0, x1);
    std::swap(y0, y1);
  }
  for (int x = x0; x <= x1; x++) {
    float t = (x - x0) / (float)(x1 - x0);
    int y = y0 * (1.0 - t) + y1 * t;
    if (steep) {
      image.set(y, x, color);
    } else {
      image.set(x, y, color);
    }
  }
}

float signedArea(const vec3f &v1, const vec3f &v2, const vec3f &v3) {
  return 0.5 * ((v2.y - v1.y) * (v2.x + v1.x) + (v3.y - v2.y) * (v3.x + v2.x) +
                (v1.y - v3.y) * (v1.x + v3.x));
}

bool isInsideTriangle(const vec3f &v, const vec3f &v1, const vec3f &v2,
                      const vec3f &v3) {
  return signedArea(v, v1, v2) > 0 && signedArea(v, v2, v3) > 0 &&
         signedArea(v, v3, v1) > 0;
}

void drawTriangle(
    const vec3f &v1, const vec3f &v2, const vec3f &v3, TGAImage &image,
    const TGAColor &color,
    std::array<std::array<float, imageWidth>, imageHeight> &zbuffer) {
  // 获取包围盒
  // 逐像素绘制
  float min_x = std::min(std::min(v1.x, v2.x), v3.x);
  float max_x = std::max(std::max(v1.x, v2.x), v3.x);
  float min_y = std::min(std::min(v1.y, v2.y), v3.y);
  float max_y = std::max(std::max(v1.y, v2.y), v3.y);

  for (int x = min_x; x <= max_x; x++) {
    for (int y = min_y; y <= max_y; y++) {
      if (isInsideTriangle(vec3f(x, y, 0), v1, v2, v3)) {
        // 绘制像素
        // TODO: z-buffer处理
        // 插值处理
        vec3f p = vec3f(x, y, 0);
        float area = signedArea(v1, v2, v3);
        float w1 = signedArea(p, v2, v3) / area;
        float w2 = signedArea(p, v3, v1) / area;
        float w3 = signedArea(p, v1, v2) / area;

        float z = w1 * v1.z + w2 * v2.z + w3 * v3.z;
        if (z > zbuffer[x][y]) {
          image.set(x, y, color);
          zbuffer[x][y] = z;
        }
      }
    }
  }
}

void wireFrameRendering(TGAImage &image, Model &model) {
  for (auto f : model.f_vertex_index) {
    int verticeIndex1 = f.x;
    int verticeIndex2 = f.y;
    int verticeIndex3 = f.z;

    vec3f v1 = model.vertices[verticeIndex1];
    vec3f v2 = model.vertices[verticeIndex2];
    vec3f v3 = model.vertices[verticeIndex3];

    // draw red lines
    drawLine(v1.x, v1.y, v2.x, v2.y, image, red);
    drawLine(v1.x, v1.y, v3.x, v3.y, image, red);
    drawLine(v2.x, v2.y, v3.x, v3.y, image, red);
  }
}

void drawModelTriangles(TGAImage &image, Model &model) {
  // z-buffer
  std::array<std::array<float, imageWidth>, imageHeight> z_buffer;

  for (auto f : model.f_vertex_index) {
    TGAColor color = {rand() % 256, rand() % 256, rand() % 256, 255};
    drawTriangle(model.vertices[f.x], model.vertices[f.y], model.vertices[f.z],
                 image, color, z_buffer);
  }
}