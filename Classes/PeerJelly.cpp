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
    if (!Sprite::initWithFile("jellyfish.png"))
    {
        return false;
    }
    return true;
}

#pragma mark -
#pragma mark Public Methods

Vec2 PeerJelly::getPeerJellyPos(JSONPacker::GameState gameState)
{
    peerJellyMovingPos = gameState.jellyPos;
    return peerJellyMovingPos;
}