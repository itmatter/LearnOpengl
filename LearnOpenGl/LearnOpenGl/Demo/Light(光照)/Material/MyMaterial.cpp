//
//  MyMaterial.cpp
//  LearnOpenGl
//
//  Created by 李礼光 on 2020/10/4.
//  Copyright © 2020 liguang. All rights reserved.
//


#include <iostream>

#include "MyMaterial.hpp"
#include "MyProgram.hpp"
#include "MyMaterialShader.h"
#include "MyMaterialVertices.h"
#include "glm.hpp"
#include "matrix_transform.hpp"
#include "type_ptr.hpp"

#define STB_IMAGE_IMPLEMENTATION
#define STB_IMAGE_STATIC
#include "stb_image.h"


int runMyMaterialCube() {
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
    MyProgram myProgram = MyProgram(myMaterialVertexShaderStr, myMaterialFragmentShaderSrc);

    ///
    GLuint VBO , VAO ;
    unsigned int squareIndicesCount = 0;
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    glBindVertexArray(VAO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(myMaterialVertices), myMaterialVertices, GL_STATIC_DRAW);
    
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), (GLvoid*)(0 * sizeof(GLfloat)));
    glEnableVertexAttribArray(0);

    //法线
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), (GLvoid*)(3 * sizeof(GLfloat)));
    glEnableVertexAttribArray(1);

    //解绑VAO
    glBindVertexArray(0);
    squareIndicesCount = sizeof(myMaterialVertices)/(sizeof(myMaterialVertices[0]) * 5);

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
        
        //材质
        GLint matAmbientLoc = glGetUniformLocation(myProgram.program, "material.ambient");
        GLint matDiffuseLoc = glGetUniformLocation(myProgram.program, "material.diffuse");
        GLint matSpecularLoc = glGetUniformLocation(myProgram.program, "material.specular");
        GLint matShineLoc = glGetUniformLocation(myProgram.program, "material.shininess");

        glUniform3f(matAmbientLoc, 1.0f, 0.5f, 0.31f);
        glUniform3f(matDiffuseLoc, 1.0f, 0.5f, 0.31f);
        glUniform3f(matSpecularLoc, 0.5f, 0.5f, 0.5f);
        glUniform1f(matShineLoc, 64.0f);
        

        //光照强度
        GLint lightAmbientStrengthLoc = glGetUniformLocation(myProgram.program, "light.ambientStrength");
        GLint lightDiffuseStrengthLoc = glGetUniformLocation(myProgram.program, "light.diffuseStrength");
        GLint lightSpecularStrengthLoc = glGetUniformLocation(myProgram.program, "light.specularStrength");

        glUniform3f(lightAmbientStrengthLoc, 0.4f, 0.4f, 0.4f);
        glUniform3f(lightDiffuseStrengthLoc, 0.7f, 0.7f, 0.7f);
        glUniform3f(lightSpecularStrengthLoc, 1.0f, 1.0f, 1.0f);

        //光源位置
        GLint myLightPosLoc = glGetUniformLocation(myProgram.program,"lightPos");
        glUniform3f(myLightPosLoc,1.0f,0.0f,4.0f); //
        
        //镜面反射
        GLint myViewPosLoc = glGetUniformLocation(myProgram.program,"viewPos");
        glUniform3f(myViewPosLoc,0.0,0.0f,3.0f); //
        
        //光照颜色
        GLint lightColorLoc = glGetUniformLocation(myProgram.program,"lightColor");
        glUniform3f(lightColorLoc,1.0f,1.0f,1.0f); //白光
        
//        //动态改变环境光和漫反射光颜色
//        glm::vec3 lightColor = glm::vec3(1.0f,1.0f,1.0f);
//        lightColor.x = sin(glfwGetTime() * 2.0f);
//        lightColor.y = sin(glfwGetTime() * 0.7f);
//        lightColor.z = sin(glfwGetTime() * 1.3f);
//        
//        glm::vec3 ambientColor = lightColor * glm::vec3(0.5f);
//        glm::vec3 diffuseColor = lightColor * glm::vec3(0.5f);
//
//        glUniform3f(matAmbientLoc,ambientColor.x,ambientColor.y,ambientColor.z);
//        glUniform3f(matDiffuseLoc,diffuseColor.x,diffuseColor.y,diffuseColor.z);
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
