//
//  MyTextures.cpp
//  LearnOpenGl
//
//  Created by LiGuang on 2020/9/14.
//  Copyright © 2020 liguang. All rights reserved.
//

#include <iostream>
#include "MyTextures.hpp"
#include "MyProgram.hpp"
#include "MyTexturesVertices.hpp"
#include "MyTexturesShader.hpp"


#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

int runMyTextureOpenGlWindow() {
    int result = glfwInit();
    if (result == GL_FALSE) {
        printf("glfwInit 初始化失败");
        return -1;
    }

    //这里的宏不好提示出来, 根据LearnOpenGL的文档提示, 用这三个
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GLFW_TRUE);

    //创建一个Window
    GLFWwindow *window = glfwCreateWindow(600, 400, "My Opengl Window", NULL, NULL);
    if(!window) {
        printf("window 创建失败");

    }

    glfwMakeContextCurrent(window);
    gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);


     //----------------------------------------------------------------------
    MyProgram myProgram = MyProgram(MyTextureVertexShaderStr, MyTextureFragmentShaderSrc);




    GLuint VBO , VAO , EBO;
    unsigned int squareIndicesCount = 0;

    //创建VBO
    glGenBuffers(1, &VBO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(MyTextureVertices), MyTextureVertices, GL_STATIC_DRAW);

    //创建VAO
    glGenVertexArrays(1, &VAO);
    glBindVertexArray(VAO);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (GLvoid*)0);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (GLvoid*)(3 * sizeof(GLfloat)));
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6 * sizeof(float)));
    glEnableVertexAttribArray(2);

    //创建EBO, 这里的EBO相当于索引的作用
    glGenBuffers(1, &EBO);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(MyTextureVerticesIndices), MyTextureVerticesIndices, GL_STATIC_DRAW);

    //解绑VAO
    glBindVertexArray(0);
    squareIndicesCount = sizeof(MyTextureVerticesIndices)/sizeof(MyTextureVerticesIndices[0]);
 

   
    
    //生成纹理
    unsigned int texture0, texture1;
    unsigned char *data0 ;
    int width0, height0, nrChannels0;

    glGenTextures(1, &texture0);
    glBindTexture(GL_TEXTURE_2D, texture0);
    // 为当前绑定的纹理对象设置环绕、过滤方式
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    //注意图片的地址, 不同路径更换下地址
    data0 = stbi_load( "/Users/liliguang/Desktop/LearnOpengl/LearnOpenGl/LearnOpenGl/Sources/Common/Sources/dizhuan.jpg" , &width0, &height0, &nrChannels0, 0);
    if (data0)
    {
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width0, height0, 0, GL_RGB, GL_UNSIGNED_BYTE, data0);
        glGenerateMipmap(GL_TEXTURE_2D);
        glBindTexture(GL_TEXTURE_2D, 0);

    }
    else
    {
        std::cout << "Failed to load texture" << std::endl;
    }
    stbi_image_free(data0);


    unsigned char *data1 ;
    int width1, height1, nrChannels1;
    glGenTextures(1, &texture1);
    glBindTexture(GL_TEXTURE_2D, texture1);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    //注意图片的地址, 不同路径更换下地址
    data1 = stbi_load("/Users/liliguang/Desktop/LearnOpengl/LearnOpenGl/LearnOpenGl/Sources/Common/Sources/smile.png", &width1, &height1, &nrChannels1, 0);
    if (data1)
    {
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width1, height1, 0, GL_RGBA, GL_UNSIGNED_BYTE, data1);
        glGenerateMipmap(GL_TEXTURE_2D);
        glBindTexture(GL_TEXTURE_2D, 0);

    }
    else
    {
        std::cout << "Failed to load texture" << std::endl;
    }
    stbi_image_free(data1);

    
    
    
    
    

    


    
    //进行绘制
    while(!glfwWindowShouldClose(window)){
       //检查事件
        glfwPollEvents();

        //渲染指令
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);
        
        
        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, texture0);
        glUniform1i(glGetUniformLocation(myProgram.program, "myTexture0"), 0);
        
        
        glActiveTexture(GL_TEXTURE1);
        glBindTexture(GL_TEXTURE_2D, texture1);
        glUniform1i(glGetUniformLocation(myProgram.program, "myTexture1"), 1);
        
        
       
        glUseProgram(myProgram.program);
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
