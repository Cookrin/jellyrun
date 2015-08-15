//
//  InfoLayer.h
//  jellyrun
//
//  Created by Tingting Gu on 2015/08/14.
//
//

#ifndef __jellyrun__InfoLayer__
#define __jellyrun__InfoLayer__

#include <stdio.h>
#include "cocos2d.h"
#include "cocosGUI.h"

USING_NS_CC;

class InfoLayer : public Layer
{
public:
    InfoLayer();
    ~InfoLayer();
    bool init();
    CREATE_FUNC(InfoLayer);
    
protected:
    Size visibleSize;
    float visibleSizeMultiplier;
    // UI
    void setupUI();
    // - DEVELOPER -
    // Tingting Gu
    
    // - DESIGNER -
    // Glenofobiya, jazzia8
    // Egor Rumyantsev, ashishlko11
    
    // - SPECIAL THANKS -
    // Daniel Haaser and other MakeSchool friends
    // Atsuko Kaizuka, Ryu Tamaki
    // Ken Watanabe and other GREE friends
    //And You
    
    ui::Text* developerLabel;
    ui::Text* developerListLabel;

    ui::Text* fontDesignerLabel;
    ui::Text* fontDesignerListLabel;

    ui::Text* designerLabel;
    ui::Text* designerListOneLabel;

    ui::Text* specialThanksLabel;
    ui::Text* specialThanksListOneLabel;
    ui::Text* specialThanksListTwoLabel;
    ui::Text* specialThanksListThreeLabel;

    void goBackButtonPressed(Ref* pSender, ui::Widget::TouchEventType eEventType);
};

#endif /* defined(__jellyrun__InfoLayer__) */
