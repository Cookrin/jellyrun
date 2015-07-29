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

        return gameState;
    }
}