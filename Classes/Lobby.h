//
//  Lobby.h
//  jellyrun
//
//  Created by Tingting Gu on 2015/07/13.
//
//

#ifndef __jellyrun__Lobby__
#define __jellyrun__Lobby__

#include "cocos2d.h"
#include "cocosGUI.h"
#include "Background.h"
#include "SeaObjects.h"

using namespace cocos2d;

// create the class Lobby
class Lobby : public Node
{
public:
    CREATE_FUNC(Lobby);

private:
    // Lifecycle
    bool init() override;
    void onEnter() override;
    void onExit() override;
    Background* lobbyBackground;
    SeaObjects* lobbySeaObjects;

    // UI
    Size visibleSize;
    float visibleSizeMultiplier;
    void setupUI();
    void singlePlayerPressed(Ref* pSender, ui::Widget::TouchEventType eEventType);
    void multiplayerPressed(Ref* pSender, ui::Widget::TouchEventType eEventType);
    void infoButtonPressed(Ref* pSender, ui::Widget::TouchEventType eEventType);

    ui::Text* titleLabel;
    ui::Text* singlePlayerLabel;
    ui::Text* multiplayerLabel;

    void update(float dt);
};

#endif /* defined(__jellyrun__Lobby__) */
