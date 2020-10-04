//
//  MyCoordinateCubeVertices.hpp
//  LearnOpenGl
//
//  Created by LiGuang on 2020/9/24.
//  Copyright © 2020 liguang. All rights reserved.
//

#ifndef MyCoordinateCubeVertices_h
#define MyCoordinateCubeVertices_h
#include "glad.h"
#include <GLFW/glfw3.h>

//立方体 : 8个点连成一个立方体
static GLfloat myCoordinateCubeVertices[] = {
    //左侧
    -0.5f, -0.5f, -0.5f, 1.0f,0.0f,0.0f, //左下后 红 0
    -0.5f, -0.5f,  0.5f, 1.0f,0.0f,0.0f, //左下前 红 1
    -0.5f,  0.5f,  0.5f, 1.0f,1.0f,0.0f, //左上前 蓝 2
    -0.5f,  0.5f, -0.5f, 1.0f,1.0f,0.0f, //左上后 蓝 3
    //右侧
     0.5f, -0.5f, -0.5f, 0.0f,0.0f,0.0f, //右下后 白 4
     0.5f, -0.5f,  0.5f, 0.0f,0.0f,0.0f, //右下前 白 5
     0.5f,  0.5f,  0.5f, 0.0f,1.0f,1.0f, //右上前 蓝 6
     0.5f,  0.5f, -0.5f, 0.0f,1.0f,1.0f, //右上后 绿 7
};


//立方体索引
static GLint myCoordinateCubeVerticesIndices[] = { // 注意索引从0开始!
    
    //第1面 : 左 0123
    0, 1, 2,
    0, 2, 3,
    
    //第2面 : 右 4567
    4, 5, 6,
    4, 6, 7,

    //第3面 : 上 2367
    2, 3, 6,
    3, 6, 7,

    //第4面 : 下 0145
    0, 1, 4,
    1, 4, 5,

    //第5面 : 前 1256
    1, 2, 5,
    2, 5, 6,

    //第6面 : 后 0347
    0, 3, 4,
    3, 4, 7,
};


// Set up vertex data (and buffer(s)) and attribute pointers
GLfloat vertices[] = {
   -0.5f, -0.5f, -0.5f,  0.0f, 0.0f,
    0.5f, -0.5f, -0.5f,  1.0f, 0.0f,
    0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
    0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
   -0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
   -0.5f, -0.5f, -0.5f,  0.0f, 0.0f,

   -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
    0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
    0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
    0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
   -0.5f,  0.5f,  0.5f,  0.0f, 1.0f,
   -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,

   -0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
   -0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
   -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
   -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
   -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
   -0.5f,  0.5f,  0.5f,  1.0f, 0.0f,

    0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
    0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
    0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
    0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
    0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
    0.5f,  0.5f,  0.5f,  1.0f, 0.0f,

   -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
    0.5f, -0.5f, -0.5f,  1.0f, 1.0f,
    0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
    0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
   -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
   -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,

   -0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
    0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
    0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
    0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
   -0.5f,  0.5f,  0.5f,  0.0f, 0.0f,
   -0.5f,  0.5f, -0.5f,  0.0f, 1.0f
};



#endif /* MyCoordinateCubeVertices_h */
