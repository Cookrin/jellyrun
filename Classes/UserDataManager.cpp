//
//  UserDataManager.cpp
//  jellyrun
//
//  Created by Tingting Gu on 2015/07/27.
//
//

#include "UserDataManager.h"

using namespace cocos2d;

#pragma mark - Static Variables

UserDataManager* UserDataManager::_instance = nullptr;
const char* UserDataManager::BESTSCORE_KEY = "bestScore";
const char* UserDataManager::DEATHTIME_KEY = "totalDeathTime";
const char* UserDataManager::MULTI_BESTSCORE_KEY = "multiBestScore";

#pragma mark - Lifecycle

UserDataManager* UserDataManager::getInstance()
{
    if (!_instance) {
        _instance = new UserDataManager();
    }
    return _instance;
}

UserDataManager::UserDataManager()
{
}

UserDataManager::~UserDataManager()
{
}

#pragma mark - Accessor

int UserDataManager::getBestScore()
{
    return UserDefault::getInstance()->getIntegerForKey(BESTSCORE_KEY, 0);
}

void UserDataManager::setBestScore(int score)
{
    UserDefault::getInstance()->setIntegerForKey(BESTSCORE_KEY, score);
    UserDefault::getInstance()->flush();
}

int UserDataManager::getMultiBestScore()
{
    return UserDefault::getInstance()->getIntegerForKey(MULTI_BESTSCORE_KEY, 0);
}

void UserDataManager::setMultiBestScore(int score)
{
    UserDefault::getInstance()->setIntegerForKey(MULTI_BESTSCORE_KEY, score);
    UserDefault::getInstance()->flush();
}

int UserDataManager::getDeathTime()
{
    return UserDefault::getInstance()->getIntegerForKey(DEATHTIME_KEY, 0);
}

void UserDataManager::setDeathTime(int deathTime)
{
    UserDefault::getInstance()->setIntegerForKey(DEATHTIME_KEY, deathTime);
    UserDefault::getInstance()->flush();
}

void UserDataManager::deleteAllUserData()
{
    if (!UserDefault::getInstance()->isXMLFileExist()) {
        return;
    }
    std::string path = UserDefault::getInstance()->getXMLFilePath();
    FileUtils::getInstance()->removeFile(path);
}