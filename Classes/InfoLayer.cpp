//
//  InfoLayer.cpp
//  jellyrun
//
//  Created by Tingting Gu on 2015/08/14.
//
//

#include "InfoLayer.h"
#include "UIConstants.h"
#include "BarrierLayer.h"
#include "cocosGUI.h"
#include "SceneManager.h"

InfoLayer::InfoLayer()
{
}

InfoLayer::~InfoLayer()
{
}

bool InfoLayer::init()
{
    if(! Node::init())
    {
        return false;
    }
    visibleSize = Director::getInstance()->getVisibleSize();
    visibleSizeMultiplier = visibleSize.width / 1134.0f;

    // add the barrier layer
    addChild(BarrierLayer::create(),0);

    LayerColor* backLayerColor = LayerColor::create(Color4B(25, 25, 25, 200));
    this->addChild(backLayerColor);

    this->setupUI();

    return true;
}

void InfoLayer::setupUI()
{
    float titleFontSize = INFO_FONT_SIZE * visibleSizeMultiplier;
    //create developer label
    this->developerLabel = ui::Text::create("- ENGINEER & UI DESIGNER -", INFO_HEAD_FONT_NAME, titleFontSize);
    this->developerLabel->setAnchorPoint(Vec2(0.5f, 0.5f));
    this->developerLabel->setPosition(Vec2(visibleSize.width*0.5f, visibleSize.height * 0.9f));
    this->developerLabel->setColor(WHITE_LABEL_COLOR);
    this->addChild(developerLabel);

    //create developer label
    this->developerListLabel = ui::Text::create("Tingting Gu", INFO_BODY_FONT_NAME, titleFontSize);
    this->developerListLabel->setAnchorPoint(Vec2(0.5f, 0.5f));
    this->developerListLabel->setPosition(Vec2(visibleSize.width*0.5f, visibleSize.height * 0.8f));
    this->developerListLabel->setColor(WHITE_LABEL_COLOR);
    this->addChild(developerListLabel);

    //create designer label
    this->designerLabel = ui::Text::create("- CHARACTER DESIGNER -", INFO_HEAD_FONT_NAME, titleFontSize);
    this->designerLabel->setAnchorPoint(Vec2(0.5f, 0.5f));
    this->designerLabel->setPosition(Vec2(visibleSize.width*0.5f, visibleSize.height * 0.7f));
    this->designerLabel->setColor(WHITE_LABEL_COLOR);
    this->addChild(designerLabel);

    //create designer label
    this->designerListOneLabel = ui::Text::create("http://graphicriver.net/  Regular Liscence", INFO_BODY_FONT_NAME, titleFontSize);
    this->designerListOneLabel->setAnchorPoint(Vec2(0.5f, 0.5f));
    this->designerListOneLabel->setPosition(Vec2(visibleSize.width*0.5f, visibleSize.height * 0.6f));
    this->designerListOneLabel->setColor(WHITE_LABEL_COLOR);
    this->addChild(designerListOneLabel);

    //create icon designer label
    this->fontDesignerLabel = ui::Text::create("- ICON DESIGNER -", INFO_HEAD_FONT_NAME, titleFontSize);
    this->fontDesignerLabel->setAnchorPoint(Vec2(0.5f, 0.5f));
    this->fontDesignerLabel->setPosition(Vec2(visibleSize.width*0.5f, visibleSize.height * 0.5f));
    this->fontDesignerLabel->setColor(WHITE_LABEL_COLOR);
    this->addChild(fontDesignerLabel);

    //create icon designer list label
    this->designerListOneLabel = ui::Text::create("http://www.flaticon.com/authors/egor-rumyantsev", INFO_BODY_FONT_NAME, titleFontSize);
    this->designerListOneLabel->setAnchorPoint(Vec2(0.5f, 0.5f));
    this->designerListOneLabel->setPosition(Vec2(visibleSize.width*0.5f, visibleSize.height * 0.4f));
    this->designerListOneLabel->setColor(WHITE_LABEL_COLOR);
    this->addChild(designerListOneLabel);

    //create special thanks label
    this->specialThanksLabel = ui::Text::create("- SPECIAL THANKS -", INFO_HEAD_FONT_NAME, titleFontSize);
    this->specialThanksLabel->setAnchorPoint(Vec2(0.5f, 0.5f));
    this->specialThanksLabel->setPosition(Vec2(visibleSize.width*0.5f, visibleSize.height * 0.3f));
    this->specialThanksLabel->setColor(WHITE_LABEL_COLOR);
    this->addChild(specialThanksLabel);

    //create special thanks list one label
    this->specialThanksListOneLabel = ui::Text::create("Make School", INFO_BODY_FONT_NAME, titleFontSize);
    this->specialThanksListOneLabel->setAnchorPoint(Vec2(0.5f, 0.5f));
    this->specialThanksListOneLabel->setPosition(Vec2(visibleSize.width*0.5f, visibleSize.height * 0.2f));
    this->specialThanksListOneLabel->setColor(WHITE_LABEL_COLOR);
    this->addChild(specialThanksListOneLabel);

    //create special thanks list two label
    this->specialThanksListTwoLabel = ui::Text::create("GREE fellows", INFO_BODY_FONT_NAME, titleFontSize);
    this->specialThanksListTwoLabel->setAnchorPoint(Vec2(0.5f, 0.5f));
    this->specialThanksListTwoLabel->setPosition(Vec2(visibleSize.width*0.5f, visibleSize.height * 0.1f));
    this->specialThanksListTwoLabel->setColor(WHITE_LABEL_COLOR);
    this->addChild(specialThanksListTwoLabel);

    // go back button
    ui::Button* goBackButton = ui::Button::create();
    goBackButton->setAnchorPoint(Vec2(0.5f, 0.5f));
    goBackButton->setPosition(Vec2(visibleSize.width* 0.9f, visibleSize.height * 0.1f));
    goBackButton->loadTextures("goBackButton.png", "goBackButtonPressed.png");
    goBackButton->addTouchEventListener(CC_CALLBACK_2(InfoLayer::goBackButtonPressed, this));
    this->addChild(goBackButton);
}

void InfoLayer::goBackButtonPressed(Ref *pSender, ui::Widget::TouchEventType eEventType)
{
    if (eEventType == ui::Widget::TouchEventType::ENDED)
    {
        Director::getInstance()->resume();
        CC_SAFE_RETAIN(this);
        this->removeFromParent();
    }
}