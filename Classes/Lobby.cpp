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
#include "Background.h"
#include "InfoLayer.h"

using namespace cocos2d;

bool Lobby::init()
{
    if (! Node::init())
    {
        return false;
    }
    return true;
}

void Lobby::onEnter()
{
    Node::onEnter();

    visibleSize = Director::getInstance()->getVisibleSize();
    visibleSizeMultiplier = visibleSize.width / 1134.0f;

    SceneManager::getInstance()->receiveMultiplayerInvitations();

    // setup background
    lobbyBackground = Background::create();
    this->addChild(lobbyBackground, 0, "lobbyBackground");

    // setup bubble particle
    auto bubbleParticle = ParticleSystemQuad::create("Bubble.plist");
    bubbleParticle->setPosition(visibleSize.width * 0.5f, visibleSize.height * (-0.1f));
    this->addChild(bubbleParticle, 0);

    // setup sea objects
    lobbySeaObjects = SeaObjects::create();
    this->addChild(lobbySeaObjects, 0, "lobbySeaObjects");

    setupUI();
    this->scheduleUpdate();
}

void Lobby::onExit()
{
    Node::onExit();
    SceneManager::getInstance()->stopAdvertisingAvailability();
}

void Lobby::setupUI()
{
    Size visibleSize = Director::getInstance()->getVisibleSize();

    float bigFontSize = BIG_TITLE_FONT_SIZE * visibleSizeMultiplier;
    //create a title label
    this->titleLabel = ui::Text::create("RUN JELLY RUN", TITLE_FONT_NAME, bigFontSize);
    this->titleLabel->setAnchorPoint(Vec2(0.5f, 0.5f));
    this->titleLabel->setPosition(Vec2(visibleSize.width*0.5f, visibleSize.height * 0.85f));
    this->titleLabel->setColor(WHITE_LABEL_COLOR);
    this->addChild(titleLabel);

    ui::Button *singlePlayerButton = ui::Button::create();
    singlePlayerButton->setAnchorPoint(Vec2(0.5f, 0.5f));
    singlePlayerButton->setPosition(Vec2(visibleSize.width * 0.333f, visibleSize.height * 0.5f));
    singlePlayerButton->loadTextures("singlePlayerButton.png", "singlePlayerButtonPressed.png");
    singlePlayerButton->addTouchEventListener(CC_CALLBACK_2(Lobby::singlePlayerPressed, this));
    this->addChild(singlePlayerButton);

    ui::Button *multiplayerButton = ui::Button::create();
    multiplayerButton->setAnchorPoint(Vec2(0.5f, 0.5f));
    multiplayerButton->setPosition(Vec2(visibleSize.width * 0.666f, visibleSize.height * 0.5f));
    multiplayerButton->loadTextures("multiplayerButton.png", "multiplayerButtonPressed.png");
    multiplayerButton->addTouchEventListener(CC_CALLBACK_2(Lobby::multiplayerPressed, this));
    this->addChild(multiplayerButton);

    float fontSize = BUTTON_FONT_SIZE * visibleSizeMultiplier;
    //create a play again label
    this->singlePlayerLabel = ui::Text::create("SINGLE PLAY", TITLE_FONT_NAME, fontSize);
    this->singlePlayerLabel->setAnchorPoint(Vec2(0.5f, 0.5f));
    this->singlePlayerLabel->setPosition(Vec2(visibleSize.width*0.333f, visibleSize.height * 0.3f));
    this->singlePlayerLabel->setColor(WHITE_LABEL_COLOR);
    this->addChild(singlePlayerLabel);

    //create a multi play label
    this->multiplayerLabel = ui::Text::create("MULTIPLAY", TITLE_FONT_NAME, fontSize);
    this->multiplayerLabel->setAnchorPoint(Vec2(0.5f, 0.5f));
    this->multiplayerLabel->setPosition(Vec2(visibleSize.width*0.666f, visibleSize.height * 0.3f));
    this->multiplayerLabel->setColor(WHITE_LABEL_COLOR);
    this->addChild(multiplayerLabel);

    // info button
    ui::Button* infoButton = ui::Button::create();
    infoButton->setAnchorPoint(Vec2(0.5f, 0.5f));
    infoButton->setPosition(Vec2(visibleSize.width* 0.9f, visibleSize.height * 0.1f));
    infoButton->loadTextures("infoButton.png", "infoButtonPressed.png");
    infoButton->addTouchEventListener(CC_CALLBACK_2(Lobby::infoButtonPressed, this));
    this->addChild(infoButton);

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
        SceneManager::getInstance()->showPeerList();
    }
}

void Lobby::infoButtonPressed(Ref *pSender, ui::Widget::TouchEventType eEventType)
{
    if (eEventType == ui::Widget::TouchEventType::ENDED)
    {
        //SceneManager::getInstance()->showPeerList();
        addChild(InfoLayer::create());
    }
}

void Lobby::update(float dt)
{
    // set background to move
    this->lobbyBackground->setBackgroundToMove();

    // set seaObjects to move
    this->lobbySeaObjects->setSeaObjectsToMove();
}
