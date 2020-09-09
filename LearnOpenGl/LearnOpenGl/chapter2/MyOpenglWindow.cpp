//
//  MyOpenglWindow.cpp
//  LearnOpenGl
//
//  Created by LiGuang on 2020/9/7.
//  Copyright © 2020 liguang. All rights reserved.
//

#include "MyOpenglWindow.hpp"
#include <iostream>
#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "MyShader.hpp"
#include "MyProgram.hpp"


int runMyOpenGlWindow() {
        
    int result = glfwInit();
    if (result == GL_FALSE) {
        printf("glfwInit 初始化失败");
        return -1;
    }
    
    //这里的宏不好提示出来, 根据LearnOpenGL的文档提示, 用这三个
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    //Mac平台需要加入
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GLFW_TRUE);

    //创建一个Window
    GLFWwindow *window = glfwCreateWindow(600, 400, "My Opengl Window", NULL, NULL);
    if(!window) {
        printf("window 创建失败");

    }
    
    
    //Makes the context of the specified window current for the calling thread.
    //opengl运行模式 -- 单线程, 理解为跟当前的Window做一次绑定操作.
    //多个线程同时调用不被允许
    glfwMakeContextCurrent(window);
    
    //任何的OpenGL接口调用都必须在初始化GLAD库后才可以正常访问。如果成功的话，该接口将返回GL_TRUE，否则就会返回GL_FALSE。
    gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);
    
    
    
    //----------------------------------------------------------------------
    // 创建和编辑顶点着色器在这里面
    
    
    
    
    
    
    
    //----------------------------------------------------------------------


    
    //进行绘制
    while(!glfwWindowShouldClose(window)){
        glfwSwapBuffers(window);
        glfwPollEvents();
    }
    
    
    //程序销毁
    glfwTerminate();
    
    return 1;
}
