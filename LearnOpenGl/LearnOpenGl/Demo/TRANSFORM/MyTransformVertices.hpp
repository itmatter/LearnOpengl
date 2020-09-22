//
//  TransformVertex.hpp
//  LearnOpenGl
//
//  Created by 李礼光 on 2020/9/21.
//  Copyright © 2020 liguang. All rights reserved.
//

#ifndef TransformVertex_h
#define TransformVertex_h

#include "glad.h"
#include <GLFW/glfw3.h>

//正方形
static GLfloat myTransformVertices[] = {
    -0.5f, -0.5f, 0.0f,  1.0f, 0.0f, 0.0f,  //左下     红
     0.5f, -0.5f, 0.0f,  0.0f, 1.0f, 0.0f,  //右下     绿
     0.5f,  0.5f, 0.0f,  0.0f, 1.0f, 0.0f,  //右上     绿
    -0.5f,  0.5f, 0.0f,  1.0f, 0.0f, 0.0f,  //左上     红
};
  

//索引
static GLint myTransformVerticesIndices[] = { // 注意索引从0开始!
    0, 1, 2, // 第一个三角形
    0, 3, 2  // 第二个三角形
};

#endif /* TransformVertex_h */
