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
#include "Jellyfish.h"
#include "Constants.h"
#include "Constants.h"
#include "UIConstants.h"
#include "Fish.h"
#include <time.h>
#include "InfiniteParallaxNode.h"
#include "UserDataManager.h"
#include "JSONPacker.h"
#include "PeerJelly.h"
#include "BlindFish.h"

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

    this->score = 0;
    this->myScore = 0;
    this->peerScore = 0;
    isTouchDown = false;
    gameIsOver = false;

    this->bestScore = UserDataManager::getInstance()->getBestScore();
    this->totalDeathTime = UserDataManager::getInstance()->getDeathTime();
    this->multiBestScore = UserDataManager::getInstance()->getMultiBestScore();
    CCLOG("TotalDeathTimebydefault=%int", totalDeathTime);
    scoreDistance = 0.0f;

    this->gameState = GameState::START;
    this->jellyIsSafe = true;

    return true;
}

void GameScene::onEnter()
{
    Node::onEnter();
    visibleSize = Director::getInstance()->getVisibleSize();

    // setup background
    backgroundNode = Background::create();
    this->addChild(backgroundNode, 0, "backgroundNode");

    // setup jellyfish
    jellyfish = Jellyfish::create();
    jellyfish->setAnchorPoint(Vec2(0.5f, 0.5f));
    jellyfish->setPosition(Vec2(visibleSize.width * 0.1f, visibleSize.height * 0.5f));
    jellyfish->setScale(JELLY_SCALE);
    Rect jellyRect = jellyfish->boundingBox();
    jellyWidth = jellyRect.size.width;
    jellyHeight = jellyRect.size.height;
    //CCLOG("jelly width and Height=%f,%f",jellyWidth,jellyHeight);
    this->addChild(jellyfish);

    if (this->networked)
    {
        // setup Peer's jellyfish
        peerJelly = PeerJelly::create();
        peerJelly->setAnchorPoint(Vec2(0.5f, 0.5f));
        peerJelly->setPosition(Vec2(visibleSize.width * 0.1f, visibleSize.height * 0.5f));
        peerJelly->setScale(JELLY_SCALE);
        this->addChild(peerJelly);
    }
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

    // If blindFish hits Jellyfish, game over
    Vector<Sprite*> blindFishes = this->getBlindFishGroup();
    int i = 0;
    for (auto blindFish:blindFishes)
    {
        i++;

        fishHitJelly = this->checkIfFishHitJelly(jellyfish, blindFish);

        this->updateJellyLife(fishHitJelly);
    }

    // set background to move
    this->backgroundNode->setBackgroundToMove();

    // Update the score
    scoreDistance += 1.0f;
    if ( scoreDistance >= 60.0f )
    {
        score ++;
        this->updateScoreLabel(score);
        scoreDistance = 0.0f;
    }
    this->myScore = score;

    if (this->networked)
    {
        this->sendGameStateOverNetwork();
    }
}

#pragma mark -
#pragma mark GameScene UI Methods

void GameScene::setupUI()
{
    Size visibleSize = Director::getInstance()->getVisibleSize();
    
    //create the pause button on the right top
    ui::Button* pauseButton = ui::Button::create();
    pauseButton->setAnchorPoint(Vec2(1.0f, 1.0f));
    pauseButton->setPosition(Vec2(visibleSize.width* 0.99f, visibleSize.height * 0.99f));
    pauseButton->loadTextures("pauseButton.png", "pauseButtonPressed.png");
    pauseButton->addTouchEventListener(CC_CALLBACK_2(GameScene::pauseButtonPressed, this));
    this->addChild(pauseButton);

    //create the score label on the left top
    this->scoreLabel = ui::Text::create("0", TITLE_FONT_NAME, TITLE_FONT_SIZE);
    this->scoreLabel->setAnchorPoint(Vec2(0.0f, 1.0f));
    this->scoreLabel->setPosition(Vec2(visibleSize.width*0.01f, visibleSize.height * 1.0f));
    this->scoreLabel->setColor(TITLE_LABEL_COLOR);
    this->addChild(scoreLabel);

    if (networked)
    {
        this->peerScoreLabel = ui::Text::create("0", TITLE_FONT_NAME, TITLE_FONT_SIZE);
        this->peerScoreLabel->setAnchorPoint(Vec2(0.0f, 1.0f));
        this->peerScoreLabel->setPosition(Vec2(visibleSize.width*0.5f, visibleSize.height * 1.0f));
        this->peerScoreLabel->setColor(TITLE_LABEL_COLOR);
        this->addChild(peerScoreLabel);
    }
}

