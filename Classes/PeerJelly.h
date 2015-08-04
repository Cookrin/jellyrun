//
//  PeerJelly.h
//  jellyrun
//
//  Created by Tingting Gu on 2015/07/30.
//
//

#ifndef __jellyrun__PeerJelly__
#define __jellyrun__PeerJelly__

#include "cocos2d.h"
#include "JSONPacker.h"

class PeerJelly : public cocos2d::Sprite
{
public:
    CREATE_FUNC(PeerJelly);
    cocos2d::Vec2 getPeerJellyPos(JSONPacker::GameState gameState);
    cocos2d::Vec2 peerJellyMovingPos;

private:
    bool init() override;
};

#endif /* defined(__jellyrun__PeerJelly__) */