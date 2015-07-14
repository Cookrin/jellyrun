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
    bool init() override;
    void onEnter() override;
    
protected:
    void setupUI();
    void pauseButtonPressed(cocos2d::Ref *pSender, ui::Widget::TouchEventType eEventType);
};

#endif /* defined(__jellyrun__GameScene__) */
