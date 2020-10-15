//
//  main.cpp
//  LearnOpenGl
//
//  Created by LiGuang on 2020/9/6.
//  Copyright © 2020 liguang. All rights reserved.
//

#include <iostream>

#include "ConfigAndRun.hpp"
#include "MyOpenglWindow.hpp"
#include "MyTextures.hpp"
#include "MyTransform.hpp"
#include "MyCoordinate.hpp"
#include "MyCoordinateCube.hpp"
#include "MyCamera.hpp"
#include "MyLight.hpp"
#include "MyMaterial.hpp"
#include "MyLightMaps.hpp"
#include "MyLightCasters.hpp"
#include "MyMultipleLightSources.hpp"
#include "MyModelLoadingDemo.hpp"

int main(int argc, const char * argv[]) {

//    return runMyOpenGlWindow();
//    return runMyTextureOpenGlWindow();
//    return runMyTransform();
//    return runMyCoordinate();
//    return runMyCameraCube();
//    return runMyLightCube();
//    return runMyMaterialCube();
//    return runMyLightMapsCube();
//    return MyLightCasters::runMyLightCastersCube();
//    return MyMultipleLightSources::runMyMultipleLightSourcesCube();

    return runMyModelLoadingDemo();
    return 0;
}

