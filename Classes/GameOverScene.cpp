//
//  GameOverScene.cpp
//  jellyrun
//
//  Created by Tingting Gu on 2015/07/24.
//
//

#include "GameOverScene.h"
#include "cocosGUI.h"
#include "SceneManager.h"
#include "UIConstants.h"
#include "GameScene.h"
#include <stdio.h>

using namespace cocos2d;

bool GameOverScene::init()
{
    if (! Node::init())
    {
        return false;
    }
    visibleSize = Director::getInstance()->getVisibleSize();

    LayerColor* background = LayerColor::create(Color4B(255, 255, 255, 255));
    background->setOpacity(255 * 0.5f);
    this->addChild(background);

    auto separateLine = DrawNode::create();

    separateLine->drawLine(
                           Vec2(visibleSize.width*0.1f, visibleSize.height*0.82f),
                           Vec2(visibleSize.width*0.9f, visibleSize.height*0.82f),
                           Color4F(0, 0, 0, 10));
    this->addChild(separateLine,10);

    setupUI();

    return true;
}

void GameOverScene::onEnter()
{
    Node::onEnter();
}

void GameOverScene::setupUI()
{
    //create a high score label
    this->highScoreLabel = ui::Text::create("BEST", TITLE_FONT_NAME, TITLE_FONT_SIZE);
    this->highScoreLabel->setAnchorPoint(Vec2(0.5f, 0.5f));
    this->highScoreLabel->setPosition(Vec2(visibleSize.width*0.2f, visibleSize.height * 0.9f));
    this->highScoreLabel->setColor(TITLE_LABEL_COLOR);
    this->addChild(highScoreLabel);

    //create score label
    this->scoreLabel = ui::Text::create("SCORE", TITLE_FONT_NAME, TITLE_FONT_SIZE);
    this->scoreLabel->setAnchorPoint(Vec2(0.5f, 0.5f));
    this->scoreLabel->setPosition(Vec2(visibleSize.width*0.5f, visibleSize.height * 0.9f));
    this->scoreLabel->setColor(TITLE_LABEL_COLOR);
    this->addChild(scoreLabel);

    //create a death time label
    this->totalDeathLabel = ui::Text::create("DEATH", TITLE_FONT_NAME, TITLE_FONT_SIZE);
    this->totalDeathLabel->setAnchorPoint(Vec2(0.5f, 0.5f));
    this->totalDeathLabel->setPosition(Vec2(visibleSize.width*0.8f, visibleSize.height * 0.9f));
    this->totalDeathLabel->setColor(TITLE_LABEL_COLOR);
    this->addChild(totalDeathLabel);

    //show best score number label
    this->bestScoreNumLabel = ui::Text::create("0", TITLE_FONT_NAME, TITLE_FONT_SIZE);
    this->bestScoreNumLabel->setAnchorPoint(Vec2(0.5f, 0.5f));
    this->bestScoreNumLabel->setPosition(Vec2(visibleSize.width*0.2f, visibleSize.height * 0.75f));
    this->bestScoreNumLabel->setColor(TITLE_LABEL_COLOR);
    this->addChild(bestScoreNumLabel);

    //create score number label
    this->scoreNumLabel = ui::Text::create("0", TITLE_FONT_NAME, TITLE_FONT_SIZE);
    this->scoreNumLabel->setAnchorPoint(Vec2(0.5f, 0.5f));
    this->scoreNumLabel->setPosition(Vec2(visibleSize.width*0.5f, visibleSize.height * 0.75f));
    this->scoreNumLabel->setColor(TITLE_LABEL_COLOR);
    this->addChild(scoreNumLabel);

    //create a death time label
    this->totalDeathNumLabel = ui::Text::create("0", TITLE_FONT_NAME, TITLE_FONT_SIZE);
    this->totalDeathNumLabel->setAnchorPoint(Vec2(0.5f, 0.5f));
    this->totalDeathNumLabel->setPosition(Vec2(visibleSize.width*0.8f, visibleSize.height * 0.75f));
    this->totalDeathNumLabel->setColor(TITLE_LABEL_COLOR);
    this->addChild(totalDeathNumLabel);

    //create a play again label
    this->playAgainLabel = ui::Text::create("PLAY AGAIN", TITLE_FONT_NAME, BUTTON_FONT_SIZE);
    this->playAgainLabel->setAnchorPoint(Vec2(0.5f, 0.5f));
    this->playAgainLabel->setPosition(Vec2(visibleSize.width*0.24f, visibleSize.height * 0.35f));
    this->playAgainLabel->setColor(TITLE_LABEL_COLOR);
    this->addChild(playAgainLabel);

    //create a continue play label
    this->continuePLayLabel = ui::Text::create("CONTINUE", TITLE_FONT_NAME, BUTTON_FONT_SIZE);
    this->continuePLayLabel->setAnchorPoint(Vec2(0.5f, 0.5f));
    this->continuePLayLabel->setPosition(Vec2(visibleSize.width*0.5f, visibleSize.height * 0.3f));
    this->continuePLayLabel->setColor(TITLE_LABEL_COLOR);
    this->addChild(continuePLayLabel);

    //create a multi play label
    this->enterMultiplayLabel = ui::Text::create("MULTIPLAY", TITLE_FONT_NAME, BUTTON_FONT_SIZE);
    this->enterMultiplayLabel->setAnchorPoint(Vec2(0.5f, 0.5f));
    this->enterMultiplayLabel->setPosition(Vec2(visibleSize.width*0.76f, visibleSize.height * 0.35f));
    this->enterMultiplayLabel->setColor(TITLE_LABEL_COLOR);
    this->addChild(enterMultiplayLabel);

    ui::Button *playAgainButton = ui::Button::create();
    playAgainButton->setAnchorPoint(Vec2(0.5f, 0.5f));
    playAgainButton->setPosition(Vec2(visibleSize.width * 0.24f, visibleSize.height * 0.5f));
    playAgainButton->loadTextures("playAgainButton.png", "playAgainButtonPressed.png");
    playAgainButton->addTouchEventListener(CC_CALLBACK_2(GameOverScene::playAgainPressed, this));
    this->addChild(playAgainButton);

    ui::Button *continuePlayButton = ui::Button::create();
    continuePlayButton->setAnchorPoint(Vec2(0.5f, 0.5f));
    continuePlayButton->setPosition(Vec2(visibleSize.width * 0.5f, visibleSize.height * 0.5f));
    continuePlayButton->loadTextures("continuePlayButton.png", "continuePlayButtonPressed.png");
    continuePlayButton->addTouchEventListener(CC_CALLBACK_2(GameOverScene::continuePlayPressed, this));
    this->addChild(continuePlayButton);

    ui::Button *multiplayerButton = ui::Button::create();
    multiplayerButton->setAnchorPoint(Vec2(0.5f, 0.5f));
    multiplayerButton->setPosition(Vec2(visibleSize.width * 0.76f, visibleSize.height * 0.5f));
    multiplayerButton->loadTextures("multiButton.png", "multiButtonPressed.png");
    multiplayerButton->addTouchEventListener(CC_CALLBACK_2(GameOverScene::multiplayerPressed, this));
    this->addChild(multiplayerButton);

    //create a leaderboards label
    this->leaderboardsLabel = ui::Text::create("LEADERBOARDS",TITLE_FONT_NAME,BUTTON_FONT_SMALL_SIZE);
    this->leaderboardsLabel->setAnchorPoint(Vec2(0.5f, 0.5f));
    this->leaderboardsLabel->setPosition(Vec2(visibleSize.width*0.4f, visibleSize.height * 0.1f));
    this->leaderboardsLabel->setColor(TITLE_LABEL_COLOR);
    this->addChild(leaderboardsLabel);

    //create a contact me label
    this->contactMeLabel = ui::Text::create("CONTACT ME", TITLE_FONT_NAME, BUTTON_FONT_SMALL_SIZE);
    this->contactMeLabel->setAnchorPoint(Vec2(0.5f, 0.5f));
    this->contactMeLabel->setPosition(Vec2(visibleSize.width*0.6f, visibleSize.height * 0.1f));
    this->contactMeLabel->setColor(TITLE_LABEL_COLOR);
    this->addChild(contactMeLabel);

    //create a leaderboards button
    ui::Button *leaderboardsButton = ui::Button::create();
    leaderboardsButton->setAnchorPoint(Vec2(0.5f, 0.5f));
    leaderboardsButton->setPosition(Vec2(visibleSize.width * 0.4f, visibleSize.height * 0.2f));
    leaderboardsButton->loadTextures("leaderboardsButton.png", "leaderboardsButtonPressed.png");
    leaderboardsButton->addTouchEventListener(CC_CALLBACK_2(GameOverScene::continuePlayPressed, this));
    this->addChild(leaderboardsButton);

    //create a contact me button
    ui::Button *contactMeButton = ui::Button::create();
    contactMeButton->setAnchorPoint(Vec2(0.5f, 0.5f));
    contactMeButton->setPosition(Vec2(visibleSize.width * 0.6f, visibleSize.height * 0.2f));
    contactMeButton->loadTextures("contactMeButton.png", "contactMeButtonPressed.png");
    contactMeButton->addTouchEventListener(CC_CALLBACK_2(GameOverScene::multiplayerPressed, this));
    this->addChild(contactMeButton);
}

