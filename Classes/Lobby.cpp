//
//  Lobby.cpp
//  jellyrun
//
//  Created by Tingting Gu on 2015/07/13.
//
//

#include "Lobby.h"

using namespace cocos2d;

bool Lobby::init()
{
    if (! Node::init())
    {
        return false;
    }
    
    LayerColor* background = LayerColor::create(Color4B(255, 255, 255, 255));
    
    this->addChild(background);
    
    return true;
}