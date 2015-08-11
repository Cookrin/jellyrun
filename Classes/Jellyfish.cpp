//
//  Jellyfish.cpp
//  jellyrun
//
//  Created by Tingting Gu on 2015/07/14.
//
//

#include "Jellyfish.h"
#include "cocos2d.h"
#include "Constants.h"
#include "GameScene.h"

using namespace cocos2d;

bool Jellyfish::init()
{
    if (!initWithSpriteFrameName("lightJelly_1.png"))
    {
        return false;
    }
    jellySize = this->getContentSize();
    jellyWidth = jellySize.width;
    jellyHeight = jellySize.height;
    this->runAction(moving());

    return true;
}

void Jellyfish::rotateJelly(Vec2 touchPos, float dt)
{
    auto jellyPos = this->getPosition();
    Vec2 jellyRotateTargetPos = touchPos - jellyPos;
    rotateRadians = jellyRotateTargetPos.getAngle();
    float rotateDegrees = CC_RADIANS_TO_DEGREES( -1 * rotateRadians);
    // set the rotateDegrees in one dt
    this->setRotation(rotateDegrees);
}

RepeatForever* Jellyfish::moving()
{
    // 3. repeat the frame
    int numFrame = 3;

    cocos2d::Vector<cocos2d::SpriteFrame *> frames;
    SpriteFrameCache *frameCache = SpriteFrameCache::getInstance();

    char file[100] = {0};

    for (int i = 0; i < numFrame; i++)
    {
        sprintf(file, "lightJelly_%d.png", i+1);
        SpriteFrame *frame = frameCache->getSpriteFrameByName(file);
        frames.pushBack(frame);
    }

    Animation *animation = Animation::createWithSpriteFrames(frames, 0.3f);
    Animate *animate = Animate::create(animation);
    auto easeInAnimation = EaseIn::create(animate, 0.3f);
    RepeatForever *repeat = RepeatForever::create(easeInAnimation);
    return repeat;
}