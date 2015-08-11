//
//  Jellyfish.h
//  jellyrun
//
//  Created by Tingting Gu on 2015/07/14.
//
//

#ifndef __jellyrun__Jellyfish__
#define __jellyrun__Jellyfish__

#include "cocos2d.h"

using namespace cocos2d;

class Jellyfish : public cocos2d::Sprite
{
public:
    CREATE_FUNC(Jellyfish);
    float rotateRadians;

    float getRotateDegrees(Vec2 touchPos, float dt);
    //float getRotateDuration();
    void rotateJelly(Vec2 touchPos, float dt);
    void setJellyVisible(Vec2 touchPos, float dt);
    Size jellySize;
    float jellyWidth;
    float jellyHeight;

protected:
    bool init() override;
    cocos2d::RepeatForever *moving();

};
#endif /* defined(__jellyrun__Jellyfish__) */
