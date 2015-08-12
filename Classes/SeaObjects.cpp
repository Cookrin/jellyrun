//
//  SeaObjects.cpp
//  jellyrun
//
//  Created by Tingting Gu on 2015/08/11.
//
//

#include "SeaObjects.h"

bool SeaObjects::init()
{
    if (! Node::init())
    {
        return false;
    }

    rockBG1 = Sprite::create("Rock.png");
    rockBG1->setAnchorPoint(Vec2(0.0f,0.0f));

    rockBG2 = Sprite::create("Rock.png");
    rockBG2->setAnchorPoint(Vec2(0.0f,0.0f));

    aquaticBG1 = Sprite::create("Aquatic.png");
    aquaticBG1->setAnchorPoint(Vec2(0.0f,0.0f));

    aquaticBG2 = Sprite::create("Aquatic.png");
    aquaticBG2->setAnchorPoint(Vec2(0.0f,0.0f));

    coralBG1 = Sprite::create("Coral.png");
    coralBG1->setAnchorPoint(Vec2(0.0f,0.0f));

    coralBG2 = Sprite::create("Coral.png");
    coralBG2->setAnchorPoint(Vec2(0.0f,0.0f));

    Size rockSize = rockBG1 ->getContentSize();

    // addChild(Node * child, int z, const Vec2& parallaxRatio, const Vec2& positionOffset);
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
                   Vec2(4.0f, 0.0f),
                   Vec2(0.0f, 0.0f));
    this->addChild(
                   aquaticBG2,
                   3,
                   Vec2(4.0f, 0.0f),
                   Vec2(rockSize.width, 0.0f)
                   );
    this->addChild(
                   coralBG1,
                   3,
                   Vec2(4.0f, 0.0f),
                   Vec2(0.0f, 0.0f));
    this->addChild(
                   coralBG2,
                   3,
                   Vec2(4.0f, 0.0f),
                   Vec2(rockSize.width, 0.0f)
                   );
    return true;
}

void SeaObjects::setSeaObjectsToMove()
{
    // Multi-background moves
    Vec2 scrollDecrement = Vec2(-1.0f, 0.0f);
    this->setPosition(this->getPosition() + scrollDecrement);
    this->updatePosition();
}