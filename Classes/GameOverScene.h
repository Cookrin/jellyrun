//
//  GameOverScene.h
//  jellyrun
//
//  Created by Tingting Gu on 2015/07/24.
//
//

#ifndef __jellyrun__GameOverScene__
#define __jellyrun__GameOverScene__

#include "cocos2d.h"
#include "cocosGUI.h"

using namespace cocos2d;

class GameOverScene : public Node
{
public:
    CREATE_FUNC(GameOverScene);
    void updateScoreLabel(int score);
    void updateBestScoreLabel(int bestScore);
    void updateDeathTimeLabel(int deathTime);

private:
    // Lifecycle
    bool init() override;
    void onEnter() override;

    // UI
    ui::Text* scoreNumLabel;
    ui::Text* bestScoreNumLabel;
    ui::Text* totalDeathNumLabel;
    void setupUI();
    void playAgainPressed(Ref* pSender, ui::Widget::TouchEventType eEventType);
    void multiplayerPressed(Ref* pSender, ui::Widget::TouchEventType eEventType);
    void leaderboardsPressed(Ref* pSender, ui::Widget::TouchEventType eEventType);
    void contactMePressed(Ref* pSender, ui::Widget::TouchEventType eEventType);
    ui::Text* scoreLabel;
    ui::Text* highScoreLabel;
    ui::Text* totalDeathLabel;
    ui::Text* playAgainLabel;
    ui::Text* enterMultiplayLabel;
    ui::Text* leaderboardsLabel;
    ui::Text* contactMeLabel;
    Size visibleSize;

    int score;
    int bestScore;
    int deathTime;
};

#endif /* defined(__jellyrun__GameOverScene__) */
