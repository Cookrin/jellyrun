//
//  Fish.cpp
//  jellyrun
//
//  Created by Tingting Gu on 2015/07/17.
//
//

#include "Fish.h"
#include "cocos2d.h"

bool Fish::init()
{
    if (! Sprite::initWithFile("fish.png"))
    {
        return false;
    }
    return true;
}