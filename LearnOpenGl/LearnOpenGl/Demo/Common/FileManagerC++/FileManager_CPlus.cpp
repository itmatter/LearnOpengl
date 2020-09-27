//
//  FileManager_CPlus.cpp
//  LearnOpenGl
//
//  Created by LiGuang on 2020/9/28.
//  Copyright © 2020 liguang. All rights reserved.
//

#include "FileManager_CPlus.hpp"
FileManager_CPlus::FileManager_CPlus(void* oc, interface call) {
    this->myOC = oc;//oc对象
    this->myCall = call;//对应方法
}

FileManager_CPlus::~FileManager_CPlus(){
    std::cout<< "CPP Object released"<< std::endl;
}

void* FileManager_CPlus::imageUrl(void* imgName) {
    this->myCall(this->myOC,imgName);//[obj msgSend:]
    return (char *)"1";
}
