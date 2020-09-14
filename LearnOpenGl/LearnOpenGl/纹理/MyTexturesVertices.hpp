//
//  MyTexturesVertices.hpp
//  LearnOpenGl
//
//  Created by LiGuang on 2020/9/15.
//  Copyright © 2020 liguang. All rights reserved.
//

#ifndef MyTexturesVertices_h
#define MyTexturesVertices_h

//纹理坐标 : 以左下角 (0.0, 0.0) 为原点
static float MyTextureVertices[] = {
//     ---- 位置 ----       ---- 颜色 ----     - 纹理坐标 -
     0.5f,  0.5f, 0.0f,   1.0f, 0.0f, 0.0f,   1.0f, 1.0f,   // 右上
     0.5f, -0.5f, 0.0f,   0.0f, 1.0f, 0.0f,   1.0f, 0.0f,   // 右下
    -0.5f, -0.5f, 0.0f,   0.0f, 0.0f, 1.0f,   0.0f, 0.0f,   // 左下
    -0.5f,  0.5f, 0.0f,   1.0f, 1.0f, 0.0f,   0.0f, 1.0f    // 左上
};

//索引
static unsigned int  MyTextureVerticesIndices[] = { // 注意索引从0开始!
    0, 1, 2, // 第一个三角形
    0, 3, 2  // 第二个三角形
};



#endif /* MyTexturesVertices_h */
