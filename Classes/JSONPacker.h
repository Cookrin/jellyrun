//
//  JSONPacker.h
//  jellyrun
//
//  Created by Tingting Gu on 2015/07/29.
//
//

#ifndef __jellyrun__JSONPacker__
#define __jellyrun__JSONPacker__

#include "cocos2d.h"
#include "Constants.h"

namespace JSONPacker
{
    struct GameState
    {
        std::string name;
        bool gameOver;
        int score;
        cocos2d::Vec2 jellyPos;
    };
    
    struct FishState
    {
        cocos2d::Vector<cocos2d::Vec2> blindFishStartPos;
        cocos2d::Vector<cocos2d::Vec2> blindFishTargetPos;
    };

    GameState unpackGameStateJSON(std::string json);
    FishState unpackFishStateJSON(std::string json);
    std::string packGameState(const GameState data);
    std::string packFishState(const FishState data);
}

#endif /* defined(__jellyrun__JSONPacker__) */
