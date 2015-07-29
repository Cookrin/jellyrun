//
//  SceneManager.h
//  jellyrun
//
//  Created by Tingting Gu on 2015/07/13.
//
//

#ifndef __jellyrun__SceneManager__
#define __jellyrun__SceneManager__

#include "cocos2d.h"
#include "NetworkingWrapper.h"

class GameScene;

class SceneManager : public NetworkingDelegate
{
public:
    static SceneManager *getInstance();
    void enterGameScene(bool networked);
    void enterLobby();
    void enterGameOver(int score, int bestScore, int deathTime);
private:
    std::unique_ptr<NetworkingWrapper> networkingWrapper;
    GameScene* gameScene;
    SceneManager();
    ~SceneManager();

    void receivedData(const void *data, unsigned long length);
    void stateChanged(ConnectionState state);
};

#endif /* defined(__jellyrun__SceneManager__) */
