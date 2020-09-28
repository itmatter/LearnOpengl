//
//  MyCamera.cpp
//  LearnOpenGl
//
//  Created by LiGuang on 2020/9/28.
//  Copyright © 2020 liguang. All rights reserved.
//

#include <iostream>

#include "MyCamera.hpp"
#include "MyProgram.hpp"
#include "MyCameraShader.hpp"
#include "MyCameraVertices.hpp"
#include "glm.hpp"
#include "matrix_transform.hpp"
#include "type_ptr.hpp"


#define STB_IMAGE_IMPLEMENTATION
#define STB_IMAGE_STATIC
#include "stb_image.h"

int runMyCameraCube() {
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
    MyProgram myProgram = MyProgram(myCameraVertexShaderStr, myCameraFragmentShaderSrc);

    ///
    GLuint VBO , VAO ;
    unsigned int squareIndicesCount = 0;
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    glBindVertexArray(VAO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(myCameraVertices), myCameraVertices, GL_STATIC_DRAW);
    
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(GLfloat), (GLvoid*)(0 * sizeof(GLfloat)));
    glEnableVertexAttribArray(0);


    //纹理坐标, 纹理坐标用的三角形坐标一致
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(GLfloat), (GLvoid*)(3 * sizeof(GLfloat)));
    glEnableVertexAttribArray(1);

    //解绑VAO
    glBindVertexArray(0);
    squareIndicesCount = sizeof(myCameraVertices)/(sizeof(myCameraVertices[0]) * 5);
    

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

    
    glm::vec3 cubePositions[2];
    for (int i = 0; i<2; i++) {
        if (i == 0) {
            cubePositions[i] =glm::vec3( 0.0f,  0.0f,  0.0f);
        } else {
            float xRandomNum = arc4random_uniform(10.0) - 5.0f;
            float yRandomNum = arc4random_uniform(10.0) - 5.0f;
            cubePositions[i] =glm::vec3( xRandomNum,  yRandomNum,  0.0f);
        }
    }
    
    //进行绘制
    while(!glfwWindowShouldClose(window)){
        glfwPollEvents();
        
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        glUseProgram(myProgram.program);

        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, texture);
        glUniform1i(glGetUniformLocation(myProgram.program, "myTexture"), 0);
        
        
        glm::mat4 model = glm::mat4(1.0f);
        glm::mat4 view = glm::mat4(1.0f);
        glm::mat4 projection = glm::mat4(1.0f);
        
        GLint myModelLoc = glGetUniformLocation(myProgram.program,"myModel");
        GLint myViewLoc = glGetUniformLocation(myProgram.program,"myView");
        GLint myProjectionLoc = glGetUniformLocation(myProgram.program,"myProjection");
        
        projection = glm::perspective(glm::radians(60.0f), 1.0f, 0.01f, 100.f);//投影矩阵
        glUniformMatrix4fv(myProjectionLoc, 1, GL_FALSE, glm::value_ptr(projection));
        
        glBindVertexArray(VAO);
        for(unsigned int i = 0; i < 2; i++)
        {
            //改变模型数据的位置
            model = glm::mat4(1.0f);
            model = glm::translate(model,glm::vec3(cubePositions[i].x,cubePositions[i].y,0.0f));//x,y平移
            glUniformMatrix4fv(myModelLoc, 1, GL_FALSE, glm::value_ptr(model));

            // 观察矩阵用视摄像机视角,也就是旋转摄像机
            GLfloat radius = 10.0f;
            GLfloat camX = sin(glfwGetTime()) * radius;
            GLfloat camZ = cos(glfwGetTime()) * radius;
            view = glm::lookAt(glm::vec3(camX, 0.0f, camZ),
                               glm::vec3(0.0f, 0.0f, 0.0f),
                               glm::vec3(0.0f, 1.0f, 0.0f));
            
            glUniformMatrix4fv(myViewLoc, 1, GL_FALSE, glm::value_ptr(view));

            glDrawArrays(GL_TRIANGLES, 0, squareIndicesCount);

        }
        glBindVertexArray(0);

        glfwSwapBuffers(window);
    }

    //程序销毁
    glfwTerminate();
    
    return 1;
}
