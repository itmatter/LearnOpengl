//
//  MyCoordinateShader.hpp
//  LearnOpenGl
//
//  Created by 李礼光 on 2020/9/23.
//  Copyright © 2020 liguang. All rights reserved.
//

#ifndef MyCoordinateShader_h
#define MyCoordinateShader_h

#define STRINGIZE(x) #x
#define SHADER(shader) STRINGIZE(shader)

/// 着色器程序之间的数据传递
static char *myCoordinateVertexShaderStr = SHADER(
    \#version 330 core\n
    layout (location = 0) in vec3 position; //顶点数据源输入
    layout (location = 1) in vec3 color; //颜色数据源输入
    out vec4 vertexColor;//把片元着色器的颜色从这里输出
                                                 
    uniform mat4 myProjection;//
    uniform mat4 myView;//
    uniform mat4 myModel;//
                               
    void main()
    {
        gl_Position = myProjection * myView * myModel * vec4(position, 1.0f);
        vertexColor = vec4(color, 1.0f); //输出给片元着色器
    }
);

//片元着色器程序
static char *myCoordinateFragmentShaderSrc = SHADER(
    \#version 330 core\n
    in vec4 vertexColor;//从顶点着色器中拿color的值
    out vec4 color;
    void main()
    {
      color = vertexColor;//获取值
    }
);





#endif /* MyCoordinateShader_h */
