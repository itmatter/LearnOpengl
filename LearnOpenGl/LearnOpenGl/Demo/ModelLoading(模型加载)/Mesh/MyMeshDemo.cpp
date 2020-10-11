//
//  MyMesh.cpp
//  LearnOpenGl
//
//  Created by LiGuang on 2020/10/10.
//  Copyright © 2020 liguang. All rights reserved.
//

#pragma once

#include <string>
#include <fstream>
#include <sstream>
#include <iostream>
#include <vector>

#include "MyMeshDemo.hpp"
#include "MyProgram.hpp"
#include "MyMeshShader.h"
#include "MyCamera.h"
#include "GLHeader.h"

#include "MeshModel.h"

using namespace std;
//using namespace MyModel;


namespace MyMeshDemo {

    // Function prototypes
    void key_callback(GLFWwindow* window, int key, int scancode, int action, int mode);
    void mouse_callback(GLFWwindow* window, double xpos, double ypos);
    void scroll_callback(GLFWwindow* window, double xoffset, double yoffset);
    void do_movement();

    // Window dimensions
    const GLuint WIDTH = 800, HEIGHT = 600;

    // Camera
    Camera  camera(glm::vec3(0.0f, 0.0f, 3.0f));
    GLfloat lastX  =  WIDTH  / 2.0;
    GLfloat lastY  =  HEIGHT / 2.0;
    bool    keys[1024];

    // Light attributes
    glm::vec3 lightPos(1.2f, 1.0f, 2.0f);

    // Deltatime
    GLfloat deltaTime = 0.05f;    // Time between current frame and last frame
    GLfloat lastFrame = 0.05f;      // Time of last frame

    // Is called whenever a key is pressed/released via GLFW
    void key_callback(GLFWwindow* window, int key, int scancode, int action, int mode)
    {
        if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
            glfwSetWindowShouldClose(window, GL_TRUE);
        if (key >= 0 && key < 1024)
        {
            if (action == GLFW_PRESS)
                keys[key] = true;
            else if (action == GLFW_RELEASE)
                keys[key] = false;
        }
    }

    void do_movement()
    {
        // Camera controls
        if (keys[GLFW_KEY_W])
            camera.ProcessKeyboard(FORWARD, deltaTime);
        if (keys[GLFW_KEY_S])
            camera.ProcessKeyboard(BACKWARD, deltaTime);
        if (keys[GLFW_KEY_A])
            camera.ProcessKeyboard(LEFT, deltaTime);
        if (keys[GLFW_KEY_D])
            camera.ProcessKeyboard(RIGHT, deltaTime);
    }

    bool firstMouse = true;
    void mouse_callback(GLFWwindow* window, double xpos, double ypos)
    {
        if (firstMouse)
        {
            lastX = xpos;
            lastY = ypos;
            firstMouse = false;
        }

        GLfloat xoffset = xpos - lastX;
        GLfloat yoffset = lastY - ypos;  // Reversed since y-coordinates go from bottom to left

        lastX = xpos;
        lastY = ypos;

        camera.ProcessMouseMovement(xoffset, yoffset);
    }

    void scroll_callback(GLFWwindow* window, double xoffset, double yoffset)
    {
        camera.ProcessMouseScroll(yoffset);
    }



    int runMyMeshCube() {
        int result = glfwInit();
        if (result == GL_FALSE) {
            printf("glfwInit 初始化失败");
            return -1;
        }
        
    
        glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
        glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
        glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
        glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GLFW_TRUE);
        GLFWwindow *window = glfwCreateWindow(WIDTH, HEIGHT, "My Opengl Window", NULL, NULL);
        if(!window) {
            printf("window 创建失败");
        }
        glfwMakeContextCurrent(window);
        gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);
        glfwSetKeyCallback(window, key_callback);
        glfwSetCursorPosCallback(window, mouse_callback);
        glfwSetScrollCallback(window, scroll_callback);

        //切换为纹理着色器程序
        MyProgram myProgram = MyProgram(myMeshVertexShaderStr, myMeshFragmentShaderSrc);
        glEnable(GL_DEPTH_TEST);
      
        MeshModel ourModel("/Users/lumi/Desktop/LearnOpengl/LearnOpenGl/LearnOpenGl/Demo/3DSources/drill.obj");

        //进行绘制
        while(!glfwWindowShouldClose(window)){
            glfwPollEvents();
            do_movement();

            glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
            glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
            //================================================
            glm::mat4 model = glm::mat4(1.0f);
            glm::mat4 view = glm::mat4(1.0f);
            glm::mat4 projection = glm::mat4(1.0f);
            
            GLint myModelLoc = glGetUniformLocation(myProgram.program,"myModel");
            GLint myViewLoc = glGetUniformLocation(myProgram.program,"myView");
            GLint myProjectionLoc = glGetUniformLocation(myProgram.program,"myProjection");
            
            glUniformMatrix4fv(myModelLoc, 1, GL_FALSE, glm::value_ptr(model));
            projection = glm::perspective(glm::radians(90.0f), 1.0f, 0.01f, 100.f);//投影矩阵
            glUniformMatrix4fv(myProjectionLoc, 1, GL_FALSE, glm::value_ptr(projection));
            
            view = camera.GetViewMatrix();
            glUniform3f(myViewLoc,  camera.Position.x, camera.Position.y, camera.Position.z);
            glUniformMatrix4fv(myViewLoc, 1, GL_FALSE, glm::value_ptr(view));
            //================================================

            //这里传myProgram,因为需要给顶点数据赋值.
            //有点类似于前面多光源里面的for循环, 多个for循环对myProgram里面的模型操作
            //
            //现在缺的是 :
            //
            //顶点着色器
            //layout (location = 0) in vec3 position; //顶点数据源输入
            //layout (location = 1) in vec3 normal; //法向量
            //layout (location = 2) in vec2 texCoords; //纹理数据源输入(2D)
            //
            //片元着色器
            //uniform sampler2D texture_diffuse
            
            //待处理里面的逻辑
            ourModel.Draw(myProgram);

            
            glBindVertexArray(0);
            glfwSwapBuffers(window);
        }

        //程序销毁
        glfwTerminate();
        return 1;
    }
}
