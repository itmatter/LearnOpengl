//
//  MyLight.cpp
//  LearnOpenGl
//
//  Created by 李礼光 on 2020/10/3.
//  Copyright © 2020 liguang. All rights reserved.
//
//  冯氏光照模型

#include <iostream>

#include "MyLight.hpp"
#include "MyProgram.hpp"
#include "MyLightShader.h"
#include "MyLightVertices.h"
#include "glm.hpp"
#include "matrix_transform.hpp"
#include "type_ptr.hpp"

#define STB_IMAGE_IMPLEMENTATION
#define STB_IMAGE_STATIC
#include "stb_image.h"


int runMyLightCube() {
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

    //切换为纹理着色器程序
    MyProgram myProgram = MyProgram(myLightVertexShaderStr, myLightFragmentShaderSrc);

    ///
    GLuint VBO , VAO ;
    unsigned int squareIndicesCount = 0;
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    glBindVertexArray(VAO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(myLightVertices), myLightVertices, GL_STATIC_DRAW);
    
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), (GLvoid*)(0 * sizeof(GLfloat)));
    glEnableVertexAttribArray(0);

    //法线
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), (GLvoid*)(3 * sizeof(GLfloat)));
    glEnableVertexAttribArray(1);

    //解绑VAO
    glBindVertexArray(0);
    squareIndicesCount = sizeof(myLightVertices)/(sizeof(myLightVertices[0]) * 6);

    glEnable(GL_DEPTH_TEST);


    
    //进行绘制
    while(!glfwWindowShouldClose(window)){
        glfwPollEvents();
        
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        glUseProgram(myProgram.program);
        
        
        //================================================
        glm::mat4 model = glm::mat4(1.0f);
        glm::mat4 view = glm::mat4(1.0f);
        glm::mat4 projection = glm::mat4(1.0f);
        
        GLint myModelLoc = glGetUniformLocation(myProgram.program,"myModel");
        GLint myViewLoc = glGetUniformLocation(myProgram.program,"myView");
        GLint myProjectionLoc = glGetUniformLocation(myProgram.program,"myProjection");
        
        projection = glm::perspective(glm::radians(60.0f), 1.0f, 0.01f, 100.f);//投影矩阵
        glUniformMatrix4fv(myProjectionLoc, 1, GL_FALSE, glm::value_ptr(projection));
        
//        model = glm::rotate(model,(GLfloat)glfwGetTime() * 1.0f, glm::vec3(1.0f,0.0f,0.0f));//以x,y轴旋转
        glUniformMatrix4fv(myModelLoc, 1, GL_FALSE, glm::value_ptr(model));

        // Light
        glm::vec3 LightEye   = glm::vec3(2.0f, 2.0f,  2.0f);
        glm::vec3 LightCenter = glm::vec3(0.0f, 0.0f, 0.0f);
        glm::vec3 LightUp    = glm::vec3(0.0f, 1.0f,  0.0f);
        
        glBindVertexArray(VAO);
        view = glm::lookAt(LightEye,       //摄像机位置
                           LightCenter,    //目标
                           LightUp);       //上向量
        
        //旋转
        
        //================================================

        
        
        
        
        //================================================
        //光源位置
        GLint myLightPosLoc = glGetUniformLocation(myProgram.program,"lightPos");
        glUniform3f(myLightPosLoc,1.0,1.3,3.0f); //
        
        //镜面反射
        GLint myViewPosLoc = glGetUniformLocation(myProgram.program,"viewPos");
        glUniform3f(myViewPosLoc,0.0,0.0f,3.0f); //
        
        //物体颜色, 光照颜色
        GLint objectColorLoc = glGetUniformLocation(myProgram.program,"objectColor");
        GLint lightColorLoc = glGetUniformLocation(myProgram.program,"lightColor");

        glUniform3f(objectColorLoc,1.0f,0.5f,0.35f);
        glUniform3f(lightColorLoc,1.0f,1.0f,1.0f); //白光
        //================================================

        
                    
        glUniformMatrix4fv(myViewLoc, 1, GL_FALSE, glm::value_ptr(view));
        glDrawArrays(GL_TRIANGLES, 0, squareIndicesCount);
        glBindVertexArray(0);

        glfwSwapBuffers(window);
    }

    //程序销毁
    glfwTerminate();
    
    return 1;
}


