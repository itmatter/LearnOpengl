//
//  MyMultipleLightSourcesShader.h
//  LearnOpenGl
//
//  Created by 李礼光 on 2020/10/7.
//  Copyright © 2020 liguang. All rights reserved.
//

#ifndef MyMultipleLightSourcesShader_h
#define MyMultipleLightSourcesShader_h

#define STRINGIZE(x) #x
#define SHADER(shader) STRINGIZE(shader)

//顶点着色器程序
static char *myMyMultipleLightSourcesVertexShaderStr = SHADER(
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
static char *myMyMultipleLightSourcesFragmentShaderSrc = SHADER(
    \#version 330 core\n
    //材质
    struct Material {
        sampler2D diffuse;
        sampler2D specular;
        float shininess;//镜面反射散射因子(半径).
    };

    //定向光源
    struct DirLight {
        vec3 direction;//光源方向
        vec3 ambient;//环境光照
        vec3 diffuse;//漫反射光照
        vec3 specular;//镜面反射光照
    };
                                                                
    //点光源
    struct PointLight {
        vec3 position;//光源位置

        float constant; //常量
        float linear;//一次项
        float quadratic;//二次项
        
        vec3 ambient;//环境光照
        vec3 diffuse;//漫反射光照
        vec3 specular;//镜面反射光照
    };

    #define NR_POINT_LIGHTS 4
                                                                
    in vec3 Normal;
    in vec3 FragPos;
    in vec2 TexCoords;
                                                      
    uniform vec3 viewPos;
    uniform Material material;//材质
    uniform DirLight dirLight;
    uniform PointLight pointLights[NR_POINT_LIGHTS];

    out vec4 color;
                                                                
    vec3 CalcDirLight(DirLight light, vec3 normal, vec3 viewDir);
    vec3 CalcPointLight(PointLight light, vec3 normal, vec3 fragPos, vec3 viewDir);

    void main()
    {
        // Properties
        vec3 norm = normalize(Normal);
        vec3 viewDir = normalize(viewPos - FragPos);
        
        // == ======================================
        //我们的照明分为3个阶段：定向，点光源和可选的手电筒，对于每个阶段，都定义了一个计算功能，用于计算每个灯的相应颜色。
        //在main（）函数中，我们获取所有计算出的颜色，并将其求和为该片段的最终颜色。
        // == ======================================
    
        // Phase 1: 定向光源
        vec3 result = CalcDirLight(dirLight, norm, viewDir);
    
        // Phase 2: 计算点光源
        for(int i = 0; i < NR_POINT_LIGHTS; i++)
            result += CalcPointLight(pointLights[i], norm, FragPos, viewDir);
    
        // Phase 3: 聚光
        // result += CalcSpotLight(spotLight, norm, FragPos, viewDir);
        
        color = vec4(result, 1.0);
    }
                                                                
                                                                
    // 使用定向光时计算颜色。
    vec3 CalcDirLight(DirLight light, vec3 normal, vec3 viewDir)
    {
        vec3 lightDir = normalize(-light.direction);
        // 漫反射因子
        float diff = max(dot(normal, lightDir), 0.0);
        // 镜面反射因子
        vec3 reflectDir = reflect(-lightDir, normal);
        float spec = pow(max(dot(viewDir, reflectDir), 0.0), material.shininess);
        // 最终颜色
        vec3 ambient = light.ambient * vec3(texture(material.diffuse, TexCoords));
        vec3 diffuse = light.diffuse * diff * vec3(texture(material.diffuse, TexCoords));
        vec3 specular = light.specular * spec * vec3(texture(material.specular, TexCoords));
        return (ambient + diffuse + specular);
    }

    // 使用点光源计算颜色
    vec3 CalcPointLight(PointLight light, vec3 normal, vec3 fragPos, vec3 viewDir)
    {
        vec3 lightDir = normalize(light.position - fragPos);
        // 漫反射因子
        float diff = max(dot(normal, lightDir), 0.0);
        // 镜面反射因子
        vec3 reflectDir = reflect(-lightDir, normal);
        float spec = pow(max(dot(viewDir, reflectDir), 0.0), material.shininess);
        // 衰减
        float distance = length(light.position - fragPos);
        float attenuation = 1.0f / (light.constant + light.linear * distance + light.quadratic * (distance * distance));
        // 最终颜色计算
        vec3 ambient = light.ambient * vec3(texture(material.diffuse, TexCoords));
        vec3 diffuse = light.diffuse * diff * vec3(texture(material.diffuse, TexCoords));
        vec3 specular = light.specular * spec * vec3(texture(material.specular, TexCoords));
    
        ambient *= attenuation;
        diffuse *= attenuation;
        specular *= attenuation;
        return (ambient + diffuse + specular);
    }
                                                                
);



#endif /* MyMultipleLightSourcesShader_h */
