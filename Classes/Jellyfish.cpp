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

void Jellyfish::rotateJelly(Vec2 targetDirection, float dt)
{
    auto jellyRotation = this->getRotation();
    auto unitRotateDegrees = JELLY_ROATEDEGREES * dt;
    if (targetDirection.x < 0)
    {
        unitRotateDegrees = (-1.0f) * unitRotateDegrees;
    }
    this->setRotation(jellyRotation + unitRotateDegrees);
}

/*
void Jellyfish::rotateJellyToOriginal(Vec2 touchPos)
{
    auto jellyPos = this->getPosition();
    Vec2 jellyRotateTargetPos = touchPos - jellyPos;
    rotateRadians = jellyRotateTargetPos.getAngle();
    float rotateDegrees = CC_RADIANS_TO_DEGREES( -1 * rotateRadians);
    this->setRotation(rotateDegrees);
}
*/

void Jellyfish::setJellyScaleDown(float dt)
{
    auto targetScaleX = 0.05f * dt;
    auto targetScaleY = 0.05f * dt;
    auto jellyScaleX = this->getScaleX();
    auto jellyScaleY = this->getScaleY();

    if (jellyScaleX > 0.3f)
    {
        this->setScale(jellyScaleX - targetScaleX, jellyScaleY - targetScaleY);
    }
}

void Jellyfish::setJellyScaleUp(float dt)
{
    auto targetScaleX = 0.05f * dt;
    auto targetScaleY = 0.05f * dt;
    auto jellyScaleX = this->getScaleX();
    auto jellyScaleY = this->getScaleY();

    if (jellyScaleX < 1.0f)
    {
        this->setScale(jellyScaleX + targetScaleX, jellyScaleY + targetScaleY);
    }
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