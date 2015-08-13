//
//  GamePause.cpp
//  jellyrun
//
//  Created by Tingting Gu on 2015/08/13.
//
//

#include "GamePause.h"
#include "GameScene.h"
#include "BarrierLayer.h"
#include "cocosGUI.h"
#include "SceneManager.h"
#include "UIConstants.h"

//#include "GameStartScene.h"

using namespace cocos2d;

GamePause::GamePause()
{
}
GamePause::~GamePause()
{
}
bool GamePause::init()
{
    if(!Layer::init())
    {
        return false;
    }

    visibleSize = Director::getInstance()->getVisibleSize();
    visibleSizeMultiplier = visibleSize.width / 1134.0f;

    // add the barrier layer
    addChild(BarrierLayer::create(),0);

    this->setupUI();

    return true;
}

void GamePause::setupUI()
{
    // Add the continue button and end game button
    ui::Button *continueButton = ui::Button::create();
    continueButton->setAnchorPoint(Vec2(0.5f, 0.5f));
    continueButton->setPosition(Vec2(visibleSize.width * 0.666f, visibleSize.height /2));
    continueButton->loadTextures("singlePlayerButton.png", "singlePlayerButtonPressed.png");
    continueButton->addTouchEventListener(CC_CALLBACK_2(GamePause::continueButtonPressed, this));
    this->addChild(continueButton);

    ui::Button *endGameButton = ui::Button::create();
    endGameButton->setAnchorPoint(Vec2(0.5f, 0.5f));
    endGameButton->setPosition(Vec2(visibleSize.width * 0.333f, visibleSize.height /2));
    endGameButton->loadTextures("endGameButton.png", "endGameButtonPressed.png");
    endGameButton->addTouchEventListener(CC_CALLBACK_2(GamePause::endGameButtonPressed, this));
    this->addChild(endGameButton);

    float fontSize = visibleSizeMultiplier * TITLE_FONT_SIZE;
    //create a continue label
    this->continueLabel = ui::Text::create("CONTINUE", TITLE_FONT_NAME, fontSize);
    this->continueLabel->setAnchorPoint(Vec2(0.5f, 0.5f));
    this->continueLabel->setPosition(Vec2(visibleSize.width*0.666f, visibleSize.height * 0.3f));
    this->continueLabel->setColor(WHITE_LABEL_COLOR);
    this->addChild(continueLabel);

    //create a end game label
    this->endGameLabel = ui::Text::create("STOP", TITLE_FONT_NAME, fontSize);
    this->endGameLabel->setAnchorPoint(Vec2(0.5f, 0.5f));
    this->endGameLabel->setPosition(Vec2(visibleSize.width*0.333f, visibleSize.height * 0.3f));
    this->endGameLabel->setColor(WHITE_LABEL_COLOR);
    this->addChild(endGameLabel);
}

void GamePause::continueButtonPressed(cocos2d::Ref *pSender, ui::Widget::TouchEventType eEventType)
{
    if (eEventType == ui::Widget::TouchEventType::ENDED)
    {
        this->removeFromParent();
        Director::getInstance()->resume();
    }
}

/*
void GamePause::restartButtonPressed(cocos2d::Ref *pSender, ui::Widget::TouchEventType eEventType)
{
    Director::getInstance()->resume();
    Director::getInstance()->replaceScene(TransitionCrossFade::create(0.5f,GameScene::createScene()));
}
*/
void GamePause::endGameButtonPressed(cocos2d::Ref *pSender, ui::Widget::TouchEventType eEventType)
{
    if (eEventType == ui::Widget::TouchEventType::ENDED)
    {
        Director::getInstance()->resume();
        SceneManager::getInstance()->enterLobby();
    }
}
