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

    // transition between game scenes
    void enterGameScene(bool networked);
    void enterLobby();
    void enterGameOver(int score, int bestScore, int deathTime);

    // multipeer connectivity
    void showPeerList();
    void receiveMultiplayerInvitations();

    // networking
    void sendData(const void* data, unsigned long length);

private:
    std::unique_ptr<NetworkingWrapper> networkingWrapper;
    GameScene* gameScene;

    // lifecycle
    SceneManager();
    ~SceneManager();

    // networking delegate
    void receivedData(const void* data, unsigned long length) override;
    void stateChanged(ConnectionState state) override;
};

#endif /* defined(__jellyrun__SceneManager__) */
