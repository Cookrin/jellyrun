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

using namespace cocos2d;

class GameScene : public cocos2d::Node {
public:
    CREATE_FUNC(GameScene);

private:

protected:
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
    cocos2d::Sprite* jellyfish;
    cocos2d::Sprite* blindFish;
    cocos2d::Sprite* fish;
    cocos2d::Vector<Sprite*> blindFishGroup;
    bool fishHitJelly;

    bool init() override;
    void onEnter() override;
    void update(float dt);
    void setGameActive(bool active);

    void setupUI();
    void pauseButtonPressed(cocos2d::Ref *pSender, ui::Widget::TouchEventType eEventType);
    

    void setupTouchHanding();
    void setJellyIfCollides(Vec2 currentTouchPos, Vec2 targetDirection, float dt);
    void setBlindFishMove(float dt);
    bool checkIfFishHitJelly(Vec2 jellyPos, Vec2 fishPos);
    cocos2d::Vector<Sprite*> getBlindFishGroup();
    Vec2 getBlindFishStartPos(int blindFishRand, int index);
    Vec2 getBlindFishTargetPos(int blindFishRand, int index);
};

#endif /* defined(__jellyrun__GameScene__) */
