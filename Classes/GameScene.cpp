//
//  GameScene.cpp
//  jellyrun
//
//  Created by Tingting Gu on 2015/07/13.
//
//

#include "GameScene.h"
#include "cocosGUI.h"
#include "SceneManager.h"
#include "Background.h"
#include "Jellyfish.h"

using namespace cocos2d;

#pragma mark -
#pragma mark GameScene Lifecycle

bool GameScene::init() {
    if (!Node::init()) {
        return false;
    }
    
    jellyfishTargetPosition = Vec2::ZERO;

    return true;
}

void GameScene::onEnter()
{
    Node::onEnter();
    
    Size visibleSize = Director::getInstance()->getVisibleSize();
    
    // setup background
    Sprite *gameBackground = Background::create();
    gameBackground->setAnchorPoint(Vec2(0.5f, 0.5f));
    gameBackground->setPosition(Vec2(visibleSize.width * 0.5f, visibleSize.height * 0.5f));
    this->addChild(gameBackground);

    this->setupUI();

    // setup jellyfish
    Sprite *jellyfish = Jellyfish::create();
    jellyfish->setAnchorPoint(Vec2(0.5f, 0.5f));
    jellyfish->setPosition(Vec2(visibleSize.width * 0.1f, visibleSize.height * 0.5f));
    jellyfish->setScale(0.3f);
    jellyfish->setTag(30);
    this->addChild(jellyfish);

    this->setupTouchHanding();

    this->scheduleUpdate();
    
}

void GameScene::update(float dt)
{
    if (jellyfishTargetPosition != Vec2::ZERO) {

        auto movingJellyfish = this->getChildByTag(30);

        Vec2 jellyfishDirection = jellyfishTargetPosition - movingJellyfish->getPosition();

        if (jellyfishDirection.getLength() >= 5)
        {
            jellyfishDirection =  jellyfishDirection.getNormalized();

            jellyfishDirection *= 300 * dt;

            movingJellyfish->setPosition(movingJellyfish->getPosition() + jellyfishDirection);
        }
    }
}

#pragma mark -
#pragma mark GameScene UI Methods

void GameScene::setupUI()
{
    Size visibleSize = Director::getInstance()->getVisibleSize();
    
    //create the pause button
    ui::Button* pauseButton = ui::Button::create();
    pauseButton->setAnchorPoint(Vec2(1.0f, 1.0f));
    pauseButton->setPosition(Vec2(visibleSize.width* 0.99f, visibleSize.height * 0.99f));
    pauseButton->loadTextures("pauseButton.png", "pauseButtonPressed.png");
    pauseButton->addTouchEventListener(CC_CALLBACK_2(GameScene::pauseButtonPressed, this));
    this->addChild(pauseButton);
}

void GameScene::pauseButtonPressed(cocos2d::Ref *pSender, ui::Widget::TouchEventType eEventType) {
    if (eEventType == ui::Widget::TouchEventType::ENDED) {
        SceneManager::getInstance()->enterLobby();
    }
}

#pragma mark -
#pragma mark GameScene Protected Methods

void GameScene::setupTouchHanding()
{
    auto touchListener = EventListenerTouchOneByOne::create();

    static Vec2 touchPos;

    touchListener->onTouchBegan = [&](Touch* touch, Event* event)
    {
        touchPos = this->convertTouchToNodeSpace(touch);

        jellyfishTargetPosition = touchPos;

        return true;
    };

    touchListener->onTouchMoved = [&](Touch* touch, Event* event)
    {
        Vec2 touchPos = this->convertTouchToNodeSpace(touch);

        jellyfishTargetPosition = touchPos;

    };

    touchListener->onTouchEnded = [&](Touch* touch, Event* event)
    {
    };

    this->getEventDispatcher()->addEventListenerWithSceneGraphPriority(touchListener, this);
}

// make the pauseButton disappear when the player touch the screen