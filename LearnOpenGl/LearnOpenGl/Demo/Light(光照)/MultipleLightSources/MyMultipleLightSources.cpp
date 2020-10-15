//
//  MyMultipleLightSources.cpp
//  LearnOpenGl
//
//  Created by 李礼光 on 2020/10/7.
//  Copyright © 2020 liguang. All rights reserved.
//

#include <iostream>
#include "MyMultipleLightSources.hpp"
#include "MyProgram.hpp"
#include "MyMultipleLightSourcesShader.h"
#include "MyMultipleLightSourcesVertices.h"
#include "MyCamera.h"

#include "glm.hpp"
#include "matrix_transform.hpp"
#include "type_ptr.hpp"

#define STB_IMAGE_IMPLEMENTATION
#define STB_IMAGE_STATIC
#include "stb_image.h"

namespace MyMultipleLightSources {
// Function prototypes
    void key_callback(GLFWwindow* window, int key, int scancode, int action, int mode);
    void mouse_callback(GLFWwindow* window, double xpos, double ypos);
    void scroll_callback(GLFWwindow* window, double xoffset, double yoffset);
    void do_movement();

    // Window dimensions
    const GLuint WIDTH = 800, HEIGHT = 600;

    // Camera
    MyCamera  camera(glm::vec3(0.0f, 0.0f, 3.0f));
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


