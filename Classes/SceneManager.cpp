//
//  SceneManager.cpp
//  jellyrun
//
//  Created by Tingting Gu on 2015/07/13.
//
//

#include "SceneManager.h"
#include "GameScene.h"
#include "Lobby.h"
#include "GameOverScene.h"

using namespace cocos2d;

#pragma mark -
#pragma mark LifeCycle

static SceneManager *sharedSceneManager = nullptr;

SceneManager *SceneManager::getInstance()
{
    if (!sharedSceneManager)
    {
        sharedSceneManager = new (std::nothrow) SceneManager();
    }
    return sharedSceneManager;
}

SceneManager::SceneManager()
{
    gameScene = nullptr;
    networkingWrapper = std::unique_ptr<NetworkingWrapper>(new NetworkingWrapper());
    networkingWrapper->setDelegate(this);
}

SceneManager::~SceneManager()
{
}

#pragma mark -
#pragma mark Public Methods

void SceneManager::enterGameScene(bool networked)
{
    Scene *scene = Scene::create();
    this->gameScene = GameScene::create();
    scene->addChild(gameScene);
    Director::getInstance()->pushScene(scene);
}

void SceneManager::enterLobby()
{
    if (gameScene)
    {
    Director::getInstance()->popScene();
    gameScene = nullptr;
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

        this->gameScene = nullptr;
    }
}

void SceneManager::receivedData(const void *data, unsigned long length)
{
}

void SceneManager::stateChanged(ConnectionState state)
{
}
