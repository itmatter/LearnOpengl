//
//  MyLightShader.h
//  LearnOpenGl
//
//  Created by 李礼光 on 2020/10/3.
//  Copyright © 2020 liguang. All rights reserved.
//

#ifndef MyLightShader_h
#define MyLightShader_h

#define STRINGIZE(x) #x
#define SHADER(shader) STRINGIZE(shader)

/// 着色器程序之间的数据传递
static char *myLightVertexShaderStr = SHADER(
    \#version 330 core\n
                                             
    layout (location = 0) in vec3 position; //顶点数据源输入
    layout (location = 1) in vec3 normal; //法向量
                                              
    uniform mat4 myProjection;//投影矩阵
    uniform mat4 myView;//观察矩阵
    uniform mat4 myModel;//模型矩阵
                                             
    out vec3 Normal;//法线向量
    out vec3 FragPos;//片段位置

    void main()
    {
        gl_Position = myProjection * myView * myModel * vec4(position, 1.0f);
        Normal = normal;
        FragPos = vec3(myModel * vec4(position, 1.0f) );
    }
);

//片元着色器程序
static char *myLightFragmentShaderSrc = SHADER(
    \#version 330 core\n

    in vec3 Normal;
    in vec3 FragPos;

    uniform vec3 objectColor;//物体颜色
    uniform vec3 lightColor;//光照颜色
    uniform vec3 lightPos;//光源位置
    uniform vec3 viewPos;//镜面反射

    out vec4 color;
                                                               
    void main()
    {
        //环境光ambient
        float ambientStrength = 0.5f;//环境强度
        vec3 ambient = ambientStrength * lightColor;//环境强度 * 白光
    
        //漫反射diffuse
        vec3 norm = normalize(Normal);//归一化法向量
        vec3 lightDir = normalize(lightPos - FragPos);//光源位置-片元位置
        float diff = max(dot(norm, lightDir),0.0);//点乘取最大值,
        vec3 diffuse = diff * lightColor;//漫反射
        
        //镜面反射specular
        float specularStrength = 1.0f;
        vec3 viewDir = normalize(viewPos - FragPos);//归一化法向量
        vec3 reflectDir = reflect(-lightDir , norm);//返回入射光线i对表面法线n的反射光线。
        float spec = pow(max(dot(viewDir, reflectDir),0.0),64);//最大值32次幂
        vec3 specular = specularStrength * spec * lightColor;//镜面反射

        vec3 result = (ambient + diffuse + specular) * objectColor;
        color = vec4(result , 1.0f);
    }
);


#endif /* MyLightShader_h */
