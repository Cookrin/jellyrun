//
//  BlindFish.cpp
//  jellyrun
//
//  Created by Tingting Gu on 2015/07/31.
//
//

#include "BlindFish.h"

using namespace cocos2d;

#pragma mark -
#pragma mark Lifecycle

bool BlindFish::init()
{
    if (!Sprite::initWithFile("BlindFish.png"))
    {
        return false;
    }
    return true;

    blindFishRect = this->boundingBox();
    blindFishHeight = blindFishRect.size.height;
    blindFishWidth = blindFishRect.size.width;
}

void BlindFish::setBlindFishStartPos(const Size visibleSize, int blindFishRand, int index)
{
    Vec2 startPos;

    if ( blindFishRand > 7 ) //blindFishSide = "fromTop"
    {
        startPos = Vec2(visibleSize.width *(index-1) / 10.0f, visibleSize.height * 0.88f);;
    }
    else if ( blindFishRand < 4 ) //blindFishSide = "fromBottom"
    {
        startPos = Vec2(visibleSize.width * index / 10.0f, visibleSize.height * 0.12f);
    }
    else if ( blindFishRand == 4 || blindFishRand == 5 ) //blindFishSide = "fromLeft" and can not be seen before moving
    {
        startPos = Vec2(visibleSize.width * 0.0f, visibleSize.height * (index - 1) / 4.0f );
    }
    else //blindFishSide = "fromRight" and can not be seen before moving
    {
        startPos = Vec2(visibleSize.width, visibleSize.height * (index - 1) / 4.0f );
    }
    this->setPosition(startPos);
}

Vec2 BlindFish::getBlindFishTargetPos(const Size visibleSize, int blindFishRand, int index)
{
    Vec2 targetPos;
    if ( blindFishRand > 7 ) //blindFishSide = "fromTop"
    {
        targetPos = Vec2(visibleSize.width *(index-1) / 10.0f, blindFishHeight * (-1.0f));
    }
    else if ( blindFishRand < 4 ) //blindFishSide = "fromBottom"
    {
        targetPos = Vec2(visibleSize.width *(index) / 10.0f, visibleSize.height);
    }
    else if ( blindFishRand == 4 || blindFishRand == 5 ) //blindFishSide = "fromLeft"
    {
        targetPos = Vec2(visibleSize.width * 1.0f, visibleSize.height * (index - 1) / 4.0f );
    }
    else //blindFishSide = "fromRight"
    {
        targetPos = Vec2(blindFishWidth * (-1.0f), visibleSize.height * (index - 1) / 4.0f );
    }
    return targetPos;
}

void BlindFish::blindFishRotation(int blindFishRand)
{
    if ( blindFishRand < 4 ) //blindFishSide = "fromBottom"
    {
        this->runAction(RotateTo::create(0.01f, 180.0f));
    }
    else if ( blindFishRand == 4 || blindFishRand == 5 ) //blindFishSide = "fromLeft"
    {
        auto leftFishAct1 = RotateTo::create(0.05f, 270.0f);
        auto leftFishAct2 = FlipX::create(true);
        auto leftFishSpawn = Spawn::create(
                                           leftFishAct1,
                                           leftFishAct2,
                                           NULL);
        this->runAction(leftFishSpawn);
    }
    else if ( blindFishRand == 6 || blindFishRand == 7)//blindFishSide = "fromRight"
    {
        this->runAction(RotateBy::create(0.05f, 90.0f));
    }
}