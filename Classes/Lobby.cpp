//
//  Lobby.cpp
//  jellyrun
//
//  Created by Tingting Gu on 2015/07/13.
//
//

#include "cocosGUI.h"
#include "Lobby.h"

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

void Lobby::onEnter() {
    
    Node::onEnter();
    
    setupUI();
}

void Lobby::setupUI() {
    Size visibleSize = Director::getInstance()->getVisibleSize();
    
    Sprite *logo = Sprite::create("logo.png");
    logo->setAnchorPoint(Vec2(0.1f, 0.9f));
    logo->setPosition(Vec2(visibleSize.width * 0.1f, visibleSize.height * 0.9f));
    this->addChild(logo);
    
    ui::Button *singlePlayerButton = ui::Button::create();
    singlePlayerButton->setAnchorPoint(Vec2(0.15f, 0.5f));
    singlePlayerButton->setPosition(Vec2(visibleSize.width * 0.15f, visibleSize.height * 0.5f));
    singlePlayerButton->loadTextures("singlePlayerButton.png", "singlePlayerButtonPressed.png");
    this->addChild(singlePlayerButton);
    
    ui::Button *multiPlayerButton = ui::Button::create();
    multiPlayerButton->setAnchorPoint(Vec2(0.85f, 0.5f));
    multiPlayerButton->setPosition(Vec2(visibleSize.width * 0.85f, visibleSize.height * 0.5f));
    multiPlayerButton->loadTextures("multiplayerButton.png", "multiplayerButtonPressed.png");
    this->addChild(multiPlayerButton);
    
    return;
}