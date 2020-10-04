//
//  MyMaterialVertices.h
//  LearnOpenGl
//
//  Created by 李礼光 on 2020/10/4.
//  Copyright © 2020 liguang. All rights reserved.
//

#ifndef MyMaterialVertices_h
#define MyMaterialVertices_h

#include "glad.h"
#include <GLFW/glfw3.h>


GLfloat myMaterialVertices[] = {
    //顶点数据              法线
   -0.5f, -0.5f, -0.5f,   0.0f,  0.0f, -1.0f,
    0.5f, -0.5f, -0.5f,   0.0f,  0.0f, -1.0f,
    0.5f,  0.5f, -0.5f,   0.0f,  0.0f, -1.0f,
    0.5f,  0.5f, -0.5f,   0.0f,  0.0f, -1.0f,
   -0.5f,  0.5f, -0.5f,   0.0f,  0.0f, -1.0f,
   -0.5f, -0.5f, -0.5f,   0.0f,  0.0f, -1.0f,

   -0.5f, -0.5f,  0.5f,   0.0f,  0.0f,  1.0f,
    0.5f, -0.5f,  0.5f,   0.0f,  0.0f,  1.0f,
    0.5f,  0.5f,  0.5f,   0.0f,  0.0f,  1.0f,
    0.5f,  0.5f,  0.5f,   0.0f,  0.0f,  1.0f,
   -0.5f,  0.5f,  0.5f,   0.0f,  0.0f,  1.0f,
   -0.5f, -0.5f,  0.5f,   0.0f,  0.0f,  1.0f,

   -0.5f,  0.5f,  0.5f,  -1.0f,  0.0f,  0.0f,
   -0.5f,  0.5f, -0.5f,  -1.0f,  0.0f,  0.0f,
   -0.5f, -0.5f, -0.5f,  -1.0f,  0.0f,  0.0f,
   -0.5f, -0.5f, -0.5f,  -1.0f,  0.0f,  0.0f,
   -0.5f, -0.5f,  0.5f,  -1.0f,  0.0f,  0.0f,
   -0.5f,  0.5f,  0.5f,  -1.0f,  0.0f,  0.0f,

    0.5f,  0.5f,  0.5f,   1.0f,  0.0f,  0.0f,
    0.5f,  0.5f, -0.5f,   1.0f,  0.0f,  0.0f,
    0.5f, -0.5f, -0.5f,   1.0f,  0.0f,  0.0f,
    0.5f, -0.5f, -0.5f,   1.0f,  0.0f,  0.0f,
    0.5f, -0.5f,  0.5f,   1.0f,  0.0f,  0.0f,
    0.5f,  0.5f,  0.5f,   1.0f,  0.0f,  0.0f,

   -0.5f, -0.5f, -0.5f,   0.0f, -1.0f,  0.0f,
    0.5f, -0.5f, -0.5f,   0.0f, -1.0f,  0.0f,
    0.5f, -0.5f,  0.5f,   0.0f, -1.0f,  0.0f,
    0.5f, -0.5f,  0.5f,   0.0f, -1.0f,  0.0f,
   -0.5f, -0.5f,  0.5f,   0.0f, -1.0f,  0.0f,
   -0.5f, -0.5f, -0.5f,   0.0f, -1.0f,  0.0f,

   -0.5f,  0.5f, -0.5f,   0.0f,  1.0f,  0.0f,
    0.5f,  0.5f, -0.5f,   0.0f,  1.0f,  0.0f,
    0.5f,  0.5f,  0.5f,   0.0f,  1.0f,  0.0f,
    0.5f,  0.5f,  0.5f,   0.0f,  1.0f,  0.0f,
   -0.5f,  0.5f,  0.5f,   0.0f,  1.0f,  0.0f,
   -0.5f,  0.5f, -0.5f,   0.0f,  1.0f,  0.0f,
};


#endif /* MyMaterialVertices_h */
