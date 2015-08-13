//
//  GamePause.h
//  jellyrun
//
//  Created by Tingting Gu on 2015/08/13.
//
//

#ifndef __jellyrun__GamePause__
#define __jellyrun__GamePause__

#include <stdio.h>
#include "cocos2d.h"
#include "cocosGUI.h"

USING_NS_CC;

class GamePause : public Layer
{
public:
    GamePause();
    ~GamePause();
    bool init();
    CREATE_FUNC(GamePause);

protected:
    Size visibleSize;
    float visibleSizeMultiplier;
    void setupUI();
    void continueButtonPressed(Ref* pSender, ui::Widget::TouchEventType eEventType);
    void endGameButtonPressed(Ref* pSender, ui::Widget::TouchEventType eEventType);
    ui::Text* continueLabel;
    ui::Text* endGameLabel;

};
#endif /* defined(__jellyrun__GamePause__) */
