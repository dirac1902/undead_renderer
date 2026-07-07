#include "const.h"
#include "draw.h"
#include "model.h"
#include "tgaimage.h"
#include "vecmath.h"
#include <fstream>
#include <iostream>
#include <sstream>
#include <vector>

const std::string input_file = "obj/diablo3_pose.obj";
const std::string output_file = "triangle.tga";

int main(int argc, char **argv) {
  TGAImage framebuffer(imageWidth, imageHeight, TGAImage::RGB);

  // 加载模型
  Model model(input_file);

  // draw
  // wireFrameRendering(framebuffer, model);
  drawModelTriangles(framebuffer, model);

  // output tga file
  framebuffer.write_tga_file(output_file);
  return 0;
}