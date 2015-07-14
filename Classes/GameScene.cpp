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

using namespace cocos2d;

bool GameScene::init() {
    if (!Node::init()) {
        return false;
    }
    
    return true;
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
        CCLOG("Go to the Pause Mode");
        SceneManager::getInstance()->enterLobby();
    }
}