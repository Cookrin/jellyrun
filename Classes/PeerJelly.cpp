//
//  PeerJelly.cpp
//  jellyrun
//
//  Created by Tingting Gu on 2015/07/30.
//
//

#include "PeerJelly.h"

using namespace cocos2d;

#pragma mark -
#pragma mark Lifecycle

bool PeerJelly::init()
{
    if (!Sprite::initWithFile("redJelly_1.png"))
    {
        return false;
    }
    this->runAction(moving());

    return true;
}

#pragma mark -
#pragma mark Public Methods

RepeatForever* PeerJelly::moving()
{
    // 3. repeat the frame
    int numFrame = 3;

    cocos2d::Vector<cocos2d::SpriteFrame *> frames;
    SpriteFrameCache *frameCache = SpriteFrameCache::getInstance();

    char file[100] = {0};

    for (int i = 0; i < numFrame; i++)
    {
        sprintf(file, "redJelly_%d.png", i+1);
        SpriteFrame *frame = frameCache->getSpriteFrameByName(file);
        frames.pushBack(frame);
    }

    Animation *animation = Animation::createWithSpriteFrames(frames, 0.3f);
    Animate *animate = Animate::create(animation);
    auto easeInAnimation = EaseIn::create(animate, 0.3f);
    RepeatForever *repeat = RepeatForever::create(easeInAnimation);
    return repeat;
}
