//
//  main.cpp
//  LearnOpenGl
//
//  Created by LiGuang on 2020/9/6.
//  Copyright © 2020 liguang. All rights reserved.
//

#include <iostream>
#import "FileManager.h"
#include "FileManager_CPlus.hpp"

#include "ConfigAndRun.hpp"
#include "MyOpenglWindow.hpp"
#include "MyTextures.hpp"
#include "MyTransform.hpp"
#include "MyCoordinate.hpp"
#include "MyCoordinateCube.hpp"
#include "MyCamera.hpp"
#include "MyLight.hpp"
#include "MyMathDemo.hpp"
#include "MyMaterial.hpp"
int main(int argc, const char * argv[]) {
//    //初始化一个OC对象
//    FileManager * oc = [FileManager shareInstance];
//    void* point = (__bridge void*)oc;
//    //创建C++对象
//    FileManager_CPlus* cpp = new FileManager_CPlus(point,  oc.imagePathWithNameApi);
//    NSLog(@"-----%s",cpp->imageUrl((__bridge void*)@"image url"));
    
    
//    return runMyOpenGlWindow();
//    return runMyTextureOpenGlWindow();
//    return runMyTransform();
//    return runMyCoordinate();
//    return runMyCameraCube();
//    return runMyLightCube();
//    mathDemo();
    
    
    return runMyMaterialCube();
    
    return 0;
}
