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
    Background* lobbyBackground;
    SeaObjects* lobbySeaObjects;

    // UI
    void setupUI();
    void singlePlayerPressed(Ref* pSender, ui::Widget::TouchEventType eEventType);
    void multiplayerPressed(Ref* pSender, ui::Widget::TouchEventType eEventType);
    ui::Text* titleLabel;

    void update(float dt);
};

#endif /* defined(__jellyrun__Lobby__) */