    int runMyMultipleLightSourcesCube() {
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

        
        //设置(键盘鼠标)输入事件
        //此函数设置指定窗口的按键回调，当按下，重复或释放按键时调用该回调。
        glfwSetKeyCallback(window, key_callback);
        
        //此函数设置指定窗口的光标位置回调，在移动光标时调用该回调。 回调提供了相对于窗口内容区域左上角的屏幕坐标位置。
        glfwSetCursorPosCallback(window, mouse_callback);

        //此函数设置指定窗口的滚动回调，在使用滚动设备（例如鼠标滚轮或触摸板的滚动区域）时调用此回调。
        //滚动回调接收所有滚动输入，例如来自鼠标滚轮或触摸板滚动区域的滚动输入。
        glfwSetScrollCallback(window, scroll_callback);

        //glfwSetInputMode
        //光标模式值 : GLFW_CURSOR_DISABLED
        //glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
        
        //切换为纹理着色器程序
        MyProgram myProgram = MyProgram(myMyMultipleLightSourcesVertexShaderStr, myMyMultipleLightSourcesFragmentShaderSrc);

        ///
        GLuint VBO , VAO ;
        unsigned int squareIndicesCount = 0;
        glGenVertexArrays(1, &VAO);
        glGenBuffers(1, &VBO);
        glBindVertexArray(VAO);

        glBindBuffer(GL_ARRAY_BUFFER, VBO);
        glBufferData(GL_ARRAY_BUFFER, sizeof(myMultipleLightSourcesVertices), myMultipleLightSourcesVertices, GL_STATIC_DRAW);
        
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
        squareIndicesCount = sizeof(myMultipleLightSourcesVertices)/(sizeof(myMultipleLightSourcesVertices[0]) * 8);

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

        //Cube位置
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

        //点光源位置
        glm::vec3 pointLightPositions[] = {
            glm::vec3( 0.7f,  0.2f,  2.0f),
            glm::vec3( 2.3f, -3.3f, -4.0f),
            glm::vec3(-4.0f,  2.0f, -12.0f),
            glm::vec3( 0.0f,  0.0f, -3.0f)
        };
        
        
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
            
            projection = glm::perspective(glm::radians(90.0f), 1.0f, 0.01f, 100.f);//投影矩阵
            glUniformMatrix4fv(myProjectionLoc, 1, GL_FALSE, glm::value_ptr(projection));
            
            view = camera.GetViewMatrix();
            glUniform3f(myViewLoc,  camera.Position.x, camera.Position.y, camera.Position.z);
            glUniformMatrix4fv(myViewLoc, 1, GL_FALSE, glm::value_ptr(view));
            glBindVertexArray(VAO);
            //================================================

            
            
            //光照
            //================================================
            //镜面反射半径
            GLint matShineLoc = glGetUniformLocation(myProgram.program, "material.shininess");
            glUniform1f(matShineLoc, 64.0f);
            GLint viewPosLoc  = glGetUniformLocation(myProgram.program, "viewPos");
            glUniform3f(viewPosLoc,  camera.Position.x, camera.Position.y, camera.Position.z);

            // 定向光源
            glUniform3f(glGetUniformLocation(myProgram.program, "dirLight.direction"), -0.2f, -1.0f, -0.3f);
            glUniform3f(glGetUniformLocation(myProgram.program, "dirLight.ambient"), 0.05f, 0.05f, 0.05f);
            glUniform3f(glGetUniformLocation(myProgram.program, "dirLight.diffuse"), 0.4f, 0.4f, 0.4f);
            glUniform3f(glGetUniformLocation(myProgram.program, "dirLight.specular"), 0.5f, 0.5f, 0.5f);
            
            // 点光源 1 红色
            glUniform3f(glGetUniformLocation(myProgram.program, "pointLights[0].position"), pointLightPositions[0].x, pointLightPositions[0].y, pointLightPositions[0].z);
            glUniform3f(glGetUniformLocation(myProgram.program, "pointLights[0].ambient"), 1.0f, 0.0f, 0.0f);
            glUniform3f(glGetUniformLocation(myProgram.program, "pointLights[0].diffuse"), 0.8f, 0.8f, 0.8f);
            glUniform3f(glGetUniformLocation(myProgram.program, "pointLights[0].specular"), 1.0f, 1.0f, 1.0f);
            glUniform1f(glGetUniformLocation(myProgram.program, "pointLights[0].constant"), 1.0f);
            glUniform1f(glGetUniformLocation(myProgram.program, "pointLights[0].linear"), 0.09);
            glUniform1f(glGetUniformLocation(myProgram.program, "pointLights[0].quadratic"), 0.032);
            // 点光源 2  绿色
            glUniform3f(glGetUniformLocation(myProgram.program, "pointLights[1].position"), pointLightPositions[1].x, pointLightPositions[1].y, pointLightPositions[1].z);
            glUniform3f(glGetUniformLocation(myProgram.program, "pointLights[1].ambient"), 0.0f, 1.0f, 0.0f);
            glUniform3f(glGetUniformLocation(myProgram.program, "pointLights[1].diffuse"), 0.8f, 0.8f, 0.8f);
            glUniform3f(glGetUniformLocation(myProgram.program, "pointLights[1].specular"), 1.0f, 1.0f, 1.0f);
            glUniform1f(glGetUniformLocation(myProgram.program, "pointLights[1].constant"), 1.0f);
            glUniform1f(glGetUniformLocation(myProgram.program, "pointLights[1].linear"), 0.09);
            glUniform1f(glGetUniformLocation(myProgram.program, "pointLights[1].quadratic"), 0.032);
            // 点光源 3 蓝色
            glUniform3f(glGetUniformLocation(myProgram.program, "pointLights[2].position"), pointLightPositions[2].x, pointLightPositions[2].y, pointLightPositions[2].z);
            glUniform3f(glGetUniformLocation(myProgram.program, "pointLights[2].ambient"), 0.0f, 0.0f, 1.0f);
            glUniform3f(glGetUniformLocation(myProgram.program, "pointLights[2].diffuse"), 0.8f, 0.8f, 0.8f);
            glUniform3f(glGetUniformLocation(myProgram.program, "pointLights[2].specular"), 1.0f, 1.0f, 1.0f);
            glUniform1f(glGetUniformLocation(myProgram.program, "pointLights[2].constant"), 1.0f);
            glUniform1f(glGetUniformLocation(myProgram.program, "pointLights[2].linear"), 0.09);
            glUniform1f(glGetUniformLocation(myProgram.program, "pointLights[2].quadratic"), 0.032);
            // 点光源 4 灰
            glUniform3f(glGetUniformLocation(myProgram.program, "pointLights[3].position"), pointLightPositions[3].x, pointLightPositions[3].y, pointLightPositions[3].z);
            glUniform3f(glGetUniformLocation(myProgram.program, "pointLights[3].ambient"), 0.5f, 0.5f, 0.5f);
            glUniform3f(glGetUniformLocation(myProgram.program, "pointLights[3].diffuse"), 0.8f, 0.8f, 0.8f);
            glUniform3f(glGetUniformLocation(myProgram.program, "pointLights[3].specular"), 1.0f, 1.0f, 1.0f);
            glUniform1f(glGetUniformLocation(myProgram.program, "pointLights[3].constant"), 1.0f);
            glUniform1f(glGetUniformLocation(myProgram.program, "pointLights[3].linear"), 0.09);
            glUniform1f(glGetUniformLocation(myProgram.program, "pointLights[3].quadratic"), 0.032);
            //================================================

            for(GLuint i = 0; i < cubePositionsCount; i++)
            {
                model = glm::translate(model, cubePositions[i]);
                GLfloat angle = 20.0f * i;
                model = glm::rotate(model, angle, glm::vec3(1.0f, 0.3f, 0.5f));
                glUniformMatrix4fv(myModelLoc, 1, GL_FALSE, glm::value_ptr(model));
                glDrawArrays(GL_TRIANGLES, 0, squareIndicesCount);
            }
            
            glBindVertexArray(0);
            glfwSwapBuffers(window);
        }

        //程序销毁
        glfwTerminate();
        return 1;
    }
}
