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
    if (! Sprite::initWithFile("jellyfish.png"))
    {
        return false;
    }
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
    auto speed = 1.0f / M_PI;
    auto rotateDuration = fabs(rotateRadians * speed);

    return rotateDuration;
}

void Jellyfish::rotateJelly(Vec2 touchPos)
{
    auto rotateDuration = this->getRotateDuration();
    auto rotateDegrees = this->getRotateDegrees(touchPos);
    this->runAction(RotateTo::create(rotateDuration, rotateDegrees));
}
