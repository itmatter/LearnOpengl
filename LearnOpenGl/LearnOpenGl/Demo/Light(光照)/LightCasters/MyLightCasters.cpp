//
//  MyLightCasters.cpp
//  LearnOpenGl
//
//  Created by 李礼光 on 2020/10/5.
//  Copyright © 2020 liguang. All rights reserved.
//

#include <iostream>
#include "MyLightCasters.hpp"
#include "MyProgram.hpp"
#include "MyLightCastersShader.h"
#include "MyLightCastersVertices.h"
#include "glm.hpp"
#include "matrix_transform.hpp"
#include "type_ptr.hpp"

#define STB_IMAGE_IMPLEMENTATION
#define STB_IMAGE_STATIC
#include "stb_image.h"

int runMyLightCastersCube() {
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
    MyProgram myProgram = MyProgram(myLightCastersVertexShaderStr, myLightCastersFragmentShaderSrc);

    ///
    GLuint VBO , VAO ;
    unsigned int squareIndicesCount = 0;
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    glBindVertexArray(VAO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(myLightCastersVertices), myLightCastersVertices, GL_STATIC_DRAW);
    
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (GLvoid*)(0 * sizeof(GLfloat)));
    glEnableVertexAttribArray(0);

    //法线
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (GLvoid*)(3 * sizeof(GLfloat)));
    glEnableVertexAttribArray(1);
    
    //纹理
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (GLvoid*)(6 * sizeof(GLfloat)));
    glEnableVertexAttribArray(2);

    //解绑VAO
    glBindVertexArray(0);
    squareIndicesCount = sizeof(myLightCastersVertices)/(sizeof(myLightCastersVertices[0]) * 8);

    glEnable(GL_DEPTH_TEST);
    
    

    //加载纹理
    unsigned int diffuseCasters_texture;
    unsigned char *diffuseCasters_data;
    int diffuseCasters_width, diffuseCasters_height, diffuseCasters_nrChannels;
    glGenTextures(1, &diffuseCasters_texture);
    glBindTexture(GL_TEXTURE_2D, diffuseCasters_texture);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    diffuseCasters_data = stbi_load( "/Users/liliguang/Desktop/LearnOpengl/LearnOpenGl/LearnOpenGl/Demo/Common/ImgSources/box.png" , &diffuseCasters_width, &diffuseCasters_height, &diffuseCasters_nrChannels, 0);
    if (diffuseCasters_data)
    {
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, diffuseCasters_width, diffuseCasters_height, 0, GL_RGBA, GL_UNSIGNED_BYTE, diffuseCasters_data);
        glGenerateMipmap(GL_TEXTURE_2D);
        glBindTexture(GL_TEXTURE_2D, 0);

    }
    else
    {
        std::cout << "Failed to load texture" << std::endl;
    }
    stbi_image_free(diffuseCasters_data);
    
    
    unsigned int specularCasters_texture;
    unsigned char *specularCasters_data;
    int specularCasters_width, specularCasters_height, specularCasters_nrChannels;
    glGenTextures(1, &specularCasters_texture);
    glBindTexture(GL_TEXTURE_2D, specularCasters_texture);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    specularCasters_data = stbi_load( "/Users/liliguang/Desktop/LearnOpengl/LearnOpenGl/LearnOpenGl/Demo/Common/ImgSources/box_specular.png" , &specularCasters_width, &specularCasters_height, &specularCasters_nrChannels, 0);
    if (specularCasters_data)
    {
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, specularCasters_width, specularCasters_height, 0, GL_RGBA, GL_UNSIGNED_BYTE, specularCasters_data);
        glGenerateMipmap(GL_TEXTURE_2D);
        glBindTexture(GL_TEXTURE_2D, 0);

    }
    else
    {
        std::cout << "Failed to load texture" << std::endl;
    }
    stbi_image_free(specularCasters_data);
    
    
    //材质-光照贴图
    glUseProgram(myProgram.program);

    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, diffuseCasters_texture);
    glUniform1i(glGetUniformLocation(myProgram.program, "material.diffuse"), 0);//环境贴图
    
    glActiveTexture(GL_TEXTURE1);
    glBindTexture(GL_TEXTURE_2D, specularCasters_texture);
    glUniform1i(glGetUniformLocation(myProgram.program, "material.specular"), 1);//环境贴图
    

    
    glm::vec3 cubePositions[] = {
         glm::vec3( 0.0f,  0.0f,  0.0f),
         glm::vec3( 2.0f, -1.0f, -1.0f),
         glm::vec3(-1.5f, -2.2f, -2.5f),
         glm::vec3(-2.8f, -1.0f, -2.3f),
         glm::vec3( 2.4f, -0.4f, -3.5f),
         glm::vec3(-1.7f,  2.0f, -0.1f),
         glm::vec3( 1.3f, -2.0f, -2.2f),
         glm::vec3( 1.5f,  2.0f, -2.9f),
         glm::vec3( 1.5f,  0.2f, -1.5f),
         glm::vec3(-1.3f,  1.0f, -1.2f)
     };
    int cubePositionsCount = sizeof(cubePositions)/(sizeof(cubePositions[0]));

    //进行绘制
    while(!glfwWindowShouldClose(window)){
        glfwPollEvents();
        
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        
        
        //================================================
        glm::mat4 model = glm::mat4(1.0f);
        glm::mat4 view = glm::mat4(1.0f);
        glm::mat4 projection = glm::mat4(1.0f);
        
        GLint myModelLoc = glGetUniformLocation(myProgram.program,"myModel");
        GLint myViewLoc = glGetUniformLocation(myProgram.program,"myView");
        GLint myProjectionLoc = glGetUniformLocation(myProgram.program,"myProjection");
        
        projection = glm::perspective(glm::radians(90.0f), 1.0f, 0.01f, 100.f);//投影矩阵
        glUniformMatrix4fv(myProjectionLoc, 1, GL_FALSE, glm::value_ptr(projection));

        // Material
        glm::vec3 MaterialEye   = glm::vec3(3.0f, 3.0f,  2.0f);
        glm::vec3 MaterialCenter = glm::vec3(1.0f, 1.0f, 0.0f);
        glm::vec3 MaterialUp    = glm::vec3(0.0f, 1.0f,  0.0f);
        
        glBindVertexArray(VAO);
        view = glm::lookAt(MaterialEye,       //摄像机位置
                           MaterialCenter,    //目标
                           MaterialUp);       //上向量
        
        //================================================

        
        
        
        //================================================
        //镜面反射半径
        GLint matShineLoc = glGetUniformLocation(myProgram.program, "material.shininess");
        glUniform1f(matShineLoc, 64.0f);

        //光照强度
        GLint lightAmbientLoc = glGetUniformLocation(myProgram.program, "light.ambient");
        GLint lightDiffuseLoc = glGetUniformLocation(myProgram.program, "light.diffuse");
        GLint lightSpecularLoc = glGetUniformLocation(myProgram.program, "light.specular");

        glUniform3f(lightAmbientLoc, 0.6f, 0.6f, 0.6f);
        glUniform3f(lightDiffuseLoc, 0.9f, 0.9f, 0.9f);
        glUniform3f(lightSpecularLoc, 1.0f, 1.0f, 1.0f);
        
        //镜面反射
        GLint myViewPosLoc = glGetUniformLocation(myProgram.program,"viewPos");
        glUniform3f(myViewPosLoc,0.0,0.0f,3.0f); //
        
        //光照方向
        GLint directionPos = glGetUniformLocation(myProgram.program, "light.direction");
        glUniform3f(directionPos, -0.2f, -1.0f, -0.3f);

        
        for(GLuint i = 0; i < cubePositionsCount; i++)
        {
            model = glm::translate(model, cubePositions[i]);
            GLfloat angle = 20.0f * i;
            model = glm::rotate(model, angle, glm::vec3(1.0f, 0.3f, 0.5f));
            glUniformMatrix4fv(myModelLoc, 1, GL_FALSE, glm::value_ptr(model));
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
