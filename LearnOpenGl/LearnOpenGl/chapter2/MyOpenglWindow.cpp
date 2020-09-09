//
//  MyOpenglWindow.cpp
//  LearnOpenGl
//
//  Created by LiGuang on 2020/9/7.
//  Copyright © 2020 liguang. All rights reserved.
//

#include "MyOpenglWindow.hpp"
#include <iostream>
#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "MyShader.hpp"
#include "MyProgram.hpp"

#define STRINGIZE(x) #x
#define SHADER(shader) STRINGIZE(shader)


// 模拟顶点数据
GLfloat vertices[] = {
    -0.5f, -0.5f, 0.0f,  //左下
    0.5f, -0.5f, 0.0f,  //右下
    0.0f,  0.5f, 0.0f   //中上
};
  
  
GLuint indices[] = { // 注意索引从0开始!
    0, 1, 3, // 第一个三角形
    1, 2, 3  // 第二个三角形
};


//顶点着色器程序
char *vertexShaderStr = SHADER(
    \#version 330 core\n
                               layout (location = 0) in vec3 position;
                               void main()
                               {
    gl_Position = vec4(position.x, position.y, position.z, 1.0);
    }
);


//片元着色器程序
char *fragmentShaderSrc = SHADER(
            \#version 330 core\n
                                 out vec4 color;
                                 void main()
                                 {
    color = vec4(1.0f, 0.5f, 0.2f, 1.0f);
    }
);





int runMyOpenGlWindow() {
        
    int result = glfwInit();
    if (result == GL_FALSE) {
        printf("glfwInit 初始化失败");
        return -1;
    }
    
    //这里的宏不好提示出来, 根据LearnOpenGL的文档提示, 用这三个
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    //Mac平台需要加入
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GLFW_TRUE);

    //创建一个Window
    GLFWwindow *window = glfwCreateWindow(600, 400, "My Opengl Window", NULL, NULL);
    if(!window) {
        printf("window 创建失败");

    }
    
    //opengl运行模式 -- 单线程, 理解为跟当前的Window做一次绑定操作.
    glfwMakeContextCurrent(window);
    
    //任何的OpenGL接口调用都必须在初始化GLAD库后才可以正常访问。如果成功的话，该接口将返回GL_TRUE，否则就会返回GL_FALSE。
    gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);
    
    
    
    
     //----------------------------------------------------------------------
    //先创建我们的Program对象, 加载顶点着色器程序和片元着色器程序
    MyProgram myProgram = MyProgram(vertexShaderStr, fragmentShaderSrc);
    
    //程序有了, 接着处理数据

    /*
     VBO
     ------------------------
     | -------------------- |
     | |VAO               | |
     | -------------------- |
     | -------------------- |
     | |VAO               | |
     | -------------------- |
     | -------------------- |
     | |VAO               | |
     | -------------------- |
     | -------------------- |
     | |VAO               | |
     | -------------------- |
     |  ....                |
     |  ....                |
     |                      |
     | -------------------- |
     | |EBO               | |
     | -------------------- |
     ------------------------
     */
    
    
    
    //创建VBO
    GLuint VBO;
    
    //这个缓冲有一个独一无二的ID，所以我们可以使用glGenBuffers函数和一个缓冲ID生成一个VBO对象：
    glGenBuffers(1, &VBO);
    //OpenGL有很多缓冲对象类型，顶点缓冲对象的缓冲类型是GL_ARRAY_BUFFER。
    //OpenGL允许我们同时绑定多个缓冲，只要它们是不同的缓冲类型。
    //我们可以使用glBindBuffer函数把新创建的缓冲绑定到GL_ARRAY_BUFFER目标上：
    //从这一刻起，我们使用的任何（在GL_ARRAY_BUFFER目标上的）缓冲调用都会用来配置当前绑定的缓冲(VBO)。
    //然后我们可以调用glBufferData函数，它会把之前定义的顶点数据复制到缓冲的内存中：
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    
    //glBufferData是一个专门用来把用户定义的数据复制到当前绑定缓冲的函数。
    //它的第一个参数是目标缓冲的类型：顶点缓冲对象当前绑定到GL_ARRAY_BUFFER目标上。
    //第二个参数指定传输数据的大小(以字节为单位)；用一个简单的sizeof计算出顶点数据大小就行。
    //第三个参数是我们希望发送的实际数据。
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    
    //创建VAO
    //要想使用VAO，要做的只是使用glBindVertexArray绑定VAO。
    //从绑定之后起，我们应该绑定和配置对应的VBO和属性指针，之后解绑VAO供之后使用。
    //当我们打算绘制一个物体的时候，我们只要在绘制物体前简单地把VAO绑定到希望使用的设定上就行了。这段代码应该看起来像这样：
    GLuint VAO;
    glGenVertexArrays(1, &VAO);
    //绑定VAO, 这里的VAO的值肯定不是为0的.
    glBindVertexArray(VAO);
    //通过glVertexAttribPointer 设置的顶点属性配置。
    //通过glVertexAttribPointer 调用进行的顶点缓冲对象与顶点属性链接。
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), (GLvoid*)0);
    glEnableVertexAttribArray(0);
    //解绑VAO
    glBindVertexArray(0);
    
    
    
    
    
    
    //这里的索引是为了效率,其实这里不需要也是能运行
    //创建EBO, 这里的EBO相当于索引的作用
    GLuint EBO;
    glGenBuffers(1, &EBO);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);
    
    
    //在glUseProgram函数调用之后，每个着色器调用和渲染调用都会使用这个程序对象（也就是之前写的着色器)了。
    //对了，在把着色器对象链接到程序对象以后，记得删除着色器对象，我们不再需要它们了：
    glUseProgram(myProgram.program);

    //----------------------------------------------------------------------
 


    
    //进行绘制
    while(!glfwWindowShouldClose(window)){
       //检查事件
        glfwPollEvents();
        
        //渲染指令
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        //这里VAO也行, VBO也行
        glBindVertexArray(VAO);
        glDrawArrays(GL_TRIANGLES, 0, 3);
        //主要渲染函数
        glBindVertexArray(0);
        
        
        
        //交换缓冲
        glfwSwapBuffers(window);
    }
    
    
    //程序销毁
    glfwTerminate();
    
    return 1;
}


