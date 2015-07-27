//
//  Lobby.cpp
//  jellyrun
//
//  Created by Tingting Gu on 2015/07/13.
//
//

#include "cocosGUI.h"
#include "Lobby.h"
#include "SceneManager.h"
#include "UIConstants.h"

using namespace cocos2d;

bool Lobby::init()
{
    if (! Node::init())
    {
        return false;
    }
    
    LayerColor* background = LayerColor::create(Color4B(255, 255, 255, 255));
    
    this->addChild(background);
    
    return true;
}

void Lobby::onEnter()
{
    
    Node::onEnter();
    
    setupUI();
}

void Lobby::setupUI()
{
    Size visibleSize = Director::getInstance()->getVisibleSize();
    
    //Sprite *logo = Sprite::create("logo.png");
    //logo->setAnchorPoint(Vec2(0.1f, 0.9f));
    //logo->setPosition(Vec2(visibleSize.width * 0.1f, visibleSize.height * 0.9f));
    //this->addChild(logo);
    
    //create a title label
    this->titleLabel = ui::Text::create("JellyRun", TITLE_FONT_NAME, TITLE_FONT_SIZE);
    this->titleLabel->setAnchorPoint(Vec2(0.5f, 0.5f));
    this->titleLabel->setPosition(Vec2(visibleSize.width*0.5f, visibleSize.height * 0.9f));
    this->titleLabel->setColor(TITLE_LABEL_COLOR);
    this->addChild(titleLabel);
    
    ui::Button *singlePlayerButton = ui::Button::create();
    singlePlayerButton->setAnchorPoint(Vec2(0.5f, 0.6f));
    singlePlayerButton->setPosition(Vec2(visibleSize.width * 0.5f, visibleSize.height * 0.6f));
    singlePlayerButton->loadTextures("singlePlayerButton.png", "singlePlayerButtonPressed.png");
    singlePlayerButton->addTouchEventListener(CC_CALLBACK_2(Lobby::singlePlayerPressed, this));
    this->addChild(singlePlayerButton);
    
    ui::Button *multiplayerButton = ui::Button::create();
    multiplayerButton->setAnchorPoint(Vec2(0.5f, 0.3f));
    multiplayerButton->setPosition(Vec2(visibleSize.width * 0.5f, visibleSize.height * 0.3f));
    multiplayerButton->loadTextures("multiplayerButton.png", "multiplayerButtonPressed.png");
    multiplayerButton->addTouchEventListener(CC_CALLBACK_2(Lobby::multiplayerPressed, this));
    this->addChild(multiplayerButton);
}

void Lobby::singlePlayerPressed(Ref *pSender, ui::Widget::TouchEventType eEventType)
{
    if (eEventType == ui::Widget::TouchEventType::ENDED)
    {
        CCLOG("Single Player Mode");
        SceneManager::getInstance()->enterGameScene(false);
    }
}

void Lobby::multiplayerPressed(Ref *pSender, ui::Widget::TouchEventType eEventType)
{
    if (eEventType == ui::Widget::TouchEventType::ENDED)
    {
        CCLOG("Two Player Mode");
    }
}