//
//  SeaObjects.h
//  jellyrun
//
//  Created by Tingting Gu on 2015/08/11.
//
//

#ifndef __jellyrun__SeaObjects__
#define __jellyrun__SeaObjects__

#include "cocos2d.h"
#include "InfiniteParallaxNode.h"

using namespace cocos2d;

class SeaObjects : public InfiniteParallaxNode
{
public:
    CREATE_FUNC(SeaObjects);
    Sprite *rockBG1;
    Sprite *rockBG2;
    Sprite *aquaticBG1;
    Sprite *aquaticBG2;
    Sprite *coralBG1;
    Sprite *coralBG2;

    void setSeaObjectsToMove();

protected:
    bool init() override;

};

#endif /* defined(__jellyrun__SeaObjects__) */
