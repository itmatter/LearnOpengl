//
//  MyTextures.cpp
//  LearnOpenGl
//
//  Created by LiGuang on 2020/9/14.
//  Copyright © 2020 liguang. All rights reserved.
//

#include <iostream>
#include "MyTextures.hpp"
#include "MyProgram.hpp"

int runMyTextureOpenGlWindow() {
    int result = glfwInit();
    if (result == GL_FALSE) {
        printf("glfwInit 初始化失败");
        return -1;
    }

    //这里的宏不好提示出来, 根据LearnOpenGL的文档提示, 用这三个
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GLFW_TRUE);

    //创建一个Window
    GLFWwindow *window = glfwCreateWindow(600, 400, "My Opengl Window", NULL, NULL);
    if(!window) {
        printf("window 创建失败");

    }

    //opengl运行模式 -- 单线程, 理解为跟当前的Window做一次绑定操作.
    glfwMakeContextCurrent(window);
    //任何的OpenGL接口调用都必须在初始化GLAD库后才可以正常访问。如果成功的话，该接口将返回GL_TRUE，否则就会返回GL_FALSE。
    gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);


     //----------------------------------------------------------------------
    //先创建我们的Program对象, 加载顶点着色器程序和片元着色器程序
    MyProgram myProgram = MyProgram(vertexShaderStr, fragmentShaderSrc);




    GLuint VBO , VAO , EBO;
    unsigned int squareIndicesCount = 0;

    //创建VBO
    glGenBuffers(1, &VBO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(squareVertices), squareVertices, GL_STATIC_DRAW);

    //创建VAO
    glGenVertexArrays(1, &VAO);
    glBindVertexArray(VAO);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), (GLvoid*)0);
    glEnableVertexAttribArray(0);

    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), (GLvoid*)(3 * sizeof(GLfloat)));
    glEnableVertexAttribArray(1);

    //创建EBO, 这里的EBO相当于索引的作用
    glGenBuffers(1, &EBO);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(squareIndices), squareIndices, GL_STATIC_DRAW);

    //解绑VAO
    glBindVertexArray(0);
    squareIndicesCount = sizeof(squareIndices)/sizeof(squareIndices[0]);
 
    //进行绘制
    while(!glfwWindowShouldClose(window)){
       //检查事件
        glfwPollEvents();

        //渲染指令
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        //在glUseProgram函数调用之后，每个着色器调用和渲染调用都会使用这个程序对象（也就是之前写的着色器)了。
        glUseProgram(myProgram.program);


        glBindVertexArray(VAO);

        //使用EBO
        glDrawElements(GL_TRIANGLES, squareIndicesCount, GL_UNSIGNED_INT, 0);


        //主要渲染函数
        glBindVertexArray(0);

        //交换缓冲
        glfwSwapBuffers(window);
    }


    //程序销毁
    glfwTerminate();
    return 1;
}
