//
//  VertexSources.h
//  LearnOpenGl
//
//  Created by LiGuang on 2020/9/14.
//  Copyright © 2020 liguang. All rights reserved.
//


#ifndef VertexSources_h
#define VertexSources_h

#include <glad/glad.h>
#include <GLFW/glfw3.h>

// 模拟顶点数据
//三角形
//GLfloat triangleVertices[] = {
//    -0.5f, -0.5f, 0.0f,  //左下
//     0.5f, -0.5f, 0.0f,  //右下
//     0.0f,  0.5f, 0.0f,   //中上
//};

//三角形
static GLfloat triangleVertices[] = {
    //顶点数据            //颜色数据
    -0.5f, -0.5f, 0.0f,  1.0f, 0.0f, 0.0f, //左下     红
     0.5f, -0.5f, 0.0f,  0.0f, 1.0f, 0.0f, //右下     绿
     0.0f,  0.5f, 0.0f,  0.0f, 0.0f, 1.0f, //中上     蓝
};
  

////正方形
//GLfloat squareVertices[] = {
//    -0.5f, -0.5f, 0.0f,     //左下
//     0.5f, -0.5f, 0.0f,     //右下
//     0.5f,  0.5f, 0.0f,     //右上
//    -0.5f,  0.5f, 0.0f,     //左上
//};

//正方形
static GLfloat squareVertices[] = {
    -0.5f, -0.5f, 0.0f,  1.0f, 0.0f, 0.0f,  //左下     红
     0.5f, -0.5f, 0.0f,  0.0f, 1.0f, 0.0f,  //右下     绿
     0.5f,  0.5f, 0.0f,  0.0f, 1.0f, 0.0f,  //右上     绿
    -0.5f,  0.5f, 0.0f,  1.0f, 0.0f, 0.0f,  //左上     红
};
  
  
static unsigned int  squareIndices[] = { // 注意索引从0开始!
    0, 1, 2, // 第一个三角形
    0, 3, 2  // 第二个三角形
};







#endif
