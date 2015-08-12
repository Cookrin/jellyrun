//
//  Background.cpp
//  jellyrun
//
//  Created by Tingting Gu on 2015/08/04.
//
//

#include "Background.h"

bool Background::init()
{
    if (! Node::init())
    {
        return false;
    }

    Size visibleSize = Director::getInstance()->getVisibleSize();

    underwaterBG1 = Sprite::create("Underwater.png");
    underwaterBG1->setAnchorPoint(Vec2(0.0f,0.0f));

    underwaterBG2 = Sprite::create("Underwater.png");
    underwaterBG2->setAnchorPoint(Vec2(0.0f,0.0f));

    shipwreckBG1 = Sprite::create("Shipwreck.png");
    shipwreckBG1->setAnchorPoint(Vec2(0.0f,0.0f));

    shipwreckBG2 = Sprite::create("Shipwreck.png");
    shipwreckBG2->setAnchorPoint(Vec2(0.0f,0.0f));

    // addChild(Node * child, int z, const Vec2& parallaxRatio, const Vec2& positionOffset);
    this->addChild(
                   underwaterBG1,
                   // Set z-index
                   0,
                   // Set ration
                   Vec2(0.5f, 0.0f),
                   // Set position
                   Vec2((0.0f), 0.0f)
                   );
    this->addChild(
                     underwaterBG2,
                     // Set z-index
                     0,
                     // Set ration
                     Vec2(0.5f, 0.0f),
                     // Set position
                     Vec2(visibleSize.width, 0.0f)
                     );
    this->addChild(
                     shipwreckBG1,
                     1,
                     Vec2(1.0f, 0.0f),
                     Vec2(visibleSize.width * 0.3f, visibleSize.width * 0.03f)
                     );
    this->addChild(
                     shipwreckBG2,
                     1,
                     Vec2(1.0f, 0.0f),
                     Vec2(visibleSize.width * 1.3f, visibleSize.width * 0.03f)
                     );
    return true;
}

void Background::setBackgroundToMove()
{
    // Multi-background moves
    Vec2 scrollDecrement = Vec2(-1.0f, 0.0f);
    this->setPosition(this->getPosition() + scrollDecrement);
    this->updatePosition();
}
