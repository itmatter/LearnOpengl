//
//  MyMeshShader.h
//  LearnOpenGl
//
//  Created by LiGuang on 2020/10/11.
//  Copyright © 2020 liguang. All rights reserved.
//

#ifndef MyMeshShader_h
#define MyMeshShader_h

#define STRINGIZE(x) #x
#define SHADER(shader) STRINGIZE(shader)

//顶点着色器程序
static char *myMeshVertexShaderStr = SHADER(
    \#version 330 core\n
                                             
    layout (location = 0) in vec3 position; //顶点数据源输入
    layout (location = 1) in vec3 normal; //法向量
    layout (location = 2) in vec2 texCoords; //纹理数据源输入(2D)

    uniform mat4 myProjection;//投影矩阵
    uniform mat4 myView;//观察矩阵
    uniform mat4 myModel;//模型矩阵
                                             
    out vec2 TexCoords;//把片元着色器的纹理从这里输出

    void main()
    {
        gl_Position = myProjection * myView * myModel * vec4(position, 1.0f);
        TexCoords = texCoords;
    }
);



//片元着色器程序
static char *myMeshFragmentShaderSrc = SHADER(
    \#version 330 core\n
                                      
    in vec2 TexCoords;
    out vec4 color;
    uniform sampler2D texture_diffuse;
    void main()
    {
        color = vec4(texture(texture_diffuse, TexCoords));
    }
                                                                
);



#endif /* MyMeshShader_h */
