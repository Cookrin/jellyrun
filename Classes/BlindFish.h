//
//  BlindFish.h
//  jellyrun
//
//  Created by Tingting Gu on 2015/07/31.
//
//

#ifndef __jellyrun__BlindFish__
#define __jellyrun__BlindFish__

#include "cocos2d.h"
#include "JSONPacker.h"

using namespace cocos2d;

class BlindFish : public cocos2d::Sprite
{
public:
    CREATE_FUNC(BlindFish);
    Vec2 getBlindFishStartPos(const Size visibleSize, int blindFishRand, int index);
    Vec2 getBlindFishTargetPos(const Size visibleSize, int blindFishRand, int index);
    cocos2d::Vec2 getPeerBlindFishStartPos(JSONPacker::FishState state, int index);
    cocos2d::Vec2 getPeerBlindFishTargetPos(JSONPacker::FishState state, int index);

    void blindFishRotation(int blindFishRand);

    Rect blindFishRect;
    float blindFishHeight;
    float blindFishWidth;

private:
    bool init() override;
};

#endif /* defined(__jellyrun__BlindFish__) */