void GameOverScene::playAgainPressed(Ref *pSender, ui::Widget::TouchEventType eEventType)
{
    if (eEventType == ui::Widget::TouchEventType::ENDED)
    {
        CCLOG("Play a new game");
        SceneManager::getInstance()->enterGameScene(false);
    }
}

void GameOverScene::continuePlayPressed(Ref *pSender, ui::Widget::TouchEventType eEventType)
{
    if (eEventType == ui::Widget::TouchEventType::ENDED)
    {
        CCLOG("Continue Playing");
    }
}

void GameOverScene::multiplayerPressed(Ref *pSender, ui::Widget::TouchEventType eEventType)
{
    if (eEventType == ui::Widget::TouchEventType::ENDED)
    {
        CCLOG("Two Player Mode");
    }
}

void GameOverScene::updateScoreLabel(int score)
{
    this->score = score;
    std::string scoreString = StringUtils::toString(score);
    this->scoreNumLabel->setString(scoreString);
}

void GameOverScene::updateBestScoreLabel(int bestScore)
{
    this->bestScore = bestScore;
    std::string scoreString = StringUtils::toString(score);
    this->bestScoreNumLabel->setString(scoreString);
}

void GameOverScene::updateDeathTimeLabel(int deathTime)
{
    this->deathTime = deathTime;
    std::string deathTimeString = StringUtils::toString(deathTime);
    this->totalDeathLabel->setString(deathTimeString);
}