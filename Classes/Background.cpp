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
    underwaterBG1->setOpacity(255 * 1.0);

    underwaterBG2 = Sprite::create("Underwater.png");
    underwaterBG2->setAnchorPoint(Vec2(0.0f,0.0f));
    underwaterBG2->setOpacity(255 * 1.0);

    shipwreckBG1 = Sprite::create("Shipwreck.png");
    shipwreckBG1->setAnchorPoint(Vec2(0.0f,0.0f));
    shipwreckBG1->setOpacity(255 * 1.0);

    shipwreckBG2 = Sprite::create("Shipwreck.png");
    shipwreckBG2->setAnchorPoint(Vec2(0.0f,0.0f));
    shipwreckBG2->setOpacity(255 * 1.0);

    rockBG1 = Sprite::create("Rock.png");
    rockBG1->setAnchorPoint(Vec2(0.0f,0.0f));
    rockBG1->setOpacity(255 * 1.0);

    rockBG2 = Sprite::create("Rock.png");
    rockBG2->setAnchorPoint(Vec2(0.0f,0.0f));
    rockBG2->setOpacity(255 * 1.0);

    aquaticBG1 = Sprite::create("Aquatic.png");
    aquaticBG1->setAnchorPoint(Vec2(0.0f,0.0f));

    aquaticBG2 = Sprite::create("Aquatic.png");
    aquaticBG2->setAnchorPoint(Vec2(0.0f,0.0f));

    coralBG1 = Sprite::create("Coral.png");
    coralBG1->setAnchorPoint(Vec2(0.0f,0.0f));

    coralBG2 = Sprite::create("Coral.png");
    coralBG2->setAnchorPoint(Vec2(0.0f,0.0f));

    Size shipwreckBGSize = shipwreckBG1->getContentSize();
    Size lightBGSize = underwaterBG1->getContentSize();
    Size rockSize = rockBG1 ->getContentSize();

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
    this->addChild(
                     rockBG1,
                     // Set z-index
                     2,
                     // Set ration
                     Vec2(2.0f, 0.0f),
                     // Set position
                     Vec2(0.0f, 0.0f)
                     );
    this->addChild(
                     rockBG2,
                     // Set z-index
                     2,
                     // Set ration
                     Vec2(2.0f, 0.0f),
                     // Set position
                     Vec2(rockSize.width, 0.0f)
                     );
    this->addChild(
                     aquaticBG1,
                     3,
                     Vec2(2.5f, 0.0f),
                     Vec2(0.0f, 0.0f));
    this->addChild(
                     aquaticBG2,
                     3,
                     Vec2(2.5f, 0.0f),
                     Vec2(visibleSize.width, 0.0f)
                     );
    this->addChild(
                     coralBG1,
                     3,
                     Vec2(2.5f, 0.0f),
                     Vec2(0.0f, 0.0f));
    this->addChild(
                     coralBG2,
                     3,
                     Vec2(2.5f, 0.0f),
                     Vec2(visibleSize.width, 0.0f)
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
