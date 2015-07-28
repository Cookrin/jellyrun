//
//  UserDataManager.h
//  jellyrun
//
//  Created by Tingting Gu on 2015/07/27.
//
//

#ifndef __jellyrun__UserDataManager__
#define __jellyrun__UserDataManager__

#include "cocos2d.h"

class UserDataManager
{
public:
    static UserDataManager* getInstance();

    int getBestScore();
    void setBestScore(int score);

    int getDeathTime();
    void setDeathTime(int deathTime);

    void deleteAllUserData();

private:
    static UserDataManager* _instance;
    static const char* BESTSCORE_KEY;
    static const char* DEATHTIME_KEY;

    UserDataManager();
    ~UserDataManager();
};

#endif /* defined(__jellyrun__UserDataManager__) */
