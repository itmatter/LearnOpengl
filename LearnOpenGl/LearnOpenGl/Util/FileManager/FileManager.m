//
//  FileManager.m
//  LearnOpenGl
//
//  Created by LiGuang on 2020/9/27.
//  Copyright © 2020 liguang. All rights reserved.
//

#import "FileManager.h"
#import <AppKit/AppKit.h>


void imagePathWithName_OCMethod(void* caller, void* parameter){
    [(__bridge id)caller imagePathWithName:parameter];//[msg send]
}

@implementation FileManager

+ (instancetype)shareInstance {
    static FileManager *single = nil;
    @synchronized (self) {
        if (single == nil) {
            single = [[FileManager alloc]init];
            single.imagePathWithNameApi = imagePathWithName_OCMethod;
        }
    }
    return single;
}


-(void)imagePathWithName:(void *)parameter{
    NSLog(@"%@",parameter);
}

-(void)dealloc{
    NSLog(@"OC Object dealloc");
}

@end
