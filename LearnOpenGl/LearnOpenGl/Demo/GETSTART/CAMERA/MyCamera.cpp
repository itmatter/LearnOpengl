//
//  MyCamera.cpp
//  LearnOpenGl
//
//  Created by LiGuang on 2020/9/28.
//  Copyright © 2020 liguang. All rights reserved.
//

#include <iostream>
#include "MyCamera.h"
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

// Function prototypes
void key_callback(GLFWwindow* window, int key, int scancode, int action, int mode);
void scroll_callback(GLFWwindow* window, double xoffset, double yoffset);
void mouse_callback(GLFWwindow* window, double xpos, double ypos);
void do_movement();

// Camera
glm::vec3 cameraPos   = glm::vec3(0.0f, 0.0f,  3.0f);
glm::vec3 cameraFront = glm::vec3(0.0f, 0.0f, -1.0f);
glm::vec3 cameraUp    = glm::vec3(0.0f, 1.0f,  0.0f);

GLfloat yaw    = -90.0f;    // Yaw is initialized to -90.0 degrees since a yaw of 0.0 results in a direction vector pointing to the right (due to how Eular angles work) so we initially rotate a bit to the left.
GLfloat pitch  =  0.0f;
GLfloat lastX  =  600.0f  / 2.0;
GLfloat lastY  =  400.0f / 2.0;
GLfloat fov =  45.0f;
bool keys[1024];

GLfloat lastFrame = 0.0f;      // Time of last frame


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
    
    
    //设置(键盘鼠标)输入事件
    
    //此函数设置指定窗口的按键回调，当按下，重复或释放按键时调用该回调。
    glfwSetKeyCallback(window, key_callback);
    
//    //此函数设置指定窗口的光标位置回调，在移动光标时调用该回调。 回调提供了相对于窗口内容区域左上角的屏幕坐标位置。
//    glfwSetCursorPosCallback(window, mouse_callback);
//
//    //此函数设置指定窗口的滚动回调，在使用滚动设备（例如鼠标滚轮或触摸板的滚动区域）时调用此回调。
//    //滚动回调接收所有滚动输入，例如来自鼠标滚轮或触摸板滚动区域的滚动输入。
    glfwSetScrollCallback(window, scroll_callback);

    //glfwSetInputMode
    //第一个参数, 当前的Window
    //第二个参数, 要设置的模式
    //第三个参数, 模式对应的值
    //光标模式 : GLFW_CURSOR
    //光标模式值 : GLFW_CURSOR_DISABLED
    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
    
  
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

    

    
    //进行绘制
    while(!glfwWindowShouldClose(window)){
        glfwPollEvents();
        do_movement();
        
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
        
        projection = glm::perspective(fov, 1.0f, 0.01f, 100.f);//投影矩阵
        glUniformMatrix4fv(myProjectionLoc, 1, GL_FALSE, glm::value_ptr(projection));
        glUniformMatrix4fv(myModelLoc, 1, GL_FALSE, glm::value_ptr(model));

        
        glBindVertexArray(VAO);
          
                    // 观察矩阵用视摄像机视角,也就是旋转摄像机
                    /**
                     glm::LookAt函数需要一个位置、目标和上向量。它可以创建一个和前面所说的同样的观察矩阵。
                     在开始做用户输入之前，我们来做些有意思的事，把我们的摄像机在场景中旋转。我们的注视点保持在(0, 0, 0)。
                     我们在每一帧都创建x和z坐标，这要使用一点三角学知识。x和z表示一个在一个圆圈上的一点，我们会使用它作为摄像机的位置。
                     通过重复计算x和y坐标，遍历所有圆圈上的点，这样摄像机就会绕着场景旋转了。
                     我们预先定义这个圆圈的半径，使用glfwGetTime函数不断增加它的值，在每次渲染迭代创建一个新的观察矩阵。
                     */
        //            GLfloat radius = 10.0f;
        ////            GLfloat camX = sin(glfwGetTime()) * radius;
        ////            GLfloat camZ = cos(glfwGetTime()) * radius;
        //            glm::vec3 cameraPos   = glm::vec3(0.0f, 0.0f, 3.0f);
        //            glm::vec3 cameraFront = glm::vec3(0.0f, 0.0f, 0.0f);
        //            glm::vec3 cameraUp    = glm::vec3(0.0f, 1.0f,  0.0f);
                    
        view = glm::lookAt(cameraPos, //摄像机位置
                           cameraFront, //目标
                           cameraUp);//上向量
                    
        glUniformMatrix4fv(myViewLoc, 1, GL_FALSE, glm::value_ptr(view));
        glDrawArrays(GL_TRIANGLES, 0, squareIndicesCount);
        glBindVertexArray(0);

        glfwSwapBuffers(window);
    }

    //程序销毁
    glfwTerminate();
    
    return 1;
}




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


// Moves/alters the camera positions based on user input
void do_movement()
{
    // Camera controls
    GLfloat cameraSpeed = 0.05f;
    if (keys[GLFW_KEY_W])//后
        cameraPos += cameraSpeed * cameraFront;
    if (keys[GLFW_KEY_S])//前
        cameraPos -= cameraSpeed * cameraFront;
    if (keys[GLFW_KEY_A])//左
        cameraPos -= glm::normalize(glm::cross(cameraFront, cameraUp)) * cameraSpeed;
    if (keys[GLFW_KEY_D])//右
        cameraPos += glm::normalize(glm::cross(cameraFront, cameraUp)) * cameraSpeed;
    
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
    GLfloat yoffset = lastY - ypos; // Reversed since y-coordinates go from bottom to left
    lastX = xpos;
    lastY = ypos;

    GLfloat sensitivity = 0.05;    // Change this value to your liking
    xoffset *= sensitivity;
    yoffset *= sensitivity;

    yaw   += xoffset;
    pitch += yoffset;

    // Make sure that when pitch is out of bounds, screen doesn't get flipped
    if (pitch > 89.0f)
        pitch = 89.0f;
    if (pitch < -89.0f)
        pitch = -89.0f;

    glm::vec3 front;
    front.x = cos(glm::radians(yaw)) * cos(glm::radians(pitch));
    front.y = sin(glm::radians(pitch));
    front.z = sin(glm::radians(yaw)) * cos(glm::radians(pitch));
    cameraFront = glm::normalize(front);
}

void scroll_callback(GLFWwindow* window, double xoffset, double yoffset)
{
    if (fov >= 1.0f && fov <= 45.0f)
        fov -= yoffset * 0.05f;
    if (fov <= 1.0f)
        fov = 1.0f;
    if (fov >= 45.0f)
        fov = 45.0f;
}
