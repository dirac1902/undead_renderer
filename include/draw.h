#pragma once
#include "tgaimage.h"
#include "math.h"
#include "model.h"
#include "const.h"
#include <iostream>

float convertValue(const float faction, const int val) {
    return (faction + 1.0) / 2.0 * (float) val;
}

void drawLine(int x0, int y0, int x1, int y1, TGAImage &image, const TGAColor &color) {
    // Bresenham's line algorithm
    // 逐x方向绘制像素
    // 先处理斜率大于1的情况
    bool steep = false;
    if(std::abs(x0 -x1) < std::abs(y0 - y1)) {
        std::swap(x0, y0);
        std::swap(x1, y1);
        steep = true;
    }
    if(x0 > x1) {
        std::swap(x0, x1);
        std::swap(y0, y1);
    }
    for(int x = x0; x <= x1; x++) {
        float t = (x - x0) / (float)(x1 - x0);
        int y = y0 * (1.0 - t) + y1 * t;
        if(steep) {
            image.set(y, x, color);
        } else {
            image.set(x, y, color);
        }
    }
}

void drawTriangle(vec3f v1, vec3f v2, vec3f v3) {
    // 获取包围盒
    // 逐像素绘制
    

}

void wireFrameRendering(TGAImage &image, Model &model) {
    for(auto f : model.f_vertex_index) {
        int verticeIndex1 = f.x;
        int verticeIndex2 = f.y;
        int verticeIndex3 = f.z;

        vec3f vertex1 = model.vertices[verticeIndex1];
        vec3f vertex2 = model.vertices[verticeIndex2];
        vec3f vertex3 = model.vertices[verticeIndex3];

        float v1x = convertValue(vertex1.x, imageWidth);
        float v1y = convertValue(vertex1.y, imageHeight);
        float v2x = convertValue(vertex2.x, imageWidth);
        float v2y = convertValue(vertex2.y, imageHeight);
        float v3x = convertValue(vertex3.x, imageWidth);
        float v3y = convertValue(vertex3.y, imageHeight);
        
        // draw red lines
        drawLine(v1x, v1y, v2x, v2y, image, red);
        drawLine(v1x, v1y, v3x, v3y, image, red);
        drawLine(v2x, v2y, v3x, v3y, image, red);
    }
}

