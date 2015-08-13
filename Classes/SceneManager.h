//
//  SceneManager.h
//  jellyrun
//
//  Created by Tingting Gu on 2015/07/13.
//
//

#ifndef __jellyrun__SceneManager__
#define __jellyrun__SceneManager__

#include "NetworkingWrapper.h"

class GameScene;
class Lobby;

class SceneManager : public NetworkingDelegate
{
public:
    bool isHost();
    static SceneManager *getInstance();
    void enterGameScene(bool networked);
    void enterLobby();
    void enterGameOver(int score, int bestScore, int deathTime);
    std::string getMyDeviceName();
    std::string getHostDeviceName();
    std::vector<std::string> getPeerList();
    void showPeerList();
    void receiveMultiplayerInvitations();
    void sendData(const void *data, unsigned long length);
    void stopAdvertisingAvailability();

private:
    std::unique_ptr<NetworkingWrapper> _networkingWrapper;
    GameScene* _gameScene;
    Lobby* _lobby;

    SceneManager();
    ~SceneManager();

    void receivedData(const void *data, unsigned long length);
    void stateChanged(ConnectionState state);
};

#endif /* defined(__jellyrun__SceneManager__) */
