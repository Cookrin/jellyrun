//
//  JSONPacker.cpp
//  jellyrun
//
//  Created by Tingting Gu on 2015/07/29.
//
//

#include "cocos2d.h"
#include "JSONPacker.h"
#include "json/document.h"
#include "json/writer.h"
#include "json/stringbuffer.h"
#include "Constants.h"

using namespace cocos2d;

namespace JSONPacker
{
    std::string packGameState(const GameState gameState)
    {
        rapidjson::Document document;
        document.SetObject();

        document.AddMember("score", gameState.score, document.GetAllocator());
        document.AddMember("name", gameState.name.c_str(), document.GetAllocator());
        document.AddMember("gameOver", gameState.gameOver, document.GetAllocator());

        rapidjson::Value jellyPos(rapidjson::kObjectType);
        jellyPos.AddMember("x", gameState.jellyPos.x, document.GetAllocator());
        jellyPos.AddMember("y", gameState.jellyPos.y, document.GetAllocator());
        document.AddMember("jellyPos", jellyPos, document.GetAllocator());

        rapidjson::StringBuffer buffer;
        rapidjson::Writer<rapidjson::StringBuffer> writer(buffer);
        document.Accept(writer);

        std::string returnString(buffer.GetString(), buffer.Size());
        return returnString;
    }

    GameState unpackGameStateJSON(std::string json)
    {
        rapidjson::Document document;
        document.Parse<0>(json.c_str());

        GameState gameState;

        gameState.score = document["score"].GetInt();
        gameState.name = document["name"].GetString();
        gameState.gameOver = document["gameOver"].GetBool();

        rapidjson::Value& jellyPos = document["jellyPos"];
        gameState.jellyPos = Vec2(jellyPos["x"].GetDouble(), jellyPos["y"].GetDouble());

        /*unpack peerBlindFishStartPos and peerBlindFishTargetPos
        
        */
        return gameState;
    }
/*
    std::string packFishState(const FishState fishState)
    {
        rapidjson::Document document;
        document.SetObject();

        //pack PeerBlindFishStartPos and peerBlindFishTargetPos

        rapidjson::Value index(rapidjson::kArrayType);
        for (int index = 0; index < gameState.blindFishStartPoses.size(); ++index)
        {
        rapidjson::Value blindFishStartPoses(rapidjson::kArrayType);
        Vec2 startPos = gameState.blindFishStartPoses[index];

         rapidjson::Value startPosJson(rapidjson::kObjectType);
         startPosJson.AddMember("x", startPos.x, document.GetAllocator());
         startPosJson.AddMember("y", startPos.y, document.GetAllocator());
         
         startPos.PushBack(startPosJson, document.GetAllocator());
         }

        rapidjson::StringBuffer buffer;
        rapidjson::Writer<rapidjson::StringBuffer> writer(buffer);
        document.Accept(writer);
        
        std::string returnString(buffer.GetString(), buffer.Size());
        return returnString;
    }

    */
}