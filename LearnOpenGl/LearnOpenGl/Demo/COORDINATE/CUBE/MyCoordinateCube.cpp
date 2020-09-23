//
//  MyCoordinateCube.cpp
//  LearnOpenGl
//
//  Created by LiGuang on 2020/9/24.
//  Copyright © 2020 liguang. All rights reserved.
//

#include <iostream>

#include "MyCoordinateCube.hpp"
#include "MyProgram.hpp"
#include "MyCoordinateCubeShader.hpp"
#include "MyCoordinateCubeVertices.hpp"
#include "glm.hpp"
#include "matrix_transform.hpp"
#include "type_ptr.hpp"


int runMyCoordinateCube() {
    int result = glfwInit();
    if (result == GL_FALSE) {
        printf("glfwInit 初始化失败");
        return -1;
    }
    
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GLFW_TRUE);
    GLFWwindow *window = glfwCreateWindow(600, 400, "My Opengl Window", NULL, NULL);
    if(!window) {
        printf("window 创建失败");
    }
    glfwMakeContextCurrent(window);
    gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);
    //----------------------------------------------------------------------
    MyProgram myProgram = MyProgram(myCoordinateCubeVertexShaderStr, myCoordinateCubeFragmentShaderSrc);
    
    GLuint VBO , VAO , EBO;
    unsigned int squareIndicesCount = 0;
    glGenBuffers(1, &VBO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(myCoordinateCubeVertices), myCoordinateCubeVertices, GL_STATIC_DRAW);
    glGenVertexArrays(1, &VAO);
    glBindVertexArray(VAO);
    
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), (GLvoid*)0);
    glEnableVertexAttribArray(0);
    
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), (GLvoid*)(3 * sizeof(GLfloat)));
    glEnableVertexAttribArray(1);
    
    //创建EBO, 这里的EBO相当于索引的作用
    glGenBuffers(1, &EBO);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(myCoordinateCubeVerticesIndices), myCoordinateCubeVerticesIndices, GL_STATIC_DRAW);

    //解绑VAO
    glBindVertexArray(0);
    squareIndicesCount = sizeof(myCoordinateCubeVerticesIndices)/sizeof(myCoordinateCubeVerticesIndices[0]);


    
    //进行绘制
    while(!glfwWindowShouldClose(window)){
       //检查事件
        glfwPollEvents();
        
        //渲染指令
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        glUseProgram(myProgram.program);
         
        glEnable(GL_DEPTH_TEST);

        ///变换处理
        GLint myModelLoc = glGetUniformLocation(myProgram.program,"myModel");
        GLint myViewLoc = glGetUniformLocation(myProgram.program,"myView");
        GLint myProjectionLoc = glGetUniformLocation(myProgram.program,"myProjection");

        //单位矩阵
        glm::mat4 model = glm::mat4(1.0f);
        glm::mat4 view = glm::mat4(1.0f);
        glm::mat4 projection = glm::mat4(1.0f);
        
        model = glm::rotate(model,(GLfloat)glfwGetTime() * 1.0f,  glm::vec3(1.0f,1.0f,0.0f));//以x,y轴旋转
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
