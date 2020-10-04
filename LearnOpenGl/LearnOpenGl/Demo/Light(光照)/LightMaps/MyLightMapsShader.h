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

/// 着色器程序之间的数据传递
static char *myLightMapsVertexShaderStr = SHADER(
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
static char *myLightMapsFragmentShaderSrc = SHADER(
    \#version 330 core\n
    //材质
    struct Material {
        vec3 ambient;//材质向量定义了在环境光照下这个物体反射的是什么颜色,通常和物体颜色相同.
        vec3 diffuse;//材质向量定义了在漫反射光照t下物体的颜色,漫反射颜色被设置为我们需要的物体颜色.
        vec3 specular;//材质向量设置的是物体受到的镜面光照的影响的颜色.
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

    uniform vec3 lightColor;//光照颜色
    uniform vec3 lightPos;//光源位置
    uniform vec3 viewPos;//镜面反射


    out vec4 color;
                                                               
    void main()
    {
        //环境光ambient
        //环境颜色 = 光源颜色 × 物体的环境材质颜色
        vec3 ambient = lightColor * material.ambient * light.ambientStrength;
    
        //漫反射diffuse
        //DiffuseFactor = max(0, dot(N, L))
        //漫反射颜色 = 光源颜色 × 物体的漫反射材质颜色 × 漫反射因子(diffuseFactor)
        vec3 norm = normalize(Normal);
        vec3 lightDir = normalize(lightPos - FragPos);
        float diffuseFactor = max(dot(norm, lightDir),0.0);
        vec3 diffuse = lightColor * material.ambient * diffuseFactor * light.diffuseStrength;
        
        //镜面反射specular
        //R=reflect(L, N)
        //SpecularFactor = pow(max(dot(R,V),0.0), shininess)
        //镜面反射颜色 = 光源颜色 × 物体的镜面材质颜色 × 镜面反射因子(SpecularFactor)
        vec3 viewDir = normalize(viewPos - FragPos);
        vec3 reflectDir = reflect(-lightDir , norm);
        float specularFactor = pow(max(dot(viewDir, reflectDir),0.0),material.shininess);
        vec3 specular = lightColor * material.ambient * specularFactor * light.specularStrength;

        //最终片段颜色：环境颜色+漫反射颜色+镜面反射颜色
        vec3 result = ambient + diffuse + specular;
        color = vec4(result , 1.0f);
    }
);

#endif /* MyLightMapsShader_h */
