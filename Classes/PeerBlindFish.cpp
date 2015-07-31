//
//  PeerBlindFish.cpp
//  jellyrun
//
//  Created by Tingting Gu on 2015/07/31.
//
//

#include "PeerBlindFish.h"

using namespace cocos2d;

#pragma mark -
#pragma mark Lifecycle

bool PeerBlindFish::init()
{
    if (!Sprite::initWithFile("BlindFish.png"))
    {
        return false;
    }
    return true;
}

#pragma mark -
#pragma mark Public Methods

void PeerBlindFish::setPeerBlindFishStartPos(JSONPacker::GameState state)
{
}

void PeerBlindFish::setPeerBlindFishTargetPos(JSONPacker::GameState state)
{
}

void PeerBlindFish::setPeerBlindFishToMove(float dt)
{
}