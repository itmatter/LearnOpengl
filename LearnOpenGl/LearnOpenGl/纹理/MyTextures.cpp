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

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"



void createTexture() {
    
    

    
    


}






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
    unsigned int texture;
    glGenTextures(1, &texture);
    glBindTexture(GL_TEXTURE_2D, texture);
    // 为当前绑定的纹理对象设置环绕、过滤方式
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    // 加载并生成纹理
    int width, height, nrChannels;
    unsigned char *data = stbi_load("/Users/lumi/Desktop/LearnOpengl/LearnOpenGl/LearnOpenGl/Common/Sources/dizhuan.jpg", &width, &height, &nrChannels, 0);
    if (data)
    {
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
        glGenerateMipmap(GL_TEXTURE_2D);
    }
    else
    {
        std::cout << "Failed to load texture" << std::endl;
    }
    stbi_image_free(data);
    

//    GLint vertexColorLocation = glGetUniformLocation(myProgram.program, "myTexture");
//    glad_glSamplerParameteri()
    
    //进行绘制
    while(!glfwWindowShouldClose(window)){
       //检查事件
        glfwPollEvents();

        //渲染指令
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        
       
        glUseProgram(myProgram.program);
        glBindTexture(GL_TEXTURE_2D, texture);
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
