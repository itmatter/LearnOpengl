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

#define STB_IMAGE_IMPLEMENTATION
#define STB_IMAGE_STATIC
#include "stb_image.h"

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
//    MyProgram myProgram = MyProgram(myCoordinateCubeVertexShaderStr, myCoordinateCubeFragmentShaderSrc);
    
    //切换为纹理着色器程序
    MyProgram myProgram = MyProgram(myCoordinateCubeTextureVertexShaderStr, myCoordinateCubeTextureFragmentShaderSrc);

//
//    GLuint VBO , VAO , EBO;
//    unsigned int squareIndicesCount = 0;
//    glGenBuffers(1, &VBO);
//    glBindBuffer(GL_ARRAY_BUFFER, VBO);
//    glBufferData(GL_ARRAY_BUFFER, sizeof(myCoordinateCubeVertices), myCoordinateCubeVertices, GL_STATIC_DRAW);
//    glGenVertexArrays(1, &VAO);
//    glBindVertexArray(VAO);
//
//    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), (GLvoid*)0);
//    glEnableVertexAttribArray(0);
//
//    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), (GLvoid*)(3 * sizeof(GLfloat)));
//    glEnableVertexAttribArray(1);
//
//    //纹理坐标, 纹理坐标用的三角形坐标一致
//    glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (GLvoid*)0);
//    glEnableVertexAttribArray(2);
//
//
//    //创建EBO, 这里的EBO相当于索引的作用
//    glGenBuffers(1, &EBO);
//    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
//    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(myCoordinateCubeVerticesIndices), myCoordinateCubeVerticesIndices, GL_STATIC_DRAW);
//
//    //解绑VAO
//    glBindVertexArray(0);
//    squareIndicesCount = sizeof(myCoordinateCubeVerticesIndices)/sizeof(myCoordinateCubeVerticesIndices[0]);
//
//
    
    
    ///
    
    ///
    GLuint VBO , VAO ;
    unsigned int squareIndicesCount = 0;
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    glBindVertexArray(VAO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
    
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(GLfloat), (GLvoid*)(0 * sizeof(GLfloat)));
    glEnableVertexAttribArray(0);


    //纹理坐标, 纹理坐标用的三角形坐标一致
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(GLfloat), (GLvoid*)(3 * sizeof(GLfloat)));
    glEnableVertexAttribArray(2);

    //解绑VAO
    glBindVertexArray(0);
    squareIndicesCount = sizeof(vertices)/(sizeof(vertices[0]) * 5);
    
    
    
    
    
    

    //生成纹理
    unsigned int texture;
    unsigned char *data;
    int width, height, nrChannels;
    glGenTextures(1, &texture);
    glBindTexture(GL_TEXTURE_2D, texture);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    data = stbi_load( "/Users/liliguang/Desktop/LearnOpengl/LearnOpenGl/LearnOpenGl/Demo/Common/ImgSources/dizhuan.jpg" , &width, &height, &nrChannels, 0);
    if (data)
    {
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
        glGenerateMipmap(GL_TEXTURE_2D);
        glBindTexture(GL_TEXTURE_2D, 0);

    }
    else
    {
        std::cout << "Failed to load texture" << std::endl;
    }
    stbi_image_free(data);
    
    glEnable(GL_DEPTH_TEST);

    glm::vec3 cubePositions[10];
    for (int i = 0; i<10; i++) {
        float xRandomNum = arc4random_uniform(10.0) - 5.0f;
        float yRandomNum = arc4random_uniform(10.0) - 5.0f;
        cubePositions[i] =glm::vec3( xRandomNum,  yRandomNum,  0.0f);
    }

    //进行绘制
    while(!glfwWindowShouldClose(window)){
       //检查事件
        glfwPollEvents();
        
        //渲染指令
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        glUseProgram(myProgram.program);

        //加载纹理
        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, texture);
        glUniform1i(glGetUniformLocation(myProgram.program, "myTexture"), 0);
        
        
        //单位矩阵
        glm::mat4 model = glm::mat4(1.0f);
        glm::mat4 view = glm::mat4(1.0f);
        glm::mat4 projection = glm::mat4(1.0f);
        
        ///变换处理
        GLint myModelLoc = glGetUniformLocation(myProgram.program,"myModel");
        GLint myViewLoc = glGetUniformLocation(myProgram.program,"myView");
        GLint myProjectionLoc = glGetUniformLocation(myProgram.program,"myProjection");
              
        projection = glm::perspective(glm::radians(120.0f), 1.0f, 0.01f, 100.f);//投影矩阵
        glUniformMatrix4fv(myProjectionLoc, 1, GL_FALSE, glm::value_ptr(projection));
        
        glBindVertexArray(VAO);
        for(unsigned int i = 0; i < 10; i++)
        {
            //改变模型数据的位置
            model = glm::mat4(1.0f);
            model = glm::translate(model,glm::vec3(cubePositions[i].x,cubePositions[i].y,0.0f));//x,y平移
            glUniformMatrix4fv(myModelLoc, 1, GL_FALSE, glm::value_ptr(model));

            view = glm::mat4(1.0f);
            view = glm::translate(view, glm::vec3(0.0f, 0.0f, -3.0f)); // 向Z轴的负方向移动
            view = glm::rotate(view,(GLfloat)glfwGetTime() * 1.0f,  glm::vec3(cubePositions[i].x,cubePositions[i].y,0.0f));//以x,y轴旋转
            glUniformMatrix4fv(myViewLoc, 1, GL_FALSE, glm::value_ptr(view));
            glDrawArrays(GL_TRIANGLES, 0, squareIndicesCount);

        }
        glBindVertexArray(0);
        //交换缓冲
        glfwSwapBuffers(window);
    }

    //程序销毁
    glfwTerminate();
    
    return 1;
}
