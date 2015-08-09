//
//  Jellyfish.cpp
//  jellyrun
//
//  Created by Tingting Gu on 2015/07/14.
//
//

#include "Jellyfish.h"
#include "cocos2d.h"

using namespace cocos2d;

bool Jellyfish::init()
{
    if (!initWithSpriteFrameName("lightJelly_1.png"))
    {
        return false;
    }

    this->runAction(moving());

    return true;
}

float Jellyfish::getRotateDegrees(Vec2 touchPos)
{
    auto jellyPos = this->getPosition();
    Vec2 vector = touchPos - jellyPos;

    rotateRadians = vector.getAngle();
    float rotateDegrees = CC_RADIANS_TO_DEGREES( -1 * rotateRadians);

    return rotateDegrees;
}

float Jellyfish::getRotateDuration()
{
    auto speed = 0.5f / M_PI;
    auto rotateDuration = fabs(rotateRadians * speed);

    return rotateDuration;
}

void Jellyfish::rotateJelly(Vec2 touchPos)
{
    auto rotateDuration = this->getRotateDuration();
    auto rotateDegrees = this->getRotateDegrees(touchPos);
    this->runAction(RotateTo::create(rotateDuration, rotateDegrees));
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