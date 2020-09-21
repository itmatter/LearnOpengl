//
//  MyShader.hpp
//  LearnOpenGl
//
//  Created by LiGuang on 2020/9/9.
//  Copyright © 2020 liguang. All rights reserved.
//

#ifndef MyShader_hpp
#define MyShader_hpp


#include <glad/glad.h>
#include <GLFW/glfw3.h>


enum MyGLShaderType
{
    MyGL_SHADER_VERTEX = 1,
    MyGL_SHADER_FRAGMENT = 2
};


class MyShader {
    public:
        MyShader(char * shaderStr, MyGLShaderType type);
        ~MyShader();
    public:
        GLuint shader = 0;
};

#endif /* MyShader_hpp */
