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

        return gameState;
    }

    std::string packFishState(const FishState fishState)
    {
        rapidjson::Document document;
        document.SetObject();

        rapidjson::Value columns(rapidjson::kArrayType);

        for (int column = 0; column < fishState.blindFishStartPos.size(); ++column)
        {
            Vec2 startPos = fishState.blindFishStartPos[column];
            rapidjson::Value startPosJson(rapidjson::kObjectType);
            startPosJson.AddMember("x", startPos.x, document.GetAllocator());
            startPosJson.AddMember("y", startPos.y, document.GetAllocator());
            columns.PushBack(startPosJson, document.GetAllocator());
        }

        document.AddMember("blindFishStartPos", columns, document.GetAllocator());

        rapidjson::Value indexes(rapidjson::kArrayType);

        for (int index = 0; index < fishState.blindFishStartPos.size(); ++index)
        {
            Vec2 targetPos = fishState.blindFishTargetPos[index];
            rapidjson::Value targetPosJson(rapidjson::kObjectType);
            targetPosJson.AddMember("x", targetPos.x, document.GetAllocator());
            targetPosJson.AddMember("y", targetPos.y, document.GetAllocator());
            indexes.PushBack(targetPosJson, document.GetAllocator());
        }

        document.AddMember("blindFishTargetPos", indexes, document.GetAllocator());

        rapidjson::StringBuffer buffer;
        rapidjson::Writer<rapidjson::StringBuffer> writer(buffer);
        document.Accept(writer);

        std::string returnString(buffer.GetString(), buffer.Size());
        return returnString;
    }

    FishState unpackFishStateJSON(std::string json)
    {
        rapidjson::Document document;
        document.Parse<0>(json.c_str());

        FishState fishState;

        rapidjson::Value& columns = document["blindFishStartPos"];
        
        for (rapidjson::SizeType column = 0; column < columns.Size(); ++ column)
        {
            rapidjson::Value& startPosJson = columns[column];
            Vec2 startPos = Vec2(startPosJson["x"].GetDouble(),
                                 startPosJson["y"].GetDouble());
            fishState.blindFishStartPos.push_back(startPos);
        }

        rapidjson::Value& indexes = document["blindFishTargetPos"];

        for (rapidjson::SizeType index = 0; index < indexes.Size(); ++ index)
        {
            rapidjson::Value& targetPosJson = indexes[index];
            Vec2 targetPos = Vec2(targetPosJson["x"].GetDouble(),
                                  targetPosJson["y"].GetDouble());
            fishState.blindFishTargetPos.push_back(targetPos);
        }

        return fishState;
    }
}