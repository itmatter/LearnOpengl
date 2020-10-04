//
//  MyCoordinateCubeShader.h
//  LearnOpenGl
//
//  Created by LiGuang on 2020/9/24.
//  Copyright © 2020 liguang. All rights reserved.
//

#ifndef MyCoordinateCubeShader_h
#define MyCoordinateCubeShader_h


#define STRINGIZE(x) #x
#define SHADER(shader) STRINGIZE(shader)

/// 着色器程序之间的数据传递
static char *myCoordinateCubeVertexShaderStr = SHADER(
    \#version 330 core\n
    layout (location = 0) in vec3 position; //顶点数据源输入
    layout (location = 1) in vec3 color; //颜色数据源输入
    out vec4 vertexColor;//把片元着色器的颜色从这里输出
                                                   
    uniform mat4 myProjection;//投影
    uniform mat4 myView;//观察
    uniform mat4 myModel;//模型
                                 
    void main()
    {
        gl_Position = myProjection * myView * myModel * vec4(position, 1.0f);
        vertexColor = vec4(color, 1.0f); //输出给片元着色器
    }
);

//片元着色器程序
static char *myCoordinateCubeFragmentShaderSrc = SHADER(
    \#version 330 core\n
    in vec4 vertexColor;//从顶点着色器中拿color的值
    out vec4 color;
    void main()
    {
      color = vertexColor;//获取值
    }
);



/// 顶点着色器 CubeTexture
static char *myCoordinateCubeTextureVertexShaderStr = SHADER(
    \#version 330 core\n
    layout (location = 0) in vec3 position; //顶点数据源输入
    layout (location = 1) in vec3 color; //颜色数据源输入
    layout (location = 2) in vec2 texCoords; //纹理数据源输入(2D)

    out vec2 vertexTexCoords;//把片元着色器的纹理从这里输出
                                                             
    uniform mat4 myProjection;//投影
    uniform mat4 myView;//观察
    uniform mat4 myModel;//模型
                                 
    void main()
    {
        gl_Position = myProjection * myView * myModel * vec4(position, 1.0f);
        vertexTexCoords = texCoords;
    }
);

/// 片元着色器 CubeTexture
static char *myCoordinateCubeTextureFragmentShaderSrc = SHADER(
    \#version 330 core\n
    in vec2 vertexTexCoords;//从顶点着色器中拿纹理的值
                        
    uniform sampler2D myTexture;
                                                               
    out vec4 FragColor;
                                                               
    void main()
    {
      FragColor = texture(myTexture, vertexTexCoords);
    }
);







#endif /* MyCoordinateCubeShader_h */
