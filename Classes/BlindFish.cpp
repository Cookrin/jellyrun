//
//  BlindFish.cpp
//  jellyrun
//
//  Created by Tingting Gu on 2015/07/31.
//
//

#include "BlindFish.h"
#include <random>

using namespace cocos2d;

#pragma mark -
#pragma mark Lifecycle

bool BlindFish::init()
{
    std::random_device rnd;
    std::mt19937 mt(rnd());
    std::uniform_int_distribution<> rand20(0, 19);

    int index = (int)(rand20(mt));

    const char* fish_name = String::createWithFormat("Fish_%d.png", index+1)->getCString();
    if (!Sprite::initWithFile(fish_name))
    {
        return false;
    }
    this->setAnchorPoint(Vec2(0.5f, 0.5f));
    this->setScale(FISH_SCALE);

    Rect blindFishRect = this->boundingBox();
    blindFishHeight = blindFishRect.size.height;
    blindFishWidth = blindFishRect.size.width;

    return true;
}

#pragma mark -
#pragma mark Public Methods

int BlindFish::setBlindFishVerticalColumnNum()
{
    int blindFishVerticalColumnNum;
    std::random_device rnd;
    std::mt19937 mt(rnd());
    std::uniform_int_distribution<> rand6(0, 5);
    blindFishVerticalColumnNum = (int)(rand6(mt));
    return blindFishVerticalColumnNum;
}

int BlindFish::setBlindFishHorizontalColumnNum()
{
    int blindFishHorizontalColumnNum;
    std::random_device rnd;
    std::mt19937 mt(rnd());
    std::uniform_int_distribution<> rand4(0, 3);
    blindFishHorizontalColumnNum = (int)(rand4(mt));
    return blindFishHorizontalColumnNum;
}

Vec2 BlindFish::getBlindFishStartPos(const Size visibleSize, int blindFishRand, int index)
{
    Vec2 startPos;

    if ( blindFishRand >= 60 ) //blindFishSide = "fromTop"
    {
        blindFishVerticalColumn = this->setBlindFishVerticalColumnNum();

        startPos = Vec2(blindFishWidth * 0.5f + visibleSize.width * blindFishVerticalColumn / 7.0f, visibleSize.height);
    }
    else if ( blindFishRand < 40 ) //blindFishSide = "fromBottom"
    {
        blindFishVerticalColumn = this->setBlindFishVerticalColumnNum();

        startPos = Vec2(blindFishWidth * 0.5f + visibleSize.width * blindFishVerticalColumn / 7.0f, 0.0f);
    }
    else if ( blindFishRand >= 40 && blindFishRand < 50 ) //blindFishSide = "fromLeft" and can not be seen before moving
    {
        blindFishHorizontalColumn = this->setBlindFishHorizontalColumnNum();

        startPos = Vec2(0.0f, visibleSize.height * blindFishHorizontalColumn / 4.0f + blindFishHeight * 0.5f);
    }
    //blindFishSide = "fromRight" and can not be seen before moving
    else if ( blindFishRand >= 50 && blindFishRand < 60 )
    {
        blindFishHorizontalColumn = this->setBlindFishHorizontalColumnNum();

        startPos = Vec2(visibleSize.width, visibleSize.height * blindFishHorizontalColumn / 4.0f + blindFishHeight * 0.5f);
    }
    return startPos;
}

Vec2 BlindFish::getBlindFishTargetPos(const Size visibleSize, int blindFishRand, int index)
{
    Vec2 targetPos;
    if ( blindFishRand >= 60 ) //blindFishSide = "fromTop"
    {
        blindFishVerticalColumn = this->setBlindFishVerticalColumnNum();

        targetPos = Vec2(blindFishWidth * 0.5f + blindFishWidth + visibleSize.width * blindFishVerticalColumn / 7.0f, blindFishHeight * (-1.0f));
    }
    else if ( blindFishRand < 40 ) //blindFishSide = "fromBottom"
    {
        blindFishVerticalColumn = this->setBlindFishVerticalColumnNum();

        targetPos = Vec2(blindFishWidth * 0.5f + visibleSize.width * blindFishVerticalColumn / 7.0f, visibleSize.height + blindFishHeight);
    }
    else if ( blindFishRand >= 40 && blindFishRand < 50 ) //blindFishSide = "fromLeft"
    {
        blindFishHorizontalColumn = this->setBlindFishHorizontalColumnNum();

        targetPos = Vec2(visibleSize.width, visibleSize.height * blindFishHorizontalColumn / 4.0f + blindFishHeight * 0.5f );
    }

    //blindFishSide = "fromRight"
    else if ( blindFishRand >= 50 && blindFishRand < 60 )
    {
        blindFishHorizontalColumn = this->setBlindFishHorizontalColumnNum();

        targetPos = Vec2(blindFishWidth * (-1.0f), visibleSize.height * blindFishHorizontalColumn / 4.0f + blindFishHeight * 0.5f);
    }
    return targetPos;
}

void BlindFish::blindFishRotation(int blindFishRand)
{
    if ( blindFishRand < 40 ) //blindFishSide = "fromBottom"
    {
        this->runAction(RotateTo::create(0.01f, 180.0f));
    }
    else if ( blindFishRand >= 40 && blindFishRand < 50 ) //blindFishSide = "fromLeft"
    {
        auto leftFishAct1 = RotateTo::create(0.05f, 270.0f);
        auto leftFishAct2 = FlipX::create(true);
        auto leftFishSpawn = Spawn::create(
                                           leftFishAct1,
                                           leftFishAct2,
                                           NULL);
        this->runAction(leftFishSpawn);
    }
    else if ( blindFishRand >= 50 && blindFishRand < 60 )//blindFishSide = "fromRight"
    {
        this->runAction(RotateBy::create(0.05f, 90.0f));
    }
}