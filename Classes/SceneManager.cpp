//
//  SceneManager.cpp
//  jellyrun
//
//  Created by Tingting Gu on 2015/07/13.
//  Implements the NetworkingDelegate interface
//

#include "SceneManager.h"
#include "GameScene.h"
#include "Lobby.h"
#include "GameOverScene.h"

using namespace cocos2d;

#pragma mark -
#pragma mark Lifecycle

static SceneManager* sharedSceneManager = nullptr;

SceneManager* SceneManager::getInstance()
{
    if (!sharedSceneManager)
    {
        sharedSceneManager = new (std::nothrow) SceneManager();
    }

    return sharedSceneManager;
}

// implementations for the constructor and destructor
SceneManager::SceneManager()
{
    // create an instance of gameScene until the timing that gamePlay buttons are clicked
    gameScene = nullptr;
    this->networkingWrapper = std::unique_ptr<NetworkingWrapper>(new NetworkingWrapper());
    this->networkingWrapper->setDelegate(this);
}

SceneManager::~SceneManager()
{
}

#pragma mark -
#pragma mark Public Methods

void SceneManager::enterGameScene(bool networked)
{
    Scene *scene = Scene::create();

    gameScene = GameScene::create();
    gameScene->setNetworkedSession(networked);

    scene->addChild(gameScene);

    Director::getInstance()->pushScene(scene);
}

void SceneManager::enterLobby()
{
    if (gameScene)
    {
        Director::getInstance()->popScene();
        gameScene = nullptr;
        networkingWrapper->disconnect();
    }
}

void SceneManager::enterGameOver(int score, int bestScore, int deathTime)
{
    if (gameScene)
    {
        Scene* scene = Scene::create();
        GameOverScene* gameOverScene = GameOverScene::create();
        scene->addChild(gameOverScene);
        Director::getInstance()->replaceScene(scene);
        gameOverScene->updateScoreLabel(score);
        gameOverScene->updateBestScoreLabel(bestScore);
        gameOverScene->updateDeathTimeLabel(deathTime);

        networkingWrapper->disconnect();
        this->gameScene = nullptr;
    }
}

void SceneManager::showPeerList()
{
    networkingWrapper->showPeerList();
}

void SceneManager::receivedData(const void *data, unsigned long length)
{
}

void SceneManager::receiveMultiplayerInvitations()
{
    networkingWrapper->startAdvertisingAvailability();
}

#pragma mark -
#pragma mark Private Methods

void SceneManager::sendData(const void *data, unsigned long length)
{
}

void SceneManager::stateChanged(ConnectionState state)
{
    switch (state)
    {
        case ConnectionState::CONNECTING:
            CCLOG("Connecting");
            break;
            
        case ConnectionState::NOT_CONNECTED:
            CCLOG("Not Connected");
            break;
            
        case ConnectionState::CONNECTED:
            CCLOG("Connected");
            
            if (!gameScene)
            {
                this->networkingWrapper->stopAdvertisingAvailability();
                this->enterGameScene(true);
            }
            break;
    }
}