void GameScene::pauseButtonPressed(cocos2d::Ref *pSender, ui::Widget::TouchEventType eEventType)
{
    if (eEventType == ui::Widget::TouchEventType::ENDED)
    {
        SceneManager::getInstance()->enterLobby();
    }
}

void GameScene::updateScoreLabel(int score)
{
    std::string scoreString = StringUtils::toString(score);
    this->scoreLabel->setString(scoreString);
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

        // rotate jellyfish when it is touched to move
        this->jellyfish->rotateJelly(touchPos);

        isTouchDown = true;

        return true;
    };

    touchListener->onTouchMoved = [&](Touch* touch, Event* event)
    {
        Vec2 touchPos = this->convertTouchToNodeSpace(touch);
        currentTouchPos = touchPos;
        // rotate jellyfish when it is touched to move
        this->jellyfish->rotateJelly(touchPos);

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

void GameScene::setGameActive(bool active)
{
    this->active = active;
    if (active)
    {
        this->schedule(CC_SCHEDULE_SELECTOR(GameScene::setBlindFishMove), 3.0f);
        this->scheduleUpdate();
    } else
    {
        this->unschedule(CC_SCHEDULE_SELECTOR(GameScene::setBlindFishMove));
        this->unscheduleUpdate();
    }
}

void GameScene::gameOver()
{
    this->gameIsOver = true;
    this->setGameActive(false);

    if (this->networked)
    {
        this->sendGameStateOverNetwork();
        
        if (_isHost)
        {
            this->sendFishStateOverNetwork();
        }

        if (score > multiBestScore)
        {
            multiBestScore = score;
            UserDataManager::getInstance()->setMultiBestScore(multiBestScore);
        }
        std::string scoreString = StringUtils::toString(score);
        std::string messageContent = "Your score is " + scoreString + "!";
        MessageBox(messageContent.c_str(), "Game Over");
        SceneManager::getInstance()->enterLobby();
    }

    else
    {
        //set the best score if score is over record
        if (score > bestScore)
        {
            bestScore = score;
            UserDataManager::getInstance()->setBestScore(bestScore);
        }
        //set the death time
        totalDeathTime ++;
        UserDataManager::getInstance()->setDeathTime(totalDeathTime);

        //enter the GameOverScene
        SceneManager::getInstance()->enterGameOver(score, bestScore, totalDeathTime);
    }
}

Vector<Sprite*> GameScene::getBlindFishGroup()
{
    return this->blindFishGroup;
}

void GameScene::updateJellyLife(bool fishHitJelly)
{
    switch (gameState)
    {
        case GameState::START:
        {
            if (fishHitJelly)
            {
                gameState = GameState::TWO_LIFE;
                // resize jellyfish
            }
            break;
        }
        case GameState::TWO_LIFE:
        {
            if (fishHitJelly)
            {
                gameState = GameState::ONE_LIFE;
                // resize jellyfish
            }
            break;
        }
        case GameState::ONE_LIFE:
        {
            if (fishHitJelly)
            {
                gameState = GameState::LOSE;
            }
            break;
        }

        case GameState::LOSE:
        {
            this->gameOver();
            break;
        }
    }
}

bool GameScene::checkIfFishHitJelly(Sprite* jellyfish, Sprite *fish)
{
    Rect jellyRect = jellyfish->getBoundingBox();
    Rect jellySmallRect;
    jellySmallRect.size.width = jellyRect.size.width * 0.8f;
    jellySmallRect.size.height = jellyRect.size.height * 0.8f;
    jellySmallRect.origin.x = jellyRect.origin.x;
    jellySmallRect.origin.y = jellyRect.origin.y;

    Rect fishRect = fish->getBoundingBox();

    Rect fishSmallRect;
    fishSmallRect.size.width = fishRect.size.width * 0.8f;
    fishSmallRect.size.height = fishRect.size.height * 0.8f;
    fishSmallRect.origin.x = fishRect.origin.x;
    fishSmallRect.origin.y = fishRect.origin.y;

    if (jellySmallRect.intersectsRect(fishSmallRect))
    {
        return true;
    }
    else
    {
        return false;
    }
}

void GameScene::setBlindFishMove(float dt)
{
    Vec2 blindFishStartPos;
    Vec2 blindFishTargetPos;
    int fishGroupSize = rand()%12;
    
    // Create the blindFishGroup for blindFish movement from four directions
    for (int index=0; index < fishGroupSize; ++index)
    {
        int blindFishRand = rand()%10;
        this->blindFish = BlindFish::create();
        this->blindFish->setAnchorPoint(Vec2(0.5f, 0.5f));
        this->blindFish->setScale(FISH_SCALE);
        this->blindFish->blindFishRotation(blindFishRand);

        if (this->networked)
        {
            if (_isHost)
            {
                blindFishStartPos = this->blindFish->getBlindFishStartPos(visibleSize, blindFishRand, index);
                blindFishTargetPos = this->blindFish->getBlindFishTargetPos(visibleSize, blindFishRand, index);
                blindFishStartPoses.push_back(blindFishStartPos);
                blindFishTargetPoses.push_back(blindFishTargetPos);
            }
            else
            {
                blindFishStartPos = this->getPeerBlindFishStartPoses()[index];
                blindFishTargetPos = this->getPeerBlindFishTargetPoses()[index];
            }
        }
        else
        {
            blindFishStartPos = this->blindFish->getBlindFishStartPos(visibleSize, blindFishRand, index);
            blindFishTargetPos = this->blindFish->getBlindFishTargetPos(visibleSize, blindFishRand, index);
        }

        blindFish->setPosition(blindFishStartPos);
        this->addChild(blindFish);
        blindFishGroup.pushBack(blindFish);

        auto moveFishAction = MoveTo::create(3.0f, blindFishTargetPos);
        auto fishSequence = Sequence::create(
                                             DelayTime::create(rand()%2),
                                             moveFishAction,
                                             CallFunc::create(CC_CALLBACK_0(GameScene::removeFromParent, blindFish)),NULL);
        blindFish->runAction(fishSequence);
    }

    if (networked)
    {
        if (this->_isHost)
        {
            this->sendFishStateOverNetwork();
        }
    }
}

int GameScene::getMyScore()
{
    return this->myScore;
}

void GameScene::setPeerScore(JSONPacker::GameState gameState)
{
    if (this->peerScore != gameState.score)
    {
        this->peerScore = gameState.score;
        std::string peerScoreString = StringUtils::toString(peerScore);
        this->peerScoreLabel->setString(peerScoreString);
    }
}

#pragma mark -
#pragma mark Networking

void GameScene::setNetworkedSession(bool networked, bool isHost)
{
    this->networked = networked;
    this->_isHost = isHost;
}

void GameScene::receivedData(const void* data, unsigned long length)
{
    const char* cstr = static_cast<const char*>(data);
    std::string json = std::string(cstr, length);

    // if data type is gameState
    if (JSONPacker::getDataType(json) == 0)
    {
        this->receivedGameStateData(json);
    }

    // if data type is fishState
    if (JSONPacker::getDataType(json) == 1)
    {
        if (!_isHost)
        {
            this->receivedFishStateData(json);
        }
    }
}

void GameScene::receivedGameStateData(std::string json)
{
    JSONPacker::GameState gameState = JSONPacker::unpackGameStateJSON(json);

    this->peerJelly->setPosition(gameState.jellyPos);

    this->setPeerScore(gameState);

    if (gameState.gameOver)
    {
        this->gameOver();
    }
}

void GameScene::receivedFishStateData(std::string json)
{
    JSONPacker::FishState fishState = JSONPacker::unpackFishStateJSON(json);
    this->peerBlindFishStartPoses = fishState.blindFishStartPos;
    this->peerBlindFishTargetPoses = fishState.blindFishTargetPos;
}

std::vector<Vec2> GameScene::getPeerBlindFishStartPoses()
{
    return this->peerBlindFishStartPoses;
}

std::vector<Vec2> GameScene::getPeerBlindFishTargetPoses()
{
    return this->peerBlindFishTargetPoses;
}

void GameScene::sendGameStateOverNetwork()
{
    JSONPacker::GameState gameState;

    gameState.score = this->getMyScore();
    gameState.name = NetworkingWrapper::getDeviceName();
    gameState.gameOver = this->gameIsOver;
    gameState.jellyPos = this->jellyfish->getPosition();

    std::string json = JSONPacker::packGameState(gameState);

    SceneManager::getInstance()->sendData(json.c_str(), json.length());
}

void GameScene::sendFishStateOverNetwork()
{
    JSONPacker::FishState fishState;

    if (blindFishStartPoses.size() > 0)
    {
        for (auto startPos : blindFishStartPoses)
        {
            fishState.blindFishStartPos.push_back(startPos);
        }
    }

    if (blindFishTargetPoses.size() > 0)
    {
        for (auto targetPos : blindFishTargetPoses)
        {
            fishState.blindFishTargetPos.push_back(targetPos);
        }
    }

    std::string json = JSONPacker::packFishState(fishState);

    SceneManager::getInstance()->sendData(json.c_str(), json.length());
}