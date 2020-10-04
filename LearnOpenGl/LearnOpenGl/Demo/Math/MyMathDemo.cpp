//
//  MyMathDemo.cpp
//  LearnOpenGl
//
//  Created by 李礼光 on 2020/10/4.
//  Copyright © 2020 liguang. All rights reserved.
//

#include "MyMathDemo.hpp"
#include "glm.hpp"
#include "matrix_transform.hpp"
#include "type_ptr.hpp"
#include "glad.h"
#include <GLFW/glfw3.h>


void mathDemo() {
    //点乘
    glm::vec3 lightPos = glm::vec3(1.0f,1.0f,0.0f);//光源位置
    glm::vec3 normal = glm::vec3(0.0f,1.0f,0.0f); //y轴方向的单位法向量

    //点乘
    float dotResult = glm::dot(lightPos, normal);//1.0*0.0 + 1.0*1.0 + 0.0+0.0
    printf("dot结果 : %f\n",dotResult);
    
    //max
    float maxResult = glm::max(dotResult, 0.0f);//1.0*0.0 + 1.0*1.0 + 0.0+0.0
    printf("max结果 : %f\n",maxResult);

    //pow 幂乘.
    float powResult = glm::pow(maxResult, 32);// maxResult的32次方,
    printf("pow结果 : %f\n",powResult);
    
    
    
}
