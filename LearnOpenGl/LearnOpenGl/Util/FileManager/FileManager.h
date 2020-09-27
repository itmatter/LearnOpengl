//
//  FileManager.h
//  LearnOpenGl
//
//  Created by LiGuang on 2020/9/27.
//  Copyright © 2020 liguang. All rights reserved.
//

#import <Foundation/Foundation.h>
#import "ObjectInterface.h"

NS_ASSUME_NONNULL_BEGIN

@interface FileManager : NSObject

+(instancetype)shareInstance;

-(void)imagePathWithName:(void*)parameter;

@property interface imagePathWithNameApi;

@end

NS_ASSUME_NONNULL_END
