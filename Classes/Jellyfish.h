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
    Size jellySize;
    float jellyWidth;
    float jellyHeight;

    void setJellyScaleDown(float dt);
    void setJellyScaleUp(float dt);
    void rotateJelly(Vec2 touchPos, float dt);
    void rotateJellyToOriginal(Vec2 touchPos);
    void setJellyVisible(Vec2 touchPos, float dt);


protected:
    bool init() override;
    cocos2d::RepeatForever *moving();

};
#endif /* defined(__jellyrun__Jellyfish__) */
