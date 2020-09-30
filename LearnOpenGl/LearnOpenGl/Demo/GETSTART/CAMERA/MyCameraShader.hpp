//
//  MyCameraShader.hpp
//  LearnOpenGl
//
//  Created by LiGuang on 2020/9/28.
//  Copyright © 2020 liguang. All rights reserved.
//

#ifndef MyCameraShader_h
#define MyCameraShader_h


#define STRINGIZE(x) #x
#define SHADER(shader) STRINGIZE(shader)

/// 着色器程序之间的数据传递
static char *myCameraVertexShaderStr = SHADER(
    \#version 330 core\n
    layout (location = 0) in vec3 position; //顶点数据源输入
    layout (location = 1) in vec2 texCoords; //纹理数据源输入(2D)
                                              
    out vec2 vertexTexCoords;//把片元着色器的颜色从这里输出
                                                 
    uniform mat4 myProjection;//投影矩阵
    uniform mat4 myView;//观察矩阵
    uniform mat4 myModel;//模型矩阵
                               
    void main()
    {
        gl_Position = myProjection * myView * myModel * vec4(position, 1.0f);
        vertexTexCoords = texCoords;
    }
);

//片元着色器程序
static char *myCameraFragmentShaderSrc = SHADER(
    \#version 330 core\n
    in vec2 vertexTexCoords;//从顶点着色器中拿纹理的值
                        
    uniform sampler2D myTexture;
                                                               
    out vec4 FragColor;
                                                               
    void main()
    {
      FragColor = texture(myTexture, vertexTexCoords);
    }
);



#endif /* MyCameraShader_h */
