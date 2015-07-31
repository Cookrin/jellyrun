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

    this->score = 0;
    isTouchDown = false;
    this->networkedSession = false;
    _isHost = true;

    this->bestScore = UserDataManager::getInstance()->getBestScore();
    this->totalDeathTime = UserDataManager::getInstance()->getDeathTime();
    CCLOG("TotalDeathTimebydefault=%int", totalDeathTime);
    scoreDistance = 0.0f;
    return true;
}

void GameScene::onEnter()
{
    Node::onEnter();
    visibleSize = Director::getInstance()->getVisibleSize();

    // setup fish
    fish = Fish::create();
    fish->setAnchorPoint(Vec2(0.0f, 0.0f));
    fish->setScale(FISH_SCALE);
    Rect fishRect = fish->boundingBox();
    fishWidth = fishRect.size.width;
    fishHeight = fishRect.size.height;
    //CCLOG("fish width and Height=%f,%f",fishWidth,fishHeight);

    // setup background
    InfiniteParallaxNode* groundNode = InfiniteParallaxNode::create();
    this->addChild(groundNode, 0, "groundNode");
    
    underwaterBG1 = Sprite::create("Underwater.png");
    underwaterBG1->setAnchorPoint(Vec2(0.0f,0.0f));
    underwaterBG1->setOpacity(255 * 1.0);

    underwaterBG2 = Sprite::create("Underwater.png");
    underwaterBG2->setAnchorPoint(Vec2(0.0f,0.0f));
    underwaterBG2->setOpacity(255 * 1.0);

    shipwreckBG1 = Sprite::create("Shipwreck.png");
    shipwreckBG1->setAnchorPoint(Vec2(0.0f,0.0f));
    shipwreckBG1->setOpacity(255 * 1.0);

    shipwreckBG2 = Sprite::create("Shipwreck.png");
    shipwreckBG2->setAnchorPoint(Vec2(0.0f,0.0f));
    shipwreckBG2->setOpacity(255 * 1.0);

    rockBG1 = Sprite::create("Rock.png");
    rockBG1->setAnchorPoint(Vec2(0.0f,0.0f));
    rockBG1->setOpacity(255 * 1.0);

    rockBG2 = Sprite::create("Rock.png");
    rockBG2->setAnchorPoint(Vec2(0.0f,0.0f));
    rockBG2->setOpacity(255 * 1.0);

    aquaticBG1 = Sprite::create("Aquatic.png");
    aquaticBG1->setAnchorPoint(Vec2(0.0f,0.0f));

    aquaticBG2 = Sprite::create("Aquatic.png");
    aquaticBG2->setAnchorPoint(Vec2(0.0f,0.0f));

    coralBG1 = Sprite::create("Coral.png");
    coralBG1->setAnchorPoint(Vec2(0.0f,0.0f));
    
    coralBG2 = Sprite::create("Coral.png");
    coralBG2->setAnchorPoint(Vec2(0.0f,0.0f));

    Size shipwreckBGSize = shipwreckBG1->getContentSize();
    Size lightBGSize = underwaterBG1->getContentSize();
    Size rockSize = rockBG1 ->getContentSize();

    // addChild(Node * child, int z, const Vec2& parallaxRatio, const Vec2& positionOffset);
    groundNode->addChild(
                         underwaterBG1,
                         // Set z-index
                         0,
                         // Set ration
                         Vec2(0.5f, 0.0f),
                         // Set position
                         Vec2((0.0f), 0.0f)
                         );
    groundNode->addChild(
                         underwaterBG2,
                         // Set z-index
                         0,
                         // Set ration
                         Vec2(0.5f, 0.0f),
                         // Set position
                         Vec2(visibleSize.width, 0.0f)
                         );
    groundNode->addChild(
                         shipwreckBG1,
                         1,
                         Vec2(1.0f, 0.0f),
                         Vec2(visibleSize.width * 0.3f, visibleSize.width * 0.03f)
                         );
    groundNode->addChild(
                         shipwreckBG2,
                         1,
                         Vec2(1.0f, 0.0f),
                         Vec2(visibleSize.width * 1.3f, visibleSize.width * 0.03f)
                         );
    groundNode->addChild(
                         rockBG1,
                         // Set z-index
                         2,
                         // Set ration
                         Vec2(2.0f, 0.0f),
                         // Set position
                         Vec2(0.0f, 0.0f)
                         );
    groundNode->addChild(
                         rockBG2,
                         // Set z-index
                         2,
                         // Set ration
                         Vec2(2.0f, 0.0f),
                         // Set position
                         Vec2(rockSize.width, 0.0f)
                         );
    groundNode->addChild(
                         aquaticBG1,
                         3,
                         Vec2(2.5f, 0.0f),
                         Vec2(0.0f, 0.0f));
    groundNode->addChild(
                         aquaticBG2,
                         3,
                         Vec2(2.5f, 0.0f),
                         Vec2(visibleSize.width, 0.0f)
                         );
    groundNode->addChild(
                         coralBG1,
                         3,
                         Vec2(2.5f, 0.0f),
                         Vec2(0.0f, 0.0f));
    groundNode->addChild(
                         coralBG2,
                         3,
                         Vec2(2.5f, 0.0f),
                         Vec2(visibleSize.width, 0.0f)
                         );

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

    if (this->networkedSession)
    {
        // setup Peer's jellyfish
        peerJelly = PeerJelly::create();
        peerJelly->setAnchorPoint(Vec2(0.5f, 0.5f));
        peerJelly->setScale(JELLY_SCALE);
        peerJelly->setPosition(Vec2(visibleSize.width * 0.5f, visibleSize.height * 0.5f));
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

    Vector<Sprite*> blindFishes = this->getBlindFishGroup();
    int i = 0;
    for (auto blindFish:blindFishes)
    {
        i++;
        fishPos = blindFish->getPosition();
        fishHitJelly = this->checkIfFishHitJelly(jellyfish, blindFish);
        if (fishHitJelly == true)
        {
            this->gameOver();
        }
    }
    //auto followAction = Follow::create(jellyfish);
    //this->runAction(followAction);
    InfiniteParallaxNode* groundNode = (InfiniteParallaxNode*)this->getChildByName("groundNode");
    Vec2 scrollDecrement = Vec2(-1.0f, 0.0f);
    groundNode->setPosition(groundNode->getPosition() + scrollDecrement);
    groundNode->updatePosition();
    scoreDistance += 1.0f;
    if ( scoreDistance >= 60.0f )
    {
        score ++;
        this->updateScoreLabel(score);
        scoreDistance = 0.0f;
    }

    if (this->networkedSession)
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

void GameScene::setGameActive(bool active)
{
    this->active = active;
    if (active)
    {
        // if host
        this->schedule(CC_SCHEDULE_SELECTOR(GameScene::setBlindFishMove), 3.0f);
        // else
            //this->schedule(CC_SCHEDULE_SELECTOR(GameScene::setPeerBlindFishMove), 3.0f);
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

    if (this->networkedSession)
    {
        this->sendGameStateOverNetwork();
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

bool GameScene::checkIfFishHitJelly(Sprite* jellyfish, Sprite *fish)
{
    Rect jellyRect = jellyfish->getBoundingBox();
    Rect fishRect = fish->getBoundingBox();

    if (jellyRect.intersectsRect(fishRect))
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
        fishPos =  fishPos = Vec2(visibleSize.width *(index-1) / 10.0f, visibleSize.height * 1.0f);;
    }
    else if ( blindFishRand < 4 ) //blindFishSide = "fromBottom"
    {
        fishPos = fishPos = Vec2(visibleSize.width * index / 10.0f, fishHeight * (-1.0f));
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
        fishPos = Vec2(visibleSize.width *(index) / 10.0f, visibleSize.height);
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

void GameScene::setBlindFishMove(float dt)
{
    Vec2 blindFishStartPos;
    Vec2 blindFishTargetPos;

    Vector<Sprite*> blindFishes = this->getBlindFishGroup();
    int index = 0;
    for (auto blindFish:blindFishes)
    {
        index++;
        int blindFishRand = rand()%10;
        blindFishStartPos = this->getBlindFishStartPos(blindFishRand, index);
        blindFishTargetPos = this->getBlindFishTargetPos(blindFishRand, index);
        blindFish->setPosition(blindFishStartPos);
        this->blindFishRotation(blindFish, blindFishRand);
        blindFish->retain();
        blindFish->removeFromParent();
        this->addChild(blindFish);
        auto moveFishAction = MoveTo::create(3.0f, blindFishTargetPos);
        auto fishSequence = Sequence::create(
                                             DelayTime::create(rand()%2),
                                             moveFishAction,
                                             CallFunc::create(CC_CALLBACK_0(GameScene::removeFromParent, blindFish)),NULL);
        blindFish->runAction(fishSequence);
    }
}

void GameScene::rotateJelly()
{
    auto rotateBy = RotateTo::create(2.0f, atan2((jellyfish->getPositionX()),(jellyfish->getPositionY()))*180.0f/3.1415926f+90.0f);
jellyfish->runAction(rotateBy);
}

void GameScene::blindFishRotation(Sprite* blindFish, int blindFishRand)
{
    if ( blindFishRand < 4 ) //blindFishSide = "fromBottom"
    {
        blindFish->runAction(RotateTo::create(0.05f, 180.0f));
    }
    else if ( blindFishRand == 4 || blindFishRand == 5 ) //blindFishSide = "fromLeft"
    {
        auto leftFishAct1 = RotateTo::create(0.05f, 270.0f);
        auto leftFishAct2 = FlipX::create(true);
        auto leftFishSpawn = Spawn::create(
                                            leftFishAct1,
                                            leftFishAct2,
                                            NULL);
        blindFish->runAction(leftFishSpawn);
    }
    else if ( blindFishRand == 6 || blindFishRand == 7)//blindFishSide = "fromRight"
    {
        blindFish->runAction(RotateBy::create(0.05f, 90.0f));
    }
}

#pragma mark -
#pragma mark Networking

void GameScene::setNetworkedSession(bool networkedSession, bool isHost)
{
    this->networkedSession = networkedSession;
    this->_isHost = isHost;
}

void GameScene::receivedData(const void* data, unsigned long length)
{
    const char* cstr = static_cast<const char*>(data);
    std::string json = std::string(cstr, length);
    JSONPacker::GameState state = JSONPacker::unpackGameStateJSON(json);

    if (state.gameOver)
    {
        this->gameOver();
    }

    this->peerJelly->setJellyPos(state);

    /*
    get the peerBindFish's startPos and TargetPos;
    */
}

void GameScene::sendGameStateOverNetwork()
{
    JSONPacker::GameState gameState;

    gameState.name = NetworkingWrapper::getDeviceName();
    gameState.score = this->score;
    gameState.gameOver = this->gameIsOver;
    gameState.jellyPos = this->jellyfish->getPosition();
    //pass the blindFish's startPos and targetPos to the peerBlindFish like this
      //gameState.peerBlindFishStartPos = this->blindFish->getBlindFishStartPos();
      //gameState.peerBlindFishTargetPos = this->blindFish->getBlindFishTargetPos();

    std::string json = JSONPacker::packGameState(gameState);

    SceneManager::getInstance()->sendData(json.c_str(), json.length());
}