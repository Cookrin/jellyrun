//
//  SceneManager.cpp
//  jellyrun
//
//  Created by Tingting Gu on 2015/07/13.
//
//

#include "SceneManager.h"
#include "GameScene.h"
#include "GameOverScene.h"
#include "JSONPacker.h"
#include "Lobby.h"

using namespace cocos2d;

#pragma mark -
#pragma mark LifeCycle

static SceneManager *_sharedSceneManager = nullptr;

SceneManager *SceneManager::getInstance()
{
    if (!_sharedSceneManager)
    {
        _sharedSceneManager = new (std::nothrow)SceneManager();
    }
    return _sharedSceneManager;
}

SceneManager::SceneManager()
{
    _gameScene = nullptr;
    this->_networkingWrapper = std::unique_ptr<NetworkingWrapper>(new NetworkingWrapper());
    this->_networkingWrapper->setDelegate(this);
}

SceneManager::~SceneManager()
{
}

#pragma mark -
#pragma mark Public Methods

void SceneManager::enterGameScene(bool networked)
{
    Scene *scene = Scene::create();
    this->_gameScene = GameScene::create();
    bool isHost = true;

    if (networked)
    {
        isHost = this->isHost();
        CCLOG("isHost = %d", isHost);
    }

    this->_gameScene->setNetworkedSession(networked, isHost);
    scene->addChild(_gameScene);

    Director::getInstance()->replaceScene(scene);
}

void SceneManager::enterLobby()
{
    if (_gameScene)
    {
        Scene *scene = Scene::create();
        this->_lobby = Lobby::create();
        scene->addChild(_lobby);

        Director::getInstance()->replaceScene(scene);
        _networkingWrapper->disconnect();
    }
}

void SceneManager::enterGameOver(int score, int bestScore, int deathTime)
{
    if (_gameScene)
    {
        _networkingWrapper->disconnect();
        this->_networkingWrapper->stopAdvertisingAvailability();
        Scene* scene = Scene::create();
        GameOverScene* gameOverScene = GameOverScene::create();
        scene->addChild(gameOverScene);
        Director::getInstance()->replaceScene(scene);
        gameOverScene->updateScoreLabel(score);
        gameOverScene->updateBestScoreLabel(bestScore);
        gameOverScene->updateDeathTimeLabel(deathTime);

        this->_gameScene = nullptr;
    }
}

std::vector<std::string> SceneManager::getPeerList()
{
    return _networkingWrapper->getPeerList();
}

void SceneManager::showPeerList()
{
    /* If myDeviceName is in the peerlist, erase it as we only need the other players device names
    for (auto peerDeviceName : peerList)
    {
        if (peerDeviceName == myDeviceName)
        {
            peerList.erase(peerDeviceName);
        }
    }
    */
    _networkingWrapper->showPeerList();
}

std::string SceneManager::getMyDeviceName()
{
    return _networkingWrapper->getDeviceName();
}

std::string SceneManager::getHostDeviceName()
{
    std::vector<std::string> peerList = this->getPeerList();
    peerList.push_back(this->getMyDeviceName());
    std::sort(peerList.begin(), peerList.end());
    return peerList[0];
}

bool SceneManager::isHost()
{
    if (this->getMyDeviceName().compare(this->getHostDeviceName()) == 0)
    {
        return true;
    }
    return false;
}

void SceneManager::receiveMultiplayerInvitations()
{
    _networkingWrapper->startAdvertisingAvailability();
}

void SceneManager::sendData(const void *data, unsigned long length)
{
    _networkingWrapper->sendData(data, length);
}

void SceneManager::stopAdvertisingAvailability()
{
    this->_networkingWrapper->stopAdvertisingAvailability();
}

#pragma mark -
#pragma mark NetworkingWrapperDelegate Methods

void SceneManager::receivedData(const void *data, unsigned long length)
{
    if (_gameScene)
    {
        _gameScene->receivedData(data, length);
    }
}

void SceneManager::stateChanged(ConnectionState state)
{
    switch (state)
    {
        case ConnectionState::NOT_CONNECTED:
            CCLOG("Not Connected");
            break;

        case ConnectionState::CONNECTING:
            CCLOG("Connecting...");
            break;

        case ConnectionState::CONNECTED:
            CCLOG("Connected!");

            if (!_gameScene)
            {
                this->_networkingWrapper->stopAdvertisingAvailability();
                this->enterGameScene(true);
            }
            break;
    }
}