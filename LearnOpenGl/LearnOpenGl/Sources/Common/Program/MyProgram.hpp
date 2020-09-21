//
//  MyProgram.hpp
//  LearnOpenGl
//
//  Created by LiGuang on 2020/9/9.
//  Copyright © 2020 liguang. All rights reserved.
//


#ifndef MyProgram_hpp
#define MyProgram_hpp

#include "glad.h"
#include <GLFW/glfw3.h>

class MyProgram {
    public:
        MyProgram(char * vertexShaderStr, char * fragmentShaderSrc);
        ~MyProgram();
    public:
        GLuint program = 0;
};


#endif /* MyProgram_hpp */
