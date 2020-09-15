//
//  MyTexturesShader.hpp
//  LearnOpenGl
//
//  Created by LiGuang on 2020/9/15.
//  Copyright © 2020 liguang. All rights reserved.
//

#ifndef MyTexturesShader_h
#define MyTexturesShader_h

#define STRINGIZE(x) #x
#define SHADER(shader) STRINGIZE(shader)

///
/// 着色器程序之间的数据传递
static char *MyTextureVertexShaderStr = SHADER(
    \#version 330 core\n
                               
    layout (location = 0) in vec3 position; //顶点数据源输入
    layout (location = 1) in vec3 color; //颜色数据源输入
    layout (location = 2) in vec2 texCoords; //纹理数据源输入(2D)

    out vec2 vertexTexCoords;//把片元着色器的纹理从这里输出
    out vec4 vertexColor;//把片元着色器的颜色从这里输出

    void main()
    {
        gl_Position = vec4(position, 1.0f);
    
        vertexColor = vec4(color, 1.0f); //输出给片元着色器
        vertexTexCoords = texCoords;
    }
);

//片元着色器程序
static char *MyTextureFragmentShaderSrc = SHADER(
    \#version 330 core\n
                                        
    in vec2 vertexTexCoords;//从顶点着色器中拿纹理的值
    in vec4 vertexColor;//从顶点着色器中拿color的值
                        
    uniform sampler2D myTexture0;//全局myTexture
    uniform sampler2D myTexture1;//全局myTexture

    out vec4 color;
    out vec4 FragColor;
                                                 
    void main()
    {
        FragColor = mix(texture(myTexture0, vertexTexCoords), texture(myTexture1, vertexTexCoords), 0.5);
    }
);

////片元着色器程序
//static char *MyTextureFragmentShaderSrc = SHADER(
//    \#version 330 core\n
//
//    in vec2 vertexTexCoords;//从顶点着色器中拿纹理的值
//    in vec4 vertexColor;//从顶点着色器中拿color的值
//
//    uniform sampler2D myTexture;//全局myTexture
//
//    out vec4 color;
//    out vec4 FragColor;
//
//    void main()
//    {
//        color = vertexColor;//获取值
//        FragColor = texture(myTexture, vertexTexCoords) * color;
//    }
//);




#endif /* MyTexturesShader_h */
