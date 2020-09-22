//
//  MyProgram.cpp
//  LearnOpenGl
//
//  Created by LiGuang on 2020/9/9.
//  Copyright © 2020 liguang. All rights reserved.
//

#include "MyProgram.hpp"
#include "MyShader.hpp"
#include <stdlib.h>
#include <stdio.h>

MyProgram::MyProgram(char* vertexShaderStr, char* fragmentShaderSrc)
{
    //创建Program
    program = glCreateProgram();

    //创建顶点着色器和片元着色器
    MyShader vertexShader(vertexShaderStr, MyGLShaderType::MyGL_SHADER_VERTEX);
    MyShader fragmentShader(fragmentShaderSrc, MyGLShaderType::MyGL_SHADER_FRAGMENT);

    //附着在Program上
    glAttachShader(program, vertexShader.shader);
    glAttachShader(program, fragmentShader.shader);

    
    //绑定
    glLinkProgram(program);

    
    //检查program
    GLint logLen = 0;
    glGetProgramiv(program, GL_INFO_LOG_LENGTH, &logLen);
    if (logLen > 0) {
        char* log = (char*)malloc(logLen);
        glGetProgramInfoLog(program, logLen, NULL, log);

        printf("Program Log:\n");
        printf("%s\n\n", log);

        free(log);
    }
};

MyProgram::~MyProgram()
{
    if (program != NULL) {
        //删除program
        glDeleteProgram(program);
        program = 0;
    }
};
