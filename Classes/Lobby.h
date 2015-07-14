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


// create the class Lobby
class Lobby : public cocos2d::Node
{
public:
    //
    CREATE_FUNC(Lobby);
    
private:
    bool init() override;
    void onEnter() override;
    void setupUI();

    void singlePlayerPressed(cocos2d::Ref* pSender, cocos2d::ui::Widget::TouchEventType eEventType);
    void multiplayerPressed(cocos2d::Ref* pSender, cocos2d::ui::Widget::TouchEventType eEventType);
};

#endif /* defined(__jellyrun__Lobby__) */
