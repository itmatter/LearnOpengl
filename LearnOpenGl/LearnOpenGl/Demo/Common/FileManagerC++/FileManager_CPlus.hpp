//
//  FileManager_CPlus.hpp
//  LearnOpenGl
//
//  Created by LiGuang on 2020/9/28.
//  Copyright © 2020 liguang. All rights reserved.
//

#ifndef FileManager_CPlus_hpp
#define FileManager_CPlus_hpp

#include <stdio.h>
#include <iostream>
#include "ObjectInterface.h"

class FileManager_CPlus {
    void* myOC;
    interface myCall;
public:
    FileManager_CPlus();
    FileManager_CPlus(void* oc ,interface call);
    ~FileManager_CPlus();
    void* imageUrl(void* imgName);
};
#endif /* FileManager_CPlus_hpp */
