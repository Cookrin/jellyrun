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
#include "Constants.h"
#include "Constants.h"
#include "Fish.h"
#include <time.h>

using namespace cocos2d;

#pragma mark -
#pragma mark GameScene Lifecycle

bool GameScene::init()
{
    if (!Node::init())
    {
        return false;
    }
    currentTouchPos = Vec2::ZERO;

    // Create the blindFishGroup for blindFish movement from four directions
    for (int index=0; index < 10; ++index)
    {
        blindFish = Fish::create();
        blindFish->setAnchorPoint(Vec2(0.0f, 0.0f));
        blindFish->setScale(FISH_SCALE);
        blindFishGroup.pushBack(blindFish);
    }
    isTouchDown = false;
    return true;
}

void GameScene::onEnter()
{
    Node::onEnter();
    
    visibleSize = Director::getInstance()->getVisibleSize();

    // setup background
    Sprite *gameBackground = Background::create();
    gameBackground->setAnchorPoint(Vec2(0.5f, 0.5f));
    gameBackground->setPosition(Vec2(visibleSize.width * 0.5f, visibleSize.height * 0.5f));
    this->addChild(gameBackground);

    // setup jellyfish
    jellyfish = Jellyfish::create();
    jellyfish->setAnchorPoint(Vec2(0.5f, 0.5f));
    jellyfish->setPosition(Vec2(visibleSize.width * 0.1f, visibleSize.height * 0.5f));
    jellyfish->setScale(JELLY_SCALE);
    Rect jellyRect = jellyfish->boundingBox();
    jellyWidth = jellyRect.size.width;
    jellyHeight = jellyRect.size.height;
    this->addChild(jellyfish);

    // setup fish
    fish = Fish::create();
    fish->setAnchorPoint(Vec2(0.0f, 0.0f));
    fish->setScale(FISH_SCALE);
    Rect fishRect = fish->boundingBox();
    fishWidth = fishRect.size.width;
    fishHeight = fishRect.size.height;

    this->setupUI();
    this->setupTouchHanding();
    this->setGameActive(true);
}

