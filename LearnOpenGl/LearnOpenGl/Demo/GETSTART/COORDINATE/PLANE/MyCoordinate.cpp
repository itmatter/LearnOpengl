//
//  MyCoordinate.cpp
//  LearnOpenGl
//
//  Created by 李礼光 on 2020/9/23.
//  Copyright © 2020 liguang. All rights reserved.
//

#include <iostream>

#include "MyCoordinate.hpp"
#include "MyProgram.hpp"
#include "MyCoordinateShader.hpp"
#include "MyCoordinateVertices.hpp"
#include "glm.hpp"
#include "matrix_transform.hpp"
#include "type_ptr.hpp"

int runMyCoordinate() {
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
    
    //opengl运行模式 -- 单线程, 理解为跟当前的Window做一次绑定操作.
    glfwMakeContextCurrent(window);
    
    //任何的OpenGL接口调用都必须在初始化GLAD库后才可以正常访问。如果成功的话，该接口将返回GL_TRUE，否则就会返回GL_FALSE。
    gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);
    
     //----------------------------------------------------------------------
    //先创建我们的Program对象, 加载顶点着色器程序和片元着色器程序
    MyProgram myProgram = MyProgram(myCoordinateVertexShaderStr, myCoordinateFragmentShaderSrc);
    
    GLuint VBO , VAO , EBO;
    unsigned int squareIndicesCount = 0;
    //创建VBO
    glGenBuffers(1, &VBO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(myCoordinateVertices), myCoordinateVertices, GL_STATIC_DRAW);
 
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
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(myCoordinateVerticesIndices), myCoordinateVerticesIndices, GL_STATIC_DRAW);

    //解绑VAO
    glBindVertexArray(0);
    squareIndicesCount = sizeof(myCoordinateVerticesIndices)/sizeof(myCoordinateVerticesIndices[0]);


    
    //进行绘制
    while(!glfwWindowShouldClose(window)){
       //检查事件
        glfwPollEvents();
        
        //渲染指令
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);
        glUseProgram(myProgram.program);
//        glEnable(GL_DEPTH_TEST);

        ///变换处理
        GLint myModelLoc = glGetUniformLocation(myProgram.program,"myModel");
        GLint myViewLoc = glGetUniformLocation(myProgram.program,"myView");
        GLint myProjectionLoc = glGetUniformLocation(myProgram.program,"myProjection");

        //单位矩阵
        glm::mat4 model = glm::mat4(1.0f);
        glm::mat4 view = glm::mat4(1.0f);
        glm::mat4 projection = glm::mat4(1.0f);
        
        model = glm::rotate(model, glm::radians(-45.0f), glm::vec3(1.0f,0.0f,0.0f));//以x轴旋转45度
        view = glm::translate(view, glm::vec3(0.0f,0.0f, -3.0f)); // 向Z轴的负方向移动
        projection = glm::perspective(glm::radians(60.0f), 1.0f, 0.01f, 100.f);//投影矩阵
        
        glUniformMatrix4fv(myModelLoc, 1, GL_FALSE, glm::value_ptr(model));
        glUniformMatrix4fv(myViewLoc, 1, GL_FALSE, glm::value_ptr(view));
        glUniformMatrix4fv(myProjectionLoc, 1, GL_FALSE, glm::value_ptr(projection));


        
        glBindVertexArray(VAO);
        glDrawElements(GL_TRIANGLES, squareIndicesCount, GL_UNSIGNED_INT, 0);
        glBindVertexArray(0);
        
        //交换缓冲
        glfwSwapBuffers(window);
    }
    
    //程序销毁
    glfwTerminate();
    
    return 1;
}
