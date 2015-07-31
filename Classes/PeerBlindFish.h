//
//  PeerBlindFish.h
//  jellyrun
//
//  Created by Tingting Gu on 2015/07/31.
//
//

#ifndef __jellyrun__PeerBlindFish__
#define __jellyrun__PeerBlindFish__

#include "cocos2d.h"
#include "JSONPacker.h"

class PeerBlindFish : public cocos2d::Sprite
{
public:
    CREATE_FUNC(PeerBlindFish);
    void setPeerBlindFishStartPos(JSONPacker::GameState state);
    void setPeerBlindFishTargetPos(JSONPacker::GameState state);
    void setPeerBlindFishToMove(float dt);

private:
    bool init() override;
};

#endif /* defined(__jellyrun__PeerBlindFish__) */
