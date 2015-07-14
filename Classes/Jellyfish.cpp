//
//  Jellyfish.cpp
//  jellyrun
//
//  Created by Tingting Gu on 2015/07/14.
//
//

#include "Jellyfish.h"
#include "cocos2d.h"

bool Jellyfish::init()
{
    if (! Sprite::initWithFile("jellyfish.png"))
    {
        return false;
    }
    return true;
}