void GameScene::update(float dt)
{
    Vec2 jellyPos = jellyfish->getPosition();

    if (currentTouchPos != Vec2::ZERO)
    {
        //move jellyPos to currentTouchPos that you tap
        Vec2 targetDirection = currentTouchPos - jellyPos;
        setJellyIfCollides(currentTouchPos, targetDirection, dt);

        // move Jellyfish as you swiped
        if (isTouchDown)
        {
            Vec2 touchDirection = currentTouchPos - initialTouchPos;
            setJellyIfCollides(currentTouchPos, touchDirection, dt);
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

void GameScene::pauseButtonPressed(cocos2d::Ref *pSender, ui::Widget::TouchEventType eEventType)
{
    if (eEventType == ui::Widget::TouchEventType::ENDED)
    {
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
        initialTouchPos = touchPos;
        currentTouchPos = touchPos;
        isTouchDown = true;
        this->rotateJelly();
        return true;
    };

    touchListener->onTouchMoved = [&](Touch* touch, Event* event)
    {
        Vec2 touchPos = this->convertTouchToNodeSpace(touch);
        currentTouchPos = touchPos;
    };

    touchListener->onTouchEnded = [&](Touch* touch, Event* event)
    {
         isTouchDown = false;
    };

    this->getEventDispatcher()->addEventListenerWithSceneGraphPriority(touchListener, this);
}

void GameScene::setJellyIfCollides(Vec2 currentTouchPos, Vec2 targetDirection, float dt)
{
    Size jellySize = jellyfish->getContentSize();
    float jellyW = jellySize.width * JELLY_SCALE;
    float jellyH = jellySize.height * JELLY_SCALE;
    Vec2 jellyPos = jellyfish->getPosition();

    if (targetDirection.getLength() > 5.0f)
    {
        targetDirection =  targetDirection.getNormalized();
        targetDirection *= 300 * dt;
        Vec2 targetJellyfishPos = jellyPos + targetDirection;
        
        if (targetJellyfishPos.x < jellyW * 0.5f)
        {
            targetJellyfishPos.x = jellyW * 0.5f;
        }
        
        else if (targetJellyfishPos.x > (visibleSize.width - jellyW * 0.5f))
        {
            targetJellyfishPos.x = visibleSize.width - jellyW * 0.5f;
        }
        
        if (targetJellyfishPos.y < jellyH * 0.5f)
        {
            targetJellyfishPos.y = jellyH * 0.5f;
        }
        
        else if (targetJellyfishPos.y > (visibleSize.height - jellyH * 0.5f))
        {
            targetJellyfishPos.y = visibleSize.height - jellyH * 0.5f;
        }
        jellyfish->setPosition(targetJellyfishPos);
    }
}

// make the pauseButton disappear when the player touch the screen

// background move ahead

void GameScene::setBlindFishMove(float dt)
{
    Vec2 blindFishTargetPos;
    Vec2 blindFishStartPos;
    Vector<Sprite*> blindFishes = this->getBlindFishGroup();
    int index = 0;
    for (auto blindFish:blindFishes)
    {
        index++;
        int blindFishRand = rand()%10;
        CCLOG("i=%int", index);
        blindFishStartPos = this->getBlindFishStartPos(blindFishRand, index);
        blindFishTargetPos = this->getBlindFishTargetPos(blindFishRand, index);
        blindFish->setPosition(blindFishStartPos);
        blindFish->retain();
        blindFish->removeFromParent();
        this->addChild(blindFish);
        auto moveFishAction = MoveTo::create(2.0f, blindFishTargetPos);
        auto fishSequence = Sequence::create(
            DelayTime::create(rand()%2),
            moveFishAction,
            CallFunc::create(CC_CALLBACK_0(GameScene::removeFromParent, blindFish)),NULL);
        blindFish->runAction(fishSequence);
    }
}

void GameScene::setGameActive(bool active)
{
    this->active = active;
    if (active) {
        this->schedule(CC_SCHEDULE_SELECTOR(GameScene::setBlindFishMove), 3.0f);
        this->scheduleUpdate();
    } else {
        this->unschedule(CC_SCHEDULE_SELECTOR(GameScene::setBlindFishMove));
        this->unscheduleUpdate();
    }
}

Vector<Sprite*> GameScene::getBlindFishGroup()
{
    return this->blindFishGroup;
}

bool GameScene::checkIfFishHitJelly(Vec2 jellyPos, Vec2 fishPos)
{
    Vec2 distanceBetweenFishAndJelly = jellyPos - fishPos;
    if ( distanceBetweenFishAndJelly.getLength() < (jellyWidth + fishWidth) )
    {
        return true;
    }
    else
    {
        return false;
    }
}

Vec2 GameScene::getBlindFishStartPos(int blindFishRand, int index)
{
    Vec2 fishPos;
    if ( blindFishRand > 7 ) //blindFishSide = "fromTop"
    {
        fishPos = Vec2(visibleSize.width *(index-1) / 10.0f, visibleSize.height * 1.0f);
    }
    else if ( blindFishRand < 4 ) //blindFishSide = "fromBottom"
    {
        fishPos = Vec2(visibleSize.width *(index-1) / 10.0f, fishHeight * (-1.0f));
    }
    else if ( blindFishRand == 4 || blindFishRand == 5 ) //blindFishSide = "fromLeft"
    {
        fishPos = Vec2(fishWidth * (-1.0f), visibleSize.height * (index - 1) / 4.0f );
    }
    else //blindFishSide = "fromRight"
    {
        fishPos = Vec2(visibleSize.width * 1.0f, visibleSize.height * (index - 1) / 4.0f );
    }
        return fishPos;
}

Vec2 GameScene::getBlindFishTargetPos(int blindFishRand, int index)
{
    Vec2 fishPos;
    if ( blindFishRand > 7 ) //blindFishSide = "fromTop"
    {
        fishPos = Vec2(visibleSize.width *(index-1) / 10.0f, fishHeight * (-1.0f));
    }
    else if ( blindFishRand < 4 ) //blindFishSide = "fromBottom"
    {
        fishPos = Vec2(visibleSize.width *(index-1) / 10.0f, visibleSize.height);
    }
    else if ( blindFishRand == 4 || blindFishRand == 5 ) //blindFishSide = "fromLeft"
    {
        fishPos = Vec2(visibleSize.width * 1.0f, visibleSize.height * (index - 1) / 4.0f );
    }
    else //blindFishSide = "fromRight"
    {
        fishPos = Vec2(fishWidth * (-1.0f), visibleSize.height * (index - 1) / 4.0f );
    }
    return fishPos;
}

void GameScene::rotateJelly()
{
auto rotateBy = RotateBy::create(2.0f, atan2((jellyfish->getPositionX()),(jellyfish->getPositionY()))*180/3.1415926+90);
jellyfish->runAction(rotateBy);
}