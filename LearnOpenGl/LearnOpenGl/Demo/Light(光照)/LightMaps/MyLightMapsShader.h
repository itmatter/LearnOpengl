//
//  MyLightMapsShader.h
//  LearnOpenGl
//
//  Created by 李礼光 on 2020/10/5.
//  Copyright © 2020 liguang. All rights reserved.
//

#ifndef MyLightMapsShader_h
#define MyLightMapsShader_h


#define STRINGIZE(x) #x
#define SHADER(shader) STRINGIZE(shader)

//顶点着色器程序
static char *myLightMapsVertexShaderStr = SHADER(
    \#version 330 core\n
                                             
    layout (location = 0) in vec3 position; //顶点数据源输入
    layout (location = 1) in vec3 normal; //法向量
    layout (location = 2) in vec2 texCoords; //纹理数据源输入(2D)

    uniform mat4 myProjection;//投影矩阵
    uniform mat4 myView;//观察矩阵
    uniform mat4 myModel;//模型矩阵
                                             
    out vec3 Normal;//法线向量
    out vec3 FragPos;//片段位置
    out vec2 TexCoords;//把片元着色器的纹理从这里输出


    void main()
    {
        gl_Position = myProjection * myView * myModel * vec4(position, 1.0f);
        Normal = normal;
        FragPos = vec3(myModel * vec4(position, 1.0f) );
        TexCoords = texCoords;
    }
);



//片元着色器程序
static char *myLightMapsFragmentShaderSrc = SHADER(
    \#version 330 core\n
    //材质
    /**
    要记住的是sampler2D也叫做模糊类型，这意味着我们不能以某种类型对它实例化，只能用uniform定义它们。
    如果我们用结构体而不是uniform实例化（就像函数的参数那样），GLSL会抛出奇怪的错误；这同样也适用于其他模糊类型。
    */
    struct Material {
        sampler2D diffuse;
        sampler2D specular;
        float shininess;//镜面反射散射因子(半径).
    };
    uniform Material material;//材质

    //光照强度
    struct Light {
        vec3 position;
        vec3 ambientStrength;//环境光照强度
        vec3 diffuseStrength;//漫反射光照强度
        vec3 specularStrength;//镜面反射光照强度
    };
    uniform Light light;

    in vec3 Normal;
    in vec3 FragPos;
    in vec2 TexCoords;

    uniform vec3 lightColor;//光照颜色
    uniform vec3 lightPos;//光源位置
    uniform vec3 viewPos;//镜面反射

    out vec4 color;
                                                               
    void main()
    {
        //环境光ambient
        //环境颜色 = 光源颜色 × 环境光照强度 × 贴图
        vec3 ambient = lightColor * light.ambientStrength * vec3(texture(material.diffuse, TexCoords));

        //漫反射diffuse
        //DiffuseFactor = max(0, dot(N, L))
        //漫反射颜色 = 光源颜色 × 漫反射因子(diffuseFactor) × 漫反射光照强度 × 贴图
        vec3 norm = normalize(Normal);
        vec3 lightDir = normalize(lightPos - FragPos);
        float diffuseFactor = max(dot(norm, lightDir),0.0);
        vec3 diffuse = lightColor * diffuseFactor * light.diffuseStrength * vec3(texture(material.diffuse, TexCoords));
    
        //镜面反射specular
        //R=reflect(L, N)
        //SpecularFactor = pow(max(dot(R,V),0.0), shininess)
        //镜面反射颜色 = 光源颜色 × 镜面反射因子(SpecularFactor) × 镜面光照强度 × 贴图
        vec3 viewDir = normalize(viewPos - FragPos);
        vec3 reflectDir = reflect(-lightDir , norm);
        float specularFactor = pow(max(dot(viewDir, reflectDir),0.0),material.shininess);
        vec3 specular = lightColor * specularFactor * light.specularStrength * vec3(texture(material.specular, TexCoords));

        //最终片段颜色：环境颜色+漫反射颜色+镜面反射颜色
        vec3 result = ambient + diffuse + specular;
        color = vec4(result , 1.0f);
    }
);

#endif /* MyLightMapsShader_h */
