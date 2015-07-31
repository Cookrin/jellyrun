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

void PeerJelly::setJellyPos(JSONPacker::GameState state)
{
    Vec2 jellyPos = state.jellyPos;
    this->setPosition(jellyPos);
}