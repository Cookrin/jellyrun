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
    };

    struct JellyState
    {
        cocos2d::Vec2 jellyStartPos;
        cocos2d::Vec2 jellyTargetPos;
        //cocos2d::Vec2 jellyRotation;
    };

    struct FishState
    {
        std::vector<cocos2d::Vec2> fishStartPos;
        std::vector<cocos2d::Vec2> fishTargetPos;
    };

    GameState unpackGameStateJSON(std::string json);
    JellyState unpackJellyStateJSON(std::string json);
    FishState unpackFishState(std::string json);

    std::string packGameState(const GameState data);
}

#endif /* defined(__jellyrun__JSONPacker__) */
