//
//  MyShader.cpp
//  LearnOpenGl
//
//  Created by LiGuang on 2020/9/9.
//  Copyright © 2020 liguang. All rights reserved.
//

#include "MyShader.hpp"
#include <stdlib.h>
#include <stdio.h>

    

MyShader::MyShader(char* shaderStr, MyGLShaderType type)
{
    
    //创建Shader
    if (type == MyGLShaderType::MyGL_SHADER_VERTEX) {
        shader = glCreateShader(GL_VERTEX_SHADER);
    }
    else if(type == MyGLShaderType::MyGL_SHADER_FRAGMENT){
        shader = glCreateShader(GL_FRAGMENT_SHADER);
    }
    else {
        shader = glCreateShader(GL_VERTEX_SHADER);
    }
    
    //加载ShaderStr
    glShaderSource(shader, 1, &shaderStr, NULL);

    //编译Shader
    glCompileShader(shader);

    //检查Shader数据
    GLint status;
    glGetShaderiv(shader, GL_COMPILE_STATUS, &status);

    GLint logLen = 0;
    glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &logLen);
    if (logLen > 0) {
        char* log = (char*)malloc(logLen);
        glGetShaderInfoLog(shader, logLen, NULL, log);

        printf("Shader Log:\n");
        printf("%s\n", log);

        free(log);
    }
};

MyShader::~MyShader()
{
    if (shader != 0) {
        //删除Shader
        glDeleteShader(shader);
        shader = 0;
    }
};

