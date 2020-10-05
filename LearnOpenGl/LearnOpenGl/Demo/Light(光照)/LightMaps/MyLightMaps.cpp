//
//  MyLightMaps.cpp
//  LearnOpenGl
//
//  Created by 李礼光 on 2020/10/5.
//  Copyright © 2020 liguang. All rights reserved.
//


#include <iostream>
#include "MyLightMaps.hpp"
#include "MyProgram.hpp"
#include "MyLightMapsShader.h"
#include "MyLightMapsVertices.h"
#include "glm.hpp"
#include "matrix_transform.hpp"
#include "type_ptr.hpp"

#define STB_IMAGE_IMPLEMENTATION
#define STB_IMAGE_STATIC
#include "stb_image.h"


int runMyLightMapsCube() {
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
    MyProgram myProgram = MyProgram(myLightMapsVertexShaderStr, myLightMapsFragmentShaderSrc);

    ///
    GLuint VBO , VAO ;
    unsigned int squareIndicesCount = 0;
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    glBindVertexArray(VAO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(myLightMapsVertices), myLightMapsVertices, GL_STATIC_DRAW);
    
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
    squareIndicesCount = sizeof(myLightMapsVertices)/(sizeof(myLightMapsVertices[0]) * 8);

    glEnable(GL_DEPTH_TEST);
    
    
    

    //加载纹理
    unsigned int diffuseMaps_texture;
    unsigned char *diffuseMaps_data;
    int diffuseMaps_width, diffuseMaps_height, diffuseMaps_nrChannels;
    glGenTextures(1, &diffuseMaps_texture);
    glBindTexture(GL_TEXTURE_2D, diffuseMaps_texture);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    diffuseMaps_data = stbi_load( "/Users/liliguang/Desktop/LearnOpengl/LearnOpenGl/LearnOpenGl/Demo/Common/ImgSources/box.png" , &diffuseMaps_width, &diffuseMaps_height, &diffuseMaps_nrChannels, 0);
    if (diffuseMaps_data)
    {
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, diffuseMaps_width, diffuseMaps_height, 0, GL_RGBA, GL_UNSIGNED_BYTE, diffuseMaps_data);
        glGenerateMipmap(GL_TEXTURE_2D);
        glBindTexture(GL_TEXTURE_2D, 0);

    }
    else
    {
        std::cout << "Failed to load texture" << std::endl;
    }
    stbi_image_free(diffuseMaps_data);
    
    
    unsigned int specularMaps_texture;
    unsigned char *specularMaps_data;
    int specularMaps_width, specularMaps_height, specularMaps_nrChannels;
    glGenTextures(1, &specularMaps_texture);
    glBindTexture(GL_TEXTURE_2D, specularMaps_texture);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    specularMaps_data = stbi_load( "/Users/liliguang/Desktop/LearnOpengl/LearnOpenGl/LearnOpenGl/Demo/Common/ImgSources/box_specular.png" , &specularMaps_width, &specularMaps_height, &specularMaps_nrChannels, 0);
    if (specularMaps_data)
    {
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, specularMaps_width, specularMaps_height, 0, GL_RGBA, GL_UNSIGNED_BYTE, specularMaps_data);
        glGenerateMipmap(GL_TEXTURE_2D);
        glBindTexture(GL_TEXTURE_2D, 0);

    }
    else
    {
        std::cout << "Failed to load texture" << std::endl;
    }
    stbi_image_free(specularMaps_data);
    
    
    //材质-光照贴图
    glUseProgram(myProgram.program);

    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, diffuseMaps_texture);
    glUniform1i(glGetUniformLocation(myProgram.program, "material.diffuse"), 0);//环境贴图
    
    glActiveTexture(GL_TEXTURE1);
    glBindTexture(GL_TEXTURE_2D, specularMaps_texture);
    glUniform1i(glGetUniformLocation(myProgram.program, "material.specular"), 1);//环境贴图
    
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
        
        projection = glm::perspective(glm::radians(60.0f), 1.0f, 0.01f, 100.f);//投影矩阵
        glUniformMatrix4fv(myProjectionLoc, 1, GL_FALSE, glm::value_ptr(projection));
        glUniformMatrix4fv(myModelLoc, 1, GL_FALSE, glm::value_ptr(model));

        // Material
        glm::vec3 MaterialEye   = glm::vec3(2.0f, 2.0f,  2.0f);
        glm::vec3 MaterialCenter = glm::vec3(0.0f, 0.0f, 0.0f);
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

        //光源位置
        GLint myLightPosLoc = glGetUniformLocation(myProgram.program,"lightPos");
        glUniform3f(myLightPosLoc,1.0f,0.0f,4.0f); //
        
        //镜面反射
        GLint myViewPosLoc = glGetUniformLocation(myProgram.program,"viewPos");
        glUniform3f(myViewPosLoc,0.0,0.0f,3.0f); //
        
        //光照颜色
        GLint lightColorLoc = glGetUniformLocation(myProgram.program,"lightColor");
        glUniform3f(lightColorLoc,1.0f,1.0f,1.0f); //白光
                    
        glUniformMatrix4fv(myViewLoc, 1, GL_FALSE, glm::value_ptr(view));
        glDrawArrays(GL_TRIANGLES, 0, squareIndicesCount);
        glBindVertexArray(0);

        glfwSwapBuffers(window);
    }

    //程序销毁
    glfwTerminate();
    
    return 1;
}
