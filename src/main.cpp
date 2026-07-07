#include "tgaimage.h"
#include "math.h"
#include "model.h"
#include "draw.h"
#include "const.h"
#include <fstream>
#include <iostream>
#include <vector>
#include <sstream>

const std::string input_file = "obj/diablo3_pose.obj";
const std::string output_file = "wireframe.tga"; 


int main(int argc, char** argv) {
    TGAImage framebuffer(imageWidth, imageHeight, TGAImage::RGB);
 
    // 加载模型
    Model model(input_file);

    // draw
    wireFrameRendering(framebuffer, model);

    // output tga file
    framebuffer.write_tga_file(output_file);
    return 0;
}