//
//  Background.cpp
//  jellyrun
//
//  Created by Tingting Gu on 2015/07/13.
//
//

#include "Background.h"
#include "cocos2d.h"

using namespace cocos2d;

bool Background::init()
{
    if (! Sprite::initWithFile("background.png"))
    {
        return false;
    }
    return true;
}