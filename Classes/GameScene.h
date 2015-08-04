//
//  GameScene.h
//  jellyrun
//
//  Created by Tingting Gu on 2015/07/13.
//
//

#ifndef __jellyrun__GameScene__
#define __jellyrun__GameScene__

#include "cocos2d.h"
#include "CocosGUI.h"
#include "JSONPacker.h"
#include "Jellyfish.h"
#include "BlindFish.h"

using namespace cocos2d;

class PeerJelly;
class BlindFish;
class Jellyfish;

class GameScene : public cocos2d::Node
{
public:
    CREATE_FUNC(GameScene);
    void setNetworkedSession(bool networkedSession, bool isHost);
    void receivedGameStateData(const void* data, unsigned long length);
    void receivedFishStateData(const void* data, unsigned long length);
    void sendGameStateOverNetwork();
    void sendFishStateOverNetwork();
    
    Jellyfish* jellyfish;
    PeerJelly* peerJelly;
    BlindFish* blindFish;

private:

protected:
    bool networked;
    bool _isHost;
    Vec2 initialTouchPos;
    Vec2 currentTouchPos;
    bool isTouchDown;
    bool active;
    Size visibleSize;
    Vec2 fishPos;
    float jellyWidth;
    float jellyHeight;
    float fishWidth;
    float fishHeight;
    cocos2d::Sprite* fish;
    cocos2d::Vector<Sprite*> blindFishGroup;
    bool fishHitJelly;
    bool gameIsOver;
    Sprite *shipwreckBG1;
    Sprite *shipwreckBG2;
    Sprite *underwaterBG1;
    Sprite *underwaterBG2;
    Sprite *rockBG1;
    Sprite *rockBG2;
    Sprite *aquaticBG1;
    Sprite *aquaticBG2;
    Sprite *coralBG1;
    Sprite *coralBG2;

    bool init() override;
    void onEnter() override;
    void update(float dt);
    void setGameActive(bool active);
    void gameOver();

    ui::Text* scoreLabel;
    ui::Text* peerScoreLabel;
    void setupUI();
    void pauseButtonPressed(cocos2d::Ref *pSender, ui::Widget::TouchEventType eEventType);
    void updateScoreLabel(int score);

    void setupTouchHanding();
    void setJellyIfCollides(Vec2 currentTouchPos, Vec2 targetDirection, float dt);
    void setBlindFishMove(float dt);
    bool checkIfFishHitJelly(Sprite *jellyfish, Sprite *fish);
    cocos2d::Vector<Sprite*> getBlindFishGroup();
    std::vector<Vec2> getBlindFishStartPoses();
    std::vector<Vec2> blindFishStartPoses;
    std::vector<Vec2> getBlindFishTargetPoses();
    std::vector<Vec2> blindFishTargetPoses;
    std::vector<Vec2> getPeerBlindFishStartPoses();
    std::vector<Vec2> peerBlindFishStartPoses;
    std::vector<Vec2> getPeerBlindFishTargetPoses();
    std::vector<Vec2> peerBlindFishTargetPoses;

    void rotateJelly(Vec2 touchPos);
    void blindFishRotation(Sprite* blindFish, int blindFishRand);

    int score;
    int scoreDistance;
    int bestScore;
    int multiBestScore;
    int totalDeathTime;

    int myScore;
    int getMyScore();
    int peerScore;
    void setPeerScore(JSONPacker::GameState gameState);
};

#endif /* defined(__jellyrun__GameScene__) */
