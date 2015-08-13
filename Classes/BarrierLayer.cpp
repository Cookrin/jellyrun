//
//  BarrierLayer.cpp
//  jellyrun
//
//  Created by Tingting Gu on 2015/08/13.
//
//

#include "BarrierLayer.h"

BarrierLayer::BarrierLayer()
{
}
BarrierLayer::~BarrierLayer()
{
}
bool BarrierLayer::init()
{
    if(!Layer::init())
        return false;
    // Add the background
    LayerColor* backLayerColor = LayerColor::create(Color4B(25, 25, 25, 125));
    this->addChild(backLayerColor);

    // Set the game scene inactive
    auto callback = [](Touch * ,Event *)
    {
        return true;
    };
    auto listener = EventListenerTouchOneByOne::create();
    listener->onTouchBegan = callback;
    listener->setSwallowTouches(true);
    _eventDispatcher->addEventListenerWithSceneGraphPriority(listener,this);

    return true;
}